/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/cliffs/outpost1a.c
 *
 *  This room was once used as a storeroom at the northwestern
 *  outpost manned by Formandil's men in the Blackwall Mountains.
 *  It is manned mostly be spiders now.
 *
 *  Copyright (C) March 1999, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/legacy/del_rimmon_room";
inherit "/d/Emerald/blackwall/delrimmon/legacy/random_noise";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* global variables */
public int     Bundles;     /* how many bundles on table? /*

/* prototypes */
public void    create_del_rimmon();
public void    init();
public int     random_noise();
public void    reset_room();
public int     get_bundle(string arg);
public string  exa_table();
public mixed   exa_bundle();


/*
 * Function name:        create_del_rimmon
 * Description  :        set up the room with domain presets
 */
public void
create_del_rimmon()
{
    set_short("a dark side-chamber");
    set_long(BSN(
        "This dark side-chamber looks as if it may have been used"
      + " as a storage area in some ancient time. Depressions which"
      + " resemble shelves have been carved into the northern wall,"
      + " below which rests a long stone table. A deep crack is visible"
      + " in the ceiling above the western wall, evidently the source"
      + " of the wind which moves steadily through the room."));

    add_item( ({ "stone", "rock" }), BSN(
        "The rock from which this chamber has been hewn is apparently"
      + " the very rock of the cliffs."));
    add_item( ({ "blocks", "stone block", "stone blocks",
                 "blocks of stone", "block" }), BSN(
        "The blocks of stone which comprise the base and surface of"
      + " the table appear to be the same material as that of the"
      + " walls."));
    add_item( ({ "sky", "sun", "moon", "stars" }), BSN(
        "The view of the sky is obscured from this indoor place."));
    add_item( ({ "cliff", "cliffs" }), BSN(
        "You are within the cliffs here, and so you cannot view"
      + " them directly."));
    add_item( ({ "dead ones", "dead insects", "dead bodies" }), BSN(
        "There are hundreds of different sorts of dead insect bodies"
      + " in the tangled mess of webs. It appears as if they are"
      + " of various beetle species, primarily."));
    add_item( ({ "beetle", "beetles", "beetle species" }), BSN(
        "Some of the beetles look to have been dead for a very long"
      + " time."));
    add_item( ({ "beatle", "beatles" }), BSN(
        "You were expecting to find Lennon and McCartney, perhaps?"));
    add_item( ({ "chamber", "dark chamber", "side-chamber",
                 "side chamber", "dark side-chamber", "here",
                 "area" }), BSN(
        "It would seem that this area was once used as a storage"
      + " chamber."));
    add_item( ({ "depressions", "depression", "shelves", "shelf",
                 "depressions which resemble shelves" }), BSN(
        "The shelves in the northern wall appear to have long"
      + " ago been claimed by the local insect population as a"
      + " dwelling place. Thick and matted webs wind from one"
      + " end of the depressions to the other, intertwined with"
      + " tiny bodies, and pieces of old pottery."));
    add_item( ({ "insect", "insects", "bodies", "body",
                 "tiny bodies", "tiny body" }), BSN(
        "The living insects appear to be mostly spiders, although"
      + " there are a good number of dead ones which look to be"
      + " other species."));
    add_item( ({ "spider", "spiders" }), BSN(
        "The spiders sit motionless in their webbed fortress in"
      + " the shelf."));
    add_item( ({ "web", "fortress", "webbed fortress", "webs",
                 "matted webs", "matted web" }), BSN(
        "The webs are thick and brown, coated with moisture and"
      + " filled with the dead bodies of insects, and pieces of"
      + " ancient pottery."));
    add_item( ({ "pottery", "ancient pottery", "pieces",
                 "pieces of pottery", "old pottery",
                 "pieces of old pottery" }), BSN(
        "Very few of the pieces of pottery are intact, and all"
      + " are thickly covered by the matted webs of insects. They"
      + " have the look of drinking vessels."));
    add_item( ({ "vessel", "vessels", "drinking vessel", 
                 "drinking vessels" }), BSN(
        "Most are broken, and all are covered with webs."));
    add_item( ({ "wall", "walls", "walls of the chamber" }), BSN(
        "The walls of the chamber are dark and rough, apparently"
      + " having been carved from the very rock of the cliff face."));
    add_item( ({ "north", "north wall", "northern wall",
                 "wall to the north" }), BSN(
        "Depressions which look to have at one time functioned as"
      + " shelves are carved in the northern wall, below which rests"
      + " a long stone table."));
    add_item( ({ "west", "west wall", "western wall",
                 "wall to the west" }), BSN(
        "The wall to the west is marked by the stains of moisture,"
      + " which apparently has seeped from a deep crack in the ceiling"
      + " above its surface."));
    add_item( ({ "east", "east wall", "eastern wall",
                 "wall to the east" }), BSN(
        "The wall to the east is plain and unremarkable."));
    add_item( ({ "south", "south wall", "southern wall",
                 "wall to the south" }), BSN(
        "A doorway is carved in the southeastern corner of the wall,"
      + " leading into a dark chamber."));
    add_item( ({ "doorway", "door" }), BSN(
        "The doorway leads into another chamber to the southeast."));
    add_item( ({ "southeast", "chamber to the southeast",
                 "another chamber" }), BSN(
        "There is only darkness beyond the doorway."));
    add_item( ({ "ceiling", "roof", "up" }), BSN(
        "A deep crack is visible to one side of the ceiling, near"
      + " to the western wall."));
    add_item( ({ "floor", "ground", "down" }), BSN(
        "The ground here is nearly devoid of dust, perhaps due to"
      + " the wind which issues from the crack in the ceiling."));
    add_item( ({ "dust" }), BSN(
        "There is very little dust in this chamber, perhaps due to"
      + " the wind which steadily blows from the crack in the"
      + " ceiling."));
    add_item( ({ "wind", "air" }), BSN(
        "A soft wind blows steadily out of this chamber through"
      + " the doorway to the southeast. It seems to be coming from"
      + " a crack in the ceiling near to the west wall."));
    add_item( ({ "crack", "deep crack", "crack in the ceiling" }), BSN(
        "The crack in the ceiling is perhaps three inches wide, and"
      + " apparently travels a good distance up above, where wind"
      + " rushes down its interior into this chamber."));
    add_item( ({ "table", "stone table", "long table",
                 "long stone table" }), exa_table);
    add_item( ({ "bundle", "bundles", "leather bundle",
                 "leather bundles" }), exa_bundle);

    add_cmd_item( ({ "crack", "deep crack", "crack in the ceiling" }),
                  ({ "enter", "climb" }), BSN(
        "The crack is only three inches wide, making it quite"
      + " impossible to climb into."));
    add_cmd_item( ({ "web", "webs", "shelf", "shelves", "depression",
                     "depressions", "north wall", "northern wall",
                     "wall to the north", "pottery", "ancient pottery",
                     "pieces of pottery" }), 
                  ({ "search" }), BSN(
        "As you move to search the shelf, dozens of spiders suddenly"
      + " scurry to avoid your moving hands. After a few moments, you"
      + " come to the conclusion that there is nothing of any real"
      + " importance in the messy tangle of webs and pottery."));

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);

    add_exit(DELRIMMON_DIR + "lakeside/cliffs/outpost1", "southeast");

    set_no_exit_msg( ({ "north", "northeast", "east", "south",
                        "southwest", "west", "northwest" }),
        "You run up against the walls of the chamber.\n");

    reset_room();
} /* create_del_rimmon */


/*
 * Function name:        init
 * Description  :        add some verbs to the player,
 *                       and set up the room noises
 */
public void
init()
{
    ::init();
    init_random_noise();

    add_action(get_bundle, "get");
} /* init */


/*
 * Function name: random_noise
 * Description  : the wind is blowing in here
 * Returns      : int -- non-zero if noises should continue,
 *                 zero if they should stop
 */
public int
random_noise()
{
    tell_room(TO, BSN(        ({
        "A gust of wind blows suddenly through the chamber.",
        "The wind whistles softly through a crack in the"
      + " ceiling above.",
        })[random(2)] ) );

    return 1;
} /* random_noise */



/*
 * function name:    reset_room
 * description  :    set the value of Bundles to > 1 if it is 0
 */
public void
reset_room()
{
    if (!Bundles)
    {
        Bundles = 1 + random(4);
    }
} /* reset_room */


/*
 * function name:        get_bundle
 * description  :        allow the player to try to get a bundle
 *                       from the table
 * arguments    :        string arg -- what the player typed
 * returns      :        1 -- success, 0 -- failure
 */
public int
get_bundle(string arg)
{
    object  bundle;

    if (!strlen(arg))
    {
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[the] 'bundle' / 'bundles' [from] [the] [long]"
      + " [stone] [table]"))
    {
        return 0;
    }

    if (!Bundles)
    {
        NFN0("There is nothing on the table.");
    }

    WRITE("You take a leather bundle from the table,"
        + " and notice with surprise the immense weight of the"
        + " object.");
    say(QCTNAME(TP) + " takes something from the long stone"
      + " table.\n");

    bundle = clone_object(DELRIMMON_DIR + "obj/explosive");

    if (bundle->move(TP))  /* too heavy for the player */
    {
        WRITE("Oops! You dropped it!");
        say(QCTNAME(TP) + " fumbles and drops what "
          + TP->query_pronoun() + " had taken.\n");

        bundle->move(TO, 1);
    }

    Bundles--;

    return 1;
} /* get_bundle */



/*
 * function name:        exa_bundle
 * description  :        describe the bundles, if there are any
 * returns      :        string -- the acorn desc,
 *                       0 -- no acorns to see
 */
public mixed
exa_bundle()
{
    if (!Bundles)
    {
        return 0;
    }

    if (Bundles == 1)
    {
        return "A single leather bundle rests in the center of the"
             + " table.\n";
    }

    return "Some leather bundles rest on the surface of the table."
         + " You count " + LANG_WNUM(Bundles) + " of them.\n";
} /* exa_bundle */


/*
 * function name:        exa_table
 * description  :        provide a description of the table
 * returns      :        string -- the description
 */
public string
exa_table()
{
    string  table_txt;

    table_txt = "This table is extremely crude, having been constructed"
              + " of blocks of stone piled atop one another to form a"
              + " work area. It does not look to have been used in"
              + " centuries. ";

    if (Bundles)
    {
        if (Bundles == 1)
        {
            table_txt += "A leather bundle rests on the surface of the"
                       + " table.";
        }
        else
        {
            table_txt += "Some leather bundles rest on the surface of"
                       + " the table.";
        }
    }

    return BSN(table_txt);
} /* exa_table */
