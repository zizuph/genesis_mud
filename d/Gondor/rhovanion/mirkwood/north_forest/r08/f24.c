#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(3);
    set_spider_nest_chance(30);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r07/f25",
        "southwest" : "r07/f23",
        "south" : "r07/f24",
        "northwest" : "r09/f23",
        "east" : "r08/f25",
        "north" : "r09/f24",
        "northeast" : "r09/f25",
        "west" : "r08/f23",
    ]));
    
}
