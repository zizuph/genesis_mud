#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(13);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r11/f12",
        "southwest" : "r11/f10",
        "south" : "r11/f11",
        "northwest" : "r13/f10",
        "east" : "r12/f12",
        "north" : "r13/f11",
        "northeast" : "r13/f12",
        "west" : "r12/f10",
    ]));
    
}
