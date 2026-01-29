#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(3);
    set_spider_nest_chance(38);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r16/f32",
        "southwest" : "r16/f30",
        "south" : "r16/f31",
        "northwest" : "r18/f30",
        "east" : "r17/f32",
        "north" : "r18/f31",
        "northeast" : "r18/f32",
        "west" : "r17/f30",
    ]));
    
}
