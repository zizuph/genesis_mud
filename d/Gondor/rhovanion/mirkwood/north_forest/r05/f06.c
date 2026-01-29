#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(26);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r04/f07",
        "southwest" : "r04/f05",
        "south" : "r04/f06",
        "northwest" : "r06/f05",
        "east" : "r05/f07",
        "north" : "r06/f06",
        "northeast" : "r06/f07",
        "west" : "r05/f05",
    ]));
    
}
