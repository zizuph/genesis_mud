inherit "/std/room";
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "defs.h"
#include "/d/Cirath/common/teamer.h"

void
reset_room()
{
    if (leader) return;
bring_room_team(TZ_MINTHOR+"npc/guard",1,2,TZ_MINTHOR+"npc/guard",1);
    leader->set_random_move(5);
    leader->set_restrain_path(({TZ_MINTHOR}));
    leader->set_monster_home(TZ_MINTHOR+"mh18");
}


void
create_room()
 {
  set_short("Passage");
  set_long("A small passage leads northwest, and southwest here. Sounds "
	+"of clanging pots and pans come from the southwest, while to "
	+"the northwest there is nothing but silence. The floor here "
	+"looks worn and a little dull, and the passage itself looks "
	+"like it sees little use.\n");
  add_item("floor","It looks a little dull and worn.\n");
  add_item("passage","It is a small side passage. It is not decorated "
	+"at all, which in itself is unusual. It makes you think that "
	+"this is not an area for visitors.\n");
  add_item(({"house","mansion"}),"You are inside of it.\n");
  ADD_SUN_ITEM
  ADD_ZIG_ITEM
  INSIDE
   add_exit(TZ_MINTHOR + "mh19","northwest", 0);
   add_exit(TZ_MINTHOR + "mh17","southwest", 0);
  set_alarm(1.1,0.0,"reset_room");
}
