#pragma once

# include <Siv3D.hpp>

class Boundary
{
	private:
		Line m_line;
		Color m_color;

	public:
		Boundary(Line const line);
		Line getLine() const;
		Color getColor() const;
		void setColor(Color color);
		void draw() const;
};
