#pragma once

# include <Siv3D.hpp>
# include "SamplePoint.hpp"

class Boundary
{
	private:
		Line m_line;
		Array<SamplePoint> m_sample_points;
		Color m_color;

	public:
		Boundary(Line const line);
		Line getLine() const;
		Array<SamplePoint>& getSamplePoints();
		void addSamplePoint(Vec2 pos);
		void addSamplePoint(SamplePoint& sample);
		void setColor(Color color);
		void draw();
};
