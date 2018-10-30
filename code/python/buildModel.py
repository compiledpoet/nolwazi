import tensorflow as tf;
import sys
import time
import random
import tensorflow.examples.tutorials.mnist.input_data as inputData;

def main():
    xs = [[0,0], [0,1], [1,0], [1,1]]
    ys = [[0], [1], [1], [0]]

    epochs = 100;
    inputSize = 2
    outputSize = 1;
    layerSizes = [512, 512, outputSize]

    inputsHolder = tf.placeholder(tf.float32, shape=[None, inputSize], name="inputs");
    labelsHolder = tf.placeholder(tf.float32, shape=[None, outputSize], name="labels");

    #hidden0
    inputSize0 = 2;
    outputSize0 = 10;
    ws0 = tf.Variable(tf.random_normal([inputSize0, outputSize0]), name="ws0");
    bs0 = tf.Variable(tf.random_normal([outputSize0]), name="bs0");
    outH0 = tf.nn.sigmoid(tf.add(tf.matmul(inputsHolder, ws0), bs0));

    #hidden1
    inputSize1 = outputSize0;
    outputSize1 = 1;
    ws1 = tf.Variable(tf.random_normal([inputSize1, outputSize1]), name="ws1");
    bs1 = tf.Variable(tf.random_normal([outputSize1]), name="bs1");
    prediction = tf.nn.sigmoid(tf.add(tf.matmul(outH0, ws1), bs1));

    loss = tf.reduce_mean(tf.squared_difference(prediction, labelsHolder));
    optimizer = tf.train.GradientDescentOptimizer(.01).minimize(loss);

    with tf.Session() as sess:
        sess.run(tf.global_variables_initializer())
        for e in range(100000):
            _, c = sess.run([optimizer, loss], feed_dict={inputsHolder: xs, labelsHolder:ys});
            print("Epoch:", e, "Ac: ", c, end='\r');



def createLayer(inputSize, outputSize):
    layer = {"weights" : tf.Variable(tf.random_normal([inputSize, outputSize])), "biases" : tf.Variable(tf.random_normal([1, outputSize]))}
    return layer;

def connectLayers(input, layers):
    y2 = tf.add(tf.matmul(input ,layers[0]["weights"]), layers[0]["biases"])
    y2 = tf.nn.sigmoid(y2)

    y1 = tf.add(tf.matmul(y2 ,layers[1]["weights"]), layers[1]["biases"])
    y1 = tf.nn.sigmoid(y1)

    y0 = tf.add(tf.matmul(y1 ,layers[2]["weights"]), layers[2]["biases"])
    y0 = tf.nn.sigmoid(y0)
    return y0

    # prevOutput = input
    # for pos in range(0, len(layers)):
    #     layer = layers[pos]
    #     output = tf.add(tf.matmul(prevOutput, layer['weights']) , layer["biases"])
    #     prevOutput = tf.nn.sigmoid(output);
    #
    # return prevOutput;

def train(input, y0, xs, ys, labs, epochs):
    sm = tf.nn.softmax_cross_entropy_with_logits(logits=y0,labels=labs)
    cost = tf.reduce_mean(sm);
    optimizer = tf.train.GradientDescentOptimizer(.1).minimize(cost)

    pred = tf.nn.softmax(y0)
    pred_label = tf.argmax(pred, 1)
    correct_prediction = tf.equal(tf.argmax(pred, 1), tf.argmax(labs, 1))
    accuracy = tf.reduce_mean(tf.cast(correct_prediction, "float"))

    with tf.Session() as sess:
        writer = tf.summary.FileWriter("./logs/xor_logs", sess.graph_def)
        sess.run(tf.global_variables_initializer())

        for epoch in range(epochs):
            sess.run(optimizer, feed_dict={ input: xs, labs: ys})
            print("Epoch:", epoch)
            print("accuracy= ", accuracy.eval(feed_dict={ input: xs, labs: ys}))


main()
