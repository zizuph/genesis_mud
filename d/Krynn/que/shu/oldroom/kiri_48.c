
#include "../local.h"
inherit ATTACKROOM;
#include "/d/Krynn/common/random_meet.h"

object monster;

void
create_attack_room()
{
    set_short("Temple of the Ancestors");
    set_long(BS("Sunlight streams through the columns here warming"
      + " your face and making the marble that you stand upon gleam"
      + " that much brighter. In glancing at the marble you notice"
      + " and inscription inlayed into the floor. Just another"
      + " testiment to the craftsmen who built this place.", 70)); 

    OUTSIDE;

    add_exit(ROOM + "kiri_47","west");

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

