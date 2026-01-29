/*
   Wayreth.

   equiproom.c
   ------------

   Coded ........: 97/09/11
   By ...........: Karath

*/

#include "/d/Krynn/wayreth/local.h"
inherit TOWERROOM;

object gRack, gSheath;

void
reset_tower_room()
{
    if (!gRack)
      {
	gRack = clone_object(TOBJ + "polearm_rack.c");
	gRack->move(TO);
      }
    if (!gSheath)
      {
	gSheath = clone_object(TOBJ + "knife_scabbards.c");
	gSheath->move(TO);
      }
    return;
}

void
create_tower_room()
{
   set_short("The equipment storage room");
   set_long("This room is very spartan, the floor a shiny hardwood. "+
	"This is the place where common equipment is stored for "+
	"mages and apprentices alike to store and share their "+
	"needed items for travel in the dangerous realms.\n");

   add_item("floor", "The floor is hardwood, polished and waxed causing "+
		"light to reflect, illuminating the place.\n");

    set_wall_type(2);
    add_prop(ROOM_I_NO_CLEANUP, 1);

    add_exit(WTOWER + "meditation", "north", 0);
    reset_tower_room();
}
