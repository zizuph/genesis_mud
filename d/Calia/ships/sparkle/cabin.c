/* 

   Cabin for the ship to Sparkle, Coded by Amelia. 

   Some bugs corrected, Maniac, 4/4/97 

*/

#pragma save_binary

inherit "/d/Genesis/ship/cabin";

#include <stdproperties.h>
#include "ship.h"
#include <macros.h>

void
create_cabin()
{
	set_cabin_sound("As the ship moves, the hammock sways "+
		"back and forth.\n");
	set_short("The captain's cabin");
	set_long("This room is small and neat, with everything in "+
		"place. The walls conform to the inside of the "+
		"ship's hull with its gracefully curved planks. "+
		"On the far side is a hammock, which sways with the "+
		"movement of the ship. You see a small wooden table "+
		"and wooden shelves, which are secured to the walls "+
		"and floor. On the side opposite from the hammock is a "+
		"very compact kitchen area. Everywhere you look you "+
		"see the gleam of polished teak and brass fixtures. "+
		"Clearly the captain keeps things ship-shape. "+
		"There is a small narrow ladder that leads up to "+
		"the deck.\n");

	add_item((({"shelf", "shelves", "wooden shelves"})),
		("The shelves are enclosed behind locked glass "+
		"doors. They contain scrolls that look like "+
		"maps and other nautical books.\n"));

	add_item((({"table", "wooden table"})),
		("There's nothing on the table, and everything "+
		"appears to be put away. The surface of the table "+
		"is polished and gleams.\n"));
	add_item((({"kitchen", "kitchen area", "stove"})),
		("The kitchen area contains a basin and a small "+
		"stove that's mounted on a swivel, so that it won't "+
		"spill when the ship moves.\n"));
	add_item("ladder", "The ladder is narrow, but well-built. "+
		"It is secured to the hatch and floor, and has a "+
		"safety rail.\n");

	add_item("hammock", "The hammock actually looks "+
		"quite comfortable. Maybe you could lie down in it.\n");

	add_prop(ROOM_I_INSIDE,1);
	add_prop(ROOM_I_LIGHT,1);
	add_prop(ROOM_I_IS,1);
        add_prop(ROOM_I_HIDE, -1);
        add_prop(ROOM_I_NO_TELEPORT,1);
	add_exit(SHIPS+"deck.c", "up", 0,0);
}


void
enter_inv(object ob, object from)
{
     ::enter_inv(ob,from);
     if (interactive(ob) && (ob->query_prop(CONT_I_HEIGHT) > 140)) 
	write("You bump your head on the low ceiling, as you enter.\n");
}

int
lie_down(string str)
{
	if ((str=="down")||(str=="down in hammock")||
		(str=="down hammock"))
		{
		write("You try to lie down in the hammock, "+
		"but it spins around, and you fall on the floor!\n");
		say(QCTNAME(TP)+" tries to lie down in the hammock, "+
		"but instead falls on the floor!\n");
		return 1;
		}
	/* else */
		notify_fail("Lie where?\n");
		return 0;
}


void
init()
{ 
    ::init(); 
    add_action(lie_down, "lie");
}

