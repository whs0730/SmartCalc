#pragma once
//函数采样模块：为函数绘图提供采样
#include <vector>
using namespace std;
// 一个采样点由横坐标 x 和纵坐标 y 组成。
struct SamplePoint {
    double x;
    double y;
};

// 函数采样类：在闭区间内等距离生成绘图坐标点。
class FunctionSampler {
public:
    vector<SamplePoint> sample(double start,double end,int pointCount,double (*function)(double)) const;
};
