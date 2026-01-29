#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r39/f27",
        "southwest" : "r39/f25",
        "south" : "r39/f26",
        "northwest" : "r37/f25",
        "east" : "r38/f27",
        "north" : "r37/f26",
        "northeast" : "r37/f27",
        "west" : "r38/f25",
    ]));
    
}
