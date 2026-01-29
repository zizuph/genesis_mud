/*
 * Village elder tent
 * TAPAKAH 05/2005
 */

#pragma strict_types

#include <stdproperties.h>
#include <macros.h>

#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/sys/terrain.h"

#include "../../daenbraigh.h"
#include "../../village/village.h"

inherit "/d/Khalakhor/std/room";
inherit DAENBRAIGH_BASE;

object elder;
object servant;
object chest;

void
create_khalakhor_room()
{
  ::create_khalakhor_room();

  set_short("Elder's tent in " + VILLAGE_NAME);
  set_long("You are inside the tent of the elder of " + VILLAGE_NAME + " " +
	   "It is very spartan here, but tidy. There is a small cot and "  +
	   "a locked chest. A set of skulls is forming a line, and a few " +
	   "papers with sketches on them are in the corner. There is also "+
	   "a set of bottles near the entrance.\n");
  add_exit("crossing","out",0);
  add_item(({"cot"}),
	   "The cot is obviously for both sleeping and sitting of the "+
	   "elder.\n");
  add_item(({"skull","skulls"}),
	   "The skulls look at you with their empty eyesockets.\n");
  add_item(({"bottles","bottle"}),
	   "They are quite dusty and have a repulsive smell and you "+
	   "really do not want to touch them.\n");
  add_item(({"paper","papers","sketch","sketches"}),
	   "They have some indistinguishable drawings and writings on "+
	   "them.\n");
  add_prop(ROOM_I_INSIDE,1);
  add_npc(V_ELDER,1,&->equip_me());
  add_npc(V_SERVANT);
  add_object(V_CHEST);
}

void
init()
{

  ::init();
}

void
reset_room()
{
  ::reset_room();
}

int *
query_local_coords()
{
  return ({-5,0});
}
