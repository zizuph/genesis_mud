inherit "/std/room";
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "defs.h"
#include "/d/Cirath/common/mobber.h"

void
reset_room()
{
   bring_room_mob("guard", TZ_MINTHOR+"npc/guard.c",1,1);
}

void
create_room()
 {
  set_short("Intersection");
  set_long("You have arrived at an intersection that leads in three "
	+"directions.  Northwest leads to what appears to be a ballroom, "
	+"east lies a beautifully crafted staircase, and it appears that "
	+"a hallway stetches off to the west.\n");
  add_item("table","A small wooden table for the guards to eat on, and "
   +"also to play cards on.\n");
  add_item("hallway","You are inside one, and one leads west.\n");
  add_item(({"cot","cots"}),"They are small cots for the guards who are "
   +"between shifts to rest on.\n");
  add_item("staircase","You are standing at the foot of a staircase made of "
        +"obsidian, lined with gold, and braced with steel bars "
        +"This must have cost the owners a fortune.\n");
  add_item(({"house","mansion"}),"You are inside of it.\n");
  ADD_SUN_ITEM
  ADD_ZIG_ITEM
  INSIDE
   add_exit(TZ_MINTHOR + "mh22","northwest", 0);
   add_exit(TZ_MINTHOR + "mh13","east", 0);
   add_exit(TZ_MINTHOR + "mh24","west",0);
  set_alarm(1.1,0.0,"reset_room");
}


