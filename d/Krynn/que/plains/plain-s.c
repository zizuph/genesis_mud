#include "local.h"
inherit TDIR+"plain_base";

void
create_plains_room()
{
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_LIGHT, 1);

    set_short("Outside Que Teh");
    set_long("You are standing just outside the entrance of Que Teh. " +
	     "Towards your north, a track continues into the wilderness, " +
	     "while the Sageway leads northeast and southwest from here. " +
	     "West is the small village of Que Teh.\n");

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
    if (arg == "T")
	return 1;
    return ::is_room(arg);
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
    if (dest == "T") // path is obvious
	return 0;
    return ::exit_not_obvious(from, dest);
}

