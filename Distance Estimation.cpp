#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <math.h>
#include <sstream>
#include <iostream>
#include <math.h>

using namespace cv;
using namespace std;

#define PI 3.14159265
#define d 7.1                          //this is the distance between the cameras in cm
#define viewangle_left PI/3.0          
#define viewangle_right PI/3.0                 

Point spatialpoint(Mat img)
{
    Mat gray;
    size_t o=0;
    cvtColor(img, gray, COLOR_BGR2GRAY);
    // smooth it, otherwise a lot of false circles may be detected
    GaussianBlur( gray, gray, Size(9, 9), 2, 2 );
    vector<Vec3f> circles;
    HoughCircles(gray, circles, HOUGH_GRADIENT,
                 2, gray.rows/4, 2, 100);
    for( size_t i = 0; i < circles.size(); i++ )
    {
         Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
         int radius = cvRound(circles[i][2]);
         Point text1(cvRound(circles[i][0])+2, cvRound(circles[i][1])+2);
         // draw the circle center
         circle( img, center, 3, Scalar(0,0,255), -1, 8, 0 );
         // draw the circle outline
         circle( img, center, radius, Scalar(0,0,255), 3, 8, 0 );

         string mystring;
         stringstream mystream;
         mystream << i;
         mystring = mystream.str();

         putText( img, mystring, text1, FONT_HERSHEY_COMPLEX, 1, Scalar(0, 0, 0), 5, 8 );

    }
    namedWindow( "circles", 1 );
    imshow( "circles", img );
    waitKey(0);
    cout << "Enter the number corresponding to the spatial point." << endl;
    cin >> o;
    Point sp;

    for( size_t i = 0; i < circles.size(); i++ )
    {
         Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        if (i==o)
        {
            sp = center;
        }
    }
    return sp;
}

int main()
{
    Mat img_left , img_right;
    img_left = imread("ball.jpeg");//the image from left camera
    img_right = imread("ball.jpeg");//the image from right camera

    Point sp_left , sp_right;

    sp_left = spatialpoint(img_left);
    cout << sp_left << endl;
    sp_right = spatialpoint(img_right);
    cout << sp_right;

    width_left = img_left.cols;
    width_right = img_right.cols;

    p_left = sp_left[1];
    p_right = sp_right[1];

    double alpha1 = 0;
    double alpha2 = 0;

    double r = 0.0; //Distance to be calculated!!

    if(p_left > width_left/2.0 && p_right < width_right/2.0)
    {
        //when the object is between both cameras
        double tan_alpha2 = ((p_right/2.0 - width_right)/(p_right/2.0)) * tan(viewangle_right);
        alpha2 = atan(tan_alpha2);
        double angle2 =  PI/2.0 - alpha2;
        double tan_alpha1 =((width_left - p_left/2.0)/(p_left/2.0)) * tan(viewangle_left);
        alpha1 = atan(tan_alpha1);
        double angle1 = PI/2.0 - alpha1;
        r = ((tan(angle1)*tan(angle2))/(tan(angle1) + tan(angle2))) * d;
    }
    else if(p_left < width_left/2.0 && p_right < width_right/2.0)
    {
        //when the object is to left of both cameras
        double tan_alpha2 = ((p_right/2.0 - width_right)/(p_right/2.0)) * tan(viewangle_right);
        alpha2 = atan(tan_alpha2);
        double angle2 =  PI/2.0 - alpha2;
        double tan_alpha1 = ((p_left/2.0 - width_left)/(p_left/2.0)) * tan(viewangle_left);
        alpha1 = atan(tan_alpha1);
        double angle1 = PI/2.0 - alpha1;
        r = (sin(angle1)*sin(angle2)*d)/(sin(alpha2-alpha1));
    }
    else if(p_left > width_left/2.0 && p_right > width_right/2.0)
    {
        //when the object is to right of both cameras
        double tan_alpha1 =((width_left - p_left/2.0)/(p_left/2.0)) * tan(viewangle_left);
        alpha1 = atan(tan_alpha1);
        double angle = PI/2.0 - alpha1;
        double tan_alpha2 = ((width_right - p_right/2.0)/(p_right/2.0)) * tan(viewangle_right);
        alpha2 = atan(tan_alpha2);
        double angle = PI/2.0 - alpha2;
        r = ((sin(angle1)*sin(angle2)*d))/sin(alpha1-alpha2);
    }
    else if(p_left == width_left/2.0)
    {
        //when the object is in front of the left camera
        double tan_alpha2 = ((p_right/2.0 - width_right)/(p_right/2.0)) * tan(viewangle_right);
        alpha2 = atan(tan_alpha2);
        double angle =  PI/2.0 - alpha2;
        r = tan(angle) * d;

    }
    else if(p_right == width_right/2.0)
    {
        //when the object is in front of the right camera
        double tan_alpha1 =((width_left - p_left/2.0)/(p_left/2.0)) * tan(viewangle_left);
        alpha1 = atan(tan_alpha1);
        double angle = PI/2.0 - alpha1;
        r = tan(angle) * d;
    }
    else
    {
        cout << "Sorry rehega";
    }
    
    return 0;
}


