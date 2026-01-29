/* 
 * file:  /d/Calia/sea/objects/excrement.c
 * Coder:       Tigerlily
 * Date:        2002-03-31
 * Special:     This is the object that provides the search
 *              item for the lucky lure quest. After chick
 *              has eaten fish, it 'loads' the excrement
 *              that player can search to find the lucky lure
 *              If the player hasn't searched it and it dries,
 *              it will leave the lure behind.
 */


inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#include SEA_QUESTS

object lure;
int lure_found = 0;

public string do_search(object actor, string str);
int remove_poop();

void
create_object()
{
    setuid(); 
    seteuid(getuid(this_object())); 
    set_short("heap of fresh bird poop");
    set_name("excrement");
    add_name(({"bird doo", "poop"}));
    add_name("heap of fresh bird poop");
    add_name("bird poop");
    add_name("bird excrement");
    add_name("_chick_poop_");
    set_long("This is a steaming heap of bird excrement."+
      " It appears to be rather fresh, judging from the smell.\n");
    set_no_show_composite(1);

    add_prop(OBJ_M_NO_GET, "This is not something that"+
      " anyone would want to take with them.\n");
    add_prop(OBJ_I_VOLUME, 150);
    add_prop(OBJ_I_WEIGHT, 150);

    add_prop(OBJ_I_SEARCH_TIME, 5);
    add_prop(OBJ_S_SEARCH_FUN, "do_search");

    // cleans up after itself
    set_alarm(30.0, 0.0, &remove_poop());


}


/*******************************************************************
 * Function name: do_search
 * Description  : Search function for lucky lure item
 * Arguments    : object actor, string search string
 * Returns      : search message
 */

public string
do_search(object actor, string str)
{
    if(!str)
    {
	write("Search what?");
	return "";
    }

    if (this_object()->id(str) && !lure_found)
    {
	if (actor->query_prop(LIVE_I_LUCKY_LURE_QUEST) && !lure_found)
	{
	    //one lure per poop
	    lure_found = 1;
	    lure = clone_object(SEA_OBJECTS + "lucky_lure");
	    lure->move(actor, 1);
	    return "You find something in the nasty heap of"+
	    " bird poop.\n";
	}
    }
    return "";
}
/*******************************************************************
 * Function name: remove_poop
 * Description  : Clean up function
 * Arguments    : none
 * Returns      : 1
 */

int
remove_poop()
{
    // if player has not found lure in the bird poop
    // and if it isn't lying around already,
    // the lure will be revealed when the poop dries

    object lure = present("metal", environment(this_object()));

    if (!lure_found && !objectp(lure))
    {
	tell_room(environment(this_object()), "The bird poop dries"+
	  " into a hard plaster-like substance. You notice that"+
	  " there is something left behind in the droppings.\n", ({}));
	lure = clone_object(SEA_OBJECTS + "lucky_lure");
	lure->move(environment(this_object()), 1);
	remove_object();
	return 1;
    }

    tell_room(environment(this_object()), "The bird poop dries"+
      " into a hard plaster-like substance.\n", ({}));
    remove_object();
    return 1;
}
