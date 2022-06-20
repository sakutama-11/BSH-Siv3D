# include <Siv3D.hpp> // OpenSiv3D v0.6.4
# include "Boundary.hpp"
# include "SamplePoint.hpp"
#include "State.h"

SamplePoint* findSamplePoint(Array<Boundary>& boundaries)
{
	// サンプルをクリックで内外方向を変更
	for (auto& b : boundaries) {
		for (auto& p : b.getSamplePoints()) {
			if (p.getCircle().leftClicked())
			{
				return &p;
			}
		}
	}
	return nullptr;
}

Boundary* findBoundaryByPos(Vec2 pos, Array<Boundary>& boundaries)
{
	for (auto& b : boundaries) {
		if (Line(b.getLine().closest(pos), pos).length() < 6)
		{
			return &b;
		}
	}
	return nullptr;
}

void Main()
{
	// 背景の色を設定
	Scene::SetBackground(ColorF{ 0, 0, 0 });
	Array<Line> lines;
	Array<Circle> circles;

	Array<Boundary> boundaries;

	bool lineOpen = false;
	SamplePoint* selectedSample = nullptr;
	Vec2 startPos;
	State state = State::none;

	while (System::Update())
	{
		switch (state)
		{
			case State::none:
				if (MouseL.down())
				{
					// サンプルをクリックで内外方向を変更
					SamplePoint* clickedPoint = findSamplePoint(boundaries);
					if (clickedPoint)
					{
						selectedSample = clickedPoint;
						state = State::sampleSelecting;
						break;
					}

					// 境界をクリックで内外方向を変更
					Boundary* b = findBoundaryByPos(Cursor::Pos(), boundaries);
					if (b)
					{
						b->addSamplePoint(b->getLine().closest(Cursor::Pos()));
						break;
					}

					// 何もないところをクリックで新しい境界を追加
					startPos = Cursor::Pos();
					state = State::lineDrawing;
					break;
				}
				else if (MouseR.down())
				{
					// 線上を右クリックで境界を削除
					boundaries.remove_if([](const Boundary& b) {
						return Line(b.getLine().closest(Cursor::Pos()), Cursor::Pos()).length() < 2;
					});
					break;
				}
				break;
			// サンプルが選択されているとき
			case State::sampleSelecting:
				if (MouseL.down())
				{
					// 左クリックでサンプルポイントの方向を固定
					selectedSample = nullptr;
					state = State::none;
					break;
				}
				// サンプルの方向を更新
				selectedSample->setDirectionByPos(Cursor::Pos());
				break;
			// 新しい線の描画中
			case State::lineDrawing:
				if (MouseL.down())
				{
					// 左クリックで境界を決定
					Line l = Line(startPos, Cursor::Pos());
					Boundary b = Boundary(l);
					boundaries << b;
					state = State::none;
				}
				// 新しい境界を描画
				Line(startPos, Cursor::Pos()).draw(4, Palette::Red);
				break;
			default:
				break;
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
