#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(18);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r11/f10",
        "southwest" : "r11/f08",
        "south" : "r11/f09",
        "northwest" : "r13/f08",
        "east" : "r12/f10",
        "north" : "r13/f09",
        "northeast" : "r13/f10",
        "west" : "r12/f08",
    ]));
    
}
