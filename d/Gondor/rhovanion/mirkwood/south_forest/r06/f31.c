#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(11);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r07/f32",
        "southwest" : "r07/f30",
        "south" : "r07/f31",
        "northwest" : "r05/f30",
        "east" : "r06/f32",
        "north" : "r05/f31",
        "northeast" : "r05/f32",
        "west" : "r06/f30",
    ]));
    
}
