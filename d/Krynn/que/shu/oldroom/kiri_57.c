
#include "../local.h"
inherit ATTACKROOM;
#include "/d/Krynn/common/random_meet.h"

object monster;

void
create_attack_room()
{
    set_short("Before the Temple of the Ancestors");
    set_long(BS("Traveling a short distance from the arena you stand"
      + " before an impressive building. Almost two stories in height,"
      + " nothing but the surrounding village wall dwarfs this structure."
      + " Its white painted columns ring the whole building, supporting"
      + " a great domed roof that rises into the sky like a full moon"
      + " just coming up over the horizion.", 70)); 

    OUTSIDE;

    add_exit(ROOM + "kiri_47","temple");
    add_exit(ROOM + "kiri_67","south");

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

