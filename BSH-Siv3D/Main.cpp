# include <Siv3D.hpp> // OpenSiv3D v0.6.4
# include "Boundary.hpp"
# include "SamplePoint.hpp"

void Main()
{
	// 背景の色を設定
	Scene::SetBackground(ColorF{ 0, 0, 0 });
	Array<Line> lines;
	Array<Circle> circles;

	Array<Boundary> boundaries;

	bool lineOpen = false;
	SamplePoint defaultSample = SamplePoint(Vec2(0, 0));
	SamplePoint* selectedSample = &defaultSample;
	Vec2 startPos;

	while (System::Update())
	{

		// ハンドル操作中のサンプルがある場合
		if (selectedSample != &defaultSample)
		{
			if (MouseL.down())
			{
				selectedSample = &defaultSample;
			}
			else
			{
				selectedSample->setDirectionByPos(Cursor::Pos());
			}
		}

		else if (MouseR.down())
		{
			// 線上を右クリックで境界を削除
			boundaries.remove_if([](const Boundary& b) {
				return Line(b.getLine().closest(Cursor::Pos()), Cursor::Pos()).length() < 2;
			});
		}
		else if (MouseL.down())
		{
			// 新しい線分の追加中
			if (lineOpen)
			{
				// 右クリックで境界を決定
				Line l = Line(startPos, Cursor::Pos());
				Boundary b = Boundary(l);
				boundaries << b;
				lineOpen = false;
			}
			else
			{
				// サンプルをクリックで内外方向を変更
				for ( auto& b : boundaries) {
					for (auto& p : b.getSamplePoints()) {
						if (p.getCircle().leftClicked())
						{
							selectedSample = &p;
							break;
						}
					}
				}
				// 境界上をクリックでサンプルポイントを追加 
				if (selectedSample == &defaultSample) {
					bool putSample = false;
					for (auto& b : boundaries) {
						if (Line(b.getLine().closest(Cursor::Pos()), Cursor::Pos()).length() < 6)
						{
							b.addSamplePoint(b.getLine().closest(Cursor::Pos()));
							putSample = true;
							break;
						}
					}

					// 何もないところをクリックで新しい境界を追加
					if (!putSample)
					{
						startPos = Cursor::Pos();
						lineOpen = true;
					}
				}
			}
		}

		// drawing
		if (lineOpen)
		{
			// 新しい境界を描画
			Line(startPos, Cursor::Pos()).draw(4, Palette::Red);
		}
		// 境界の交点を計算
		Array<Vec2> points;
        for (int i = 0; i < boundaries.size(); i++)
        {
            for (int j = i+1; j < boundaries.size(); j++)
            {
				auto pos = boundaries[i].getLine().intersectsAt(boundaries[j].getLine());
				if (pos.has_value()) {
					points << pos.value();
				}
            }
        }
		// 交点が時計回りに並ぶように極座標で整列
		std::sort(points.begin(), points.end(), [](auto const& left, auto const& right) {
			return std::atan2((left - Scene::Center()).y, (left - Scene::Center()).x) < std::atan2((right - Scene::Center()).y, (right - Scene::Center()).x);
		});

		// ポリゴンを描画
		Polygon(points).draw(Palette::Red);

		// 境界を描画
		for (auto& b : boundaries)
		{
			b.draw();
		}
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
