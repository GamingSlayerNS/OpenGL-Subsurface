#include "Curve.h"

//@author SpeedyNS
//Code only works for 8 pts
Curve::Curve()
{
}

Curve::~Curve()
{
}

void Curve::init()
{
	this->control_points_pos = {
		{ 0.0, 8.5, -2.0 },		//P0
		{ -3.0, 11.0, 2.3 },	//P1
		{ -6.0, 8.5, -2.5 },	//P2
		{ -4.0, 5.5, 2.8 },		//P3
		{ 1.0, 2.0, -4.0 },		//P4
		{ 4.0, 2.0, 3.0 },		//P5
		{ 7.0, 8.0, -2.0 },		//P6
		{ 3.0, 10.0, 3.7 }		//P7
	};
}

void Curve::calculateCurve()
{
	this->curve_points_pos = {
		{ 0.0, 8.5, -2.0 },		//P0
		{ -3.0, 11.0, 2.3 },	//P1
		{ -6.0, 8.5, -2.5 },	//P2
		{ -4.0, 5.5, 2.8 },		//P3
		{ 1.0, 2.0, -4.0 },		//P4
		{ 4.0, 2.0, 3.0 },		//P5
		{ 7.0, 8.0, -2.0 },		//P6
		{ 3.0, 10.0, 3.7 }		//P7
	};
	this->catmullMatrix = {     //Matrix from Powerpoint for catmull multiplication
		{ -0.5, 1.5, -1.5, 0.5},
		{ 1.0, -2.5, 2, -0.5},
		{ -0.5, 0.0, 0.5, 0.0},
		{ 0.0, 1.0, 0.0, 0.0}
	};

    //Create the points matrix
    for (int i = 0; i < curve_points_pos.size(); i++)
    {
        if(i == 0)
        {
            point1 = curve_points_pos[curve_points_pos.size() - 1];
            point2 = curve_points_pos[i];
            point3 = curve_points_pos[i + 1];
            point4 = curve_points_pos[i + 2];

        }
        else if(i == curve_points_pos.size() - 2)
        {
            point1 = curve_points_pos[i - 1];
            point2 = curve_points_pos[i];
            point3 = curve_points_pos[i + 1];
            point4 = curve_points_pos[0];

        }
        else if (i == curve_points_pos.size() - 1)
        {
            point1 = curve_points_pos[i - 1];
            point2 = curve_points_pos[i];
            point3 = curve_points_pos[0];
            point4 = curve_points_pos[1];

        }
        else
        {
            point1 = curve_points_pos[i - 1];
            point2 = curve_points_pos[i];
            point3 = curve_points_pos[i + 1];
            point4 = curve_points_pos[i + 2];
        }

        pointMatrix =
        {
                {point1[0],point1[1],point1[2] },
                {point2[0],point2[1],point2[2] },
                {point3[0],point3[1],point3[2] },
                {point4[0],point4[1],point4[2] }
        };

        for (int t = 1; t < num_points_per_segment; t++)
        {
            time = (double) t / (double) num_points_per_segment;
            this->timeMatrix = { time * time * time, time * time, time, 1.0 };

            tempMatrix = catmullMatrix * timeMatrix;
            tempPoint = pointMatrix * tempMatrix;
            this->points.push_back(tempPoint);
        }
    }

    curve_points_pos.clear();
    for (int i = 0; i < points.size(); i++)  //tot_points*curve_points_pos.size()
    {
        this->curve_points_pos.push_back(points[i]);
    }
}