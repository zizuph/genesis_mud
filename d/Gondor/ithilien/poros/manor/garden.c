/*
 *   /d/Gondor/ithilien/poros/manor/garden.c
 *
 *   A path outside the manor used as a hidden base by corsairs.
 *
 *   Talisan,  January 1996
 *
 *   Revision history:
 *    7/21/98 - Lantern taken from the Pelargir lighthouse hidden
 *              here by Tyr.
 */

#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";
inherit "/d/Gondor/common/lib/herbsearch";

#include <stdproperties.h>
#include <language.h>
#include <macros.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/pelargir/beacon_defs.h"

#define HEAP_NAMES \
   "[large] 'rubble' / 'mound' / 'corner' / 'debris'"

static int    Lantern_is_here;   /* if true, lantern is in the rubble */

/* prototypes */
public void  create_area_room();
public void  reset_room();
public string  do_search(object tp, string arg);


void
create_area_room()
{
    FIX_EUID;		/* may clone lantern */

    set_land("Gondor");
    set_areaname("Ithilien");
    set_area("southern");
    set_areadesc("small garden pathway");
    set_areatype(0);

    set_extraline("The pathway continues through what must have once "
      + "been a garden. Amongst the weeds stands an old well. "
      + "While an arched doorway leads into the manor to the north, "
      + "and a flight of stairs leads down to the southwest.");

    add_prop(OBJ_I_SEARCH_TIME, 6);
    add_prop(OBJ_S_SEARCH_FUN, "do_search");

    set_search_places( ({ "grass", "garden", "bushes", "weeds" }) );
    add_herb_file(HERB_DIR + "athelas");
    add_herb_file(HERB_DIR + "astaldo");
    add_herb_file(HERB_DIR + "annalda");
    add_herb_file(HERB_DIR + "lothore");
    add_herb_file(HERB_DIR + "curugwath");
    add_herb_file(HERB_DIR + "handasse");

    add_exit(POROS_DIR + "manor/westhall3", "north", 0, 1);
    add_exit(POROS_DIR + "manor/landing", "southwest", 0, 1);

    add_item( ({ "path", "pathway" }) , BSN("The path shows signs of "+
        "recent use, and has been cleared of the debris that litters "+
        "the rest of the area."));

    add_item( ({ "debris" }) , BSN("It is mostly rubble from the manor, "+
        "and thicker areas of weeds that were cut down."));

    add_item( ({ "garden", "ground" }) , BSN("This is a small terraced "+
        "garden on the south end of the manor. However all that grows "+
        "in the garden now is weeds."));

    add_item( ({ "well" }) , BSN("It is an old well, partially crumbling. "+
        "It isn't clear if it's still in use or not."));

    add_item( ({ "manor", "manor house", "house", "ruins", "old manor" }) , 
        BSN("Over time elements have taken their toll on the old manor "+
        "house, causing the collapse of the structure in many places. "+
        "The manor, once home to a Dunadan Lord, seems to have been "+
        "uninhabited for centuries."));

    add_item( ({ "weeds", "scrub", "brush" }) , BSN("Weeds and scrub grow "+
        "undisturbed throughout most of the small garden. Some areas "+
        "have been cleared up along the path."));

    add_item( ({ "stairs", "steps" }) , BSN("The stairs are old and worn, "+
        "much like the rest of the manor."));

    add_item( ({ "rubble", "mound" }) , BSN("Rubble from collapsed areas of "+
        "the manor are scattered in many places throughout the small "+
        "garden. There is a particularly large mound of it in one "+
        "corner."));

    reset_room();

}   /* end create_area_room() */


/*
 * Function name:    reset_room
 * Description:      set Lantern_is_here
 */

public void
reset_room()
{
    ::reset_room();
    Lantern_is_here = 1;
}   /* end reset_room */



/*
 * Function name:    do_search
 * Description:      handles searching the room and items
 * Arguments:        object tp  -- this player
 *                   string arg -- whatever the player searched
 * Returns:          string     -- describes the result of the search
 *
 * Remarks: Players can search any of the room items, plus "here".
 *              Acceptable searches here are in: rubble, mound, large
 *              mound, corner, debris or any of those with "for lantern" 
 *              appended. Searching for anything else results in a 
 *              rejection (returns null string). Null string also 
 *              returns if there is no lantern in the rubble.
 *
 *          Null string return is default message "Your search reveals 
 *              nothing special".
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
        /* If they didn't direct the search to the rubble, give them
         * a hint.
         */
        return BSN("Aimlessly poking about rarely reveals anything "+
            "of serious interest.");
    }

    if (!Lantern_is_here)
    {
	/* There is nothing for them to find at this time */
        return herb_search(tp,arg);
    }

    if (!parse_command(arg, ({}), HEAP_NAMES) &&
        !parse_command(arg, ({}),
                       HEAP_NAMES+" 'for' [large] 'lantern'"))
    {
        return herb_search(tp,arg);
    }


    Lantern_is_here = 0;
    ob = clone_object(LANTERN_FILE);
    msg = "You find "+LANG_ADDART(ob->short())+" hidden in the trash.\n";
    if (ob->move(tp))
    {
    	msg += "Oops, you dropped it!\n";
    	ob->move(TO, 1);
    }

    return msg;

}   /* end do_search */
