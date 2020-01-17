


#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;

Mat src;
Mat src_gray;
Mat src_org;
int thresh = 100;
int max_thresh = 255;
RNG rng(12345);

/// Function header
void thresh_callback(int, void* );
Mat Morphology_Operations( int, void* );
/** @function main */
int main( int argc, char** argv )
{
  /// Load source image and convert it to gray
  src = imread( "/works/opencv/opencv_lesson_1/opencv_lesson_1/input_02.jpg", 1 );
  src_org = imread( "/works/opencv/opencv_lesson_1/opencv_lesson_1/input_02.jpg", 1 );
  /// Convert image to gray and blur it
  // cvtColor( src, src_gray, COLOR_BGR2GRAY );
  src_gray = src.clone();
  src_gray =  Morphology_Operations(0,0);
    
    
//    cvtColor(src_gray, src, COLOR_BGR2HSV);
//    // Detect the object based on HSV Range Values
//    inRange(src, Scalar(0, 0, 0), Scalar(255, 255, 92), src_gray);
    
    
    
  blur( src_gray, src_gray, Size(3,3) );

  /// Create Window
  const char* source_window = "Source";
  namedWindow( source_window, WINDOW_AUTOSIZE );
  imshow( source_window, src );

  createTrackbar( " Canny thresh:", "Source", &thresh, max_thresh, thresh_callback );
  thresh_callback( 0, 0 );

  waitKey(0);
  return(0);
}

Mat Morphology_Operations( int, void* )
{
  // Since MORPH_X : 2,3,4,5 and 6
  //int operation = morph_operator + 2;
  //Mat element = getStructuringElement( morph_elem, Size( 2*morph_size + 1, 2*morph_size+1 ), Point( morph_size, morph_size ) );
  //morphologyEx( src, dst, operation, element );
  //imshow( window_name, dst );
    Mat dst;
    
    int operation = 5;
    int morph_size = 4;
    Mat element = getStructuringElement( 0, Size( 2*morph_size + 1, 2*morph_size+1 ), Point( morph_size, morph_size ) );
    morphologyEx( src_gray, dst, operation, element );
    imshow( "step1", dst );
    
    return dst;
}
/** @function thresh_callback */
void thresh_callback(int, void* )
{
  Mat canny_output;
    Mat output = src_org.clone();
  vector<vector<Point> > contours;
  vector<Vec4i> hierarchy;

  /// Detect edges using canny
  Canny( src_gray, canny_output, thresh, thresh*2, 3 );
  /// Find contours
  findContours( canny_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0) );

  /// Draw contours
  Mat drawing = Mat::zeros( canny_output.size(), CV_8UC3 );
    bool done = false;
  for( int i = 0; i< contours.size(); i++ ){
         Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );

         vector<Point> approx;
         approxPolyDP(Mat(contours[i]), approx, 3, true);
      if (approx.size() > 3 && approx.size() < 10) {
          
          drawContours( drawing, contours, i, color, 2, 8, hierarchy, 0, Point() );
          Scalar colorR = Scalar( 0,255,244);
          RotatedRect rrect = minAreaRect(contours[i]);
          Point2f vertex[4];
          rrect.points(vertex);
          for (int j = 0; j < 4; j++)
          {
              line(drawing, vertex[j], vertex[(j + 1) % 4], colorR, 2);
          }
          if (done){
              continue;
          }
          if (rrect.size.width > 20 && rrect.size.height > 20) {
             // done = true;
              Scalar colorT = Scalar( 255,255,0);
              for (int j = 0; j < 4; j++)
              {
                  line(drawing, vertex[j], vertex[(j + 1) % 4], colorT, 4);
                  line(output, vertex[j], vertex[(j + 1) % 4], colorT, 2);
              }
              char szText[100];
              sprintf(szText, "%4.2f", abs(rrect.angle));
              Point2f endPoint;
              endPoint.x =rrect.center.x + 40;
              endPoint.y =rrect.center.y + 0;
              putText(output, szText, endPoint, 0, 1.0,  colorT, 2);
              endPoint.x =rrect.center.x + 40;
              endPoint.y =rrect.center.y + 30;
              sprintf(szText, "(%4.2f,%4.2f)", rrect.center.x, rrect.center.y);
              putText(output, szText, endPoint, 0, 1.0,  colorT, 2);
              
              
              endPoint.x =rrect.center.x + 200;
              endPoint.y =rrect.center.y + 0;
              line(output, rrect.center, endPoint, colorT, 1);
              
              endPoint.x =rrect.center.x - 200*cos((rrect.angle)/3.1415926);
              endPoint.y =rrect.center.y - 200*sin((rrect.angle)/3.1415926);
              line(output, rrect.center, endPoint, colorT, 1);
              
              imshow( "Results", output );
          }
      }

     }

  /// Show in a window
  namedWindow( "Contours", WINDOW_AUTOSIZE );
  imshow( "Contours", drawing );

    

}
