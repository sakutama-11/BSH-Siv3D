# include <Siv3D.hpp> // OpenSiv3D v0.6.4
# include "Boundary.hpp"
# include "SamplePoint.hpp"

void Main()
{
	// 背景の色を設定 | Set background color
	Scene::SetBackground(ColorF{ 0, 0, 0 });
	Array<Line> lines;
	Array<Circle> circles;

	Array<Boundary> boundaries;
	Array<SamplePoint> samplePoints;

	bool lineOpen = false;
	Vec2 startPos;

	while (System::Update())
	{
        // draw lines
		if (MouseR.down())
		{
				lines.remove_if([](const Line& l) {
					return Line(l.closest(Cursor::Pos()), Cursor::Pos()).length() < 2;
				});
		}
		else if (MouseL.down())
		{
			if (lineOpen)
			{
				Line l = Line(startPos, Cursor::Pos());
				Boundary b = Boundary(l);
				boundaries << b;
				lineOpen = false;
			}
			else
			{
				bool putSample = false;
				for (const auto& l : lines) {
					if ( Line(l.closest(Cursor::Pos()), Cursor::Pos()).length() < 6
						)
					{
						circles << Circle(l.closest(Cursor::Pos()), 4);
						putSample = true;
					}
				}
				
				if (!putSample)
				{
					startPos = Cursor::Pos();
					lineOpen = true;
				}
			}
		}
		if (lineOpen)
		{
			Line(startPos, Cursor::Pos()).draw(4, Palette::Red);
		}
		for (auto& b : boundaries)
		{
			b.draw();
		}
		for (const auto& c : circles)
		{
			c.draw(Palette::Red);
		}

		// calculate intersections
		Array<Vec2> points;
        for (int i = 0; i < lines.size(); i++)
        {
            for (int j = i+1; j < lines.size(); j++)
            {
				auto pos = lines[i].intersectsAt(lines[j]);
				if (pos.has_value()) {
					points << pos.value();
				}
            }
        }
		// sort points by arctan so that points are aligned by clockwise
		std::sort(points.begin(), points.end(), [](auto const& left, auto const& right) {
			return std::atan2((left - Scene::Center()).y, (left - Scene::Center()).x) < std::atan2((right - Scene::Center()).y, (right - Scene::Center()).x);
		});

		// draw polygon
		Polygon(points).draw(Palette::Red);
	}
}

//
// - Debug ビルド: プログラムの最適化を減らす代わりに、エラーやクラッシュ時に詳細な情報を得られます。
//
// - Release ビルド: 最大限の最適化でビルドします。
//
// - [デバッグ] メニュー → [デバッグの開始] でプログラムを実行すると、[出力] ウィンドウに詳細なログが表示され、エラーの原因を探せます。
//
// - Visual Studio を更新した直後は、プログラムのリビルド（[ビルド]メニュー → [ソリューションのリビルド]）が必要です。
//
// Siv3D リファレンス
// https://zenn.dev/reputeless/books/siv3d-documentation
//
// Siv3D Reference
// https://zenn.dev/reputeless/books/siv3d-documentation-en
//
// Siv3D コミュニティへの参加（Slack や Twitter, BBS で気軽に質問や情報交換ができます）
// https://zenn.dev/reputeless/books/siv3d-documentation/viewer/community
//
// Siv3D User Community
// https://zenn.dev/reputeless/books/siv3d-documentation-en/viewer/community
//
// 新機能の提案やバグの報告 | Feedback
// https://github.com/Siv3D/OpenSiv3D/issues
//
// Sponsoring Siv3D
// https://github.com/sponsors/Reputeless
//
