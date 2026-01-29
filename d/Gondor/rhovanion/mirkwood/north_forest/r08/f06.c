#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(52);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r07/f07",
        "southwest" : "r07/f05",
        "south" : "r07/f06",
        "northwest" : "r09/f05",
        "east" : "r08/f07",
        "north" : "r09/f06",
        "northeast" : "r09/f07",
        "west" : "r08/f05",
    ]));
    
}
