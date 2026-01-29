#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(68);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r07/f08",
        "southwest" : "r07/f06",
        "south" : "r07/f07",
        "northwest" : "r09/f06",
        "east" : "r08/f08",
        "north" : "r09/f07",
        "northeast" : "r09/f08",
        "west" : "r08/f06",
    ]));
    
}
