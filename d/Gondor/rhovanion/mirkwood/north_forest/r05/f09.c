#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(3);
    set_spider_nest_chance(38);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r04/f10",
        "southwest" : "r04/f08",
        "south" : "r04/f09",
        "northwest" : "r06/f08",
        "east" : "r05/f10",
        "north" : "r06/f09",
        "northeast" : "r06/f10",
        "west" : "r05/f08",
    ]));
    
}
