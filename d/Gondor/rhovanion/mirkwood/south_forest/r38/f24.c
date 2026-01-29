#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r39/f25",
        "southwest" : "r39/f23",
        "south" : "r39/f24",
        "northwest" : "r37/f23",
        "east" : "r38/f25",
        "north" : "r37/f24",
        "northeast" : "r37/f25",
        "west" : "r38/f23",
    ]));
    
}
