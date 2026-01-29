#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(97);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r05/m25",
        "southwest" : "r05/m23",
        "south" : "r05/m24",
        "northwest" : "r07/f23",
        "east" : "r06/m25",
        "north" : "r07/f24",
        "northeast" : "r07/f25",
        "west" : "r06/f23",
    ]));
    
}
