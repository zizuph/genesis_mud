#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(79);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r07/f12",
        "southwest" : "r07/f10",
        "south" : "r07/f11",
        "northwest" : "r09/f10",
        "east" : "r08/f12",
        "north" : "r09/f11",
        "northeast" : "r09/f12",
        "west" : "r08/f10",
    ]));
    
}
