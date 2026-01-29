#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r39/f18",
        "southwest" : "r39/f16",
        "south" : "r39/f17",
        "northwest" : "r37/f16",
        "east" : "r38/f18",
        "north" : "r37/f17",
        "northeast" : "r37/f18",
        "west" : "r38/f16",
    ]));
    
}
