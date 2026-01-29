/*
 * Hammerhands guild, startloc room
 * TAPAKAH, 10/2005
 */
#pragma strict_types

#include <stdproperties.h>

#include "/d/Khalakhor/sys/defs.h"

#include "../../daenbraigh.h"
#include "../../hhands/hhands.h"

inherit "/d/Khalakhor/std/room";
inherit HH_GUILDROOM;

int start(string str);

void
create_khalakhor_room()
{
  ::create_khalakhor_room();

  set_short("Dormitory of Hammerhands guild");
  set_long("You are standing in the dormitory of the guild. You see bunks "+
	   "lined along the walls in a military fashion. You can <start "+
	   "here> if you want.\n");
  add_item(({"bunks","walls"}),
	   "Short, narrow beds line up the walls. The beds are barely five "+
	   "feet in length so they obviously are not fitted for elves or " +
	   "humans.\n");
  add_exit("join","west",&check_enter(HH_ACCESS_ALL));
  add_exit("train","south",&check_enter(HH_ACCESS_MEMBER));
  add_prop(HH_INSIDE,1);
  add_prop(ROOM_I_INSIDE,1);
}
void
reset_room()
{
  ::reset_room();
}
void
init() {

  ::init();
  add_action("start","start");
 
}

int
start(string str) {

  if (str!="here")
    write("Start where?\n");
  else {
    write("Okay, from now on you will start here.\n");
    TP->set_default_start_location(file_name(TO));
  }
  return 1;
}
