#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r39/f31",
        "southwest" : "r39/f29",
        "south" : "r39/f30",
        "northwest" : "r37/f29",
        "east" : "r38/f31",
        "north" : "r37/f30",
        "northeast" : "r37/f31",
        "west" : "r38/f29",
    ]));
    
}
