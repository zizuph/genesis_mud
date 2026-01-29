#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(25);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r06/f46",
        "southwest" : "r06/f44",
        "south" : "r06/f45",
        "northwest" : "r08/f44",
        "east" : "r07/f46",
        "north" : "r08/f45",
        "northeast" : "r08/f46",
        "west" : "r07/f44",
    ]));
    
}
