 /* /d/Cirath/ships/roke/tyr_port.c
  * An eyrie.
  * Decius, December 1996
  */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "ship.h"
#include "defs.h"
#include <stdproperties.h>
#include <macros.h>

object ship;

void
reset_room()
{
  if(!ship){
    ship=clone_object(SHIPS+"ship.c");
    ship->move(TO);
    ship->start_ship();
    }
}

void
create_room()
{
  set_short("An eyrie");

  set_long("Scattered feathers adorn what appears to be "+
    "a huge nest made of trees and small boulders. A "+
    "pair of half-giant guards stand next to a set "+
    "of stairs leading down to the nest. This appears to "+
    "be the residence of a rather large bird.  "+
    "Near the stairs, you see a "+
   "carving of some kind.\n");

  add_item("carving","It has the image of two crossed axes "+
    "carved what looks like a coat of arms.\n");

   add_item("stairs","A stone stairway, carved from the mountain granite.\n");

  add_item("feathers","Some very large dark brown feathers "+
    "are scattered throughout the nest... they must be from "+
    "a huge bird.\n");

  add_item(({"guards","half-giants","half-giant guards"}),
    "Bored half-giant guards stand watch beside the stairs, "+
    "looking utterly thrilled to be doing so.\n");

  add_item(({"nest","huge nest"}),
    "This is a gigantic nest made up of trees that have been "+
    "ripped forcibly from the ground!\n");


  add_prop(ROOM_I_NO_CLEANUP,1);
  add_prop(OBJ_S_WIZINFO,"To restart the ship, type "+
    "'Call here restart_ship <reason>'.\n");

  OUTSIDE;
  ADD_SUN_ITEM;
  add_prop(ROOM_I_LIGHT,1);

  add_exit(WILD+"pass/pass20.c","up",0,1,0);
  reset_room();
}
