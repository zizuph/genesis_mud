/*  description: Entrance to the water kroug
 *               tunnels.
 */

#pragma strict_types
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "defs.h"

inherit BASE_CAVE;
#include "larva.h"

void
create_water_room()
{
    set_short("Entrance to a tunnel");
    set_long("The culvert opens onto a tunnel that"+
      " leads deep into the rock. The tunnel is circular"+
      " as though someone had bored through"+
      " the rock with a huge drill. To the north it"+
      " is partially submerged.  You notice that some"+
      " sort of moisture is seeping through cracks"+
      " in the walls, creating puddles on the floor.\n");

    add_item(({"walls", "ceiling", "floor"}),
      "The walls and ceiling are solid rock and"+
      " are curved into a circular tunnel. There is"+
      " some dark substance coating them, and a nasty"+
      " fluid seeps through fine cracks in the surface.\n");
    add_item(({"substance", "dark substance"}),
      "It is hard to define what this substance is."+
      " It has a texture like something between mold"+
      " and slime. The smell here leads you to suspect"+
      " that the environment is anything but healthful.\n");
    add_item(({"cracks", "fine cracks", "rock"}),
      "The solid rock walls and ceiling are permeated"+
      " with fine cracks.\n");

    add_item(({"moisture", "puddles", "cracks"}),
      "The walls and ceiling are leaking some nasty"+
      " substance through fine cracks in the rock. You"+
      " wonder from the smell if it is polluted.\n");
    add_item(({"odour", "nasty odour", "nasty foetid odour"}), 
      "Whatever is causing this odour, the air"+
      " quality here is really poor.\n");

    add_prop(ROOM_I_LIGHT, 0);
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

    reset_room();
    add_exit(CLIFF_ROOM + "rocks2", "out", 0, 0);
    add_exit(CAVE_LEV1 + "tunnel1", "down", 0, 0);

}


void
hook_smelled(string str)
{
    write("It smells like toxic waste of some kind. You"+
      " wonder if it will be harmful to your health to"+
      " stay here long.\n");

}


