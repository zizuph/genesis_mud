inherit "/std/room";
#include "/d/Cirath/common/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "defs.h"
#include "/d/Cirath/common/mobber.h"

void
reset_room()
{
    bring_room_mob("guard", TZ_MINTHOR+"npc/guard",1,1);
}

void
create_room()
 {
  set_short("Corner of Hall");
  set_long("You are in a short hallway which leads east towards the center "
	+"of the house and south back towards the entrance.  This is "
	+"a pretty nondescript part of the house and is slightly "
	+"disappointing considering the lavishness of the rest of the house.\n");
  add_item("wall","The wall is off to your side.\n");
  add_item("hallway","It leads south and east directions.\n");
  add_item("ceiling","It is above you.\n");
  add_item(({"house","mansion"}),"You are inside of it.\n");

  ADD_SUN_ITEM
  ADD_ZIG_ITEM
  INSIDE

  add_exit(TZ_MINTHOR + "mh25","south",0);
  add_exit(TZ_MINTHOR + "mh23","east",0);
  set_alarm(1.1,0.0,"reset_room");
}

