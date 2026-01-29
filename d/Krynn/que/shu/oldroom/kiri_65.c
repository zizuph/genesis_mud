
#include "../local.h"
inherit ATTACKROOM;
#include "/d/Krynn/common/random_meet.h"

object monster;

void
create_attack_room()
{
    set_short("On grass path in Que Kiri");
    set_long(BS("The path here has seen alot of use as it has"
      + " turned into a large rut that bends towards the southwest"
      + " The reason for such wearing can be seen"
      + " in the large number of villagers coming and going to the"
      + " southwest carrying large jugs and leather containers."
      + " The path continues on to the southeast and the"
      + " northwest.", 70));

    OUTSIDE;

    add_exit(ROOM + "kiri_54","northwest");
    add_exit(ROOM + "kiri_76","southeast");
    add_exit(ROOM + "kiri_74","southwest");

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

