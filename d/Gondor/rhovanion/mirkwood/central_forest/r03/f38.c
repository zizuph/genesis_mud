#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(70);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r02/f39",
        "southwest" : "r02/f37",
        "south" : "r02/f38",
        "northwest" : "r04/m37",
        "east" : "r03/f39",
        "north" : "r04/m38",
        "northeast" : "r04/f39",
        "west" : "r03/f37",
    ]));
    
}
