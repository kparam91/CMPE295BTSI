import numpy as np
import matplotlib.pyplot as plt
from os import listdir
from os.path import isfile, join
import operator
import sys
# Make sure that caffe is on the python path:
caffe_root = '/home/ubuntu/TSI/bvlc_googlenet/'  # this file is expected to be in {caffe_root}/examples
import sys
sys.path.insert(0, caffe_root + 'python')

import caffe
print sys.argv[1]
# Set the right path to your model definition file, pretrained model weights,
# and the image you would like to classify.
#MODEL_FILE = './examples/cifar10/cifar10_quick.prototxt'  // deploy.prototxt file for our model
MODEL_FILE = 'deploy.prototxt'
PRETRAINED = '/home/ubuntu/TSI/bvlc_googlenet/snapshot/tsi1_iter_11400.caffemodel'
IMAGE_FILE = '/home/ubuntu/testTSI/'+str(sys.argv[1])#bikelane1290.JPG'                

'''
NoLeftTurn1597.JPG
NoRightTurn1122.JPG                
speedLimit1285.JPG
NoRightTurn1167.JPG                
Stop1464.JPG
Stop1651.JPG
'''

caffe.set_mode_cpu()
net = caffe.Classifier(MODEL_FILE, PRETRAINED,
                       mean=np.load(caffe_root +'input.npy' ).mean(1).mean(1),
                       channel_swap=(2,1,0),
                       raw_scale=255,
                       image_dims=(227, 227))
input_image = caffe.io.load_image(IMAGE_FILE)
#plt.imshow(input_image)

prediction = net.predict([input_image])  # predict takes any number of images, and formats them for the Caffe net automatically
print 'prediction shape:', prediction[0].shape
#plt.plot(prediction[0])
#print 'predicted class: BIKE LANE'
# prediction[0]
print 'suk max', prediction[0]
scores= prediction.flatten().tolist()
#print scores

scores_dictionary={'stop' : scores[0], 'speed': scores[1], 'pedestrian' : scores[2], 'oneway' : scores[3], 'noright' : scores[4], 'noleft' : scores[5], 'bikelane' : scores[6]}
#sorted(data, key=data.get)	
#print sorted(scores_dictionary.values(),key=scores_dictionary)
#print sorted(scores_dictionary.items(), key=operator.itemgetter(1))

#print 'man max', 
index=prediction[0].argmax()
if(index==0):
	print('Stop detected')
elif(index==1):
	print('Speed Limit')
elif(index==2):
	print('Pedestrian')
elif(index==3):
	print('One Way')
elif(index==4):
	print('No Right Turn')
elif(index==5):
	print('No Left Turn')
elif(index==6):
	print('Bike Lane')
i=0
for m,k in sorted(scores_dictionary.items(), key=operator.itemgetter(1)):
	i=i+1
	if i==6 :
		print m

i=0
for m,k in sorted(scores_dictionary.items(), key=operator.itemgetter(1)):
        i=i+1
        if i==5 :
                print m
#plt.show()
