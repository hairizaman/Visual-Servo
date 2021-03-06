//
// Created by xcy on 19-6-4.
//
//To Do
// overexposure image has no radon transform
#include "Detector.h"
#include <ctime>

int main(int argc, char *argv[])
{
    cv::Mat test_image = cv::imread(argv[1]);
    if(test_image.empty())
    {
        cout<<"unable to load image"<<endl;
        return -1;
    }
    int radonAngleRange=63,radonOperation=radon::RT_SUM;
    Detector knife_detector(true,true,false);
    knife_detector.radonAngleRange=radonAngleRange;
    knife_detector.radonOperation=radonOperation;
    std::clock_t c_start = std::clock();
    std::vector<cv::Point> knife_trace=knife_detector.get_knifeTrace(test_image);
    std::clock_t c_end = std::clock();
    long double time_elapsed_ms =1000.0*(c_end-c_start) / CLOCKS_PER_SEC;
    cout<<"result x:"<<knife_detector.beginPoint.x<<"result y:"<<knife_detector.beginPoint.y<<endl;
    std::cout << "CPU time used: " << time_elapsed_ms << " ms\n";
    std::vector<cv::Point> segments=knife_detector.get_traceSegments(knife_trace,10);
    std::cout<<"the segments numbers:"<<segments.size()<<std::endl;
    for(auto & segment : segments)
    {
        cout<<segment.x<<segment.y<<endl;
    }/*
    cv::Point   kinfe_beginPoint=knife_detector.get_BeginPoint(test_image);
    cout<<"result x:"<<knife_detector.beginPoint.x<<"result y:"<<knife_detector.beginPoint.y<<endl;*/
    return 0;
}
