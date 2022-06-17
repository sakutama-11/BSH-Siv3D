# pragma once
# include <Siv3D.hpp>

class SamplePoint
{
	// variable
	private:
		s3d::Circle m_point;
		s3d::Line m_handle;
		// 算出可能なので消してもよい
		int m_direction;
		float m_t;

	// acsessor
	public:
		SamplePoint( Vec2 pos );
		void setDirection(int direction);
		void setHandle();
		void draw(s3d::Color color);
};
