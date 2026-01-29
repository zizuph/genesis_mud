#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(19);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r09/f03",
        "southwest" : "r09/f01",
        "south" : "r09/f02",
        "northwest" : "r11/f01",
        "east" : "r10/f03",
        "north" : "r11/f02",
        "northeast" : "r11/f03",
        "west" : "r10/f01",
    ]));
    
}
