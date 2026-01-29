inherit "/std/room";
#include "/d/Cirath/common/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "defs.h"
#include "/d/Cirath/common/mobber.h"

void
reset_room()
{
  bring_room_mob("human",TZ_MINTHOR+"npc/lilam",1,1);
}

void
create_room()
 {
  set_short("Solarium");
  set_long("You are now at the very back of the house.  This room has "
	+"what appears to be crystalline windows that let diffuse light "
	+"into the room.  There are a couple of padded chairs and some "
	+"cushions on the floor for people to relax in.  The most unusual "
	+"thing you notice here, though, are the plants.  They line the "
	+"base of the windows and hang from the ceiling.  It is "
	+"unimaginable the amount of money it takes to provide for so many "
	+"plants.  The Minthor's must have a vast fortune.\n");
  add_item("wall","The wall is off to your side.\n");
  add_item("hallway","It leads in all directions.\n");
  add_item(({"stone","stones"}),"The stairs are made of some precious "
        +"ones. There are obsidian steps, with other glittering jewels "
        +"set in.\n");
  add_item(({"cushion","cushions"}),"There are a few cushions thrown around "
        +"the room which appear to be used to sit in.\n");
  add_item("ceiling","It is above you.\n");
  add_item("plants","There are a large variety of plants, none which you "
        +"are familiar with.  In a land with virtually no water, this is "
        +"an exercise in wealth and waste.\n");
  add_item(({"house","mansion"}),"You are inside of it.\n");
  add_item(({"windows","window","crystalline windows"}),"They appear to "
	+"be made of some form of strange translucent crystal that only "
	+"allows a fraction of the overpowering sun into the room.\n");
  add_item(({"chair","chairs","padded chairs","padded chair"}),"These "
	+"chairs are very soft and comfortable, they seem to almost mold "
	+"to your body.\n");
  ADD_SUN_ITEM
  ADD_ZIG_ITEM
  INSIDE
  add_exit(TZ_MINTHOR + "mh27","south",0);
  add_exit(TZ_MINTHOR + "mh21","west",0);
  add_exit(TZ_MINTHOR + "mh19","east",0);
  set_alarm(1.1,0.0,"reset_room");
}

