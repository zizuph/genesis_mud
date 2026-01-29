#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(8);
    add_mirkwood_exits(([
        "southeast" : "r25/f24",
        "southwest" : "r25/f22",
        "south" : "r25/f23",
        "northwest" : "r23/f22",
        "east" : "r24/f24",
        "north" : "r23/f23",
        "northeast" : "r23/f24",
        "west" : "r24/f22",
    ]));
    
}
