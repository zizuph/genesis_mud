#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(19);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r07/f32",
        "southwest" : "r07/f30",
        "south" : "r07/f31",
        "northwest" : "r09/f30",
        "east" : "r08/f32",
        "north" : "r09/f31",
        "northeast" : "r09/f32",
        "west" : "r08/f30",
    ]));
    
}
