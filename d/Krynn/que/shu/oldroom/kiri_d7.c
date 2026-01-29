
#include "../local.h"
inherit ATTACKROOM;
#include "/d/Krynn/common/random_meet.h"

object monster;

void
create_attack_room()
{
    set_short("On a gravel path in Que Kiri");
    set_long(BS("You look out over a large bustling village"
      + " amazed that such life could spring up out of the"
      + " desolate plains that surrounds it.	To your left and"
      + " right you can see paths leading off to tents and huts."
      + " While the gravel path continues north, to what seems to be"
      + " the very center of the village itself.", 70)); 

    OUTSIDE;

    add_exit(ROOM + "kiri_d8","east");
    add_exit(ROOM + "kiri_d6","west");
    add_exit(ROOM + "kiri_c7","north");
    add_exit(ROOM + "kiri_e7","south");

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

