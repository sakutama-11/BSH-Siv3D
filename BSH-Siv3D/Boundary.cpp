# include <Siv3D.hpp>

# include "Boundary.hpp"

Boundary::Boundary(Vec2 begin, Vec2 end, Vec2 sceneSize)
{
	if (begin.x == end.x)
	{
		m_line = Line(begin.x, 0, end.x, sceneSize.y);
	}
	else
	{
		Rect rect(0, 0, sceneSize.x, sceneSize.y);
		Vec2 b(0, -begin.x * (end - begin).y / (end - begin).x + begin.y);
		Vec2 e(sceneSize.x, (sceneSize.x + 1.f -begin.x) * (end - begin).y / (end - begin).x + begin.y);
		Line longLine(b, e);
		if (const auto points = rect.intersectsAt(longLine))
		{
			rect.draw(Palette::Skyblue);
			m_line = Line(points.value()[0], points.value()[1]);
		}
	}
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
