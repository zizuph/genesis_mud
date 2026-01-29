#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(14);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r09/f30",
        "southwest" : "r09/f28",
        "south" : "r09/f29",
        "northwest" : "r11/f28",
        "east" : "r10/f30",
        "north" : "r11/f29",
        "northeast" : "r11/f30",
        "west" : "r10/f28",
    ]));
    
}
