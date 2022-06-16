# include "stdafx.h"

SamplePoint::SamplePoint(Boundary boundary, Vec2 pos)
{
	m_boundary = boundary;
	// calc t from Boundary.line and pos

	m_point = s3d::Circle(pos, 6);
	m_direction = 0;

	static const double pi = 3.141592653589793;
	m_handle = s3d::Line(pos, pos + Vec2(6 * std::cos(2 * pi / 360 * m_direction), 6 * std::sin(2 * pi / 360 * m_direction));
}

SamplePoint::setDirection(int direction)
{
	m_direction = direction;
	setHandle();
}

SamplePoint::setHandle()
{
	m_direction = direction;
	Vec2 pos = m_handle.begin;
	m_handle.set(pos, pos + Vec2(6 * std::cos(2 * pi / 360 * m_direction), 6 * std::sin(2 * pi / 360 * m_direction));
}

SamplePoint::draw()
{
	m_handle.draw(1, s3d::Palette::Black);
	m_point.draw(s3d::Palette::Red);

}
