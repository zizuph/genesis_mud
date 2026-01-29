#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "path";

void create_mirkwood_south_forest_path_room() {

	add_long("The small path you are on twists its way through " +
        "the trees from the north to the southeast. ",
        ({ LIGHT_MIDDAY, LIGHT_BRIGHT }));

add_mirkwood_exits(([
        "southwest" : "r04/f07",
		"southeast" : "/d/Gondor/rhovanion/mirkwood/woodsmen/weanting1",
        "south" : "r04/f08",
        "northwest" : "r02/f07",
        "east" : "r03/f09",
        "north" : "r02/p08",
        "northeast" : "r02/f09",
        "west" : "r03/f07",
    ]));
    
}
