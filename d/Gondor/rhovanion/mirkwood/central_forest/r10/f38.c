#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(3);
    set_spider_nest_chance(30);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r09/f39",
        "southwest" : "r09/f37",
        "south" : "r09/f38",
        "northwest" : "r11/f37",
        "east" : "r10/f39",
        "north" : "r11/f38",
        "northeast" : "r11/f39",
        "west" : "r10/f37",
    ]));
    
}
