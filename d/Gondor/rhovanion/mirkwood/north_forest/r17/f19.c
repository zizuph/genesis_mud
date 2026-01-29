#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(13);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r16/f20",
        "southwest" : "r16/f18",
        "south" : "r16/f19",
        "northwest" : "r18/f18",
        "east" : "r17/f20",
        "north" : "r18/f19",
        "northeast" : "r18/f20",
        "west" : "r17/f18",
    ]));
    
}
