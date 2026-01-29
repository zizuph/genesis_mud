#include "defs.h"

inherit SEWER_ROOM;

/* global variables */
public string       Dir = "";  /* where is the channel from here? */

/* prototypes */
public void        add_level_1_items();


public void         set_channel_dir(string s) { Dir = s; }
public string       query_channel_dir() { return Dir; }


public void
create_sewer_passage_room()
{
}

public nomask void
create_sewer_room()
{
    create_sewer_passage_room();
    add_level_1_items();
}

public int
do_drink(string arg)
{
    string what, where;

    if (!strlen(arg))
    {
        notify_fail("Drink what?\n");
        return 0;
    }

    if (parse_command(arg,
                      ({}),
                      "'from' / 'out' / 'in' / 'inside' [of] %s",
                      where) ||
        parse_command(arg,
                      ({}),
                      "%s 'from' / 'out' / 'in' / 'inside' [of] %s",
                      what,
                      where))
    {
        if (!parse_command(where,
                           ({}),
                           "[the] [sewer] [sewage] 'channel' [of] [sewage]") &&
            !parse_command(where, ({}), "[the] 'sewer'"))
        {
            notify_fail("Drink from where?\n");
            return 0;
        }

        where = "channel";
    }
    else
    {
        what = arg;
    }

    // If the player has specified that he wants to drink from the channel,
    // we allow some more general terms for the sewage. If we didn't do this,
    // I'm afraid someone might unintentionally drink the sewage when he
    // meant to "drink the water" from somewhere else.
    if (where == "channel")
    {
        if (what &&
            !parse_command(what,
                           ({}),
                           "[some] [of] [the] [sewer] 'water' / 'sewage'"))
        {
            notify_fail("Drink what from the sewage channel?\n");
            return 0;
        }
    }
    else
    {
        // Don't want to catch just "drink water"
        if (!parse_command(what, ({}), "[some] [of] [the] 'sewer' 'water'") &&
            !parse_command(what, ({}), "[some] [of] [the] 'sewage'"))
        {
            notify_fail("Drink what?\n");
            return 0;
        }
    }

    write("You drink some of the sewer water from the channel.\n");
    return 1;
}

public void
init()
{
    ::init();

    add_action(do_drink, "drink");
}


/*
 * Function name:        add_level_1_items
 * Description  :        add items for rooms on level 1
 */
public void
add_level_1_items()
{
    try_item( ({ "mold", "patch of mold", "patches of mold" }),
        "Mold clings to the mortar in places along the wall. You even"
      + " glimpse a few fungal blooms now and again.\n");
    try_item( ({ "fungus", "bloom", "fungal bloom" }),
        "Once in a while, you glimpse a patch of fungus growing between"
      + " the mold and other film which coats these walls. Upon close"
      + " inspection, you are repulsed to find that the odor coming from"
      + " these blooms is almost too much to bear. If a larger specimen"
      + " could be found, it would be a fairly incredible tool of"
      + " torture for those with a delicate nose.\n");
    try_item( ({ "wall", "walls", "sewer wall", "sewer walls",
                 "wall of the sewer", "walls of the sewer",
                 "brick wall", "brick walls" }),
        "The walls of the sewer system are comprised of brick and"
      + " mortar. Though in fairly good repair, dark stains and"
      + " patches of mold mar the surface of the walls, creating"
      + " an atmosphere of uneasiness and gloom.\n");
    try_item( ({ "brick", "bricks", "red brick", "red bricks" }),
        "The bricks which make up the bulk of the sewer walls are"
      + " the color of red clay. Moisture coats the surface of the"
      + " bricks, which are in places deeply stained and covered"
      + " with an unsightly film.\n");
    try_item( ({ "surface of the brick", "surface of the bricks",
                 "moisture", "film", "unsightly film" }),
        "In many places, the walls of the sewers are coated with"
      + " moisture which is of unknown origin. Perhaps it is"
      + " little more than condensation. Perhaps it is moisture from"
      + " the earth which has leaked through from beyond the walls."
      + " In some places it is covering deep stains.\n");
    try_item( ({ "stain", "stains", "deep stain", "deep stains",
                 "dark stain", "dark stains" }),
        "Dark stains mar the surface of the brick walls. Looking"
      + " closer, you notice that the stains are actually a brown"
      + " slimy moss which has grown to coat the mortar and much"
      + " of the bricks themselves.\n");
    try_item( ({ "mortar" }),
        "Though hard as stone, the mortar appears to ooze from"
      + " between the bricks like frosting in a layer cake. It"
      + " would seem that little care for beauty went into the"
      + " construction of these sewers.\n");
    try_item( ({ "moss", "brown moss", "slimy moss",
                 "slimy brown moss", "brown slimy moss" }),
        "The brown moss is very dense in places, covering entire"
      + " sections of the walls. From afar it looks like dark stains,"
      + " but up close, you notice that it is actually a very"
      + " intricate living organism. In drier areas, it is furry,"
      + " with many tiny fronds extending like a carpet from the"
      + " base of the root mesh. Where the moss is wet, it takes on"
      + " the characteristics of a brown sludge.\n");

    try_item( ({ "ground", "floor", "ledge", "walkway",
                 "edge", "ledges", "walkways", "down" }),
        "The ledge on this side of the channel forms a walkway"
      + " which is narrow, and difficult to walk upon. It is"
      + " comprised of thick slabs of stone which have been fit"
      + " together and set in place.\n");
    try_item( ({ "stone", "slabs", "thick slabs", "slab",
                 "thick slab", "slab of stone", "slabs of stone",
                 "thick slab of stone", "thick slabs of stone",
                 "stone slab", "stone slabs", "thick stone slab",
                 "thick stone slabs" }),
        "The stone slabs which make up the ledge are smooth and"
      + " grey. Dark pools of water interrupt the walkway in"
      + " places, making traversing the sewer system difficult"
      + " and treacherous.\n");
    try_item( ({ "pool", "pools", "dark pool", "dark pools",
                 "pool of water", "pools of water",
                 "dark pools of water", "dark pool of water" }),
        "The pools of water are slimy and smell foul. You notice"
      + " that the floor is very slippery around where they"
      + " lie.\n");

    try_item( ({ "sewer", "sewers", "area", "here", "system",
                 "sewer system", "tunnel", "tunnels",
                 "corridor", "corridors" }),
        "The sewer system which runs under telberin is roughly"
      + " the same design as the streets which are above it. Four"
      + " main channels run the sewage north, south, east, and"
      + " west running slightly downhill toward collecting pools"
      + " which then drain to deeper levels of the sewers. On the"
      + " side of each channels are ledges which can serve as"
      + " walkways to maintanence crews which must occasionally"
      + " make their way down here for repairs.\n");
    try_item( ({ "collecting pool", "collecting pools" }),
        "The collecting pools are at the end of each main"
      + " channel, running away from the center of the city."
      + " None are visible from here.\n");
    try_item( ({ "deeper level", "deeper levels" }),
        "There are probably access ladders to the deeper levels"
      + " of the sewers somewhere in the area.\n");

    try_item( ({ "channel", "channels", "sewage channel",
                 "sewage channels" }),
        "Directly to the " + Dir + " of this walkway, sewage"
      + " runs away from the center of the city travelling in"
      + " the waters of a deep channel. A very slight, yet"
      + " perceptible incline in these corridors uses the"
      + " force of gravity to direct the sewage to collecting"
      + " pools which force the sewage down to the deeper levels"
      + " of the sewer system.\n");
    try_item( ({ "incline", "gravity", "force of gravity" }),
        "There is a definite incline in these corridors and the"
      + " channels that define them. As one travels toward the"
      + " center of the sewer system, one engages in a very"
      + " slight climb. Heading away from center, takes you"
      + " very slightly downhill.\n");
    try_item( ({ "sewage", "sewer water", "water" }),
        "The sewage flows gently along the channel, travelling"
      + " down the slight incline which leads away from the center"
      + " of the city. You can only imagine how dreadful it"
      + " would be to slip and end up in that mess.\n");

    try_item( ({ "ceiling", "roof", "up" }),
        "The same bricks which make up the walls of these passages"
      + " were used in the construction of the ceiling. Drips"
      + " of water constantly drop from the ceiling, where"
      + " condensation from the sewer water has formed.\n");
    try_item( ({ "drip", "drips", "drop", "drops",
                 "drip of water", "drips of water",
                 "condensation" }),
        "The drips from the ceiling are barely audible over the"
      + " sound of the gently flowing water.\n");
} /* add_level_1_items */
