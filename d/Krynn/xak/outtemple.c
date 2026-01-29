/* Xak Tsorath coded by Percy */

#include "xlocal.h"

inherit XAKOUTROOM

#include <ss_types.h>
#include <macros.h>

void
create_xak_room() 
{
    object door;
    
    set_short("The temple entrance");
    set_long("On the east side of the street lies the entrance doors to the holy"
	     + " temple of Mishakal. Pillars line the steps that lead up to"
	     + " the main doors. This building seems to have been"
	     + " strangely untouched by the forces that devastated the"
	     + " rest of the city. You can feel the goodness that the"
	     + " temple represents. The street comes to an end here"
	     + " the way north blocked by further rubble.\n");
    
    add_exit(TDIR + "square.c", "south", 0);
    OUTSIDE;
    LIGHT;
    add_item(({"symbol", "symbols", "holy symbol", "circles"}), "@@symbol");
    add_item(({"street", "streets", "houses", "city", "ruins"}), "@@ruins");
    add_item(({"metal door", "door", "doors", "double door", "double doors", "metal doors"}), "@@doors");
    add_item(({"pillar", "pillars", "temple"}), "@@temple");
    door = clone_object(OBJ + "t_doora.c");
    door->move(TO);
    door->set_key(K_TEMPLE);
}

void
init()
{
    ADA("pick");
    ADA("knock");
    ::init();
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
ruins()
{
    write("The ruins of this city are pityful indeed. Wrought by the"
	  + " massive forces of the cataclysm that took place in Krynn many"
	  + " years earlier the streets of this city are all either totally"
	  + " blocked by rubble or they have been dragged underground. Only"
	  + " one street looks even half passable and that lies to your south.\n");
    return "";
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
    write("The symbol is the holy symbol of Mishakal, 2 circles joined"
	  + " together.\n");
    SAY(" studies the symbol on the doors.");
    return "";
}

string
temple()
{
    write("The temple looks to be in good condition, at least from"
	  + " the outside. Three steps lead up to the main doors which are"
	  + " flanked by several tall pillars made of a smooth white stone.\n");
    return "";
}







