
#include "../local.h"
inherit ATTACKROOM;
#include "/d/Krynn/common/random_meet.h"

object monster;

void
create_attack_room()
{
    set_short("On a grass path in Que Kiri");
    set_long(BS("You are standing in the middle of a grass path"
      + " within the Que Kiri village. To the southeast you notice"
      + " a large offical looking building with people milling about"
      + " around the front of it. Towards the northwest"
      + " you can make out some small stone structures.", 70));
  set_change_long(1,BS(BURN_MACG+BURN_MACF+BURN_SCREAMA+BURN_SHAPESE,70));

    OUTSIDE;

    add_exit(ROOM + "kiri_29","northwest");
    add_exit(ROOM + "kiri_4b","southeast");

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

