/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/cliffs/cliff_master.c
 *
 *  The base file for the ledges along the cliffs of the Blackwall
 *  Mountains which surround the lake of Del Rimmon.
 *
 *  Copyright (c) July 1997, Cooper Sherry (Gorboth)
 *
 *  Emerald Conversion: November 2000
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/del_rimmon";
inherit "/d/Emerald/blackwall/delrimmon/legacy/del_rimmon_room";

#include <composite.h>
#include <filter_funs.h>
#include <language.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* global variables */
int     Catapult_ledge;
string  Cliff_Base;     /* the room below this cliff ledge */

/* prototypes */
public void    create_ledge();
public void    create_del_rimmon();
public void    add_catapult_ledge();
public void    reset_room();
public mixed   em_climbing_hook(string str);
public void    drop_off_ledge(object ob, object to);
public void    init();
public int     drop_stuff(string arg);
public string  exa_cliff_base(string arg = "");

public void    set_catapult_ledge(int i = 1) { Catapult_ledge = i; }
public int     query_catapult_ledge() { return Catapult_ledge; }
public void    set_cliff_base(string s) { Cliff_Base = s; }
public mixed   query_cliff_base() { return Cliff_Base; }

/*
 * function name:        create_ledge
 * description  :        our dummy routine for inheriting rooms
 */
public void
create_ledge()
{
} /* create_ledge */

/*
 * function name:        create_del_rimmon
 * description  :        set up the room with area presets
 */
public void
create_del_rimmon()
{
    set_loc(4);
    create_ledge();

    add_name("del_rimmon_cliffs");

    set_short(del_rimmon_short);
    set_long(del_rimmon_long);

    if (Catapult_ledge)
    {
        add_catapult_ledge();
    }

    switch(random(3))
    {
        case 0:
            try_item(({"cliff","cliffs"}), BSN(
                "Sheer and jagged cliffs sit both above and below this"
              + " narrow ledge. Outcroppings of stone and pockets of"
              + " boulders are arrayed along the ridges."));
            try_item(({"outcropping","outcroppings",             
                       "outcropping of stone","outcroppings of stone"}),
                BSN("Outcroppings of stone jut out at various angles"
              + " from the cliff sides. Often, they cast long shadows"
              + " beside their bulky frames."));
            try_item(({"shadows","shadow"}), BSN(
                "The shadows cast by the outcroppings of rock are often"
              + " long and narrow, striping the cliffsides with"
              + " darkness."));
            try_item(({"pocket","pockets","pockets of boulders",
                       "pocket of boulders","boulder","boulders"}), BSN(
                "Boulders have had countless centuries to slide down"
              + " from the cliffs above and collect in piles among"
              + " the crags and jutties of the stone walls.")); 
            try_item(({"pile","piles","crags","jutties","crag","jutty"}),
                BSN("Boulders of many sizes are strewn in the piles"
              + " which rest in many of the crags and jutties of the"  
              + " cliff faces."));
            try_item(({"ledge","narrow ledge","ground","path"}), BSN(
                "The ledge here is extremely narrow, tracking along"
              + " the curvature of the cliff faces in a general north-"
              + "south direction. In places, boulders are strewn across"
              + " the path, making movement difficult."));
            break;
        case 1:
            try_item(({"path","ledge","ground","narrow ledge"}), BSN(
                "The ledge winds narrowly here, tracing the outline of"
              + " the crags and spires of stone which rise with the face"
              + " of the cliff above. The base of the cliff lies far"
              + " below."));
            try_item(({"cliff","cliffs","face","cliff face",
                       "face of the cliff"}), BSN(
                "The cliff which houses this narrow ledge runs raggedly"
              + " in a general north-south direction here. Great crags"
              + " and spires of stone cut away from the cliff face,"
              + " making movement perilous along its border."));
            try_item(({"crag","crags","spire","spires"}), BSN(
                "Crags and spires of stone run up the length of the"
              + " cliff face above the ledge here, their carven"
              + " forms evidence to the slow violence of the upheaval"
              + " of ancient land masses."));
            break;
        case 2:
            try_item(({"path","ledge","ground","narrow ledge"}), BSN(
                "A narrow ledge juts out from the cliff face here,"
              + " allowing barely enough room for the sure-footed to"
              + " traverse its length."));
            try_item(({"cliff","cliffs","cliff face"}), BSN(
                "The sides of the cliffs which support this ledge are"
              + " rugged and scored by many years of erosion and"
              + " upheaval. Hardy mountain vegetation grows in"
              + " small pockets amongst the stone."));
            try_item(({"hardy mountain vegetation","vegetation",
                       "hardy vegetation","mountain vegetation"}), BSN(
                "Extremely dry looking shrubs grow in scanty pockets"
              + " along the cliff face. It looks as if they cling to"
              + " the rock by burrowing with tough roots into the"
              + " pores of the stone, perhaps to find water there."));
            try_item(({"shrub","shrubs","dry shrubs"}), BSN(
                "The shrubs are dry and brittle looking, growing at"
              + " odd and bending angles from the nearly vertical slope"
              + " of the cliff face."));
            break;
    }

    try_item( ({ "down", "base", "base of the cliff",
                 "cliff base", "below", "ground below",
                 "over the edge", "over edge" }), exa_cliff_base);
    add_view();

    reset_room();
} /* create_del_rimmon */

/*
 * function name:        add_catapult_ledge
 * description  :        add some items to the room if it has been
 *                       declared as one of the special ledges
 */
public void
add_catapult_ledge()
{
    try_item(({"ledge","ground","path","narrow ledge"}), BSN(
        "The ledge here seems to have been reinforced somewhat,"
      + " as it widens dramatically to allow for greater surface"
      + " area."));
    try_item(({"cliff","cliff face","cliffs","cliffside"}), BSN(
        "A large section of the cliff face has been hewn out here"
      + " to create an alcove which rises perhaps thirty feet from"
      + " the base of the ledge. It would appear that this"
      + " was done to shelter and house the catapult which"
      + " has rested here for many years."));
    try_item(({"alcove","alcoves"}), BSN(
        "The alcove has been cut deep into the cliff to provide"
      + " room for the catapult. It rises perhaps thirty feet above,"
      + " and spans a width of more than fifteen feet."));
} /* add_catapult_ledge */

/*
 * function name:        reset_room
 * description  :        randomly add rocks to some rooms on resets
 */
public void
reset_room()
{
    int     i, n;
    object  stone;

    if (present("_del_rimmon_stone"))
    {
        return;
    }

    for (i = 0, n = (2 + random(3)); i < n; i++)
    {
        stone = clone_object(
            DEL_RIMMON_DIR + "legacy/random_rock");
        stone->add_prop(HEAP_S_UNIQUE_ID, "dr_stone_"
          + stone->short());
        stone->move(this_object());
    }
    return;
} /* reset_room */

/*
 * Function name: em_climbing_hook
 * Description  : Support for the verb 'climb' which players are likely
 *                to attempt in these rooms. Redefine this function to
 *                allow climbing in any of the inheriting rooms.
 * Arguments    : string str - what the player typed after 'climb'
 * Returns      : 0 ( we don't let them climb in most rooms )
 */
public mixed
em_climbing_hook(string str)
{
    if (!strlen(str))
    {
        NFN0("Climb what?");
    }

    if (!parse_command(str, ({}),
        "[up] [the] 'cliff' / 'cliffs' [wall] [walls]"))
    {
        return 0;
    }

    NFN0("The cliffs here look far too perilious to attempt any"
       + " climbing.");
} /* em_climbing_hook */


/*
 * Function name:        drop_off_ledge
 * Description  :        Moves the object dropped off the ledge
 *                       to the room below, and tells any onlookers
 *                       what happened. If the object is explosive,
 *                       cause it to explode.
 * Arguments    :        object ob -- what was dropped?
 *                       object to -- the room in which it lands
 */
public void
drop_off_ledge(object ob, object to)
{
    if (!to->short())
    {
        ob->remove_object();
    }

    ob->move(to);
    ob->set_no_show_composite(0);
    tell_room(to, CAP(LANG_ADDART(ob->short())) + " falls suddenly"
      + " from above, and lands on the ground with a thud.\n");

    if (ob->id("explosive"))
    {
        ob->bomb_explode();
    }
} /* drop_off_ledge */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(drop_stuff, "drop");
    add_action(drop_stuff, "throw");
    add_action(em_climbing_hook, "climb");
} /* init */


/*
 * Function name:        drop_stuff
 * Description  :        allow the player to drop stuff off of the
 *                       cliff ledge.
 * Arguments    :        string arg -- what the player typed
 * Returns      :        1 -- success, 0 -- failure
 *
 */
public int
drop_stuff(string arg)
{
    mixed   fail;
    object  drop_ob;

    if (!strlen(arg))
    {
        NFN0(CAP(QVB) + " what?");
    }

    if (!parse_command(arg, all_inventory(TP),
        "[the] %o [off] [over] [on] [to] [the]"
      + " 'edge' / 'ledge' / 'cliff' / 'down' / 'side' / 'wall'"
      + " / 'landing' / 'overlook' / 'path' / 'pathway'", drop_ob))
    {
        return 0;
    }

    if (drop_ob->query_no_show_composite())
    {
        return 0;
    }

    if (drop_ob->query_prop(OBJ_M_NO_DROP))
    {
        NFN0("You cannot throw the " + drop_ob->short()
                 + " away.");
    }

    WRITE("You " + QVB + " the " + drop_ob->short() + " off the"
        + " side of the ledge, where it falls to the ground"
        + " far below.");
    say(QCTNAME(TP) + " " + QVB + "s " + LANG_ADDART(drop_ob->short())
        + " off the side of the ledge, where it falls to the"
        + " ground far below.\n");

    drop_ob->set_no_show_composite(1);

    set_alarm(2.0, 0.0,
              &drop_off_ledge(drop_ob, find_object(Cliff_Base)));

    return 1;
} /* drop_stuff */


/*
 * Function name:        exa_cliff_base
 * Description  :        allows the player to see below the ledge,
 *                       and notice if there are any livings down
 * Arguments    :        string arg - If defined, this can be a special
 *                                    description of the base.
 *                       there.
 * Returns      :        string -- the description
 */
public string
exa_cliff_base(string arg = "")
{
    string base_desc;
    object *lnames;

    if (!strlen(arg))
    {
        base_desc = "Peering over the ledge, you are able to"
                  + " see the base of the cliffs far below. ";
    }
    else
    {
        base_desc = arg;
    }

    FIX_EUID
    Cliff_Base->load_me();
    lnames = FILTER_LIVE(all_inventory(find_object(Cliff_Base)));

    if (sizeof(lnames) > 0)
    {
        base_desc += CAP(COMPOSITE_LIVE(lnames)) + " can be"
                   + " seen moving around down there.";
    }

    return BSN(base_desc);
} /* exa_cliff_base */
