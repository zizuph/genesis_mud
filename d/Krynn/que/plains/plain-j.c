#include "local.h"
inherit TDIR+"plain_base";

void
create_plains_room()
{
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_LIGHT, 1);

    set_short("Outside Que Kiri");
    set_long("You are standing just outside the entrance of Que Kiri. " +
	     "There are several tracks continuing into the " +
	     "wilderness, west is the small village of Que Kiri. " +
	     "The path to the north will lead to Solace, the track south" +
	     "east will take you to Que Shu or Que Teh.\n");

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
    if (arg == "K")
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
    if (dest == "K") // path is obvious
	return 0;
    return ::exit_not_obvious(from, dest);
}

