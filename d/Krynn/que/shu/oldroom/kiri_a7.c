
#include "../local.h"
inherit ATTACKROOM;
#include "/d/Krynn/common/random_meet.h"

object monster;

void
create_attack_room()
{
    set_short("On a gravel path in Que Kiri");
    set_long(BS("Here the villagers pass you with a smile and a nod"
      + " hurrying off to their duties. To your north you can make out some"
      + " sort of large circular depression in the ground. To the south" 
      + " you can see the open gates of the village off in the"
      + " distance.", 70)); 

    OUTSIDE;

    add_exit(ROOM + "kiri_97","north");
    add_exit(ROOM + "kiri_b7","south");

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

