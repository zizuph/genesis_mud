#include "/d/Krynn/common/defs.h"
#include "/sys/stdproperties.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEINROOM;

create_icewall_room()
{
   
   object door;
   
   set_short("Castle Dungeons");
   set_long(BS("You are in the corridor of the castle dungeons. The"
         +" walls are covered with slime, the air is damp, and"
         +" it smells really bad. The corridor continues north while"
         +" to the east and west are prison cells. To the south"
         +" is the basement of the castle.",70));
   
   add_item("slime",
      "The slime is green and wet and looks like snot.\n");
   add_item("cells",
      "The east cell door appears to be locked.\n");
   add_item("lock",
      "The keyhole is a bit rusty but useable.\n");
   
   add_exit(BASE+"cellw","west",0);
   add_exit(BASE+"prisonn","north",0);
   add_exit(BASE + "basement","south",0);
   
   door = clone_object(ICE_CAST_O + "celldoor.c");
   door->move(TO);
   door->set_key(BASEKEY);
}


