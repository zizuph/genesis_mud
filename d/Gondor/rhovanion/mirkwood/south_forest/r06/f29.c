#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(18);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r07/f30",
        "southwest" : "r07/f28",
        "south" : "r07/f29",
        "northwest" : "r05/f28",
        "east" : "r06/f30",
        "north" : "r05/f29",
        "northeast" : "r05/f30",
        "west" : "r06/f28",
    ]));
    
}
