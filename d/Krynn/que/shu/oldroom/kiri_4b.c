
#include "../local.h"
inherit ATTACKROOM;
#include "/d/Krynn/common/random_meet.h"

object monster;

void
create_attack_room()
{
    set_short("On a grass path in Que Kiri");
    set_long(BS("You are standing in front of the Village Hall."
     + " This is where the council elders meet to discuss important"
     + " matters concerning the village. It seems that the council"
     + " is in session now, because a crowd has formed outside"
     + " the hall attempting to listen in on what is being"
     + " argued about on the inside. There is another path here"
     + " that heads off towards the center of the village.", 70));

    OUTSIDE;

    add_exit(ROOM + "kiri_3a","northwest");
    add_exit(ROOM + "kiri_5c","southeast");
    add_exit(ROOM + "kiri_3b","hall");
    add_exit(ROOM + "kiri_5a","southwest");

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

