#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(70);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r05/f20",
        "southwest" : "r05/f18",
        "south" : "r05/f19",
        "northwest" : "r07/f18",
        "east" : "r06/f20",
        "north" : "r07/f19",
        "northeast" : "r07/f20",
        "west" : "r06/f18",
    ]));
    
}
