# include "stdafx.h"
# include "Boundary.hpp"

Boundary::Boundary(Line const line)
{
	m_line = line;
}

s3d::Line Boundary::getLine()
{
	return m_line;
}

s3d::Array<SamplePoint> Boundary::getSamplePoints()
{
	return m_sample_points;
}

void Boundary::addSamplePoint(SamplePoint& sample)
{
	if (!m_samplr_points) {
		m_sample_points = s3d::Array<SamplePoint>();
	}
	m_sample_points << sample;
}

void Boundary::setColor(s3d::Color color)
{
	m_color = color;
}

void Boundary::draw()
{
	m_line.draw(4, Palette::Orange);
}
