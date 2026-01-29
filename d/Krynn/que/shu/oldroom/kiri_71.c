
#include "../local.h"
inherit ATTACKROOM;
#include "/d/Krynn/common/random_meet.h"

object monster;

void
create_attack_room()
{
    set_short("On a grass path in Que Kiri");
    set_long(BS("You are standing at the western most end of the great"
    + " walled village. Here the concentrations of tents and huts are"
    + " the highest, making for a great deal of activity. There are"
    + " women working on magnificent woven cloths and colorful ceremonial"
    + " robes off to your left, while you can spot leather hides and"
    + " meat drying in the sun towards your right. The children soon"
    + " form a ring around you staring in awe at your strange clothing"
    + " and unusual gestures, laughing and giggling until something else"
    + " captures their attention and they run off.", 70));

    OUTSIDE;

    add_exit(ROOM + "kiri_61","north");
    add_exit(ROOM + "kiri_81","south");

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

