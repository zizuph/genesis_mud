#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(13);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r04/f39",
        "southwest" : "r04/f37",
        "south" : "r04/f38",
        "northwest" : "r02/f37",
        "east" : "r03/f39",
        "north" : "r02/f38",
        "northeast" : "r02/f39",
        "west" : "r03/f37",
    ]));
    
}
