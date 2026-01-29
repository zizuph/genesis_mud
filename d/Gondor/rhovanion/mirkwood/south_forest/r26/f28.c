#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r27/f29",
        "southwest" : "r27/f27",
        "south" : "r27/f28",
        "northwest" : "r25/f27",
        "east" : "r26/f29",
        "north" : "r25/f28",
        "northeast" : "r25/f29",
        "west" : "r26/f27",
    ]));
    
}
