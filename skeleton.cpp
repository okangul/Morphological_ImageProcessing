#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>
using namespace std;
using namespace cv;

void bubbleSort(int array[], int c) {
        int i, j;
        for (i = 0; i < c; i++) {
                for (j = 0; j < i; j++) {
                        int tmp = array[i];
                        array[i] = array[j];
                        array[j] = tmp;
                }
        }
}





int element[3][3]={{255,255,255},{255,255,255},{255,255,255}};
int A[6][6]={{0,0,0,0,0,0},{0,0,0,255,255,255},{0,0,255,255,255,255},{0,255,255,255,255,0},{0,255,255,255,0,0},{0,255,255,255,0,0}};

// PROGRAM BY OKAN GUL

int main(int argc, char **argv) {
 
  
  if(argc != 2) {
    cout << "USAGE: skeleton <input file path>" << endl;
    return -1;
  }
  
  //Load two copies of the image. One to leave as the original, and one to be modified.
  //Done for display purposes only
  //Use CV_LOAD_IMAGE_GRAYSCALE for greyscale images
  Mat I = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
  Mat F = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
  Mat K = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
  Mat L = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
  Mat M = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
  Mat Result = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
  
  //Create a pointer so that we can quickly toggle between which image is being displayed
  Mat *image = &I;
 
  //Check that the images loaded
  if(!I.data || !F.data) {
    cout << "ERROR: Could not load image data." << endl;
    return -1;
  }
  
  //Create the display window
  namedWindow("Unix Sample Skeleton");


// YOU SHOULD PUT F FOR BINARY IMAGE TO RESULT

  for(int i = 0; i < I.rows; i++)
  {

    for(int j = 0; j < I.cols; j++)
    {
      if(I.at<uchar>(i,j)>185)
        F.at<uchar>(i,j)=255;
      else
        F.at<uchar>(i,j)=0;
    }
  }
  for(int i = 0; i < K.rows; i++)
  {

    for(int j = 0; j < K.cols; j++)
    {
      K.at<uchar>(i,j)=0;
      Result.at<uchar>(i,j)=0;
      M.at<uchar>(i,j)=0;

    }
  }

  
    
  // YOU SHOULD PUT K FOR BINARY IMAGE OPENING RESULT
   
  int sum=9;
  int count=0;

  // erosiooon

  for (int i=0; i<F.rows; i++){
    for (int j=0; j<F.cols; j++) {
      if ((int)F.at<uchar>(i,j)==255) {     // if the foreground pixel is 1
        count = 0;

        for (int m=0; m<3; m++){
          for (int n=0; n<3; n++) {
            if ((i-2+m) >= 0 && (j-2+n) >=0 && (i-2+m) < F.rows && (j-2+n) < F.cols){
              if((int)F.at<uchar>(i-2+m,j-2+n)==255){
                count ++;
              }
            }
          }
        }
        // if all ELEMENT foreground pixels are included in the foreground of 
        // the current pixel's neighborhood, then MAKE 255 this pixel in erosion
        if (sum == count){
          
          K.at<uchar>(i,j) = 255;
        }
        

      }
    }
  }

  // dilosion  


  for (int i=0; i<K.rows; i++){
    for (int j=0; j<K.cols; j++) {
      if ((int)K.at<uchar>(i,j)==255) {       
        // if the foreground pixel is not zero, then fill in the pixel
        // covered by the ELEMENT
        for (int m=0; m<3; m++){
          for (int n=0; n<3; n++) {
            if ((i-2+m) >= 0 && (j-2+n) >=0 && (i-2+m) < K.rows && (j-2+n) < K.cols)
              if ((int)K.at<uchar>(i-2+m, j-2+n)!=255)
                K.at<uchar>(i-2+m, j-2+n) = 255;
          }
        }
      }
    }
  }




  for(int a=2; a<K.rows;a++){
        for( int b=2 ;b<K.cols; b++){
            if((int)(K.at<uchar>(a,b))==255){
              Result.at<uchar>(a,b)=I.at<uchar>(a,b);
            }
        }
    }

    // YOU SHOULD PUT M FOR GRAYSCALE IMAGE OPENING RESULT
  // grayscale erosionn


  int p[9];
  int x[9];
  int l=0;
   for (int i=0; i<I.rows; i++)
    for (int j=0; j<I.cols; j++) {
      l = 0;
      for (int m=0; m<3; m++){
        for (int n=0; n<3; n++) {
          if ((i-1+m) >= 0 && (j-1+n) >=0 && (i-1+m) < I.rows && (j-1+n) < I.cols){
            p[l] = I.at<uchar>(i-1+m, j-1+n) - 50;
            l++;
          }
        }
      }
      bubbleSort(p, l);
      L.at<uchar>(i,j) = p[0];
    }

    // grayscale dilosioon

    
  for (int i=0; i<I.rows; i++){
    for (int j=0; j<I.cols; j++) {
      l = 0;
      for (int m=0; m<3; m++){
        for (int n=0; n<3; n++) {
          if ((i-1+m) >= 0 && (j-1+n) >=0 && (i-1+m) < I.rows && (j-1+n) < I.cols){
            x[l] =L.at<uchar>(i-1+m, j-1+n) + 120;
            l++;
          }
        }
      }
      bubbleSort(x, l);
      M.at<uchar>(i,j) = x[l-1];
    }
  }
   
    

  
  //Display loop
  bool loop = true;
  while(loop) {
    imshow("Unix Sample Skeleton", *image);
    
    switch(cvWaitKey(15)) {
      case 27:  //Exit display loop if ESC is pressed
        loop = false;
        break;
      case 32:  //Swap image pointer if space is pressed
        if(image == &I) image = &Result;
        else image = &I;
        break;
      default:
        break;
    }
  }
}
