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
   leader->set_monster_home(TZ_MINTHOR+"mh19");
}


void
create_room()
 {
  set_short("Guardroom");
  set_long("You have entered what seems to be a small guardroom. "
   +"This is where the guards to the Minthor house stay when they "
   +"are between shifts. There are a few small cots back in the "
  +"corner of the room, while in the center is a small table. The "
   +"guards here are highly trained, and don't like unwelcome visitors "
   +"so if you weren't invited, beware.\n");
  add_item("table","A small wooden table for the guards to eat on, and "
   +"also to play cards on.\n");
  add_item("guardroom","It is what you are standing in. It also looks "
   +"to be an unwelcome place for visitors, unless they are looking for "
   +"a fight.\n");
  add_item(({"cot","cots"}),"They are small cots for the guards who are "
   +"between shifts to rest on.\n");
  add_item(({"house","mansion"}),"You are inside of it.\n");
  ADD_SUN_ITEM
  ADD_ZIG_ITEM
  INSIDE
   add_exit(TZ_MINTHOR + "mh20","west", 0);
   add_exit(TZ_MINTHOR + "mh18","southeast", 0);
  set_alarm(1.1,0.0,"reset_room");
}

