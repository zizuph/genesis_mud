inherit "/std/room";
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "defs.h"
#include "/d/Cirath/common/defs.h"
#include "/d/Cirath/common/mobber.h"

void
reset_room()
{
   object npc = present ("human", TO);
    if(!objectp(npc))
    {
    bring_room_mob("human", DES_NPC+"human",1,1);
    }
}

void
create_room()
 {
  set_short("On a road, east of Tyr");
  set_long("The road continues on an east-west track here.  East "
  	+"heading further away from Tyr, while west leads towards "
  	+"the massive Champion's gate.  Surrounding the road, "
  	+"the desert wastes of Athas rage unchecked, high winds "
  	+"scorching through the valleys, dust storms strong enough "
  	+"to scour bones clean.  For some reason, though, the road "
  	+"never gets the worst of it.\n");
    add_item(({"gate","east gate","champion's gate"}),
    	"Carved through the thick stone walls which surround Tyr, "
    	+"the Champion's Gate is composed of a massive tunnel and "
    	+"the portcullises on either side.  It has kept invaders "
    	+"from breaching Tyr's defences for millenia.\n");
    add_item("road","It is made of earth packed virtually rock "
    	+"hard from use over the ages.\n");
    add_exit(DESERT + "d15","north");
    add_exit(DESERT + "d16","northeast");
    add_exit(DESERT + "d14","northwest");
    add_exit(DESERT + "r3","east");
   add_exit(DESERT + "r1","west");
    add_exit(DESERT + "d8","southwest");
    add_exit(DESERT + "d9","south");
    add_exit(DESERT + "d10","southeast");
   set_alarm(1.0,0.0,"reset_room");
}

