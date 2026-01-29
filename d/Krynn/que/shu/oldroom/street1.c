/* created by Aridor 06/28/94 */

#include "../local.h"
inherit ATTACKROOM;
#include "/d/Krynn/common/random_meet.h"
#define TABLE "/d/Krynn/common/rndtables/tblwar"

object monster;

void
create_attack_room()
{
    set_short("In a street in Que Kiri");
    set_long("You are standing in a peaceful street in the " +
	     "middle of Que Kiri. The village is bustling " +
	     "with activity.\n");

    OUTSIDE;

    add_exit(ROOM + "street1","west");
    add_exit(ROOM + "street1","east");
    add_exit(ROOM + "street1","north");
    add_exit(ROOM + "street1","south");

}

int
hook_change_room(int which)
{
    if (which == 0)
      {
	  if (monster)
	    return 0;
	  monster = RANDOM_MEET(TABLE);
	  monster->move_living("xx",TO);
	  return 1;
      }
    if (which == 1)
      if (monster)
	return 0;
    return 1;
}

