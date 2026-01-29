/* Xak Tsorath coded by Percy */

#include "xlocal.h"

inherit XAKINROOM

#include <ss_types.h>
#include <macros.h>

void
create_xak_room()
{
    object door;
    
    set_short("The temple entry");
    set_long("You are inside the holy temple of Mishakal."
	     + " Entering this temple gives you a good feeling all over"
	     + ". You remember all the good times in your life and"
	     + " somehow you know that no matter what happens in your life"
	     + " things will always work out for the best in the end."
	     + " Double doors lead out of the room"
	     + " and back into the city to your west. This entry"
	     + " leads east and into a main hall.\n");
    
    add_exit(TDIR + "temphall.c", "east", 0);
    
    INSIDE;
    DARK;
    add_item(({"symbol", "symbols", "holy symbol", "circles"}), "@@symbol");
    add_item(({"metal door", "door", "doors", "double door", "double doors", "metal doors"}), "@@doors");
    
    door = clone_object(OBJ + "t_doorb.c");
    door->move(TO);
    door->set_key(K_TEMPLE);
}

void
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
	  + " look very old and very very solid."
	  + " The doors bear a symbol of 2 silver coloured circles"
	  + " joined together.\n");
    SAY(" studies the doors carefully.");
    return "";
}

string
symbol()
{
    write("The symbol is the holy symbol of mishakal, 2 circles joined"
	  + " together.\n");
    SAY(" studies the symbol on the doors.");
    return "";
}

