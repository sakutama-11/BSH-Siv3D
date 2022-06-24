# include "SamplePoint.hpp"
# include "Boundary.hpp"

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

SamplePoint::SamplePoint(Vec2 pos, Boundary* boundary)
{
	m_boundary = boundary;
	m_point = Circle(pos, 6);
	m_color = boundary->getColor();
	m_direction = 0;
	m_handle = Line();
	setHandle();
	m_t = 0;
}

Vec2 SamplePoint::getPos()
{
	return m_point.center;
}

Circle SamplePoint::getCircle()
{
	return m_point;
}

float SamplePoint::getDirection()
{
	return m_direction;
}

void SamplePoint::setDirection(float direction)
{
	m_direction = direction;
	setHandle();
}

void SamplePoint::setHandle()
{
	Vec2 pos = m_point.center;
	m_handle.set(pos, pos + Vec2(8 * std::cos(m_direction), 8 * std::sin(m_direction)));
}

void SamplePoint::draw()
{
	m_handle.draw(2, m_color);
	m_point.draw(m_color);
}

void SamplePoint::setPos(Vec2 pos)
{
	m_point.setCenter(pos);
	setHandle();
}

void SamplePoint::setDirectionByPos(Vec2 pos)
{
	Vec2 dir = pos - m_point.center;
	m_direction = std::atan2(dir.y, dir.x);
	setHandle();
}
