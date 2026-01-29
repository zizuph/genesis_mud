#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(4);
    set_spider_nest_chance(45);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "northwest" : MIRKWOOD_ELFPATH_DIR + "p22",
        
        "southeast" : "r15/f24",
        "southwest" : "r15/f22",
        "south" : "r15/f23",
        "east" : "r16/f24",
        "north" : "r17/f23",
        "northeast" : "r17/f24",
        "west" : "r16/f22",
    ]));
    
}
