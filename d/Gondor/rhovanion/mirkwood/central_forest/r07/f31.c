#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(83);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r06/m32",
        "southwest" : "r06/m30",
        "south" : "r06/m31",
        "northwest" : "r08/f30",
        "east" : "r07/f32",
        "north" : "r08/f31",
        "northeast" : "r08/f32",
        "west" : "r07/f30",
    ]));
    
}
