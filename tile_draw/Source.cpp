#define ASLIB_INCLUDE_DL
#include "AsLib.hpp"

int32_t asMain()
{
	//560, 700
	MainControl mc(u8"Tile View", Pos2(720, 720));
	constexpr Pos2 w_pos2(10,10);

	//マップテクスチャ
	AsTexture under_tile_te(u8"p/under_tile.png");
	AsTexture tile_te(u8"p/tile.png", int32_t(AsTexture(u8"p/tile.png").pixelNumX()*5.0f)*2, 10);

	//マップ管理
	AsTextureMapArray tma;
	tma.push(nullptr);
	tma.push(&under_tile_te, aslib_texture_map_field_type_empty);
	tma.push(&tile_te, aslib_texture_map_field_type_wall,8);

	//マップ生成
	tma.resizeMap(w_pos2);
	tma.setLayer(2, 1);

	//tma.putMap(1, 1);
	tma.randMap(2, 0, 1);
	//tma.mazeMap(4, 0, 1);

	static PosA4F pl(1.0f, 1.0f, 1.0f, 1.0f);
	constexpr PosA4F map_p(0.0f, 0.0f, 5.0f, 10.0f);
	AsMapView mv(map_p, 'y');
	mv.setMap(w_pos2);

	const size_t count_max = 180;
	size_t count = 0;

	const size_t update_count_max = 60;
	size_t update_count = 0;

	float speed = 0.1f;

	while (asLoop())
	{
		tma.update();
		mv.draw(&tma);

		mv.setMobView(pl);
		if (asKeyUp()) pl.y -= speed;
		if (asKeyDown()) pl.y += speed;
		if (asKeyLeft()) pl.x -= speed;
		if (asKeyRight()) pl.x += speed;
		if (asKey0()) speed += 0.001f;
		if (asKey9()) speed -= 0.001f;

		++count;
		if (count >= count_max) {
			tma.randMap(2, 0, 1);
			count = 0;
		}
		++update_count;
		if (update_count >= update_count_max) {
			under_tile_te(u8"p/under_tile.png");
			tile_te(u8"p/tile.png", int32_t(AsTexture(u8"p/tile.png").pixelNumX()*5.0f)*2, 10);
			update_count = 0;
		}
	}

	return 0;
}