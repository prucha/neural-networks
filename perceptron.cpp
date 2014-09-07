// **********************************************************************
// *																	*
// *			CLASS DEFINITION: PERCEPTRON NETWORK classes			*
// *					Version: 24 January 2002						*
// *						by Milan Prucha								*
// *																	*
// **********************************************************************



#include "perceptron.h"

//============================================================================
// neuron object
//============================================================================

//default constructor - no parameters supplied
Cneuron::Cneuron() : dendriteTotal(2), activation(0), y(0), d(0), dy(0)
{
	//'CreateDendrites' needs to be called before this is used
	dendrites = NULL;
}

//=============================================================================
// ALTERNATIVE CONSTRUCTOR
//=============================================================================

Cneuron::Cneuron(unsigned int newDendriteTotal) : dendriteTotal(newDendriteTotal),
activation(0), y(0), d(0), dy(0)
{
	//the minimum number of dendrites (including the bias) to make the adaline viable
	//is 3. Adjust 'dendriteTotal' if needed.
	if(dendriteTotal<1)
		dendriteTotal=1;

	//--------------------------------------------------------------------------
	// allocate memory for the neuron's dendrites and attach pointer
	dendrites = new dendrite[dendriteTotal];

	//Generate random values for each dendrite's weights
	unsigned int random = 0;
	unsigned int i=0;

	for(i=0; i<dendriteTotal; i++)
	{
		random = rand()%61;
		dendrites[i].w = (double)(random+20)/100;
	}

	//assign 1 to all dendrite 'x' elements
	for(i=0; i<dendriteTotal; i++)
	{
		dendrites[i].x = 1;
	}
}

//=============================================================================
//Copy Constructor



//==============================================================================
//  DESTRUCTOR
//==============================================================================

Cneuron::~Cneuron()
{
	if(dendrites!=NULL)
	{
		//deletes dynamically allocated array to which 'dendrites' is a pointer
		delete [] dendrites;
	}
}

//===============================================================================
//  MEMBER FUNCTIONS
//===============================================================================

void Cneuron::CreateDendrites(unsigned int newDendriteTotal)
{
	dendriteTotal = newDendriteTotal;

	if(dendriteTotal < 1)
		dendriteTotal = 1;

	//---------------------------------------------------------------------------
	// allocate memory for the neuron's dendrites and attach pointer
	dendrites = new dendrite[dendriteTotal];

	//Generate random values for each dendrite's weights
	unsigned int random = 0;
	unsigned int i=0;

	for(i=0; i<dendriteTotal; i++)
	{
		random = rand()%61;
		dendrites[i].w = (double)(random+20)/100;
	}

	//assign 1 to all dendrite 'x' elements
	for(i=0; i<dendriteTotal; i++)
	{
		dendrites[i].x = 1;
	}
}

//===============================================================================

//Set the input of a dendrite
//Any attempt to set the bias input(x) will be rejected (dendrites[0])
//as this is ALWAYS +1
bool Cneuron::SetDendrite_x(unsigned int dendriteElem, double new_x)
{
	if(dendrites==NULL)
	{
		return 0;
	}
	//----------------------------------------------------

	if(dendriteElem < dendriteTotal && dendriteElem != 0)
	{
		dendrites[dendriteElem].x = new_x;
		return 1;
	}

	return 0;
}

//==================================================================================

//Set the weight value applied to a dendrite
bool Cneuron::SetDendrite_w(unsigned int dendriteElem, double new_w)
{
	if(dendrites==NULL)
	{
		return 0;
	}
	//----------------------------------------------------

	if(dendriteElem < dendriteTotal)
	{
		dendrites[dendriteElem].w = new_w;
		return 1;
	}

	return 0;
}

//===================================================================================

//returns the input currently applied to the dendrite
double Cneuron::GetDendrite_x(unsigned int dendriteElem)
{
	if(dendrites==NULL)
	{
		return 0;
	}
	//----------------------------------------------------

	double result=0;

	if(dendriteElem < dendriteTotal)
	{ //'dendriteElem' is within the legal range
		result = dendrites[dendriteElem].x;
	}

	return result;

}

//====================================================================================

//returns the current weight applied to the dendrite
double Cneuron::GetDendrite_w(unsigned int dendriteElem)
{
	if(dendrites==NULL)
	{
		return 0;
	}

	//--------------------------------------------------------------------------------

	double result=0;

	if(dendriteElem <  dendriteTotal)
	{ //'dendriteElem' is within the legal range
		result = dendrites[dendriteElem].w;
	}

	return result;

}

//====================================================================================
//calculates and sets the net activation of the neuron
//then passes this through a 'Sigmoid Function'
// to get a non-linear output

void Cneuron::CalcOutput()
{
	if(dendrites==NULL)
	{
		return;
	}

	//-------------------------------------------------------------------------------

	activation = 0;

	//calculate the current weighted output of each dendrite
	// (x*w) and find the net activation by adding these  together
	for(unsigned int d=0; d<dendriteTotal; d++)
	{
		activation += (dendrites[d].x * dendrites[d].w);
	}

	//calculate the output by passing the net activation through a 
	//sigmoid function
	y = 1/(1 + exp(- activation));

}

//====================================================================================

double Cneuron::GetActivation()
{
	return activation;
}

//=====================================================================================

double Cneuron::GetOutput()
{
	return y;
}

//======================================================================================

double Cneuron::GetDesiredOutput()
{
	return dy;
}

//======================================================================================

void Cneuron::SetOutput(double new_y)
{
	if(new_y > 1)
		new_y = 1;

	y = new_y;	
}

//======================================================================================

//retrieve the Delta (or Error) in the neuron's output
double Cneuron::GetDelta()
{
	return d;
}

//======================================================================================

void Cneuron::SetDelta(double new_d)
{
	d = new_d;
}

//======================================================================================

void Cneuron::SetDesiredOutput(double new_dy)
{
	if(new_dy > 1)
		new_dy = 1;

	dy = new_dy;
}

//======================================================================================

void Cneuron::info()
{

	for(unsigned int i=0; i<dendriteTotal; i++)
	{	
		printf("\n\t(x) Input of Dendrite  (%d): %g", i, dendrites[i].x);
		printf("\n\t(w) Weight of Dendrite (%d): %g\n", i, dendrites[i].w);
	}

	printf("\n\tNet Activation : %g", activation);
	printf("\n\t(d) Delta-error: %g", d);
	printf("\n\t Desired Output: %g", dy);
	printf("\n\t(y) Axon Output: %g", y);

	printf("");	
}

//=======================================================================================
// layer object
//=======================================================================================

//DEFAULT CONSTRUCTOR - no parameters supplied
Clayer::Clayer() : type(1), neuronTotal(0), dendriteTotal(2) 
{
	// 'CreateNeurons' needs to be called before this is used
	neurons = NULL;
}

//=======================================================================================
//CUSTOM CONSTRUCTOR

Clayer::Clayer(unsigned int newNeuronTotal, unsigned int newDendriteTotal, unsigned int newType) :
neuronTotal(newNeuronTotal), dendriteTotal(newDendriteTotal), type(newType)
{
	
	//check that the passed values aren't too small
	if(neuronTotal < 1)
		neuronTotal=1;

	if(type==0)
	{
		dendriteTotal=1; 
	}
	else
	{
		if(dendriteTotal < 2)
			dendriteTotal=2; //includes bias input	
	}

	neurons = new Cneuron[neuronTotal]; 

	for(unsigned int i=0; i<neuronTotal; i++)
	{
		neurons[i].CreateDendrites(newDendriteTotal);
	}
	
}

//=======================================================================================
//COPY CONSTRUCTOR




//=======================================================================================
//DESTRUCTOR

Clayer::~Clayer()
{
	if(neurons!=NULL)
	{
		//deletes dynamically allocated array to which 'neurons' is a pointer
		delete [] neurons;
	}
}

//=======================================================================================
//MEMBER FUNCTIONS

void Clayer::CreateNeurons(unsigned int newNeuronTotal, unsigned int newDendriteTotal,
unsigned int newType)
{
	neuronTotal = newNeuronTotal;
	dendriteTotal = newDendriteTotal;
	type = newType;

	//check that the passed values aren't too small
	if(neuronTotal < 1)
		neuronTotal=1;


	if(type==0)
	{
		dendriteTotal=1; 
	}
	else
	{
		if(dendriteTotal < 2)
			dendriteTotal=2; //includes bias input	
	}


	neurons = new Cneuron[neuronTotal]; 

	for(unsigned int i=0; i<neuronTotal; i++)
	{
		neurons[i].CreateDendrites(newDendriteTotal);
	}
}


//=======================================================================================

bool Clayer::SetDendrite_x(unsigned int neuronElem, unsigned int dendriteElem, double new_x)
{
	if(neurons==NULL)
	{
		return 0;
	}	
	//-------------------------------------------------
	bool result=0;
	
	
	if(neuronElem < neuronTotal)
	{
		//if this is a neuron in the 'input layer' then feed the input
		//straight into the output(y) without processing.
		if(type == 0)
		{
			neurons[neuronElem].SetOutput(new_x);
		}
		else
		{
			result = neurons[neuronElem].SetDendrite_x(dendriteElem, new_x);

			return (result);
		}
	}

	return 0;
}// end of SetDendrite_x


//========================================================================================

bool Clayer::SetDendrite_w(unsigned int neuronElem, unsigned int dendriteElem, double new_w)
{
	
	if(neurons==NULL)
	{
		return 0;
	}	
	//-------------------------------------------------
	bool result=0;

	if(neuronElem < neuronTotal)
	{
		result = neurons[neuronElem].SetDendrite_w(dendriteElem, new_w);

		return (result);
	}

	return 0;
}//end of SetDendrite_w

//=========================================================================================

double Clayer::GetDendrite_x(unsigned int neuronElem, unsigned int dendriteElem)
{
	if(neurons==NULL)
	{
		return 0;
	}	
	//-------------------------------------------------	

	double result=0;

	if(neuronElem < neuronTotal)
	{ 
		result = neurons[neuronElem].GetDendrite_x(dendriteElem);
	}

	return result;
	
}//end of GetDendrite_x

//===========================================================================================

double Clayer::GetDendrite_w(unsigned int neuronElem, unsigned int dendriteElem)
{
	if(neurons==NULL)
	{
		return 0;
	}	
	//-------------------------------------------------	

	double result=0;

	if(neuronElem < neuronTotal)
	{ 
		result = neurons[neuronElem].GetDendrite_w(dendriteElem);
	}

	return result;
	
}//end of GetDendrite_x

//===========================================================================================

void Clayer::CalcOutput()
{

	if(neurons==NULL)
	{
		return;
	}	
	//--------------------------------------------------------------------------
	//Go through each neuron in the layer and calculate the output

	//if this layer is the 'input layer' then ignore (no processing takes place)
	if(type != 0)
	{
		for(unsigned int i=0; i<neuronTotal; i++)
		{
			neurons[i].CalcOutput();
		}
	}

}//end of CalcOutput

//===========================================================================================

//Delta (or Error) in the neuron's output
bool Clayer::SetDelta(unsigned int neuronElem, double new_d)
{
	//check that neurons have been created
	if(neurons==NULL)
		return 0;

	//check that neuron element is valid
	if(neuronElem >= neuronTotal)
		return 0;
	//--------------------------------------------------

	neurons[neuronElem].SetDelta(new_d);

	//return success
	return 1;
}

//===========================================================================================

//Set the desired output of a neuron in the outputlayer(2) only
bool Clayer::SetDesiredOutput(unsigned int neuronElem, double new_dy)
{
	
	//check that this is the output layer
	//and that neurons have been created
	if(type!=2 || neurons==NULL)
		return 0;

	//check that neuron element is valid
	if(neuronElem >= neuronTotal)
		return 0;

	neurons[neuronElem].SetDesiredOutput(new_dy);

	
	//return success
	return 1;
}

//===========================================================================================

double Clayer::GetActivation(unsigned int neuronElem)
{
	if(neurons==NULL)
	{
		return 0;
	}	
	//-------------------------------------------------
	
	double result;

	if(neuronElem < neuronTotal)
	{
		result = neurons[neuronElem].GetActivation();
	}

	return result;
}

//===========================================================================================

double Clayer::GetDesiredOutput(unsigned int neuronElem)
{
	if(neurons==NULL)
	{
		return 0;
	}	
	//-------------------------------------------------	

	double result;

	if(neuronElem < neuronTotal)
	{
		result = neurons[neuronElem].GetDesiredOutput();
	}

	return result;
}

//===========================================================================================

//retrieve the Delta (or Error) in the neuron's output
double Clayer::GetDelta(unsigned int neuronElem)
{
	if(neurons==NULL)
	{
		return 0;
	}	
	//-------------------------------------------------

	double result;

	if(neuronElem < neuronTotal)
	{
		result = neurons[neuronElem].GetDelta();
	}

	return result;
}

//===========================================================================================
double Clayer::GetOutput(unsigned int neuronElem)
{
	if(neurons==NULL)
	{
		return 0;
	}	
	//-------------------------------------------------

	double result;

	result = neurons[neuronElem].GetOutput();

	return result;
}

//===========================================================================================

unsigned int Clayer::GetNeuronTotal()
{
	return neuronTotal;
}

//===========================================================================================

void Clayer::info()
{	
	switch(type)
	{
		case 0:
			printf("\n(INPUT LAYER) ");
			break;
		case 1:
			printf("\n(HIDDEN LAYER) ");
			break;
		default:
			printf("\n(OUTPUT LAYER) ");
			break;
	}

	for(unsigned int i=0; i < neuronTotal; i++)
	{
		printf("\n   Neuron: %d", i);
		neurons[i].info();	
		printf("\n");
	}
	
}

//============================================================================================

void Clayer::setType(unsigned int newType)
{
	type = newType;
}

//=============================================================================================



//===========================================================================================
// NETWORK OBJECT
//===========================================================================================

//default constructor - no parameters supplied
Cnetwork::Cnetwork() : layerTotal(2), pass(0), epoch(0), eta(0.5), epsilon(0.001), rmsDelta(0)
{
	//'createLayers' (DMAs layer objects) followed by
	//'defineLayer' needs to be called for each layer in
	//the network before this can be used
	layers = NULL;
}

//===========================================================================================
//custom constructor

Cnetwork::Cnetwork(unsigned int newLayerTotal, double newEta, double newEpsilon) :
layerTotal(newLayerTotal), pass(0), epoch(0), eta(newEta), epsilon(newEpsilon), rmsDelta(0)
{
	//each network must have at least an input layer and output layer
	if(layerTotal < 2)
		layerTotal = 2;

	//allocate memory for the 'layer' objects
	layers = new Clayer[layerTotal];
}

//===========================================================================================
//copy constructor






//===========================================================================================
//destructor

Cnetwork::~Cnetwork()
{
	if(layers!=NULL)
	{
		//deletes dynamically allocated array to which 'layers' is a pointer
		delete [] layers;
	}
}

//===========================================================================================
//member functions

void Cnetwork::createLayers(unsigned int newlayerTotal)
{
	//allocate memory for the 'layer' objects
	layers = new Clayer[layerTotal];
}

//============================================================================================

bool Cnetwork::defineLayer(unsigned int layerElem, unsigned int newNeuronTotal)
{
	unsigned int dendriteNum=1;
	unsigned int neuronNum;
	unsigned int newType;

	//assign the layer 'type'	
	if(layerElem == 0)
	{
		//define as 'input layer'
		newType=0;
	}
	else
	if(layerElem==(layerTotal-1))
	{
		//define as 'output layer'
		newType=2;
	}
	else
	{
		//define as 'hidden layer'
		newType=1;
	}

	
	//Determine the number of dendrites
	//(The number of neurons in the previous layer +1)
	if(layerElem>0)
	{
		neuronNum = layers[(layerElem-1)].GetNeuronTotal();

		//if the number of neurons in the previous layer is 0
		//then the layer has not been defined yet (each layer must contain
		//at least 1 neuron). In this case the number of dendrites required
		//by neurons in the current layer cannot be determined. return FAILED. 
		if(neuronNum == 0)
			return 0;
		
		dendriteNum = (neuronNum + 1);
	}

	//create the neurons for this layer
	//(CreateNeurons
	layers[layerElem].CreateNeurons(newNeuronTotal, dendriteNum, newType);

	
	//return success
	return 1;
}

//=============================================================================================


//=============================================================================================

bool Cnetwork::SetDendrite_x(unsigned int layerElem, unsigned int neuronElem,
unsigned int dendriteElem, double new_x)
{
	//layer has not been created or defined
	if(layers==NULL)
		return 0;

	if(layers[layerElem].GetNeuronTotal() ==0)
		return 0;
		
	//-------------------------------------------------	

	bool result=0;

	if(layerElem < layerTotal)
	{ 
		result = layers[layerElem].SetDendrite_x(neuronElem, dendriteElem, new_x);
		return result;
	}

	return 0;
}

//=============================================================================================

bool Cnetwork::SetDendrite_w(unsigned int layerElem, unsigned int neuronElem,
unsigned int dendriteElem, double new_w)
{
	//layer has not been created or defined
	if(layers==NULL)
		return 0;

	if(layers[layerElem].GetNeuronTotal()==0)
		return 0;
		
	//-------------------------------------------------	

	bool result=0;

	if(layerElem < layerTotal)
	{ 
		result = layers[layerElem].SetDendrite_w(neuronElem, dendriteElem, new_w);
		return result;
	}

	return 0;
	
}

//=============================================================================================

double Cnetwork::GetDendrite_x(unsigned int layerElem, unsigned int neuronElem,
unsigned int dendriteElem)
{
	//layer has not been created or defined
	if(layers==NULL)
		return 0;

	if(layers[layerElem].GetNeuronTotal()==0)
		return 0;
		
	//-------------------------------------------------	

	double result=0;

	if(layerElem < layerTotal)
	{ 
		result = layers[layerElem].GetDendrite_x(neuronElem, dendriteElem);
	}

	return result;
}

//=============================================================================================

double Cnetwork::GetDendrite_w(unsigned int layerElem, unsigned int neuronElem,
unsigned int dendriteElem)
{
	//layer has not been created or defined
	if(layers==NULL)
		return 0;

	if(layers[layerElem].GetNeuronTotal()==0)
		return 0;
		
	//-------------------------------------------------	

	double result=0;

	if(layerElem < layerTotal)
	{ 
		result = layers[layerElem].GetDendrite_w(neuronElem, dendriteElem);
	}

	return result;
}

//=============================================================================================

//Delta (or Error) in the neuron's output
bool Cnetwork::SetDelta(unsigned int layerElem, unsigned int neuronElem,
double new_d)
{
	//layer has not been created or defined
	if(layers==NULL)
		return 0;

	if(layers[layerElem].GetNeuronTotal()==0)
		return 0;

	
	//-------------------------------------------------	
	
    bool result=0;

	if(layerElem < layerTotal)
	{
		result = layers[layerElem].SetDelta(neuronElem, new_d);
	}

	return result;
}

//=============================================================================================
bool Cnetwork::SetDesiredOutput(unsigned int neuronElem, double new_dy)
{
	//layer has not been created or defined
	if(layers==NULL)
		return 0;

	if(layers[(layerTotal-1)].GetNeuronTotal()==0)
		return 0;	
	//----------------------------------------------------------------
	
	layers[(layerTotal-1)].SetDesiredOutput(neuronElem, new_dy);
	
	return 1;
}

//=============================================================================================

double Cnetwork::GetDesiredOutput(unsigned int layerElem, unsigned int neuronElem)
{

	//layer has not been created or defined
	if(layers==NULL)
		return 0;

	if(layers[layerElem].GetNeuronTotal()==0)
		return 0;

	//-----------------------------------------------------------

	double result=0;

	if(layerElem < layerTotal)
	{ 
		result = layers[layerElem].GetDesiredOutput(neuronElem);
	}

	return result;

}

//=============================================================================================

unsigned int Cnetwork::GetPass()
{
	return pass;
}

//=============================================================================================

double Cnetwork::GetRMS()
{
	return rmsDelta;
}

//=============================================================================================
void Cnetwork::info()
{

	printf("\nEPOCH: %d", epoch);
	printf("\nTRAINING PASS: %d\n", pass);
	printf("\nETA (learning co-efficient)  : %g", eta);
	printf("\nEPSILON (net-error threshold): %g", epsilon);
	printf("\nROOT-MEAN-SQUARE error       : %g\n", rmsDelta);


	if(layers==NULL)
	{
		printf("\n\nLayers not initialised!");
	}
	else
	{
		for(unsigned int i=0; i < layerTotal; i++)
		{
			printf("\nLayer (%d)", i);
			layers[i].info();	
		}
	}

}

//=============================================================================================
// TRAINING ALGORITHM OUTLINE

//FORWARD PASS:
//  1. Present the pattern at the input layer.
//  2. Let the hidden units evaluate their output using the pattern.
//  3. Let the output units evaluate their output using the result in step 2.
//     from the hidden units.

//BACKWARD PASS:
//  4. Apply the target pattern to the output layer.
//  5. Calculate the 'deltas' on the output nodes.
//  6. Train each output node using gradient descent.
//  7. For each hidden node, calculate its delta.
//  8. For each hidden node, use the 'delta'found in step 7 to train according
//	   to gradient descent.


void Cnetwork::train()
{
	double axonOutput=0; //the axon output of a previous layer neuron to be transferred
						//to the dendrites of the neurons in the current layer.
						//also used in the back-propagation/weight adjust algorithm.

	double weight; //stores 'dendrite.w' to be used in equation
	double delta;  //stores the retrieved delta error 

	double newDelta; //the new delta value to be assigned to the neuron
	double desiredOutput;
	double temp; //used to temporarily store part of the 
	//back-propagation equation

	unsigned int neuronTotal=0; 
	unsigned int dendriteTotal=0; 
	unsigned int nextLayerNeurons=0;

	//used in forloops
	unsigned int la=1;
	unsigned int ne=0;
	unsigned int de=1; 


	//-------------------------------------------------------------
	//FORWARD PASS:
	//Get the inputs from the input layer and forward-propagate
	//through the net. 
	//-------------------------------------------------------------
	for(la=1; la<layerTotal; la++)
	{
		//find out how neurons in the current layer
		neuronTotal = layers[la].GetNeuronTotal();
		
		//the number of neurons in the previous layer(+1) = the number
		//of dendrites in each neuron of the current layer
		dendriteTotal = (1 + layers[(la-1)].GetNeuronTotal());
	
	
		//go through each neuron in the current layer 
		for(ne=0; ne < neuronTotal; ne++)
		{
			//transfer the neuron's output to the dendrite's inputs
			for(de=1; de < dendriteTotal; de++)
			{
				//get output from previous layer's neuron...
				axonOutput=layers[(la-1)].GetOutput(de-1);

				//...transfer to dendrite of neuron in current layer
				layers[la].SetDendrite_x(ne,de,axonOutput);
			}
			
		}//end of for: neurons
		
		//Calculates the outputs for all the neurons in the layer
		layers[la].CalcOutput();

	} //end of for: layers

	//
	//-------------------------------------------------------------
	// BACKWARD PASS:
	// Back-Propagation algorithm (sets the delta for each neuron)
	//-------------------------------------------------------------
	
	//First, we need to calculate the delta (or error) of each 'output
	//layer' neuron (this is determined by the difference between the
	//desired and actual outputs from the neuron)

	la = layerTotal-1;

	//Get the number of neurons in the output layer
	neuronTotal = layers[la].GetNeuronTotal();
	

	for(ne=0; ne < neuronTotal; ne++)
	{
		//get the ACTUAL OUTPUT of the current 'output layer' neuron
		axonOutput=layers[la].GetOutput(ne);

		//get the DESIRED OUTPUT of the current neuron
		desiredOutput=layers[la].GetDesiredOutput(ne);

		//now calculate the delta error for this neuron
		newDelta=axonOutput*(1-axonOutput)*(desiredOutput-axonOutput);

		//assign new delta value to neuron
		layers[la].SetDelta(ne, newDelta);
	}

	//--------------------------------------------------------------
	
	//Now, we need to calculate the deltas of all neurons in each 
	//hidden layer working from the back to the front

	//set the layer index to the last 'hidden layer' 
	//layer element 0 is the 'input layer'

	for(la = layerTotal-2; la>0; la--)
	{
		//Get the number of neurons in the current 'hidden layer'
		neuronTotal = layers[la].GetNeuronTotal();	
		nextLayerNeurons = layers[la+1].GetNeuronTotal();

		//now, work through each neuron in turn and calculate the delta
		for(ne=0; ne < neuronTotal; ne++)
		{
				//get the ACTUAL OUTPUT of the current 'output layer' neuron
				axonOutput=layers[la].GetOutput(ne);
				temp=0;

				

				//pre-calculate the last part of the back-propagation equation
				for(unsigned int i=0; i<nextLayerNeurons; i++)
				{
					//Get the weight of the corresponding neuron's dendrite
					//in the next layer
					//		next layer:				   (neuron, dendrite)  
					weight = layers[la+1].GetDendrite_w( i,      (ne+1) );  


					//retrieve the delta from this neuron
					delta = layers[la+1].GetDelta(i);

					temp +=	(weight*delta);
				}
				
				//calculate the new delta for this neuron
				newDelta = axonOutput * (1-axonOutput) * temp;

				//assign new delta value to neuron
				layers[la].SetDelta(ne, newDelta);

		}//end of forloop:neurons

	}//end of for loop: layers



	//------------------------------------------------------------------------
	//	ADJUST WEIGHTS
	//------------------------------------------------------------------------
	//calculate and apply the 'change in weight' to all dendrites

	for(la = layerTotal-1; la>0; la--)
	{
		//find out how neurons in the current layer
		neuronTotal = layers[la].GetNeuronTotal();

		//the number of neurons in the previous layer(+1) = the number
		//of dendrites in each neuron of the current layer
		dendriteTotal = (1 + layers[(la-1)].GetNeuronTotal());
		
		//go through each neuron in the current layer 
		for(ne=0; ne < neuronTotal; ne++)
		{
			
			//get the delta Error for the current neuron
			delta = layers[la].GetDelta(ne);

			//transfer the neuron's output to the dendrite's inputs
			for(de=0; de < dendriteTotal; de++)
			{
				//get the input value(x) of the current dendrite
				temp = layers[la].GetDendrite_x(ne, de);

				//calculate the CHANGE IN WEIGHT to be applied to the dendrite
				//(eta x input x delta)
				weight = eta*temp*delta;

				//printf("\n%g x %g x %g = %g",eta,temp,delta,weight);

				//add the CHANGE IN WEIGHT to the current weight
				weight = (layers[la].GetDendrite_w(ne,de)) + weight;

				//assign this weight value to the dendrite
				layers[la].SetDendrite_w(ne, de, weight);

			}
			
		}//end of for: neurons



	}//end of for loop: layers


	//-----------------------------------------------------------------
	//  CALCULATE THE ROOT-MEAN-SQUARE OF ALL DELTAS IN THE NETWORK
	//-----------------------------------------------------------------
	
		// How many processing units are there in the network

	unsigned int unitTotal = 0; //use this to get the mean
	unsigned int neuronsLayer = 0;
	la = layerTotal-1;

	double sqDeltas = 0; //stores the square of all the deltas
	delta = 0 ; //current delta error value
	double mean = 0;	//store the mean
	double rms = 0; //the root-mean-square
	unsigned int i=0;

	// get the number of neurons in each layer EXCEPT the input layer
	// (this has no processing units, therefor no deltas)
	for(i=la; i>0; i--)
	{
		unitTotal += layers[i].GetNeuronTotal();
	}


	//////////////////////////// TEMP ///////////////////////////////////
	// printf("\n\nTotal number of processing units: %d", unitTotal);


	//-------------------------------------------------------------------
	// calculate the Root-Mean-Square of the neuron deltas
	// in the output layer

	// calculate the square of all the deltas
	for(i=la; i>0; i--)
	{
		//go through each neuron in the current layer
		//(get the # of neurons in the layer)
		neuronsLayer = layers[i].GetNeuronTotal();

		for(unsigned int n=0; n < neuronsLayer; n++)
		{
			//get the delta of the current neuron
			delta = layers[i].GetDelta(n);

			//square this delta
			delta = delta*delta;

			//printf("\n");
			//printf("\nDelta of neuron %d in layer %d is: %g", n,i, delta);

			//add this to the total square of deltas
			sqDeltas += delta;
		}
	}

	//Find the mean of all the squared deltas
	mean = sqDeltas / unitTotal;

	//calculate the root of this mean
	rms = sqrt(mean);
	
	//pass this value to the network object
	rmsDelta=rms;

	//printf("\n\nThe square of all the deltas is: %g", sqDeltas );
	//printf("\nThe mean is: %g", mean);
	//printf("\nThe RMS is: %g", rms);

	//----------------------------------------------------------------------
//network has completed one pass through the training algorithm and 
//all deltas & weights have been adjusted. Increment the pass counter
pass++;

}//end of function: train()

//===========================================================================

bool Cnetwork::IsTrained()
{

	//This function should only be called once the training algorithm
	//has passed through the entire training set.
	epoch++;

	//------------------------------------------------------------------------
	//if the 'root-mean-square' is below 'epsilon' then the network is trained 
	//return success to stop training
	if(rmsDelta < epsilon)
	{
		return 1;
	}
	else
	{
		return 0;
	}

}//end of IsTrained()

//===================================================================

void Cnetwork::test()
{

	double axonOutput=0; //the axon output of a previous layer neuron to be transferred
						//to the dendrites of the neurons in the current layer

	unsigned int neuronTotal=0; 
	unsigned int dendriteTotal=0; 

	//-------------------------------------------------------------
	//Get the inputs from the input layer and forward-propagate
	//through the net. 
	//-------------------------------------------------------------
	//This is identical to the first stage of the 'train()' function 

	for(unsigned int la=1; la<layerTotal; la++)
	{
		//find out how neurons in the current layer
		neuronTotal = layers[la].GetNeuronTotal();
		
		//the number of neurons in the previous layer+1 = the number
		//of dendrites in each neuron of the current layer
		dendriteTotal = (1 + layers[(la-1)].GetNeuronTotal());
	
		//go through each neuron in the current layer 
		for(unsigned int ne=0; ne < neuronTotal; ne++)
		{

			//transfer the neuron's output to the dendrite's inputs
			for(unsigned de=1; de < dendriteTotal; de++)
			{
				//get output from previous layer's neuron...
				axonOutput=layers[(la-1)].GetOutput(de-1);

				//...transfer to dendrite of neuron in current layer
				layers[la].SetDendrite_x(ne,de,axonOutput);
			}
			
		}//end of for: neurons
		
		//Calculates the outputs for all the neurons in the layer
		layers[la].CalcOutput();

	} //end of for: layers

}//end of function: test


