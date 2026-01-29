inherit "/std/room";
#include "/d/Cirath/common/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/d/Cirath/tyr/tyr.h"
#include "defs.h"
#include "/d/Cirath/common/mobber.h"

void
reset_room()
{
   bring_room_mob("guard", TYR_NPC+"guard", 1, 1);
}

 
create_room()
 {
  set_short("Short Hallway");
  set_long("You are in a small hallway between the stairs leading down "
	+"and the route to the bedrooms of the house.  There are two "
	+"incredibly ornate doors here, one to the southeast, one to "
	+"the southwest.  The hall also turns northward towards another "
	+"part of the house.  Above you head you see a red crystalline "
   +"skylight, which bathes the area in an eerie pink light.  It "
	+"reminds you of the color of crushed brains.\n");
  add_item(({"wall","walls"}),"The walls stretch "
	+"around you.\n");
  add_item(({"skylight","crystalline skylight"}),"Above your head in a "
	+"recessed part of the ceiling you see the large skylight.  It "
	+"was obviously placed there to allow light in, but it is curious "
	+"that someone would choose such a strange shade of red.  It was "
	+"probably created by either templar magic, or some extremely "
	+"talented crystal worker.\n");
  add_item(({"door","doors","southeast door","southwest door"})," The doors "
	+"look to be made of beautiful carved agafari wood, which is known "
	+"for its strength and durability.  It would be a mistake to try and "
	+"break it down.\n");

  ADD_SUN_ITEM
  
  INSIDE

  add_exit(TZ_MINTHOR + "mh28","east",0);
  add_exit(TZ_MINTHOR + "mh31","southwest","@@door");
  add_exit(TZ_MINTHOR + "mh30","southeast","@@door");
  add_exit(TZ_MINTHOR + "mh32","north",0);
  set_alarm(1.1,0.0,"reset_room");
}

door()
{
        write("You gently twist the obsidian knob on the door, and "
	+"it swings open noiselessly.\n");
        return 0;
}


