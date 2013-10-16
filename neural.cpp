/*
 * Written by: Paras Chopra
 * Email: paras1987@gmail.com
 * Web: www.paraschopra.com
 * Comment: Use this code as you like, but please give me credit whenever I deserve it.
 *
 * Improved version by András Mamenyák
 * Changelog
 * - fixed build errors
 * - fixed segfault errors
 * - cleaner code
 * - improved runtime: 25% faster
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

class Dendrite
{
public:
  double weight;  // Weight of the neuron
  int points_to;  // The index of the neuron of the next layer to which it points

  Dendrite(double weight = 0.0, int points_to = 0) : weight(weight), points_to(points_to)
  {}
};

class Neuron
{
public:
  int id;
  double value;
  double bias;
  double delta;
  Dendrite *dendrites;

  Neuron(int id = 0, double value = 0.0, double bias = 0.0) : id(id), value(value), bias(bias)
  {
    delta = 0.0;
  }

  ~Neuron()
  {
    delete[] dendrites;
  }

  /*
   * Set the dendrites from the neuron to given dendrite
   */
  void set_dendrites(int n)
  {
    dendrites = new Dendrite[n];

    for (int i = 0; i < n; i++)  // Initialize the dendrite to attach to next layer
      dendrites[i].points_to = i;
  }
};

class Layer
{
public:
  Layer()
  {}

  ~Layer()
  {
    delete[] neuron;
  }

  void initialize(int size)
  {
    neuron = new Neuron[size];
  }

  Neuron get_neuron(int index)
  {
    return neuron[index];
  }

  void set_neuron(Neuron neuron, int index)
  {
    this->neuron[index] = neuron;
  }

  Neuron *neuron;
};

class Network
{
public:
  Network()
  {
    srand(time(NULL));
  }

  ~Network()
  {
    delete[] inputs;
    delete[] outputs;
  }

  /*
   * Set various parameters of the net
   */
  void set_data(double learning_rate, int layer[])
  {
    this->learning_rate = learning_rate;

    inputs = new double[layer[0]];
    outputs = new double[layer[2]];

    for (int i = 0; i < 3; i++)
    {
      neuron_per_layer[i] = layer[i];
      this->layer[i].initialize(layer[i]);  // Initialize each layer with the specified size
    }

    randomize();
  }

  void set_input_output(double input[], double output[])
  {
    for (int i = 0; i < neuron_per_layer[0]; i++)
      layer[0].neuron[i].value = input[i];

    update_output();

    for (int i = 0; i < neuron_per_layer[2]; i++)
      output[i] = layer[2].neuron[i].value;
  }

  /*
   * The standard backprop Learning algorithm
   *
   * For output layer:
   * Delta = (Target - Actual) * Actual * (1 - Actual)
   *
   * For hidden layer:
   * Delta  = Actual * (1 - Actual) * Sum(Weight_from_current_to_next AND Delta_of_next)
   *
   * Weight += LearningRate * Delta * Input
   */
  void train(double input[], double output[])
  {
    double Actual, Delta;

    for (int i = 0; i < neuron_per_layer[0]; i++)
      layer[0].neuron[i].value = input[i];

    update_output();

    for (int i = 2; i > 0; i--)  // Go from last layer to first layer
      for (int j = 0; j < neuron_per_layer[i]; j++)
      {
        Actual = layer[i].neuron[j].value;  // Actual value

        if(i == 2)  // Output layer
        {
          Delta = (output[j] - Actual) * Actual * (1.0 - Actual);  // Function to compute error
          layer[i].neuron[j].delta = Delta;
        }
        else  // Hidden layer
        {
          Delta = Actual * (1.0 - Actual) * sum_weight_delta(i, j);
        }

        if (i > 0)  // Input layer does not have a bias
          layer[i].neuron[j].bias += Delta*learning_rate;

        for (int k = 0; k < neuron_per_layer[i-1]; k++)  // Calculate the new weights
          layer[i-1].neuron[k].dendrites[j].weight +=  Delta*learning_rate*layer[i-1].neuron[k].value;
      }
  }

private:
  /*
   * Randomize weights and biases
   */
  void randomize()
  {
    for (int i = 0; i < 3; i++)
      for (int j = 0; j < neuron_per_layer[i]; j++)
      {
        if (i < 2)  // Last layer does not require weights
        {
          layer[i].neuron[j].set_dendrites(neuron_per_layer[i+1]); // Initialize the dendites

          for (int k = 0; k < neuron_per_layer[i+1]; k++)
            layer[i].neuron[j].dendrites[k].weight = get_rand(); // Let weight be the random value
        }

        if (i > 0)  // First layer does not need biases
        {
          layer[i].neuron[j].bias = get_rand();
        }
      }
  }

  /*
   * Gives the output of the net
   */
  void update_output()
  {
    for (int i = 1; i < 3; i++)
      for (int j = 0; j < neuron_per_layer[i]; j++)
      {
        for (int k = 0; k < neuron_per_layer[i-1]; k++)  // Multiply and add all the inputs
          layer[i].neuron[j].value += layer[i-1].neuron[k].value*layer[i-1].neuron[k].dendrites[j].weight;

        layer[i].neuron[j].value += layer[i].neuron[j].bias;  // Add bias
        layer[i].neuron[j].value = limiter(layer[i].neuron[j].value);  // Squash that value
      }
  }

  /*
   * Sigmoid activation function
   */
  double limiter(double x)
  {
    return 1.0/(1.0 + exp(-x));
  }

  double get_rand()
  {
    return -1.0 + ((double) rand()/RAND_MAX)*2.0;
  }

  /*
   * Calculate sum of weights * delta. Used in back prop.
   */
  double sum_weight_delta(int Nlayer, int Nneuron)
  {
    double result = 0.0;

    for (int i = 0; i < neuron_per_layer[Nlayer+1]; i++)  // Go through all the neuron in the next layer
      result += layer[Nlayer].neuron[Nlayer].dendrites[i].weight*layer[Nlayer+1].neuron[i].delta;

    return result;
  }

  double learning_rate;
  Layer layer[3];
  double *inputs;
  double *outputs;
  int neuron_per_layer[3];
};

int main()
{
  int layer[3] = {2, 2, 1};  // input, hidden, output
  Network network;

  network.set_data(0.1, layer);

  std::cout << "Start training.\n\n";

  // XOR
  int iter = 0;
  double tr_inp[4][2] = {{0.0, 0.0}, {1.0, 0.0}, {0.0, 1.0}, {1.0, 1.0}};
  double tr_out[4][1] = {{0.0}, {1.0}, {1.0}, {0.0}};

  std::cout << "Enter number of training Iterations: ";
  std::cin >> iter;

  for(int i = 0; i < iter; i++)
    for(int j = 0; j < 4; j++)
      network.train(tr_inp[j], tr_out[j]);

  std::cout << "\nEnd training.";


  std::cout << "\n\nStart testing.";

  double output[4];

  for(int j = 0; j < 4; j++)
  {
    std::cout << "\n\nCase number: " << j+1;

    network.set_input_output(tr_inp[j], output);

    for(int i = 0; i < layer[0]; i++)
      std::cout << "\nInput" << i+1 << " : " << tr_inp[j][i];

    for(int i = 0; i < layer[2]; i++)
      std::cout << "\nOutput" << i+1 << " : " << output[i];
  }

  std::cout << "\n\nEnd testing.\n";

  return 0;
}
