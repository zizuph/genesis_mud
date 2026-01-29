#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest_edge";

void create_mirkwood_north_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southeast" : MIRKWOOD_ELFPATH_DIR + "p31",
        "southwest" : "r02/f29",
        "south" : "r02/f30",
        "northwest" : "r04/f29",
        "east" : "r03/f31",
        "north" : "r04/f30",
        "northeast" : "r04/f31",
        "west" : "r03/f29",
    ]));
    
}
