inherit "/std/room";
#include "/d/Roke/common/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <language.h>
#include "/d/Roke/Cirath/defs.h"
#include <macros.h>

void create_room()
{
  set_short("On a path");
  
  set_long(break_string(
           "You are standing on a small path close to a stream. There are high mountains "+
           "to the north and south. The vegatation is sparse here.\n"
           ,60));  

  add_item("path","It's small and narrow.\n");
  add_item("stream","The water looks lovely!\n");
  add_item("water","What shouldn't you give to dive into that water!\n");
  add_item("vegetation","Just some low, dry bushes and grass.\n");

  OUTSIDE;
  WATER;

  add_exit(NOMADS+"p02","southeast");
}

void
init()
{
  ::init();
  add_action("diver","dive");
}

int diver(string str)
{
  if (str=="into water" && TP->query_skill(SS_SWIM) > 35)
  {
    write("You dive into the stream.\n");
    TP->move_living("",NOMADS+"w1");
    return 1;
  }
  return 0;
}
