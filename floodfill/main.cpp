#include <vector>
#include <opencv2/opencv.hpp>
using namespace cv;

struct RGBcell{
    unsigned char c[3];

    RGBcell(unsigned char red, unsigned char green, unsigned char blue){
        c[0] = red;
        c[1] = green;
        c[2] = blue;
    }

    bool operator==(RGBcell color){
        return (c[0] == color.c[0] && c[1] == color.c[1] && c[2] == color.c[2]);
    }

    double dist(){
        return sqrt(c[0]*c[0] + c[1]*c[1] + c[2]*c[2]);
    }

    double operator <<(RGBcell o){
        auto r = abs(c[0] - o.c[0]);
        auto g = abs(c[1] - o.c[1]);
        auto b = abs(c[2] - o.c[2]);
        return sqrt(r*r + g*g + b*b);
    } 
};

Mat floodFill(Mat image, std::pair<unsigned int, unsigned int> pxy, RGBcell color){
    Mat aux = image.clone();
    auto p = (unsigned char*)aux.data;
    int rows = image.rows;
    int cols = image.cols;
    int ch = image.channels();
    Mat pintada = Mat(rows, cols, CV_8UC3);
    unsigned int point = (pxy.second - 1)*cols*ch + (pxy.first - 1)*ch;
    auto pant = (unsigned char*)pintada.data;
    RGBcell past(p[point + 2], p[point + 1], p[point]);
    pant[point] = color.c[2];
    pant[point + 1] = color.c[1];
    pant[point + 2] = color.c[0];
    Mat pintando = pintada.clone();
    auto pact = (unsigned char*)pintando.data;
    do{
        pintada.deallocate();
        pintada = pintando.clone();
        pant = (unsigned char*)pintada.data;
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                RGBcell check(pant[i*cols*ch + j*ch + 2], pant[i*cols*ch + j*ch + 1], pant[i*cols*ch + j*ch]);
                if(check == color){
                    for(int l = -1; l < 2; l++){
                        for(int c = -1; c < 2; c++){
                            if(l == 0 || c == 0){
                                if(l + i >= 0 && l + i < rows){
                                    if(c + j >= 0 && c + j < cols){
                                        unsigned int actual = (i+l)*cols*ch + (j+c)*ch;
                                        RGBcell actualPix(p[actual + 2], p[actual + 1], p[actual]);
                                        if(actualPix == past){
                                            pact[actual + 2] = color.c[0];
                                            pact[actual + 1] = color.c[1];
                                            pact[actual] = color.c[2];
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    } while(!(sum(pintando != pintada) == Scalar(0,0,0,0)));

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            RGBcell check(pant[i*cols*ch + j*ch + 2], pant[i*cols*ch + j*ch + 1], pant[i*cols*ch + j*ch]);
            if(check == color){
                unsigned int actual = i*cols*ch + j*ch;
                p[actual + 2] = color.c[0];
                p[actual + 1] = color.c[1];
                p[actual] = color.c[2];
            }
        }
    }

    return aux;
}

int main(){
    Mat image = imread("../img4.png", IMREAD_COLOR);
    auto flooded = floodFill(image, std::pair(100u, 100u), RGBcell(0, 0, 255));
    imshow("Original", image);
    imshow("Flooded", flooded);
    waitKey();
}