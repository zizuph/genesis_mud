#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(79);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r05/f45",
        "southwest" : "r05/f43",
        "south" : "r05/f44",
        "northwest" : "r07/f43",
        "east" : "r06/f45",
        "north" : "r07/f44",
        "northeast" : "r07/f45",
        "west" : "r06/f43",
    ]));
    
}
