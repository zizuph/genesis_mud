#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(8);
    add_mirkwood_exits(([
        "southeast" : "r26/f24",
        "southwest" : "r26/f22",
        "south" : "r26/f23",
        "northwest" : "r24/f22",
        "east" : "r25/f24",
        "north" : "r24/f23",
        "northeast" : "r24/f24",
        "west" : "r25/f22",
    ]));
    
}
