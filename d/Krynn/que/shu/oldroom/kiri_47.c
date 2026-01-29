
#include "../local.h"
inherit ATTACKROOM;
#include "/d/Krynn/common/random_meet.h"

object monster;

void
create_attack_room()
{
    set_short("Temple of the Ancestors");
    set_long(BS("You stand in the center of the temple admiring"
      + " its beauty and architecture. The columns ring the entire"
      + " structure allowing the outside breeze	to pass through unhindered."
      + " Below you is a smooth marble floor that reminds you of"
      + " the temples in Palanthas, while on the dome ceiling is"
      + " a large mural done in brilliant colors. Just being here"
      + " gives you a deep feeling of peace.", 70)); 

    OUTSIDE;

    add_exit(ROOM + "kiri_37","north");
    add_exit(ROOM + "kiri_48","east");
    add_exit(ROOM + "kiri_46","west");
    add_exit(ROOM + "kiri_57","out");

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

