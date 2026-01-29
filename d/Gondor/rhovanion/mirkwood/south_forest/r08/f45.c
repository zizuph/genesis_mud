#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(14);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r09/f46",
        "southwest" : "r09/f44",
        "south" : "r09/f45",
        "northwest" : "r07/f44",
        "east" : "r08/f46",
        "north" : "r07/f45",
        "northeast" : "r07/f46",
        "west" : "r08/f44",
    ]));
    
}
