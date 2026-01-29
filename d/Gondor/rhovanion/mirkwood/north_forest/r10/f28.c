#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(26);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r09/f29",
        "southwest" : "r09/f27",
        "south" : "r09/f28",
        "northwest" : "r11/f27",
        "east" : "r10/f29",
        "north" : "r11/f28",
        "northeast" : "r11/f29",
        "west" : "r10/f27",
    ]));
    
}
