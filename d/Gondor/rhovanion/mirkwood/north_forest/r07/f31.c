#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(14);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r06/f32",
        "southwest" : "r06/f30",
        "south" : "r06/f31",
        "northwest" : "r08/f30",
        "east" : "r07/f32",
        "north" : "r08/f31",
        "northeast" : "r08/f32",
        "west" : "r07/f30",
    ]));
    
}
