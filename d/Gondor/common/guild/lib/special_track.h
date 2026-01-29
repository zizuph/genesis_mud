#include "/d/Gondor/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

#define RACE_ARRAY ({ "elf","gnome","dwarf","human","goblin" })

int
confuse(string str, object room)
{
  room = TP->query_prop(LIVE_O_LAST_ROOM);

  if(!str) NFN0("What?");
  if(str != "trail") NFN0("Confuse who?");

  if(TP->query_skill(SS_TRACKING)+TP->query_stat(SS_INT)/10 >
    35+random(66))
  {
    write("You do your best to confuse the trail behind you.\n");
    say(QCTNAME(this_player())+" bends downs and does something "+
      "to the trail behind "+OBJECTIVE(this_player())+".\n");
    room->add_prop(ROOM_S_DIR,({ ONE_OF_LIST(room->query_exit_cmds()),
      ONE_OF_LIST(RACE_ARRAY) }));
    return 1;
  }
  else
  {
    write("You do your best to confuse the trail behind you.\n");
    say(QCTNAME(this_player())+" bends downs and does something "+
      "to the trail behind "+OBJECTIVE(this_player())+".\n");
    return 1;
  }
}
