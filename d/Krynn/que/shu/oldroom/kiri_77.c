
#include "../local.h"
inherit ATTACKROOM;
#include "/d/Krynn/common/random_meet.h"

object monster;

void
create_attack_room()
{
    set_short("Center of arena");
    set_long(BS("You stand on a circle of grass in the center"
      + " of the great arena. The stone steps rise up around you"
      + " as if you were in the bottom of a great bowl. You've heard"
      + " that the barbarians of the plains are well known for their"
      + " games of strength and courage. You envision yourself"
      + " facing down one of the Que Kiri's massive warriors,"
      + " and showing the village what a real warrior can do." 
      + " You open your eyes suddenly and come back to the real"
      + " world.", 70));

    OUTSIDE;

    add_exit(ROOM + "kiri_67","north");
    add_exit(ROOM + "kiri_76","west");
    add_exit(ROOM + "kiri_87","south");
    add_exit(ROOM + "kiri_78","east");
    
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

