# include <Siv3D.hpp>

# include "Boundary.hpp"
# include "SamplePoint.hpp"

Boundary::Boundary(Line const line)
{
	m_line = line;
	m_color = s3d::RandomColor();
}

s3d::Line Boundary::getLine()
{
	return m_line;
}

s3d::Array<SamplePoint> Boundary::getSamplePoints()
{
	return m_sample_points;
}

void Boundary::addSamplePoint(Vec2 pos)
{
	SamplePoint sample = SamplePoint::SamplePoint(pos);
	if (!m_sample_points) {
		m_sample_points = s3d::Array<SamplePoint>();
	}
	m_sample_points << sample;
}

void Boundary::addSamplePoint(SamplePoint& sample)
{
	if (!m_sample_points) {
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
	m_line.draw(4, m_color);
	for (auto& sample : m_sample_points) {
		sample.draw(m_color);
	}
}
