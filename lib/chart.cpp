#include "chart.h"

Chart::Chart()
{
}

Chart::~Chart() {}

double Chart::findMax(QVector<double>& v) const
{
    double max = INT_MIN;
    for(int i=0; i<v.size(); i++) {
        if(v[i] > max)
            max = v[i];
    }
    return max;
}

double Chart::totalSum(QVector<double> &v) const
{
    double sum = 0;
    for(int i=0; i<v.size(); i++)
        sum += v[i];
    return sum;
}
