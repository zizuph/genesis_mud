#include "local.h"
inherit TDIR+"plain_base";

void
create_plains_room()
{
    set_short("In the village of Que Teh");
    set_long("You are surrounded by several tents and small huts. " +
	     "The village appears to have been left in a haste, you " +
	     "cannot see anything alive around. Luckily, neither can " +
	     "you see anything dead either. By going east, you get " +
	     "outside the village onto the Plains of Abanasinia.\n");
    add_item(({"tents","huts"}),
	     "You cannot see anything special.\n");
    add_search(({"tents","huts"}),5,
	       "You come to the conclusion that the population has fled " +
	       "the village in haste, most likely due to some threat. " +
	       "Strange though, that the village has not been plundered and " +
	       "burnt.\n");

    add_std_exits();
}

/* Function name: is_room
 * Description:	  Test if letter on map corresponds to a room.
 * Argument:	  arg - letter corresponding to rooms
 * Returns:	  1 if room    else 0
 * Note:	  _ALWAYS_ make " " return 0
 */
public int
is_room(string arg)
{
    if (arg == "T" || arg == "s")
	return 1;
    return 0;
}

/* Function name: exit_not_obvious
 * Description:	  Test if exit from one room to another should be not obvious
 * Argument:	  from - letter corresponding to from room
 *		  dest - letter corresponding to dest room
 * Returns:	  1 if not obvious    else 0 - exit will be obvious
 */
public int
exit_not_obvious(string from, string dest)
{
    if (from == "T" && dest =="j")
	return 0;
    return 1;
}
