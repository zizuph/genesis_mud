/**********************************************************************
 * - rack_room.c                                                    - *
 * - A room that holds racks for Gladiators to hold thier equipment - *
 * - Also contains a "board" that only the High Overseer can post   - *
 * - rack policy on.                                                - *
 * - Created by Damaris@Genesis 09/2005                             - *
 **********************************************************************/
#pragma strict_types
#pragma save_binary

inherit "/std/room";
#include "defs.h"
#include <macros.h>


public void
create_room()
{
	object rack1;
	object rack2;
	object rack3;
	object board;
	
	set_short("rack room");
        set_long("The light from dim torches cast a warm glow all " +
	"around the racks that are firmly attached to the walls. It "+
	"is far from being barren here, as the racks take up a "+
	"significant portion of the room. Alongside the axe rack is "+
	"a sign that the High Overseer has attached to the wall "+
	"here, outlining the rules and regulations for use of the "+
	"racks.\n");
	add_item(({"room", "area", "rack room"}), query_long);
	add_item(({"walls", "wall"}),
	"The walls are covered with equipment racks.\n");
	add_item(({"floor", "ground"}),
	"The floor is made of some kind of rock mixture.\n");
	add_item(({"rock mixture"}),
	"The rock mixture looks like it is small rocks mixed with some "+
	"mud that has hardened with straw and other substances.\n");
	add_item(({"torch", "torches"}),
	"The torches add dim light and are firmly attached to the "+
	"walls.\n");
	rack1 = clone_object(GLAD_OBJ+"racks/armour_rack");
	rack1->move(TO); 

	rack2 = clone_object(GLAD_OBJ+"racks/weapon_rack");
	rack2->move(TO); 

	rack3 = clone_object(GLAD_OBJ+"racks/axe_rack");
	rack3->move(TO); 

	board = clone_object(GLAD_OBJ+"rack_board");
	board->move(TO); 	
	add_prop(ROOM_I_NO_CLEANUP,1);
	add_prop(ROOM_I_LIGHT, 1);
	add_prop(ROOM_I_INSIDE, 1);

	add_exit("startspt", "north");
	
	
}
	
