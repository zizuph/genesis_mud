#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(18);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r02/f46",
        "southwest" : "r02/f44",
        "south" : "r02/f45",
        "northwest" : "r04/f44",
        "east" : "r03/f46",
        "north" : "r04/f45",
        "northeast" : "r04/f46",
        "west" : "r03/f44",
    ]));
    
}
