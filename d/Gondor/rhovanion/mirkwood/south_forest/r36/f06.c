#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r37/f07",
        "southwest" : "r37/f05",
        "south" : "r37/f06",
        "northwest" : "r35/f05",
        "east" : "r36/f07",
        "north" : "r35/f06",
        "northeast" : "r35/f07",
        "west" : "r36/f05",
    ]));
    
}
