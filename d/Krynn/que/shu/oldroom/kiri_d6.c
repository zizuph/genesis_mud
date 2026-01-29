
#include "../local.h"
inherit ATTACKROOM;
#include "/d/Krynn/common/random_meet.h"

object monster;

void
create_attack_room()
{
    set_short("On a grass path in Que Kiri");
    set_long(BS("You are standing in the middle of a grass path"
      + " within the Que Kiri village. The sights and sounds of"
      + " the village overwhelm your senses. Never have you seen"
      + " such a close, interworking group of people. To the northwest"
      + " you spot the beginnings of some tents, which seem to be the"
      + " the main living quarters to these people. To the east you"
      + " spot the entrance of the village.", 70));

    OUTSIDE;

    add_exit(ROOM + "kiri_c5","northwest");
    add_exit(ROOM + "kiri_d7","east");

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

