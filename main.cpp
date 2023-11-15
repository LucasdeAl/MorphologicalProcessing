#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <string>

using namespace std;
using namespace cv;

Mat ErosionRetangle(Mat image,std::pair<int, int> msize){
    int X = static_cast<int>(image.rows);
    int Y = static_cast<int>(image.cols);
    Mat applied = Mat(X, Y, CV_8UC1, Scalar::all(0));
    int lin = msize.first, col = msize.second;
    double size = lin*col;
    std::vector<double> kernel(size,1); 
    uint8_t* pixelImagePtr;
    uint8_t* pixelAppliedPtr;
    pixelImagePtr = (uint8_t*)image.data;
    pixelAppliedPtr = (uint8_t*)applied.data;
    int reflin = lin/2, refcol = col/2;
    for(int i = 0; i < image.rows; i++)
    {
        for(int j = 0; j < image.cols; j++)
        {
            int result = 1;
            for(int l = 0; l < lin; l++){
                for(int c = 0; c < col; c++){
                    int thisline = i + (l - reflin), thiscol = j + (c - refcol);
                    if(thisline >= 0 and thisline < image.rows){
                        if(thiscol >= 0 and thiscol < image.cols and ((int)kernel[l*col + c])==1){
                            result *= (int)((pixelImagePtr[thisline*image.cols + thiscol]/255.0) * kernel[l*col + c]);
                        }
                    }
                }
            }
            result !=0 ? pixelAppliedPtr[i*image.cols + j] = round(result * 255.0): pixelAppliedPtr[i*image.cols + j] = 0;
            }
        }
    


    String windowName = "Imagem com kernel customizado";

    namedWindow(windowName);

    imshow(windowName, applied);

    waitKey(0);

    destroyWindow(windowName);

    return applied;
}

//g++ main.cpp -o main -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc
int main(int argc, char** argv)
{
    // Read the image file as
    // imread("default.jpg");
    Mat image = imread("./images/placa.tif",IMREAD_GRAYSCALE);
  
    // Error Handling
    if (image.empty()) {
        cout << "Image File "
             << "Not Found" << endl;
  
        // wait for any key press
        cin.get();  
        return -1;
    }
   
    Mat equalized = ErosionRetangle(image,{45,45});
    //imshow("Window Name", equalized);
    
    //waitKey(0);
    return 0;
}