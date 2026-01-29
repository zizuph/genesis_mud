#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest_edge";

void create_mirkwood_central_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "northwest" : MIRKWOOD_ELFPATH_DIR + "p05",
        "north"     : MIRKWOOD_ELFPATH_DIR + "p06",
        "northeast" : MIRKWOOD_ELFPATH_DIR + "p07",
        
        "southeast" : "r16/f07",
        "southwest" : "r16/f05",
        "south" : "r16/f06",
        "east" : "r17/f07",
        "west" : "r17/f05",
    ]));
    
}
