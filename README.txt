GITHUB LINK: https://github.com/kparam91/CMPE295BTSI.git

I)Compile Instructions
1. Prerequisite: Cmake must be installed

2. Run scri.py to compile and build all the files.




II)Run Instructions

1. Raw_moments.cpp: 
    This file will extract raw, central, normalized central and 
    hu moments of the images passed as command line arguments, and store them in a csv file. 
    The last argument must always be the character'z' in order to terminate the loop.
    example: ./Raw_moments DoNotEnter6.JPG DoNotEnter7.JPG z

2. signClassification.cpp
    This file will identify signs based on description given by the user. 
    This includes, color shape and position of the sign within the image.
    Run this file as ./signClassification 
    Follow the prompts to validate the processing engine.
    To end the program enter q when the program asks the question:
     "Enter the shape of the sign OR enter q to exit"
 
3.Shape_detect_final.cpp
     INPUT PARAMETERS
    videofile - the video which contains the traffic sign object.

    execute the code as ./Shape_detect_final videofile
    when the video is playing, right click to pause the video at a particular frame
    right click. This frame will be saved automatically
    The saved image will be opened in a new window
    Automatically, the traffic signs (multiple) will be detected and marked in the image.
    The ROI will be saved in the folder containing your source code.
    OUTPUT
     ROI images

4. The other code files that can optionally be executed:
covariance .cpp with maximum 5 images as arguments to find their mean and covariance.
VideoCapture: captures frames and stores them with a time stamp





