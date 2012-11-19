#ifndef __GLOBALCONSTS__
#define __GLOBALCONSTS__

class GlobalConsts {
public:
	static const int MAX_WIDTH= 79;
	static const int MAX_HEIGHT= 24;
	enum MapObjectType {
		Empty,
		Wall,
		Legened,
		Food,
		Quiver,
		Bomb
	};

};
#endif

