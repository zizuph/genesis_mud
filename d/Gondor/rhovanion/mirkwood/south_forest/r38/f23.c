#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r39/f24",
        "southwest" : "r39/f22",
        "south" : "r39/f23",
        "northwest" : "r37/f22",
        "east" : "r38/f24",
        "north" : "r37/f23",
        "northeast" : "r37/f24",
        "west" : "r38/f22",
    ]));
    
}
