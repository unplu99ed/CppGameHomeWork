#ifndef __GLOBALCONSTS__
#define __GLOBALCONSTS__

class GlobalConsts {
public:
	static const int MAX_LENGHT= 79;
	static const int MAX_WIDHT= 24;
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