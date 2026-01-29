/*
 * /d/Gondor/lebennin/sroad/path12.c
 *
 * Copyright (C) August 20, 1998 by Ron Miller (Tyr)
 * This is the southeast corner of a clearing.  The lens taken from 
 * the Pelargir lighthouse is hidden here.
 *
 * Revision history:
 *    5/17/99 - npc's added by Tyr
 *    6/17/99 - herbs added by Tyr
 *    6/28/99 - revised per Gnadnar's suggestions by Tyr
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
   "[large] 'trash' / 'heap' / 'pile' / 'scraps' / 'junk' / 'debris'"

static int    Lens_is_here;   /* if true, lens is hidden in the heap */

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

    set_short("The edge of a clearing");
    set_long(BSN("A trail of scraps and trash lead northwest toward "+
        "the remains of an exhausted campfire. This appears to be the "+
        "trash heap for the entire camp."));
 
    add_item(({"heap","trash heap","bones","pile","large pile","trash",
        "animal bones","small animal bones","scraps","bits","pieces",
        "bits and pieces"}), BSN("Whoever camps in this area has "+
        "recklessly thrown their trash away here, making a rather "+
        "large pile of nothing but junk."));

    add_item(({"trail"}), BSN("Someone was not particularly careful "+
        "in hauling their trash here, dropping bits and pieces of "+
        "debris between here and the camp's center, toward the "+
        "northwest."));

    add_item(({"junk","thing","collection","debris","scraps","nothing"}),
        BSN("Mostly a collection of small animal bones, and "+
        "unidentifiable pieces of scrap metal, and glass. There is no "+
        "telling what else might buried in that pile."));

    add_item(({"pieces","metal","scrap metal"}), BSN("The discarded "+
        "metal pieces are either unfamiliar or deformed totally beyond "+
        "recognition."));

    add_item(({"glint","light","angle","right angle"}), BSN("When "+
        "viewed from just the right angle, light is briefly reflected "+
        "by some of the bits of glass within the debris."));

    add_item(({"bottle","broken bottle","object","glass object","edge",
        "something","glass"}), exa_glass);

    add_item(({"southern edge","clearing","small clearing","here",
        "space","side","sides"}), BSN("The underbrush has been "+
        "chopped back to provide enough space to set up a small camp "+
        "here."));

    add_item(({"remains","campfire","small campfire","ashes",
        "wet ashes","firewood","burnt firewood"}), BSN("To the "+
        "northwest lies a pile of wet ashes and partially burnt "+
        "firewood."));

    add_item(({"someone","privateer","privateers","people","whoever"}),
        BSN("Luckily, the privateers who normally use this camp are "+
        "away at the moment."));

    add_item(({"camp","small camp","hideout","area"}), BSN("This camp "+
        "looks as if it may serve as some sort of hideout for the "+
        "Corsairs known to traffic the river near here."));

    add_item(({"northwest","center"}), BSN("The center of the camp "+
        "lies to the northwest."));

    add_item(({"corsair","corsairs"}), BSN("There are no Corsairs "+
        "in camp at the moment."));

    add_item(({"river","river sirith","sirith","west"}), BSN("The "+
        "River Sirith lies west of the clearing, beyond the underbrush "+
        "and trees."));

    add_item(({"underbrush"}), BSN("This clearing is totally "+
        "surrounded by a wide variety of trees and shrubs typical "+
        "of this area."));

    add_item(({"shrub","shrubs","bushes","woody bushes","variety",
        "small trees"}), BSN("The short woody bushes here are actually "+
        "more like small versions of the tall trees surrounding this "+
        "clearing."));

    add_item(({"tree","trees","tall trees"}), BSN("Tall trees "+
        "completely surround this small clearing, totally hiding it "+
        "from prying eyes."));

    add_item(({"eye","eyes","prying eyes","outsiders"}), BSN("The "+
        "thick trees surrounding this clearing prevent spying by "+
        "outsiders."));


    /* Adding herbs to this room */

    set_up_herbs( ({ (HERB_DIR+"lothore"),
                     (HERB_DIR+"attanar"),
                     (HERB_DIR+"athelas"),
                  }),
                  ({ "grass","ground","bush","bushes","underbrush",
                     "path","pathway",}),
                  7);

    /* routine for searching the trash heap */
    /* this must be added AFTER setting up the herbs */
    add_prop(OBJ_S_SEARCH_FUN, "do_search");

    /* set how long the search should take (range is 3-8) */
    add_prop(OBJ_I_SEARCH_TIME, 7);

    add_exit("path9", "north", 0, 1);
    add_exit("path8", "northwest", 0, 1);
    add_exit("path11", "west", 0, 1);

    reset_room();
}   /* end create_gondor */

/*
 * Function name:    reset_room
 * Description:      set Lens_is_here & add npc's
 */
public void
reset_room()
{
    ::reset_room();

    Lens_is_here = 1;

    Guard = clone_npc(Guard, (POROS_DIR + "npcs/guard"));
    Mate = clone_npc(Mate, (POROS_DIR + "npcs/mate"));
    set_alarm(4.0, 0.0,
        &clone_npcs(Corsair, (POROS_DIR + "npcs/corsair"), 10.0));
}   /* end reset_room */

/*
 * Function name:    do_search
 * Description:      handles searching the room and items
 * Arguments:        object tp  -- this player
 *                   string arg -- whatever the player searched
 * Returns:          string     -- describes the result of the search
 *
 * Remarks: Players can search any of the room items, plus "here".
 *              Acceptable searches here are in: heap, trash, trash heap,
 *              pile, large pile, scraps, junk, debris, or any of those
 *              with "for lens" or "for glass" appended.
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

    /* Note-arg will never be null if player just does "search", mudlib will
     * set arg to "here".
     */          
    arg = LOW(arg);
    if (arg == "here")
    {
        /* If they didn't direct the search to the trash heap, give them
         * a hint.
         */
        return BSN("Aimlessly poking about rarely reveals anything "+
            "of serious interest.");
    }

    /* If lens is not here */
    if (!Lens_is_here)
    {
        /* There is nothing for them to find at this time */
	return ::herb_search(tp, arg);
    }

    if (!parse_command(arg, ({}), HEAP_NAMES) &&
        !parse_command(arg, ({}),
                       HEAP_NAMES+" 'for' [large] [glass] 'lens'"))
    {
	return ::herb_search(tp, arg);
    }

    /* If lens is here */
    Lens_is_here = 0;
    ob = clone_object(LENS_FILE);
    msg = "You find "+LANG_ADDART(ob->short())+" hidden in the trash.\n";

    if (ob->move(tp))
    {
        /* If player can't carry it (too heavy) */
        msg += "Oops, you dropped it!\n";
        /* ob->move(TO, 1); */   /* remove if next line works */
        move(ENV(TP), 1);  
    }

    return msg;
}   /* end do_search */

/*
 * Function name:    exa_glass
 * Description:      VBFC for the glass lens
 * Returns:          string -- the lens description
 */

public string
exa_glass()
{
    if (Lens_is_here)
    {
        return BSN("What first appeared to be the edge "+
        "of a partially buried bottle may actually be the edge of "+
        "something larger.  Perhaps a closer inspection is warranted.");
    }

    return "You find nothing but shattered pieces of old bottles.\n";
} /* end exa_glass */
