import math
import random
import csv

def sigmoid (t, beta=1):
    return 1/(1+math.exp(-beta*t))

class Neuron(object):
    def __init__(self, in_neurons=[], in_weights=[]):
        self.in_neurons = in_neurons
        self.in_weights = in_weights
        self.output = 0

    def addInputNeuron(self, in_neuron, in_weight):
        self.in_neurons.append(in_neuron)
        self.in_weights.append(in_weight)
        
    def fire(self):
        sigmoid_input = 0
        for i in range(len(self.in_neurons)):
            sigmoid_input += self.in_neurons[i].output * self.in_weights[i]
        self.output = sigmoid(sigmoid_input)

    def getValue(self):
        return self.output
    
class InputNeuron(Neuron):
    def __init__(self, input_value):
        self.input = input_value
        self.output = input_value
        
    def updateInput(self, input_value):
        self.input = input_value
        self.output = input_value

    def addInputNeuron(self):
        return
    
    def fire(self):
        self.output = self.input

class NeuronLayer(object):
    def __init__(self, num_neurons, connection_layer, connection_matrix):
        for i in range(len(connection_matrix)):
            self.neurons = [Neuron(connection_layer.neurons, connection_matrix[i]) for i in connection_matrix]

    def fireAll(self):
        for neuron in self.neurons:
            neuron.fire()

    def getOutputs(self):
        return [n.output for n in self.neurons]

    def getWeights(self):
        weights = []
        for n in self.neurons:
            weights += n.in_weights
        return weights
    
    def __getitem__(self,k):
        return self.neurons[k]

    def __setitem__(self, k, value):
        if (value.__class__.__bases__[0].__name__ is "Neuron"):
            self.neurons[k] = value
        else:
            raise TypeError('Not a Neuron type')

class InputNeuronLayer(NeuronLayer):
    def __init__(self, num_neurons):
        self.neurons = [InputNeuron(0) for neuron in xrange(num_neurons)]

    def setInputs(self, inputs):
        for i, n in enumerate(self.neurons):# xrange(len(self.neurons)):
            self.neurons[i].updateInput(inputs[i])

def chunks(l, n):
    return [l[i:i+n] for i in range(0, len(l), n)]

class FullyConnectedNeuronLayer(NeuronLayer):
    def __init__(self, num_neurons, in_layer, rand_weights=True, connection_weights=[]):
        if rand_weights:
            self.neurons = [Neuron(in_layer.neurons, [random.uniform(-.1,.1) for a in xrange(len(in_layer.neurons))]) for i in xrange(num_neurons)]
        else:
            w = chunks(connection_weights, len(in_layer.neurons))
            self.neurons = [Neuron(in_layer.neurons, k) for k in w ]

class BackPropagationTrainer(object):
    def __init__(self,network, eta=.1, interations=100):
        self.eta = eta
        self.iterations = iterations
        self.network = network
        
    def train(self, training_data):
        """
        train(self, training_data) takes training data array of the format
        [[input_fields1, output_fields1],
         [input_fields2, output_fields2],
         ...,
         [input_fieldsN, output_fieldsN]]

        where N is the number of training data sets, and input fields is
        as long as the number of input neurons and output fields is as long
        as the number of ouput neurons.

        NOTE: binary input and output is preffered and will converge faster,
        but not strictly necissary

        Example training_data input:
        #                 A XOR B XOR C = OUT
        training_data = [[0,    0,    0,   0],
                         [0,    0,    1,   1],
                         [0,    1,    0,   1],
                         [0,    1,    1,   0],
                         [1,    0,    0,   1],
                         [1,    0,    1,   0],
                         [1,    1,    0,   0],
                         [1,    1,    1,   1]]

        """

if __name__ == "__main__":
    inputLayer = InputNeuronLayer(126)    
    hiddenLayer = FullyConnectedNeuronLayer(256, inputLayer)
    outputLayer = FullyConnectedNeuronLayer(7, hiddenLayer)

    network = [inputLayer,hiddenLayer, outputLayer]

    # Attempting training for connect 4
    # read in data from trainingdata.csv 
    training_data = []
    f = open("trainingdata2.csv", 'rb')
    reader = csv.reader(f)
    try:
        for row in reader:
            training_data.append([int(elem) for elem in row])
    except csv.Error:
        sys.exit('file %s, line %d: %s' % (filename, reader.line_num, e))
    f.close()
    f = open("trainingdata.csv", 'rb')
    reader = csv.reader(f)
    try:
        for row in reader:
            training_data.append([int(elem) for elem in row])
    except csv.Error:
        sys.exit('file %s, line %d: %s' % (filename, reader.line_num, e))
    f.close()

        
#    training_data = [[0,    0,    0,   0, 1, 1],
#                     [0,    0,    1,   1, 0, 1],
#                     [0,    1,    0,   1, 0, 1],
#                     [0,    1,    1,   0, 0, 1],
#                     [1,    0,    0,   1, 0, 1],
#                     [1,    0,    1,   0, 1, 1],
#                     [1,    1,    0,   0, 0, 1],
#                     [1,    1,    1,   1, 0, 0]]                     

    eta = .01
    deltas = []
    for arr in range(1):
        for input_t in training_data:
            deltas = []
            network[0].setInputs(input_t[0:len(network[0].neurons)])
            output_t = input_t[len(network[0].neurons):len(input_t)]
            for layer in network:
                layer.fireAll()

            old_weights = []
            for index, neuron in enumerate(network[2].neurons):
                d = (neuron.output*(1-neuron.output)*(output_t[index] - neuron.output))
                deltas.append(d)
                old_weights_sub = []
                for i in range(len(neuron.in_weights)):
                    old_weights_sub.append(neuron.in_weights[i])
                    neuron.in_weights[i] += eta * d*neuron.in_neurons[i].output
                old_weights.append(old_weights_sub)

            deltas_h = []
            for k,neuron in enumerate(network[1].neurons):            
                h = 0
                for delta, old_weight in zip(deltas,old_weights):
                    h += old_weight[k]*delta                    

                d_h = neuron.output * (1-neuron.output) *h
                for i in range(len(neuron.in_weights)):
                    neuron.in_weights[i] += eta*d_h*neuron.in_neurons[i].output

    print ",".join([str(w) for w in hiddenLayer.getWeights()])
    print ",".join([str(w) for w in outputLayer.getWeights()])
    #for input_t in training_data[::1000]:
    #    deltas = []
    #    network[0].setInputs(input_t[0:len(network[0].neurons)])
    #    for layer in network:
    #        layer.fireAll()
    
#        print "|=============|"
#        print "| %i XOR %i XOR %i = %i |" % tuple(input_t)
#        for i, output in enumerate(network[2].getOutputs()):
#            if (output > .75):
#                print "| %i | %1.4f |" % (i, output)
#            else:
#                print "| %i | %1.4f |" % (i, output)
#        print "\=============/"


