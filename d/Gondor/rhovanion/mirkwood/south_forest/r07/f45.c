#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(19);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r08/f46",
        "southwest" : "r08/f44",
        "south" : "r08/f45",
        "northwest" : "r06/f44",
        "east" : "r07/f46",
        "north" : "r06/f45",
        "northeast" : "r06/f46",
        "west" : "r07/f44",
    ]));
    
}
