#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest_edge";

void create_mirkwood_north_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    add_long("On top of a small overhang, with some of its roots exposed in the " +
        "air, you see an old oak tree.",
        ({LIGHT_MIDDAY, LIGHT_BRIGHT}));

    add_item_light(({"tree", "old tree", "oak tree", "old oak tree", "weathered tree", "weathered oak tree", "weathered old oak tree"}),
        "Standing atop a small rise, which overhangs the ground in front of you, " +
        "is a weathered, old oak tree. The tree reaches up to the forest ceiling with " +
        "venerable strength. Reaching out of the overhang itself, gnarled and twisted, " +
        "are the exposed roots of the old oak. When seem in the dim light of Mirkwood, " +
        "the shadow cast by the tree roots looks both creepy and sinister.\n", ({LIGHT_MIDDAY, LIGHT_BRIGHT}));
    add_item_light(({"root", "roots", "mass", "gnarled roots", "gnarled root", "exposed roots", "exposed root", "oak roots", "oak root", "twisted roots", "twisted root"}),
        "The roots from this weathered, old oak are twisted and gnarled as they curl across " +
        "the exposed edge of the overhang. The way the light and shadows play with your eyes, " +
        "it almost seems as if the roots are reaching out towards you.\n", ({LIGHT_MIDDAY, LIGHT_BRIGHT}));
    add_item_light(({"overhang", "over hang", "small overhang", "small over hang", "rise", "gentle rise", "small rise"}),
        "There is a gentle rise in this part of Mirkwood forest, which culminates " +
        "in a small overhang in front of you. Atop the rise, an old oak tree stretches " +
        "up to reach towards the forest ceiling. While the overhang itself has " +
        "exposed a mass of gnarled and twisted roots.\n", ({LIGHT_MIDDAY, LIGHT_BRIGHT}));
    add_item_light(({"shadow", "shadows"}),
        "@@shadow_item@@", ({LIGHT_MIDDAY, LIGHT_BRIGHT}));

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southeast" : "r16/f27",
        "southwest" : "r16/f25",
        "south" : "r16/f26",
        "northwest" : "r18/f25",
        "east" : "r17/f27",
        "north" : "r18/f26",
        "west" : "r17/f25",
    ]));

    setuid();
    seteuid(getuid());
    object nest = clone_object(MIRKWOOD_OBJ_DIR + "north_forest/den_1");
    nest->move(this_object());
    
    
}

string shadow_item()
{
    if (query_light_level_for_living(this_player()) == LIGHT_MIDDAY)
    {
        return "The way the shadows move, the roots of this old oak "
            + "tree and so gnarled and twisted that they give the "
            + "creepy impression that they are reaching out to try "
            + "and grab you!\n";
    }

    if (query_light_level_for_living(this_player()) == LIGHT_BRIGHT)
    {
        return "The way the shadows move, the roots of this old oak tree "
            + "and so gnarled and twisted that they give the creepy "
            + "impression that they are reaching out to try and grab you! "
            + "But as you look closer, you can just make out an old animal "
            + "den which has been dug directly into the overhang itself.\n";
    }
    
    return "Shadows have been draped all around you as you wander "
        + "through the brush here, somewhere somewhere of Mirkwood forest.\n";
}