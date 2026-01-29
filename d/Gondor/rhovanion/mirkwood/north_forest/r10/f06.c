#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(76);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r09/f07",
        "southwest" : "r09/f05",
        "south" : "r09/f06",
        "northwest" : "r11/f05",
        "east" : "r10/f07",
        "north" : "r11/f06",
        "northeast" : "r11/f07",
        "west" : "r10/f05",
    ]));
    
}
