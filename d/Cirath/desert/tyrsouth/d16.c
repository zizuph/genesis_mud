inherit "/std/room";
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "defs.h"
#include "/d/Cirath/common/defs.h"
#include "/d/Cirath/common/mobber.h"

void
reset_room()
{
    object npc = present ("braxat",TO);
    if(!objectp(npc))
    {
           bring_room_mob("braxat", DES_NPC+"braxat",1,1);
    }
}


void
create_room()
 {
  set_short("Rocky Outcropping");
  set_long("A cliff guards the way west here, preventing further "
  	+"travel in that direction.  The face rises about 12 feet "
  	+"before apparently leveling off on top.  You think that "
  	+"at some point in the past this must have been a lake "
  	+"bottom, and this cliff was actually the edge of the "
  	+"lake.  To the south, the rocky ground continues, while "
  	+"to the north, flat parched earth lies.\n");
  add_item(({"face","cliff","cliff face"}),
  	"A sheer wall of rock rising to about 12 feet high looms to "
  	+"the west.  Vivid bands of color are readily apparent, showing "
  	+"the ancient history of the Athasian wastes,\n");
  add_item(({"large rocks","rocks","outcroppings","rocky outcroppings"}),
  	"Large rough edged rocks thrust upward from the ground, some "
  	+"still part of some massive formation, some broken shards "
  	+"of it.\n");
  add_item("shade","A rare thing on Athas, and a thing even rarer to "
  	+"find unoccupied.  Things lurk in the shade, beware.\n");

  add_exit(SOUTH + "d6","south");
  add_exit(SOUTH + "d7","southeast");
  add_exit(SOUTH + "d15","east");
  add_exit(SOUTH + "d17","north");
  add_exit(SOUTH + "d18","northeast");
  set_alarm(1.0,0.0,"reset_room");
}

