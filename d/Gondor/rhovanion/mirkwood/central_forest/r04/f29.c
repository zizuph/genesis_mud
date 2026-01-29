#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(95);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r03/f30",
        "southwest" : "r03/f28",
        "south" : "r03/f29",
        "northwest" : "r05/m28",
        "east" : "r04/f30",
        "north" : "r05/m29",
        "northeast" : "r05/m30",
        "west" : "r04/f28",
    ]));
    
}
