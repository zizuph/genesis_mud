
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
      + " tents and huts of the Que Kiri people. While there are"
      + " plenty of women and children working and playing here,"
      + " you start to notice a lack of young men. You attempt"
      + " to question a young girl about it, but she just smiles"
      + " and grins not really understanding your language."
      + " You decide that they all must be off on some hunting"
      + " expedition.", 70)); 

    OUTSIDE;

    add_exit(ROOM + "kiri_ba","northeast");
    add_exit(ROOM + "kiri_d8","southwest");

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

