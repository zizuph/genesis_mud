#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest_edge";

void create_mirkwood_north_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    add_long("Out of the corner of your eye, you notice a strange " +
        "looking tree.",
        ({LIGHT_BRIGHT}));

    add_item_light(({"tree", "dead tree", "dead fall", "deadfall", "strange tree", "strange looking tree"}),
        "Upon closer inspection, you notice that this strange tree is " +
        "really nothing more than an old deadfall. As dense as Mirkwood is, " +
        "it seems that the dead tree had nowhere else to go but to lean awkwardly " +
        "against the tree beside it. The end result was that a strange little niche " +
        "was created between the two trees, and that was what caught your eye.\n", ({LIGHT_BRIGHT}));
    add_item_light(({"niche", "strange niche"}),
        "This niche was created when one old tree died, and instead of falling " +
        "to the ground, leaned awkwardly against the tree beside it. Strangely enough, " +
        "it appears that inside this niche, there is a small wooden shelter which " +
        "has been constructed.\n", ({LIGHT_BRIGHT}));

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southeast" : "r16/f10",
        "southwest" : "r16/f08",
        "south" : "r16/f09",
        "northwest" : "r18/f08",
        "east" : "r17/f10",
        "north" : "r18/f09",
        "northeast" : "r18/f10",
        "west" : "r17/f08",
    ]));

    setuid();
    seteuid(getuid());
    object nest = clone_object(MIRKWOOD_OBJ_DIR + "north_forest/shelter_1");
    nest->move(this_object());
    
}
