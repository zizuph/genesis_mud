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
  set_long("Large rocks dot the landscape here, some lying flat on "
  	+"the ground, some standing and pointing straight towards the "
  	+"sky.  East of here, the the landscape flattens out and the "
  	+"large rocks are no longer present, but for some reason, there "
  	+"are a large number of them here.\n");
  add_item(({"large rocks","rocks","outcroppings","rocky outcroppings"}),
  	"Large rough edged rocks thrust upward from the ground, some "
  	+"still part of some massive formation, some broken shards "
  	+"of it.\n");
  add_item("shade","A rare thing on Athas, and a thing even rarer to "
  	+"find unoccupied.  Things lurk in the shade, beware.\n");
  add_exit(SOUTH + "d7","west");
  add_exit(SOUTH + "d9","east");
  add_exit(SOUTH + "d15","northwest");
  add_exit(SOUTH + "d14","north");
  add_exit(SOUTH + "d13","northeast");
  add_exit(SOUTH + "d3", "southwest");
  add_exit(SOUTH + "d2", "south");
  add_exit(SOUTH + "d1", "southeast");
  set_alarm(1.0,0.0,"reset_room");
}

