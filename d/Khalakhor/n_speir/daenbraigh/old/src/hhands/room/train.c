/*
 * Hammerhand training room
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

  set_short("Training room of Hammerhands guild");
  set_long("This is the room where the members of the guild train their "+
	   "weapon skill. If the trainer is present, members may <learn> "+
	   "or <improve> their skills. They may also <spar> with him.\n");

  add_exit("pub","west",&check_enter(HH_ACCESS_MEMBER));
  add_exit("join","northwest",&check_enter(HH_ACCESS_MEMBER));
  add_exit("dorm","north",&check_enter(HH_ACCESS_MEMBER));
  add_exit("rack","northeast",&check_enter(HH_ACCESS_MEMBER));
  add_exit("entrance2","southeast",&check_enter(HH_ACCESS_MEMBER));
  add_exit("forge","southwest",&check_enter(HH_ACCESS_MEMBER));
  add_prop(ROOM_I_INSIDE,1);
  add_prop(HH_INSIDE,1);
  add_npc(HH_TRAIN,1,&->equip_me());

}

void
reset_room()
{
  ::reset_room();
}

