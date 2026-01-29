#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(13);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r07/f45",
        "southwest" : "r07/f43",
        "south" : "r07/f44",
        "northwest" : "r09/f43",
        "east" : "r08/f45",
        "north" : "r09/f44",
        "northeast" : "r09/f45",
        "west" : "r08/f43",
    ]));
    
}
