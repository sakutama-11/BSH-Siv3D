# pragma once
# include <Siv3D.hpp>

class SamplePoint
{
	private:
		Circle m_point;
		Line m_handle;
		// 算出可能なので消してもよい
		int m_direction;
		float m_t;

	public:
		SamplePoint( Vec2 pos );
		void setDirection(int direction);
		void setHandle();
		void draw(Color color);
};
