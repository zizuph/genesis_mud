#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(13);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r09/f31",
        "southwest" : "r09/f29",
        "south" : "r09/f30",
        "northwest" : "r11/f29",
        "east" : "r10/f31",
        "north" : "r11/f30",
        "northeast" : "r11/f31",
        "west" : "r10/f29",
    ]));
    
}
