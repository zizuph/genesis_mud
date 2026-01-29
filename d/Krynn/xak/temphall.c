/* Xak Tsorath coded by Percy */

#include "xlocal.h"

inherit XAKINROOM

#include <ss_types.h>
#include <macros.h>

void
create_xak_room()
{
    object door;
    
    set_short("The temple hall");
    set_long("You are standing in the temple hall. The floor is made"
	     + " of finest marble and the wealth that this city must once"
	     + " have had is apparent. To the west lies an entry chamber"
	     + " while to the east stands another set of double doors.\n");
    
    add_exit(TDIR + "tempentry.c", "west", 0);
    
    INSIDE;
    DARK;
    add_item(({"metal door", "door", "doors", "double door", "double doors", "metal doors"}), "@@doors");
    
    door = clone_object(OBJ + "t_hall_doora.c");
    door->move(TO);
    door->set_key(K_TEMPLE);
}

init()
{
    ::init();
      ADA("pick");
      ADA("knock");
}

int
pick(string str)
{
    NF("Pick what?\n");
    if ((str == "lock") || (str == "the lock") || (str == "door lock"))
      {
	  write("You try to pick the lock, but it is too complex for you.\n");
	  SAY(" is messing with the door lock.");
	  return 1;
      }
    return 0;
}

int
knock(string str)
{
    NF("Knock where?\n");
    if ((str == "on the door") || (str == "on the doors")
	|| (str == " on the double doors") || (str == "door"))
      {
	  write("You knock on the doors, the sound of your knocking " +
        	"is swallowed up by the deathly silence of the city.....\n");
	  SAY(" knocks on the door very loudly.");
	  return 1;
      }
    return 0;
}

string
doors()
{
    write("These double doors are made of a strange silvery blue metal, they"
	  + " look very old and very very solid.\n");
    SAY(" studies the doors carefully.");
    return "";
}

