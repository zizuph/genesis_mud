#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest_edge";

void create_mirkwood_central_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "northwest" : MIRKWOOD_ELFPATH_DIR + "p06",
        "north"     : MIRKWOOD_ELFPATH_DIR + "p07",
        "northeast" : MIRKWOOD_ELFPATH_DIR + "p08",
        
        "southeast" : "r16/f08",
        "southwest" : "r16/f06",
        "south" : "r16/f07",
        "east" : "r17/f08",
        "west" : "r17/f06",
    ]));
    
}
