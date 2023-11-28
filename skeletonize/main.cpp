#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <string>

using namespace std;
using namespace cv;

Mat erosionRetangle(Mat image,std::pair<int, int> msize){
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
            result !=0 ? pixelAppliedPtr[i*image.cols + j] = 255: pixelAppliedPtr[i*image.cols + j] = 0;
            }
        }
    


    String windowName = "Erosão com elemento estruturante retangular";

    namedWindow(windowName);

    imshow(windowName, applied);

    waitKey(0);

    destroyWindow(windowName);

    return applied;
}

Mat dilatationRetangle(Mat image,std::pair<int, int> msize){
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
            int result = 0;
            for(int l = 0; l < lin; l++){
                for(int c = 0; c < col; c++){
                    int thisline = i + (l - reflin), thiscol = j + (c - refcol);
                    if(thisline >= 0 and thisline < image.rows){
                        if(thiscol >= 0 and thiscol < image.cols and ((int)kernel[l*col + c])==1){
                            result += (int)((pixelImagePtr[thisline*image.cols + thiscol]/255.0) * kernel[l*col + c]);
                        }
                    }
                }
            }
            result !=0 ? pixelAppliedPtr[i*image.cols + j] = 255: pixelAppliedPtr[i*image.cols + j] = 0;
            }
        }
    


    String windowName = "Dilatação com elemento estruturante retangular";

    namedWindow(windowName);

    imshow(windowName, applied);

    waitKey(0);

    destroyWindow(windowName);

    return applied;
}

Mat dilatationCircle(Mat image,Mat element){
    std::vector<uint8_t> kernel(element.data, element.data + element.total());
    int msize = kernel.size();
    int X = static_cast<int>(image.rows);
    int Y = static_cast<int>(image.cols);
    Mat applied = Mat(X, Y, CV_8UC1, Scalar::all(0));
    int lin = sqrt(msize), col = sqrt(msize);
    double size = lin*col;
    uint8_t* pixelImagePtr;
    uint8_t* pixelAppliedPtr;
    pixelImagePtr = (uint8_t*)image.data;
    pixelAppliedPtr = (uint8_t*)applied.data;
    int reflin = lin/2, refcol = col/2;
    for(int i = 0; i < image.rows; i++)
    {
        for(int j = 0; j < image.cols; j++)
        {
            int result = 0;
            for(int l = 0; l < lin; l++){
                for(int c = 0; c < col; c++){
                    int thisline = i + (l - reflin), thiscol = j + (c - refcol);
                    if(thisline >= 0 and thisline < image.rows){
                        if(thiscol >= 0 and thiscol < image.cols and ((int)kernel[l*col + c])==1){
                            result += (int)((pixelImagePtr[thisline*image.cols + thiscol]/255.0) * kernel[l*col + c]);
                        }
                    }
                }
            }
            result !=0 ? pixelAppliedPtr[i*image.cols + j] = 255: pixelAppliedPtr[i*image.cols + j] = 0;
            }
        }
    


    //String windowName = "Dilatação com elemento estruturante circular";

    //namedWindow(windowName);

    //imshow(windowName, applied);

    //waitKey(0);

    //destroyWindow(windowName);

    return applied;
}



Mat erosionCircle(Mat image,Mat element){
    std::vector<uint8_t> kernel(element.data, element.data + element.total());
    int msize = kernel.size();
    int X = static_cast<int>(image.rows);
    int Y = static_cast<int>(image.cols);
    Mat applied = Mat(X, Y, CV_8UC1, Scalar::all(0));
    int lin = sqrt(msize), col = sqrt(msize);
    double size = lin*col;
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
                        if(thiscol >= 0 and thiscol < image.cols and ((int)(kernel[l*col + c]/255))==1){
                            result *= (int)((pixelImagePtr[thisline*image.cols + thiscol]/255.0) * (kernel[l*col + c]/255));
                        }
                    }
                }
            }
            result !=0 ? pixelAppliedPtr[i*image.cols + j] = 255: pixelAppliedPtr[i*image.cols + j] = 0;
            }
        }
    


    //String windowName = "Erosão com elemento estruturante circular";

    //namedWindow(windowName);

    //imshow(windowName, applied);

    //waitKey(0);

    //destroyWindow(windowName);

    return applied;
}

Mat opening(Mat image,Mat element)
{
    Mat A = erosionCircle(image,element);
    return dilatationCircle(A,element); 
}


Mat circularStructuringElement(int radius) {
    Mat element = Mat::zeros(2 * radius + 1, 2 * radius + 1, CV_8U);
    Point center(radius, radius);
    circle(element, center, radius, Scalar(255), -1);
    return element;
}

bool ZhangSuen(Mat& img, int etapa) {
    Mat marker = Mat::zeros(img.size(), CV_8UC1);

    bool change = false;

    for (int i = 1; i < img.rows - 1; ++i) {
        for (int j = 1; j < img.cols - 1; ++j) {
            uchar p1 = img.at<uchar>(i,j);
            uchar p2 = img.at<uchar>(i - 1, j);
            uchar p3 = img.at<uchar>(i - 1, j + 1);
            uchar p4 = img.at<uchar>(i, j + 1);
            uchar p5 = img.at<uchar>(i + 1, j + 1);
            uchar p6 = img.at<uchar>(i + 1, j);
            uchar p7 = img.at<uchar>(i + 1, j - 1);
            uchar p8 = img.at<uchar>(i, j - 1);
            uchar p9 = img.at<uchar>(i - 1, j - 1);
            
            //transições de 0 para 1
            int A = (p2 == 0 && p3 == 255) + (p3 == 0 && p4 == 255) + (p4 == 0 && p5 == 255) + (p5 == 0 && p6 == 255) +
                    (p6 == 0 && p7 == 255) + (p7 == 0 && p8 == 255) + (p8 == 0 && p9 == 255) + (p9 == 0 && p2 == 255);

            //quantidade de pixels não zero em volta de p1
            int B = (p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9)/255;

            int m1 = (etapa == 0 && p2 * p4 * p6 == 0 && p4 * p6* p8 == 0 ) && (A == 1) && p1 == 255;// passo 1 de iterações
            int m2 = (etapa == 1 && p2 * p4 * p8 == 0 && p2 * p6 * p8 == 0) && (A == 1) && p1 == 255; // passo 2 de iterações

            if (B >= 2 && B <= 6 && A == 1 && m1) {
                marker.at<uchar>(i, j) = 255;
                change = true;
            }

            if (B >= 2 && B <= 6 && A == 1 && m2) {
                marker.at<uchar>(i, j) = 255;
                change = true;
            }
        }
    }

    img = img & ~marker;
    return change;
}

void skeletonize(Mat& img, int maxIter) {
    bool change1 = true;
    bool change2 = true;
    int i = 0;
    while ((change1||change2) && i < maxIter){
        change1 = ZhangSuen(img, 0);
        change2 = ZhangSuen(img,1);
        i++;
    }
}

Mat grayscaleToBinary(Mat& image,uint8_t threshold)
{
    int cn = image.channels();
    Mat bin = Mat::zeros(image.size(), CV_8UC1);

    for(int i=0;i<bin.rows;i++)
    {
        for(int j=0;j<bin.cols;j++)
        {   
            uint8_t gray = image.at<uint8_t>(i,j);

            if(gray > threshold)
            {
                bin.at<uint8_t>(i, j) = 0;
            }else
            {
                bin.at<uint8_t>(i, j) = 255;
            }   
        }
    }
    return bin;
}


//g++ main.cpp -o main -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc
int main(int argc, char** argv)
{
    
    Mat image = imread("./images/silhueta.png",IMREAD_GRAYSCALE);
    Mat bin = grayscaleToBinary(image,45);

    //Mat image = imread("./images/cavalo.jpeg",IMREAD_GRAYSCALE);
    //Mat bin = grayscaleToBinary(image,45);

    if (image.empty()) {
        cout << "Image File "
             << "Not Found" << endl;
        cin.get();  
        return -1;
    }
   
    skeletonize(bin,200);


    imshow("Imagem Skeletonizada", bin);
    waitKey(0);
    
    //waitKey(0);
    return 0;
}