/*
 * /d/Gondor/tharbad/trail/path9.c
 *
 * Copyright (C) August 20, 1998 by Ron Miller (Tyr)
 *
 * This spot is the hidden off the eastern edge of a clearing.
 * The mirror taken from the Pelargir lighthouse is hidden here.
 *
 * Revision history:
 *    5/17/99 - npc's added by Tyr
 *    6/17/99 - herbs added by Tyr
 *    6/28/99 - revised per Gnadnar's suggestions by Tyr
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room";
inherit "/d/Gondor/common/lib/herbsearch";

#include <stdproperties.h>    /* for ROOM_I_INSIDE, OBJ_*_SEARCH_*  */
#include <language.h>         /* for LANG_ADDART                    */
#include <macros.h>           /* for QCTNAME                        */
#include "/d/Gondor/defs.h"
#include "/d/Gondor/pelargir/beacon_defs.h"

#define HEAP_NAMES \
   "[large] [larger] 'pile' / 'leaves'"

static int    Mirror_is_here;   /* if true, mirror is hidden in leaves */

/* prototypes */
public void  create_gondor();
public void  reset_room();
public string  do_search(object tp, string arg);
public string  exa_glass();

object  *Corsair = allocate(4),
        Guard,
        Mate;

/*
 * Function name:    create_gondor
 * Description:      create the basic room
 */
public void
create_gondor()
{
    FIX_EUID;

    set_short("Near a clearing");
    set_long(BSN("Someone went to a lot of trouble to create a "+
        "hidden arbor here."));

    add_item( ({ "bower", "arbor", "hidden arbor", "here", "spot", "recess" }) ,
        BSN("Tree branches and shrubs have been carefully arranged to "+
        "form a leafy, shaded recess here. The leaves which used to lay "+
        "scattered about the ground have been gathered into several "+
        "piles around the edges of this secluded spot."));
 
    add_item( ({ "piles", "leaves", "several piles", "ground", "others" }) ,
        BSN("Most of the leaf piles are quite unremarkable. "+
        "One, however, is quite a bit larger than all the others."));

    add_item( ({ "large pile", "larger pile", "largest pile", "mound" }) ,
        BSN("This mound is significantly larger than the others. It "+
        "may actually be covering some large object hidden within."));

    add_item( ({ "object", "large object" }) , BSN("The leaves are too "+
        "tightly packed to see whatever may be buried within them."));
 
    add_item( ({ "someone", "privateer", "privateers" }) , BSN("Luckily, "+
        "the privateers who normally use this camp are away at the "+
        "moment."));

    add_item( ({ "shrub", "shrubs", "bushes", "woody bushes", "variety",
        "small trees" }) , BSN("The short woody bushes here are actually "+
        "more like small versions of the tall trees surrounding this "+
        "hidden arbor."));

    add_item( ({ "tree", "trees", "tall trees", "edges" }) , BSN("Tall trees "+
        "completely surround this small arbor, totally hiding it."));

    /* Adding herbs to this room */
    set_up_herbs( ({ (HERB_DIR+"lothore"),
                     (HERB_DIR+"suranie"),
                     (HERB_DIR+"attanar"),
                  }),
                  ({ "grass", "ground", "bush", "bushes", "underbrush",
                     "path", "pathway", }),
                  7);

    /* routine for searching the large leaf pile */
    add_prop(OBJ_S_SEARCH_FUN, "do_search");

    /* set how long the search should take (range is 3-8) */
    add_prop(OBJ_I_SEARCH_TIME, 5);


    add_exit("path7", "northwest", 0, 1);

    reset_room();
}   /* end create_gondor */

/*
 * Function name:    reset_room
 * Description:      set Mirror_is_here & add npc's
 */
public void
reset_room()
{
    ::reset_room();
    Mirror_is_here = 1;

    /* add generic corsair npc's */
    Guard = clone_npc(Guard, (POROS_DIR + "npcs/guard"));
    Mate = clone_npc(Mate, (POROS_DIR + "npcs/mate"));
    clone_npcs(Corsair, (POROS_DIR + "npcs/corsair"), 0.0);
}   /* end reset_room */

/*
 * Function name:    do_search
 * Description:      handles searching the room and items
 * Arguments:        object tp  -- this player
 *                   string arg -- whatever the player searched
 * Returns:          string     -- describes the result of the search
 *
 * Remarks: Players can search any of the room items, plus "here".
 *              Acceptable searches here are in: pile, large pile,
 *              leaves or any of those with "for mirror" or "for glass"
 *              appended.
 *
 * 	    In all other cases where arg is not "here", return
 *		the results of ::herb_search(), since the room also
 *		contains herbs.
 */

public string
do_search(object tp, string arg)
{
    string    msg,
        saymsg;
    object    ob;

    /* Note-arg will never be null if player just does "search", 
     * mudlib will set arg to "here".
     */          

    arg = LOW(arg);
    if (arg == "here")
    {
        /* If they didn't direct the search to the large leaf pile,
         * give them a hint.
         */
        return BSN("Poking about small piles of leaves rarely reveals "+
            "anything of serious interest.");
    }

    if (!Mirror_is_here)
    /* If mirror is not here */
    {
        return ::herb_search(tp, arg);
        /* There is nothing for them to find at this time */
    }

    if (!parse_command(arg, ({}), HEAP_NAMES) &&
        !parse_command(arg, ({}),
                       HEAP_NAMES+" 'for' [large] [glass] 'mirror'"))
    {
        return ::herb_search(tp, arg);
    }

    /* If mirror is here */
    Mirror_is_here = 0;
    ob = clone_object(MIRROR_FILE);
    msg = "You find "+LANG_ADDART(ob->short())+" hidden in the leaves.\n";

    if (ob->move(tp))
    {
        /* If player can't carry it (too heavy) */
        msg += "Oops, you dropped it!\n";
        ob->move(TO, 1);
    }

    return msg;
}   /* end do_search */

/*
 * Function name:    exa_glass
 * Description:      VBFC for the glass mirror
 * Returns:          string -- the mirror description
 */
public string
exa_glass()
{
    if (Mirror_is_here)
    {
        return BSN("What first appeared to be a large, shiny piece "+
        "of unremarkable glass may actually be something more "+
        "interesting. Perhaps a closer inspection is warranted.");
    }

    return "You find nothing but moulding leaves.\n";
} /* end exa_glass */
