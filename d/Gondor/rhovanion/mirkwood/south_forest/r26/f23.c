#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r27/f24",
        "southwest" : "r27/f22",
        "south" : "r27/f23",
        "northwest" : "r25/f22",
        "east" : "r26/f24",
        "north" : "r25/f23",
        "northeast" : "r25/f24",
        "west" : "r26/f22",
    ]));
    
}
