/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/hollow_stump.c
 *
 *  This is the inside of a stump located at:
 *
 *      /d/Emerald/blackwall/delrimmon/lakeside/w_wood3b.c
 *
 *  Not very much has happened inside this old tree stump in the last
 *  few centuries. Bits of things have fallen to cover the floor from
 *  all the rot. Acorns can be found here by industrious players.
 *
 *  Copyright (c) November 2000, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/legacy/del_rimmon_room";
inherit "/d/Emerald/blackwall/delrimmon/lib/herb_search";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* definitions */
#define        FOUND_ACORN    "_found_del_rimmon_acorn"

/* global variables */
public mixed       Portal;

/* Prototypes */
public void    create_del_rimmon();
public int     stump_search(string arg);
public int     try_climb(string arg);
public void    init();
public void    reset_room();
public void    leave_inv(object ob, object to);


/*
 * Function name:        create_del_rimmon
 * Description  :        set up the room with area presets
 */
public void
create_del_rimmon()
{
    add_name(STUMP);

    set_short("in a hollow tree stump");
    set_long("All around you, the sides of a great tree stump loom up"
           + " and over your head, bending inward like mighty rafters"
           + " in a circular room. All sorts of fungi and bracken cling"
           + " to the dry wood, where the innards of the once mighty"
           + " tree loom over a soft bed of dirt and sod on the ground"
           + " at your feet.\n");

    add_item( ({ "sides", "side", "side of the stump",
                 "sides of the stump", "innards", "wall", "walls",
               }),
        "The sides of the tree stump are all around you, closing you"
      + " into this little chamber in the forest. Many forms of fungi"
      + " cling to the wood.\n");
    add_item( ({ "here", "area", "chamber", "little chamber",
                 "stump", "tree stump", "stumps" }),
        "You are within the great stump of a once mighty tree. The sides"
      + " of this stump form a chamber of sorts, which close you in and"
      + " set you quite apart from the forest here.\n");
    add_item( ({ "tree" }),
        "Though it obviously was once a vast and tall tree, this old"
      + " wood can hardly be called anything but a stump now.\n");
    add_item( ({ "wood", "dry wood", "old wood" }),
        "The wood which forms the walls of this stump is covered with"
      + " fungi and bracken. It is very old, and rotted in many places,"
      + " housing almost certainly many tiny creatures in its folds.\n");
    add_item( ({ "creatures", "insects", "tiny creatures", "folds" }),
        "One can only imagine the millions of things which must live"
      + " in the wood of this giant stump.\n");
    add_item( ({ "forest", "tree", "hole", "up", "above", "opening" }),
        "The branches of nearby trees are visible swaying above, where"
      + " the walls of the stump taper to an opening.\n");
    add_item( ({ "branch", "branches", "tree branch", "tree branches" }),
        "Tree branches sway gently to and fro above, visible through"
      + " an opening in the walls of the trunk overhead.\n");
    add_item( ({ "fungi", "fungus", "bracken" }),
        "The insides of the stump are crowded with many colorful"
      + " forms of fungi which cling to the wood. Some of the growths"
      + " look to be very ancient.\n");
    add_item( ({ "growth", "growths", "ancient growth",
                 "ancient growths" }),
        "It almost seems as if some of this fungus has been on the"
      + " wood for over a hundred years.\n");
    add_item( ({ "ground", "down", "dirt", "bed", "soft bed",
                 "bed of dirt", "dirt bed", "soft bed of dirt",
                 "sod", "dirt and sod" }),
        "The years of weather and decay have produced a soft bed of"
      + " dirt and sod which comprises the ground at the foot of the"
      + " chamber within this tree stump.\n");

    add_cmd_item( ({ "stump", "wood", "fungi", "fungus",
                     "walls", "wall", "tree" }),
                  ({ "search", "dig" }),
        "You search around the area, not exactly sure what you might"
      + " find in this old stump. After a little while, you decide to"
      + " give it a rest.\n");

    add_prop(ROOM_S_DARK_LONG,
        "Inside the dark confines of a tree stump.\n");
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
    add_prop(ROOM_S_EXIT_FROM_DESC,
        "from inside a nearby stump.");

    set_up_herbs( ({ "/d/Emerald/herbs/darkroot",
                     "/d/Emerald/herbs/darkroot",
                     "/d/Emerald/herbs/darkroot" }),
                          ({ "ground", "bush", "tree",
                             "undergrowth", "trees", "forest",
                             "shrub", "shrubs", "bushes",
                             "roots", "root", "stump" }),
                  3 );

    add_exit(DELRIMMON_DIR + "lakeside/w_wood3b", "out");

    set_no_exit_msg( ({ "north", "northeast", "east", "southeast",
                        "south", "southwest", "west", "northwest",
                        "up", "down" }),
        "There doesn't seem to be any way to go except out.\n");

    reset_room();
} /* create_del_rimmon */


/*
 * Function name:        stump_search
 *
 * Description  :        Let the player search around, if they search
 *                       the ground, they might find some acorns.
 * Arguments    :        string arg - what the player typed
 * Returns      :        1 - success,
 *                       0 - failure
 */
public int
stump_search(string arg)
{
    object   acorn;

    if (!strlen(arg))
    {
        return 0;   /* let the mudlib handle this */
    }

    if (!parse_command(arg, ({}),
        "[around] [in] [the] [soft]"
      + " 'bed' / 'dirt' / 'ground' / 'sod'"
      + " [of] [dirt] [and] [sod]"))
    {
        return 0;   /* let the mudlib handle this, too */
    }

    if (this_player()->query_prop(FOUND_ACORN))
    {
        write("You search around a bit more in the dirt, but don't find"
            + " anything else.\n");
        return 1;
    }

    write("You dig around in the dirt and sod on the ground. Aside from"
        + " a little acorn, you don't find much of anything. You do"
        + " keep the acorn, though.\n");

    acorn = clone_object(DELRIMMON_DIR + "obj/acorn");

    if (acorn->move(this_player()))  /* player is too encumbered */
    {
        write("Oops! You dropped it!\n");
        say(QCTNAME(this_player()) + " fumbles and drops something"
          + " on the ground.\n");

        acorn->move(this_object(), 1);
    }

    this_player()->add_prop(FOUND_ACORN, 1);

    return 1;
} /* stump_search */


/*
 * Function name:        try_climb
 * Description  :        respond to attempts to climb
 * Arguments    :        string arg - what the player typed
 * Returns      :        1 - success
 *                       0 - failure
 */
public int
try_climb(string arg)
{
    if (!strlen(arg))
    {
        notify_fail("What do you want to climb?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[on] [out] [through] [of] [the] [great] [large] [dry]"
      + " 'stump' / 'wood' / 'wall' / 'walls' / 'fungi' / 'fungus'"
      + " / 'opening' / 'hole' / 'up'"
      + " [in] [the] [wall] [walls] [of] [the] [stump]"))
    {
        notify_fail("That didn't make sense.\n");
        return 0;   /* what they typed didn't make sense */
    }

    write("The walls of the stump are steeply undercut here from the"
        + " inside, making climbing quite impossible.\n");

    return 1;
} /* try_climb */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(stump_search, "search");
    add_action(stump_search, "dig");
    add_action(try_climb, "climb");
} /* init */


/*
 * Function name:        reset_room
 * Description  :        clone the portal to the room
 */
public void
reset_room()
{
    if (!present("_del_rimmon_portal", this_object()))
    {
        Portal = clone_object(DELRIMMON_DIR + "obj/portal");
        Portal->move(this_object());
    }

    set_searched(- random(3));
    return;
} /* reset_room */


/* 
 * Function name: leave_inv
 * Description:   Called when objects leave this container or when an
 *                object is about to change its weight/volume/light status.
 * Arguments:     ob: The object that just leaved this inventory
 *                to: Where it went.
 */
public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if (Portal->query_standing() == ob)
    {
        Portal->remove_standing();
    }
} /* leave_inv */
