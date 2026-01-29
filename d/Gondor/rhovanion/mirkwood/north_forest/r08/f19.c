#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(22);

    set_distance_to_edge(8);
    add_mirkwood_exits(([
        "southeast" : "r07/f20",
        "southwest" : "r07/f18",
        "south" : "r07/f19",
        "northwest" : "r09/f18",
        "east" : "r08/f20",
        "north" : "r09/f19",
        "northeast" : "r09/f20",
        "west" : "r08/f18",
    ]));
    
}
