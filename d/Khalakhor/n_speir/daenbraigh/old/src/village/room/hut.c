/*
 * Village regular hut
 * TAPAKAH 04/2005
 */

#pragma strict_types

#include <stdproperties.h>

#include "/d/Khalakhor/sys/defs.h"
#include "../../daenbraigh.h"
#include "../../village/village.h"

inherit "/d/Khalakhor/std/room";

object villager1, villager2;

void
create_gvillage_hut()
{
  ::create_khalakhor_room();

  set_short("A inside a hut in " + VILLAGE_NAME);
  set_long("You are inside an ordinary hut inside " + VILLAGE_NAME + ". It "+
	   "has only one room but is relatively spacey. You can see a "     +
	   "sleeping mat near wall and a cupboard opposite to it. A "       +
	   "crudely built table and a stool are in the center of the room. "+
	   "\n");

  add_item(({"mat"}),
	   "A feather filled mat, dirty but intact, obviously for sleeping.\n");
  add_item(({"cupboard"}),
	   "The owner of the hut probably keeps all his belongings inside, clothes,\n"+
	   "tools and dishes. It is locked shut.\n");
  add_item(({"wall","walls","stones","mortar"}),
	   "The walls of the hut are made of stones and mortar.\n");
  add_item(({"table"}),
	   "This all-purpose three-legged table mostly serves the hut inhabitants for\n"+
	   "eating.\n");
  add_item(({"stool"}),
	   "A very simple three-legged stool.\n");
  add_prop(ROOM_I_INSIDE,1);
  reset_room();
}

void
init()
{
  ::init();
}

void
reset_room()
{
  if(! villager1) {
    villager1 = clone_object(V_GOBLIN);
    villager1->move_living("X",TO);
  }
  if(! villager2) {
    villager2 = clone_object(V_GOBLIN);
    villager2->move_living("X",TO);
  }
  if(villager2) {
    villager2->set_monster_home(TO->file_name());
    villager2->set_random_move(30);
    villager2->set_restrain_path(VILLAGEPATH);
  }
}

