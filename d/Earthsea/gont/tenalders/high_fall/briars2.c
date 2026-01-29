/*
*  coded by Amelia 3/16/97
*  old forest room north of Ten Alders
*  specials:  room_tell.c and search for herbs
 *  This room is just for the Morgul Mage beastie to land
 *  in;)
*
*/

inherit "/d/Earthsea/std/room";

#pragma no_clone
#pragma strict_types

#include <macros.h>
#include <stdproperties.h>
#include "defs.h"



void
reset_room()
{
}

void
create_earthsea_room()
{

    set_short("A briar patch");
    set_long(BS("You find yourself inside a dense briar patch. "+
	"Although sharp spiky thorns threaten to gouge you, there is "+
	"a soft nest on the ground of green grass. It is a fine spot "+
	"for a small animal to seek protection.\n", 70));


    add_item((({"green grass", "grass", "nest", "soft nest"})),
      "On the floor of the patch the ground is surprisingly soft, "+
      "like a soft nest for a small animal seeking protection.\n");
    add_item((({"thorns", "spiky thorns", "briars", "briar patch"})),
      "The wall of thorny briars makes a natural defense against "+
      "predators.\n");


    add_prop(ROOM_I_IS, 1);
    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_INSIDE, 0);

    reset_room();

    add_exit(HIGH_FALL+"n6.c", "back");
}
