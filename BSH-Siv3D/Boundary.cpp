# include <Siv3D.hpp>

# include "Boundary.hpp"
# include "SamplePoint.hpp"

Boundary::Boundary(Line const line)
{
	m_line = line;
	m_color = RandomColor();
	m_sample_points = Array<SamplePoint>();
}

Line Boundary::getLine() const
{
	return m_line;
}

Array<SamplePoint>& Boundary::getSamplePoints()
{
	return m_sample_points;
}

void Boundary::addSamplePoint(Vec2 pos)
{
	SamplePoint sample = SamplePoint::SamplePoint(pos);
	m_sample_points << sample;
}

void Boundary::addSamplePoint(SamplePoint& sample)
{
	m_sample_points << sample;
}

void Boundary::setColor(Color color)
{
	m_color = color;
}

void Boundary::draw()
{
	for (auto& sample : m_sample_points) {
		sample.draw(m_color);
	}
	m_line.draw(4, m_color);
}
