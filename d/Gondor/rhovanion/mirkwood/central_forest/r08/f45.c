#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(19);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r07/f46",
        "southwest" : "r07/f44",
        "south" : "r07/f45",
        "northwest" : "r09/f44",
        "east" : "r08/f46",
        "north" : "r09/f45",
        "northeast" : "r09/f46",
        "west" : "r08/f44",
    ]));
    
}
