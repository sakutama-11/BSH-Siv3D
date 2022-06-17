# include "SamplePoint.hpp"

//SamplePoint::SamplePoint(Boundary boundary, Vec2 pos)
//{
//	m_boundary = boundary;
//	// calc t from Boundary.line and pos
//
//	m_point = Circle(pos, 6);
//	m_direction = 0;
//
//	static const double pi = 3.141592653589793;
//	m_handle = Line(pos, pos + Vec2(6 * std::cos(2 * pi / 360 * m_direction), 6 * std::sin(2 * pi / 360 * m_direction));
//}

SamplePoint::SamplePoint(Vec2 pos)
{
	m_point = Circle(pos, 6);
	m_direction = 0;
	
	m_handle = Line(pos, pos + Vec2(10 * std::cos(2 * Math::Pi / 360 * m_direction), 10 * std::sin(2 * Math::Pi / 360 * m_direction)));
	m_t = 0;
}

void SamplePoint::setDirection(int direction)
{
	m_direction = direction;
	setHandle();
}

void SamplePoint::setHandle()
{
	Vec2 pos = m_handle.begin;
	m_handle.set(pos, pos + Vec2(6 * std::cos(2 * Math::Pi / 360 * m_direction), 6 * std::sin(2 * Math::Pi / 360 * m_direction)));
}

void SamplePoint::draw(Color color)
{
	m_handle.draw(2, color);
	m_point.draw(color);
}
