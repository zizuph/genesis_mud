/*
 * Hammerhands guild, north entrance
 * TAPAKAH, 10/2005
 */

#pragma strict_types

#include <stdproperties.h>

#include "/d/Khalakhor/sys/defs.h"

#include "../../daenbraigh.h"
#include "../../hhands/hhands.h"

inherit "/d/Khalakhor/std/room";
inherit HH_GUILDROOM;

void
create_khalakhor_room()
{
  ::create_khalakhor_room();

  set_short("Entrance to Hammerhand guild");
  set_long("You are standing at the entrance to a cube-like building. "+
	   "A low arch leads inside. Above the arch you see an emblem of "+
	   "two crossed clubs above a forge and a letter 'H' at each side "+
	   "of the club. To the northwest a path leads into the conifer "+
	   "forest surrounding the building. You hear thumping and clanking "+
	   "sounds from within, followed by colorful curses.\n");
  add_item(({"arch","entrance"}),
	   "A low arch, awkward for tall people like humans and elves, "+
	    "leads inside the building.\n");
  add_item(({"clubs","forge","letter","letters","emblem"}),
	   "The emblem shows two crossed clubs, handles down. Beneath the "+
	   "cross point is a crude blacksmith's forge, and the emblem is "+
	   "flanked by two letters 'H'.\n");
  add_item(({"trees","firs","pines","pine","tree","fir","forest"}),
	   "Mighty trees compete in reaching the sun, growing thickly. Some "+
	   "of them bear marks of arrow heads, sword blades and club thumps."+
	   "\n");
  add_item(({"path","trail"}),
	   "The path is obviously well-kept and cleaned regularly.\n");
	   
  add_exit("join","southeast",&check_enter(HH_ACCESS_ALL));
  add_exit("path10","northwest");
  add_npc(HH_GUARD,2,&->set_guard());
  add_prop(ROOM_I_INSIDE,0);
  add_prop(HH_INSIDE,0);
}

void
reset_room()
{
  ::reset_room();
}
