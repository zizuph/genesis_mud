#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(14);

    set_distance_to_edge(8);
    add_mirkwood_exits(([
        "southeast" : "r09/f32",
        "southwest" : "r09/f30",
        "south" : "r09/f31",
        "northwest" : "r07/f30",
        "east" : "r08/f32",
        "north" : "r07/f31",
        "northeast" : "r07/f32",
        "west" : "r08/f30",
    ]));
    
}
