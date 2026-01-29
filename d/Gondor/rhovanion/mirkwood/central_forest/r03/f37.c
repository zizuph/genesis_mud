#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(74);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r02/f38",
        "southwest" : "r02/f36",
        "south" : "r02/f37",
        "northwest" : "r04/m36",
        "east" : "r03/f38",
        "north" : "r04/m37",
        "northeast" : "r04/m38",
        "west" : "r03/m36",
    ]));
    
}
