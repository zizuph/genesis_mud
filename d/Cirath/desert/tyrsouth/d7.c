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
  set_long("You are in the midst of a large rocky outcropping.  On "
  	+"all sides of you rough edged rocks and boulders lie like "
  	+"sleeping giants.  The cracked earth beneath your feet kicks "
  	+"up small puffs of dust as you walk, and your footsteps echo "
  	+"hollowly against the stones around you.  A little to the west, "
  	+"you think you can make out a dark area against a cliff that "
  	+"surrounds the barrens you are in.\n");
  add_item("dust","As ever-present as the blinding sun, is the dust "
  	+"that seems to coat Athas like a gritty blanket.\n");
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

  add_exit(SOUTH + "d4","southwest");
  add_exit(SOUTH + "d3","south");
  add_exit(SOUTH + "d2","southeast");
  add_exit(SOUTH + "d6","west");
  add_exit(SOUTH + "d8","east");
  add_exit(SOUTH + "d16","northwest");
  add_exit(SOUTH + "d15","north");
  add_exit(SOUTH + "d14","northeast");
  set_alarm(1.0,0.0,"reset_room");
}

