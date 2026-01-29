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
		bring_room_mob("braxat",DES_NPC+"brax_leader",1,1);
    }
}


void
create_room()
 {
  set_short("Small Cave");
  set_long("You have entered a small cave on the western side of "
  	+"the rocky barrens south of Tyr.  Littering the ground here "
  	+"you see bones, pieces of chitin, and some bloodstained "
  	+"rocks.  The smell of death and rotting flesh is rich in "
  	+"here, pungent like sour milk on a baby's breath.  Whatever "
  	+"it is, its probably not good.\n");
  add_item("bones","Miscellansous pieces of bone from assorted animals "
  	+"litter the floor.  Human, erdlu, gith, and many other are "
  	+"easily recognizable amongst the mess.\n");
  add_item(({"chitin","pieces","pieces of chitin"}),
  	"Scraps of chitin chewed to small shards also cover the floor.  "
  	+"There are pieces that look like partially disolved mekillot "
  	+"and kank chitin.\n");
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

   add_exit(SOUTH + "d6","east");
  set_alarm(1.0,0.0,"reset_room");
}

