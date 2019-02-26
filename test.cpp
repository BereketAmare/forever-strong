/*This is the Blinking Game source code
Tibebu Getachew
Bereket Amare
Kidus Mekonnen
AAU 2018/19 */


// including the necessary header files
#include <iostream>
#include "opencv2/opencv.hpp"
#include <dlib/opencv.h>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_io.h>
#include <dlib/image_processing.h>
#include <ctime>

using namespace dlib;
using namespace std;

//defining the distance calculating function
float euclidean(dlib::point a, dlib::point b) {
	return sqrt(pow(a(0) - b(0), 2) + pow(a(1) - b(1), 2));
}

//defining the eye aspect ratio
float eye_aspect_ratio(std::vector<dlib::point > eye) {
	float A = euclidean(eye[1], eye[5]);
	float B = euclidean(eye[2], eye[4]);
	float C = euclidean(eye[0], eye[3]);

	float ear = (A + B) / (2.0 * C);
	return ear;

}


int main(int argc, char* argv[]) {
	//checking if the required arguments are given
    if (argc < 2) {
        cout << "Required arguments not given\nUsage:\n\t./new <shape_predictor>" << endl;
        return 1;
    }
    try {
		    Restart:	
		    
		    // initializing the important variables
		    float EYE_AR_THRESH = 0.17;
		    int  EYE_AR_CONSEC_FRAMES = 1;
		    int BLINK = 1;
		    int COUNTER = 0;
		    int  TOTAL = 0;
		    
		    //assigning the face detector and shape predictor
		    frontal_face_detector detector = get_frontal_face_detector();
		    shape_predictor sp; 
		    
		    //reconstructing(deserializing) the data in sp to use it in our program
		    deserialize(argv[1]) >> sp;
		    
		    //opening the video stream
		    cv::VideoCapture cap(0);
		    
		    //checking if there's a problem opening the video stream
		    if (!cap.isOpened()) {
			    cout << "Error opening video stream" << endl;
			    return -1;
		    }
		    
		    //declaring the appropriate time variables
			int start_s=clock();
			int end_s;
		    
		    //main loop of the program
		    while(true) {
		    	
		    	//opening a cv frame and directing the video stream to the frame
			    cv::Mat frame;
			    cap >> frame;
			    
			    //resizing the frame to appropriate sizes and converting the frame to an image data type
			    cv::resize(frame, frame, cv::Size(640, 480));
				cv_image<bgr_pixel> cimg(frame);
				
				//detecting faces from the images
	            std::vector<rectangle> faces = detector(cimg);
	            
	            
				for (int i = 0; i < faces.size(); i++) {
					rectangle rect = faces[i];
					
					//providing the arguments for sp
					full_object_detection shape = sp(cimg, rect);
					
					//initializing the start and end of the left eye indices
					float lStart = 42.0;				
					float lEnd= 48.0;
					
					//using dlib to grab the 6 indices of the left eye pushing the results to lEye
					std::vector<dlib::point > lEye;
					for (int j = lStart; j < lEnd; j++) {
						lEye.push_back(shape.part(j));
					}
					
					//calculating the eye aspect ratio for the left eye
					float leftEar = eye_aspect_ratio(lEye);
					
					//initializing the start and end of the right eye indices
					float rStart= 36.00;
					float rEnd= 42.00;
					
					//using dlib to grab the 6 indices of the right eye pushing the results to rEye
					std::vector<dlib::point >rEye;
					for (int j = rStart; j < rEnd; j++) {
						rEye.push_back(shape.part(j));
					}
					
					//calculating the eye aspect ratio for the right eye
					float rightEar = eye_aspect_ratio(rEye);
					
					//calculating the average eye aspect ratio
					float ear = (leftEar + rightEar) / 2.0;
					
					//checking if the eye aspect ratio is less than the treshold 
					//if it is incrementing counter				
					if (ear < EYE_AR_THRESH) 
						COUNTER++;
					
					//checking if counter is greater or equal to consecutive frames
					//if it is incrementing total
					if (COUNTER >= EYE_AR_CONSEC_FRAMES)
								TOTAL++;
					
					//if total equals blink assigning that instant time to end_s
					if (TOTAL == BLINK){
						 end_s = clock();
						break;
					}	
					
					//measuring the time span between end_s and start_s
					double time_span = (end_s - start_s)/double (CLOCKS_PER_SEC);
					
					//the text 'YOU BLINKED', the time and the two options(R to restart and E to exit) will be displayed when the player blinks
					if (COUNTER >= EYE_AR_CONSEC_FRAMES){
						cv::putText(frame, "YOU BLINKED" , cv::Point(180, 150), 
	       				   		 cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 255, 2));
						cv::putText(frame, "YOUR TIME IS : " + to_string(time_span) + " sec",cv::Point(114, 181), 
					             cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 255, 2));
						cv::putText(frame, "Press R to Restart", cv::Point(146, 265),
	   			 				 cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 255, 2));
						cv::putText(frame, "Press E to Exit", cv::Point(166, 295), 
	 			 				 cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 255, 2));
					}				
			
				}
			//telling cv to show the frame
			cv::imshow("Frame", frame);
			
			//if the user presses e the program will break form the loop and the frame will be closed
			//if the user presses r the program will executing again from line 44
			char c = (char)cv::waitKey(25);
			if(c == 'e')
				break;
			if(c == 'r'){
				goto Restart;					
			}
	}	    
	    cap.release();
	    cv::destroyAllWindows();
    } 
    // the exception for not building will be displayed
    catch (exception& e) {
        cout << "exception thrown" << endl;
        cout << e.what() << endl;
    }
    return 0;
}
