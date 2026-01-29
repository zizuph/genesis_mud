/*
 * Hammerhands guild, rack room
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

  set_short("Rackroom of Hammerhands guild");
  set_long("In this room guild members store their beloved weapons, the "+
	   "clubs. Various models of clubs, maces and hammers decorate the "+
	   "walls.\n");

  add_item(({"models","clubs","maces","hammers","walls"}),
	   "Beautifully crafted models of the weapons set in sconces adorn "+
	   "the walls.\n");
  add_exit("train","southwest",&check_enter(HH_ACCESS_MEMBER));
  add_prop(HH_INSIDE,1);
  add_prop(ROOM_I_INSIDE,1);
  add_object(HH_RACK);
}

void
reset_room()
{
  ::reset_room();
}
