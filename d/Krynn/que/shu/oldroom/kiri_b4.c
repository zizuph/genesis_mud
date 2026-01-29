
#include "../local.h"
inherit ATTACKROOM;
#include "/d/Krynn/common/random_meet.h"

object monster;

void
create_attack_room()
{
    set_short("On a grass path in Que Kiri");
    set_long(BS("You are standing in the middle of a grass path"
      + " within the Que Kiri village. Scattered around you are the"
      + " tents and huts of the Que Kiri people. There is a path"
      + " here that branches off and heads towards the center"
      + " of the village. While your current path continues on through"
      + " the jumble of tents and villagers.", 70)); 

    OUTSIDE;

    add_exit(ROOM + "kiri_a5","northeast");
    add_exit(ROOM + "kiri_a3","northwest");
    add_exit(ROOM + "kiri_c5","southeast");

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

