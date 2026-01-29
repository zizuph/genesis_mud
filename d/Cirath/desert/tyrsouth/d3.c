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
  set_long("The cracked earth of the barrens gradual merges into "
  	+"an area covered by large boulders and rocky outcroppings.  "
  	+"Strangely shaped rocks stretch up from the ground at all "
  	+"angles, providing shade from the sun, but also providing "
  	+"concealment for enemies.\n");
  add_item(({"boulders","rocks","outcroppings","rocky outcroppings"}),
  	"Large rough edged rocks thrust upward from the ground, some "
  	+"still part of some massive formation, some broken shards "
  	+"of it.\n");
  add_item("shade","A rare thing on Athas, and a thing even rarer to "
  	+"find unoccupied.  Things lurk in the shade, beware.\n");
  add_exit(SOUTH + "d4","west");
  add_exit(SOUTH + "d2","east");
  add_exit(SOUTH + "d6","northwest");
  add_exit(SOUTH + "d7","north");
  add_exit(SOUTH + "d8","northeast");
  set_alarm(1.0,0.0,"reset_room");
}

