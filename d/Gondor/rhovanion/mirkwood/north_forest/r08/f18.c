#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(27);

    set_distance_to_edge(8);
    add_mirkwood_exits(([
        "southeast" : "r07/f19",
        "southwest" : "r07/f17",
        "south" : "r07/f18",
        "northwest" : "r09/f17",
        "east" : "r08/f19",
        "north" : "r09/f18",
        "northeast" : "r09/f19",
        "west" : "r08/f17",
    ]));
    
}
