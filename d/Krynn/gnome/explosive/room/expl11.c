/**
* Coded by Louie 2004
* 
* Arming Room.
* This is where a player finally arms their explosive device (proto.c).
* They can do it outside of this room, but this room gives a bonus
* to success.
*
*/
#pragma strict_types

#include "../local.h"
inherit GNOME_IR;

/*prototypes*/

void
create_gnome_room()
{

    SHORT("Arming Room in the Explosives Development Center");
    LONG("This is a tiny room in the Explosives Development Center " +
    	"of Gnomish "+
      "Industries.  " +
      "The walls are completely made of metal.  There is nothing " +
      "in this room, as its only purpose is to provide a place " +
      "for someone to arm their explosive device.  " +
      "A stairway leads along the wall up to a hatch in the " +
      "ceiling.  " +
      "It is deathly quiet here.  " +
      "\n");

	clone_object(GNOME_OBJ+"hatcho")->move(TO);
	
	ITEM(({"stairway","stairs"}),
		"The stairs lead up the wall to the hatch in the ceiling.  " +
		"\n");

}


