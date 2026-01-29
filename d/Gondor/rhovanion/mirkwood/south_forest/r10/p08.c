#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "path";

void create_mirkwood_south_forest_path_room() {

	add_long("The small path you are on twists its way through " +
        "the trees from the north to the southeast. ",
        ({ LIGHT_MIDDAY, LIGHT_BRIGHT }));

    add_mirkwood_exits(([
        "southwest" : "r11/f07",
        "south" : "r11/f08",
        "southeast" : "/d/Gondor/rhovanion/mirkwood/woodsmen/gairent1.c",
        "northwest" : "r09/f07",
        "east" : "r10/f09",
        "north" : "r09/p08",
        "northeast" : "r09/f09",
        "west" : "r10/f07",
    ]));
    
}
