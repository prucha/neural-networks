// **********************************************************************
// *																	*
// *			TEST PROGRAM: PERCEPTRON NETWORK classes				*
// *					Version: 24 January 2002						*
// *						by Milan Prucha								*
// *																	*
// **********************************************************************


#include "perceptron.h"


int main(int argc, char* argv[])
{

bool test =0;

	//seed the rand() function
	srand( (unsigned)time(NULL) );

//TEST NEURON OBJECT
//Cneuron myNeuron(3);

//myNeuron.SetDendrite_x(0, 0.56);
//myNeuron.SetDendrite_x(1, 0.7);
//myNeuron.SetDendrite_x(2, 0.867);

//myNeuron.CalcOutput();
//myNeuron.info();

//==================================

//TEST LAYER OBJECT
//Clayer mylayer(3,3,1);
//mylayer.SetDendrite_w(0,0,0.5);
//mylayer.SetDendrite_w(1,0,0.7);

//if(!mylayer.SetDendrite_x(0,1,0.2))
//	printf("\n Can't assign to zero element");

//mylayer.SetDendrite_x(0,2,0.56);
//mylayer.SetDendrite_x(0,3,0.72);
//mylayer.CalcOutput();
//mylayer.info();
//getch();

//Clayer input(4,5,0);

//input.SetDendrite_x(0,0,0.6);
//input.SetDendrite_x(1,0,0.5);
//input.SetDendrite_x(2,0,0.4);
//input.SetDendrite_x(3,0,0.3);

//input.info();

//====================================================
//TEST NETWORK OBJECT 
//====================================================

//Cnetwork myNetwork(3);	//network has 3 layers

//myNetwork.defineLayer(0,3); //input layer - has 3 neurons
//myNetwork.defineLayer(1,2); //hidden layer - has 2 neurons
//myNetwork.defineLayer(2,3); //output layer - has 3 neurons



//As the input layer neurons have no active dendrites,
//this should set the output of each neuron.
//myNetwork.SetDendrite_x(0,0,0,0.1);
//myNetwork.SetDendrite_x(0,1,0,0.2);
//myNetwork.SetDendrite_x(0,2,0,0.3);

//====================================================
// Set Weights
//====================================================

//hidden layer
//myNetwork.SetDendrite_w(1,0,0, 0.49);
//myNetwork.SetDendrite_w(1,0,1, 0.48);
//myNetwork.SetDendrite_w(1,0,2, 0.39);
//myNetwork.SetDendrite_w(1,0,3, 0.51);

//myNetwork.SetDendrite_w(1,1,0, 0.28);
//myNetwork.SetDendrite_w(1,1,1, 0.47);
//myNetwork.SetDendrite_w(1,1,2, 0.78);
//myNetwork.SetDendrite_w(1,1,3, 0.48);



//output layer
//myNetwork.SetDendrite_w(2,0,0, 0.38);
//myNetwork.SetDendrite_w(2,0,1, 0.68);
//myNetwork.SetDendrite_w(2,0,2, 0.47);

//myNetwork.SetDendrite_w(2,1,0, 0.39);
//myNetwork.SetDendrite_w(2,1,1, 0.44);
//myNetwork.SetDendrite_w(2,1,2, 0.44);

//myNetwork.SetDendrite_w(2,2,0, 0.44);
//myNetwork.SetDendrite_w(2,2,1, 0.54);
//myNetwork.SetDendrite_w(2,2,2, 0.43);

//====================================================

//myNetwork.info();
//getch();

//myNetwork.SetDesiredOutput(0,0.5);
//myNetwork.SetDesiredOutput(1,0.5);
//myNetwork.SetDesiredOutput(2,0.5);

//printf("\n\n");

//myNetwork.info();

//=======================================================

Cnetwork myNetwork(3);

myNetwork.defineLayer(0,2); //input layer - has 2 neurons
myNetwork.defineLayer(1,2); //hidden layer - has 2 neurons
myNetwork.defineLayer(2,1); //output layer - has 1 neuron

//As the input layer neurons have no active dendrites,
//this should set the output of each neuron.
myNetwork.SetDendrite_x(0,0,0,0);  //neuron: 0

myNetwork.SetDendrite_x(0,1,0,0);  //neuron: 1

//=======================================================
// Set Weights
//=======================================================

//hidden layer
myNetwork.SetDendrite_w(1,0,0,  0.862518);
myNetwork.SetDendrite_w(1,0,1, -0.155797);
myNetwork.SetDendrite_w(1,0,2,  0.282885);

myNetwork.SetDendrite_w(1,1,0,  0.834986);
myNetwork.SetDendrite_w(1,1,1, -0.505997);
myNetwork.SetDendrite_w(1,1,2, -0.864449);


//output layer
myNetwork.SetDendrite_w(2,0,0,  0.036498);
myNetwork.SetDendrite_w(2,0,1, -0.430437);
myNetwork.SetDendrite_w(2,0,2,  0.481210);



//=====================================================
//Set Desired Outputs
//=====================================================

//with inputs [0,0] the output SHOULD be 0
myNetwork.SetDesiredOutput(0, 0); 

//=====================================================
bool trained = 0;
unsigned int p;
double rms = 0;

while(trained==0)
{

//------------------------------------------------
//PATTERN 1:
//Set Input Pattern
myNetwork.SetDendrite_x(0,0,0,0);  //neuron: 0
myNetwork.SetDendrite_x(0,1,0,0);  //neuron: 1

//Set Desired Outputs for this input pattern
//with inputs [0,0] the output SHOULD be 0
myNetwork.SetDesiredOutput(0, 0); 
myNetwork.info();

myNetwork.train();
myNetwork.info();
getch();

//------------------------------------------------
//PATTERN 2:
myNetwork.SetDendrite_x(0,0,0,0);  //neuron: 0
myNetwork.SetDendrite_x(0,1,0,1);  //neuron: 1

//Set Desired Outputs for this input pattern
//with inputs [0,1] the output SHOULD be 0
myNetwork.SetDesiredOutput(0,1); 

myNetwork.train();
myNetwork.info();
getch();

//------------------------------------------------
//PATTERN 3:
myNetwork.SetDendrite_w(0,0,0,1); //neuron: 1
myNetwork.SetDendrite_w(0,1,0,0); //neuron: 0

myNetwork.SetDesiredOutput(0,1); 
 
myNetwork.train();
myNetwork.info();
getch();

//------------------------------------------------
//PATTERN 4:
myNetwork.SetDendrite_w(0,0,0,1); //neuron: 1
myNetwork.SetDendrite_w(0,1,0,1); //neuron: 0

myNetwork.SetDesiredOutput(0,0); 
 
myNetwork.train();
myNetwork.info();
getch();

//-------------------------------------------------

p= myNetwork.GetPass();
//rms = myNetwork.GetRMS();

printf("\nPASS: %d", p);
//printf("\nRMS: %g", rms);

//-------------------------------------------------
trained = myNetwork.IsTrained(); 
getch();
}

printf("\n Network Trained");
myNetwork.info();

//=====================================================
return 0;
}

