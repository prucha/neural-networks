// **********************************************************************
// *																	*
// *			HEADER FILE: PERCEPTRON NETWORK classes					*
// *					Version: 24 January 2002						*
// *						by Milan Prucha								*
// *																	*
// **********************************************************************

// This set of classes simulate a typical MULTI-LAYER PERCEPTRON NETWORK.
// It creates networks that are FULLY CONNECTED, which means the output
// of every neuron in one layer is connected to an input of every neuron
// in the next layer. The user can define the number of layers in a network
// and how many neurons each layer contains.


#ifndef PERCEPTRON_H
#define PERCEPTRON_H



#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef int BOOL;
enum{FALSE, TRUE};


class Cneuron
{

private:

	//dendrite element (dendrites[0]) is reserved for the perceptron's bias (or offset)
	//it's input 'x' is ALWAYS set to 1. 

	struct dendrite
	{
		double x;	//(or INPUT) any value in the range 0<>1
		double w; //weighting value on the dendrite

		dendrite() : x(1), w(0.5) {}
		dendrite(double new_x, double new_w=0.5) {}
		//~dendrite();
	};
	
	
	dendrite* dendrites; //The input elements that feed into the neuron 						 
	unsigned int dendriteTotal;	
	double activation;	//the sum of the weighted inputs (or dendrites)	
	double y;		//the actual output			
	double d;	//delta (or ERROR) between the desired and actual outputs
	double dy; //only used in output layer neurons 
						  //(to calculate delta) 

public:
	
	//sets up and DMAs the dendrites of a neuron
	//(if default constructor is used this needs to be called before neuron is used)
	void CreateDendrites(unsigned int newDendriteTotal);

	//Set the input of a dendrite
	//Any attempt to set the bias input(x) will be rejected (dendrites[0]) as this is ALWAYS +1
	bool SetDendrite_x(unsigned int dendriteElem, double new_x);

	//Set the weight value applied to a dendrite
	//(usually random values are assigned before training begins)
	bool SetDendrite_w(unsigned int dendriteElem, double new_w);

	//returns the input currently applied to the dendrite
	double GetDendrite_x(unsigned int dendriteElem); 

	//returns the current weight applied to the dendrite
	double GetDendrite_w(unsigned int dendriteElem);

	//calculates and sets the net activation of the neuron,
	//then passes this through a 'Sigmoid Function' to
	//get a non-linear output
	void CalcOutput();

	//get the current activation level of the neuron
	double GetActivation();
	
	//Get the actual output of the neuron after it  has passed through the 'sigmoid function'
	double GetOutput();

	//Get the Desired Output of an output layer neuron
	double GetDesiredOutput();

	//Explicitly set the output value: This is use to set up the input layer neurons. No
	//processing takes place at input layer neurons. They are used simply to supply input
	//values to be processed by subsequent layers in the net.
	void SetOutput(double new_y);

	//retrieve the Delta (or Error) in the neuron's output
	double GetDelta();

	//Delta (or Error) in the neuron's output
	//used to adjust the dendrite weights of the neuron
	void SetDelta(double new_d);

	//set the desired output of an output layer neuron
	void SetDesiredOutput(double new_dy); 

	//Display info about the neuron
	void info();

	//constructors
	Cneuron();
	Cneuron(unsigned int newDendriteTotal); //dendrite total will be set by the layer object
	~Cneuron(); //destructor

}; 


//============================================================================================


class Clayer
{

private:

	Cneuron* neurons;	
	unsigned int neuronTotal; //number of neuron elements contained within the layer
	unsigned int dendriteTotal;	//The number of dendrites -1 = the number of neurons
	//in the previous layer. All neurons within a layer have the same number of
	//dendrites (inputs).

	unsigned int type; //type of layer: (set during initialisation)
	// 0 => input layer		1 => hidden layer	2 => output layer
	// There is only ever one input & output layer.
	// There can be any number of hidden layers in-between.

public:


	//Create the neuron elements for this layer (each with dendrites determined by the 
	//number of neurons in the previous layer) - also sets layer 'type' as this
	//affects the way that neurons are processed within the layer. 

	void CreateNeurons(unsigned int newNeuronTotal, unsigned int newDendriteTotal,
						unsigned int newType);

	bool SetDendrite_x(unsigned int neuronElem, unsigned int dendriteElem, double new_x);
	bool SetDendrite_w(unsigned int neuronElem, unsigned int dendriteElem, double new_w);
	
	double GetDendrite_x(unsigned int neuronElem, unsigned int dendriteElem); 
	double GetDendrite_w(unsigned int neuronElem, unsigned int dendriteElem);

	//calculate the outputs of all the neurons in the layer
	//(execution depends on the layer type)
	void CalcOutput(); 

	double GetActivation(unsigned int neuronElem);

	//Get the Desired Output of an output layer neuron
	double GetDesiredOutput(unsigned int neuronElem);

	//Get the actual output of the neuron after it  has passed through the 'sigmoid function'
	double GetOutput(unsigned int neuronElem);

	//Set the desired output of a neuron in the outputlayer(2) only
	bool SetDesiredOutput(unsigned int neuronElem, double new_dy);

	//retrieve the Delta (or Error) in the neuron's output
	double GetDelta(unsigned int neuronElem);

	//Delta (or Error) in the neuron's output
	bool SetDelta(unsigned int neuronElem, double new_d);

	unsigned int GetNeuronTotal();


	//Display info on the layer
	void info();

	void setType(unsigned int newType);

	//constructors
	Clayer();
	Clayer(unsigned int newNeuronTotal, unsigned int newDendriteTotal=3, unsigned int newType=1);
	~Clayer();
};


//============================================================================================


class Cnetwork
{
private:
	
	//0 (first element) => input layer		
	//1 (inbetween elements) => hidden layers
	//2 (last element) => output layer
	Clayer* layers;	

	//the number of layers in the entire network
	unsigned int layerTotal; 

	unsigned int pass; //the number of passes through the training algorithm

	unsigned int epoch; //the number of times the training algorithm has been applied to
						//the entire training/pattern set. Incremented by 'IsTrained()'.
	
	double eta; //(n) also known as the 'learning co-efficient' ( eta x delta x input(i) )
	
	double epsilon; //the 'netError' must be below this value to terminate training

	///////////////NOT YET IMPLEMENTED//////////////////////////////////////////////////
	double alpha; //modulates 'momentum'  - which is proportional to 
				//the change in weight from the previous training pass?????

	double rmsDelta; //the 'Root-Mean-Square' of all the delta errors

public:

	//initialises 'layers' array
	void createLayers(unsigned int newlayerTotal); 

	//Assigns the layer type and sets the up the neurons within the layer  
	bool defineLayer(unsigned int layerElem, unsigned int newNeuronTotal);

	bool SetDendrite_x(unsigned int layerElem, unsigned int neuronElem,
	unsigned int dendriteElem, double new_x);

	bool SetDendrite_w(unsigned int layerElem, unsigned int neuronElem,
	unsigned int dendriteElem, double new_w);

	double GetDendrite_x(unsigned int layerElem, unsigned int neuronElem,
	unsigned int dendriteElem);

	double GetDendrite_w(unsigned int layerElem, unsigned int neuronElem,
	unsigned int dendriteElem);

	//Delta (or Error) in the neuron's output
	bool SetDelta(unsigned int layerElem, unsigned int neuronElem,
	double new_d);
	
	bool SetDesiredOutput(unsigned int neuronElem, double new_dy);

	//Get the Desired Output of an output layer neuron
	double GetDesiredOutput(unsigned int layerElem, unsigned int neuronElem);

	//return the current pass of the training algorithm
	unsigned int GetPass();

	//Get the current 'Root-Mean-Square' of all the deltas
	double GetRMS();

	//Display info on the neural net
	void info();

	//Run the network through a TRAINING pass
	//The inputs and desired outputs must be set before
	//this is executed.
	void train();

	//if the mean_error is below the threshold 'epsilon' 
	//then return TRUE (the network is trained!)
	bool IsTrained();

	//inputs are propagated through the network and outputs are produced at the 
	//output layer neurons.
	void test();

	//contructors
	Cnetwork();
	Cnetwork(unsigned int newlayerTotal, double newEta=0.5, double newEpsilon=0.001);
	~Cnetwork();
};

//==============================================================================================







#endif