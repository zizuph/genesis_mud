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
  set_long("The barrens end here at a low cliff face.  Ribbons of "
  	+"color run through the wall in front of you, giving a brief "
  	+"glimpse of Athas's history.  A dim cave mouth opens to the "
  	+"west here, the reek of rotting meat polluting the air.  "
  	+"Large rocks are piled around here, as well as large chunks "
  	+"of rock sprouting from the ground like jagged tree "
  	+"stumps.\n");
  add_item("cave","A shallow depression in the cliff face, more than "
  	+"adequate for a few creatures to use for shelter.\n");
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

  add_exit(SOUTH + "d4","south");
  add_exit(SOUTH + "d3","southeast");
  add_exit(SOUTH + "d5","west");
  add_exit(SOUTH + "d7","east");
  add_exit(SOUTH + "d16","north");
  add_exit(SOUTH + "d15","northeast");
  set_alarm(1.0,0.0,"reset_room");
}

