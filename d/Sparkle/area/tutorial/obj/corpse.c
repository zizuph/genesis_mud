/*
 *  /d/Sparkle/area/tutorial/obj/corpse.c
 *
 *  This corpse contains a gemstone that players who find him can
 *  take. He can only be reached if you fight your way through the
 *  lion family in the cave. Located at:
 *
 *      /d/Sparkle/area/tutorial/cliffs/cave_alcove.c
 *
 *  Created November 2005, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit "/std/object";

#include <stdproperties.h>

/* prototypes */
public void        create_object();
public string      do_search(object pl, string arg);
public void        search_corpse(object player);


/*
 * Function name:        create_object
 * Description  :        set up the object
 */
public void
create_object()
{
    set_name("corpse");
    add_name( ({ "body", "adventurer", "_tutorial_corpse" }) );
    add_adj( ({ "old", "withered", "unfortunate" }) );

    set_short("old withered corpse");
    set_long("Here lies the body of an unfortunate adventurer who must"
      + " have run afoul of the denizens of this cave. For some reason,"
      + " the corpse has not been picked apart like so many of the"
      + " other skeletons around here. It still has its clothing, and"
      + " perhaps a few possessions.\n");

    add_prop(OBJ_M_NO_GET, "The corpse is too heavy to lift.\n");
    add_prop(OBJ_I_WEIGHT, 7000);
    add_prop(OBJ_I_VOLUME, 5000);

    add_prop(OBJ_S_SEARCH_FUN, "do_search");

    setuid();
    seteuid(getuid());
} /* create_object */


/*
 * Function name:        do_search
 * Description  :        allow the player to search the corpse
 * Arguments    :        object pl  - the player object,
 *                       string arg - what the player tried to search
 * Returns      :        int 1 - success, 0 - failure
 */
public string
do_search(object pl, string arg)
{
    if (!strlen(arg) || 
        !parse_command(arg, ({}),
        "[the] [old] [withered] [unfortunate] 'body' / 'corpse' /"
      + " 'adventurer'"))
    {
        return "Your search reveals nothing special.\n";
    }

    set_alarm(0.0, 0.0, &search_corpse(pl));
    return "You search the contents of the corpse thoroughly ... \n";
} /* do_search */


/*
 * Function name:        search_corpse
 * Description  :        show the contents of the corpse
 * Arguments    :        object player - the player
 */
public void
search_corpse(object player)
{
    object  gem;

    set_this_player(player);

    if (CHECK_TUTORIAL_BIT(GEM_BIT))
    {
        write("There is nothing of interest on the corpse.\n");
        return;
    }

    gem = clone_object("/d/Genesis/gems/obj/ruby");
    gem->move(this_player());

    write("You find a ruby on the corpse and take it!\n");

    SET_TUTORIAL_BIT(GEM_BIT);
    return;
} /* search_corpse */
