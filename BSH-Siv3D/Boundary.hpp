#pragma once

# include <Siv3D.hpp>
# include "SamplePoint.hpp"

class Boundary
{
	private:
		s3d::Line m_line;
		s3d::Array<SamplePoint> m_sample_points;
		s3d::Color m_color;

	public:
		Boundary(Line const line);
		s3d::Line getLine();
		s3d::Array<SamplePoint> getSamplePoints();
		void addSamplePoint(Vec2 pos);
		void addSamplePoint(SamplePoint& sample);
		void setColor(s3d::Color color);
		void draw();
};
