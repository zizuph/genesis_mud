#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(81);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r09/f08",
        "southwest" : "r09/f06",
        "south" : "r09/f07",
        "northwest" : "r11/f06",
        "east" : "r10/f08",
        "north" : "r11/f07",
        "northeast" : "r11/f08",
        "west" : "r10/f06",
    ]));
    
}
