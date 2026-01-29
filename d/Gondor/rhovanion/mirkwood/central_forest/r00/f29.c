#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(11);

    set_distance_to_edge(0);
    add_mirkwood_exits(([
        "southwest" : MIRKWOOD_OLDROAD_DIR + "r23",
        "south" : MIRKWOOD_OLDROAD_DIR + "r24",
        "southeast" : MIRKWOOD_OLDROAD_DIR + "r25",
        
        "northwest" : "r01/f28",
        "east" : "r00/f30",
        "north" : "r01/f29",
        "northeast" : "r01/f30",
        "west" : "r00/f28",
    ]));
    
}
