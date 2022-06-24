# include <Siv3D.hpp>

# include "Boundary.hpp"

Boundary::Boundary(Line const line)
{
	m_line = line;
	m_color = RandomColor();
}

Line Boundary::getLine() const
{
	return m_line;
}

Color Boundary::getColor() const
{
	return m_color;
}

void Boundary::setColor(Color color)
{
	m_color = color;
}

void Boundary::draw() const
{
	m_line.draw(4, m_color);
}
