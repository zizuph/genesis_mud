#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r36/f07",
        "southwest" : "r36/f05",
        "south" : "r36/f06",
        "northwest" : "r34/f05",
        "east" : "r35/f07",
        "north" : "r34/f06",
        "northeast" : "r34/f07",
        "west" : "r35/f05",
    ]));
    
}
