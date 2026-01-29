#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southeast" : "r35/f07",
        "southwest" : "r35/f05",
        "south" : "r35/f06",
        "east" : "r34/f07",
        "north" : "r33/f06",
        "northeast" : "r33/f07",
        "west" : "r34/f05",
    ]));
    
}
