#pragma once
#include <vector>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>

class Curve
{
public:
	Curve();
	~Curve();
	
	void init();
	void calculateCurve();
	
public:
	float tau = 0.5; // Coefficient for catmull-rom spline
	int num_points_per_segment = 200;

	std::vector<glm::vec3> control_points_pos;
	std::vector<glm::vec3> curve_points_pos;
	glm::mat4 catmullMatrix;
	glm::vec4 timeMatrix;
	glm::vec3 point1, point2, point3, point4;
	glm::mat4x3 pointMatrix;
	//Calulation vars
	glm::vec4 tempMatrix;
	glm::vec3 tempPoint;
	double time;
	std::vector<glm::vec3> points;
};