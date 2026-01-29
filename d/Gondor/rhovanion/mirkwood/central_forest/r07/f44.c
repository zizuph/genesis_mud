#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(4);
    set_spider_nest_chance(46);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r06/f45",
        "southwest" : "r06/f43",
        "south" : "r06/f44",
        "northwest" : "r08/f43",
        "east" : "r07/f45",
        "north" : "r08/f44",
        "northeast" : "r08/f45",
        "west" : "r07/f43",
    ]));
    
}
