#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(4);
    set_spider_nest_chance(46);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r06/f07",
        "southwest" : "r06/f05",
        "south" : "r06/f06",
        "northwest" : "r08/f05",
        "east" : "r07/f07",
        "north" : "r08/f06",
        "northeast" : "r08/f07",
        "west" : "r07/f05",
    ]));
    
}
