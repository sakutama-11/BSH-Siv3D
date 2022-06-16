# include "stdafx.h"

# ifndef   BOUNDARY_HPP
# define   BOUNDARY_HPP

class SamplePoint;

class Boundary
{
	// variable
	private:
		s3d::Line line;
		s3d::Array<SamplePoint> sample_points;
		Color color;

	// acsessor
	public:
		Boundary( Line const line );
		s3d::Line getLine();
		s3d::Array<SamplePoint> getSamplePoints();
		void addSamplePoint(SamplePoint& sample);
		void setColor(s3d::Color color);
		void draw();
};

#endif // BOUNDARY_HPP
