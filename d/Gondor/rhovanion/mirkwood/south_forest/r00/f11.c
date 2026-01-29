#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "northwest" : MIRKWOOD_OLDROAD_DIR + "r05",
        "north" : MIRKWOOD_OLDROAD_DIR + "r06",
        "northeast" : MIRKWOOD_OLDROAD_DIR + "r07",

        "southeast" : "r01/f12",
        "southwest" : "r01/f10",
        "south" : "r01/f11",
        "east" : "r00/f12",
        "west" : "r00/f10",
    ]));
    
}
