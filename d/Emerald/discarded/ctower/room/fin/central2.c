#include "../../ctower.h"

inherit FINSTD;

#include "/d/Emerald/quest_handler/quest_handler.h"
#include <macros.h>
 
void
create_fin()
{
  set_short("Central hall");
 
  set_long("You are in the central hall of the tower.  "+
     "There is a huge crystal chandelier floating near the ceiling, "+
     "giving off a rainbow of colors that make you dizzy if you "+
     "stare at them too long.\n");
 
  add_item(({"chandelier"}), "You examine the chandelier "+
     "and get dizzy, almost falling down.  You only manage to keep your "+
     "balance when you look away.  You feel a little sick.\n");
 
  add_exit(CTOWER_ROOM_FIN + "finalsu1", "northwest");
  add_exit(CTOWER_ROOM_FIN + "finalsu3", "southwest");
  add_exit(CTOWER_ROOM_FIN + "finalsu2", "northeast");
  add_exit(CTOWER_ROOM_FIN + "finalsu4", "southeast");
}
 
int
sing(string str)
{
  notify_fail("Sing what?\n");
  if (strlen(str))
  {
    return 0;
  }

  if (!QH_QUEST_COMPLETED(this_player(), CTOWER_QUEST_NAME))
  {
    return 0;
  }
   
  write("You start singing and find yourself magically transferred.\n");

  if (!this_player()->move_living("M", CTOWER_ROOM + "central1", 1))
  {
    say(QCTNAME(this_player()) +
        "The chandelier starts to glow. Getting brighter and brighter until "+
        "the room is nothing but a blinding radiance. The light lasts but a "+
        "moment, and when your eyes readjust to the now dim light, you "+
        "notice that " + this_player()->query_pronoun() + " has " +
        "disappeared.\n");

    tell_room(CTOWER_ROOM + "central1", 
        "The chandelier starts to glow. Getting brighter "+
        "and brighter until the room is nothing but a blinding radiance. "+
        "The light lasts but a moment, and when your eyes readjust to the "+
        "now dim light, you notice that " + QTNAME(this_player()) +
        " has appeared.\n", this_player());
  }
 
  return 1;
}
 
int
touch(string str)
{
  notify_fail("Touch what?\n");
  if (str != "chandelier" && str != "the chandelier")
  {
    return 0;
  }
 
  write("You can't reach the chandelier.\n");
  return 1;
}

void
init()
{
  ::init();

  add_action(sing, "sing");
  add_action(touch, "touch");
}
