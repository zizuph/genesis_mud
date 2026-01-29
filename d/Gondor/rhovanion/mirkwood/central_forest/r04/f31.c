#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(81);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r03/f32",
        "southwest" : "r03/f30",
        "south" : "r03/f31",
        "northwest" : "r05/m30",
        "east" : "r04/f32",
        "north" : "r05/m31",
        "northeast" : "r05/m32",
        "west" : "r04/f30",
    ]));
    
}
