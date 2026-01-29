inherit "/std/room";
#include "/d/Roke/common/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <language.h>
#include "/d/Roke/Cirath/defs.h"
#include <macros.h>

void create_room()
{
  set_short("On a desert path");
  
  set_long(break_string(
           "You are standing on a small path in a canyon. A stream, that flows in east-"+
           "west direction, makes some vegetation to grow here in the desert.\n"
           ,60));  

  add_item("path","It's small and narrow.\n");
  add_item("canyon","It's deep and impressive.\n");
  add_item("desert","You get thirsty just thinking on it...\n");
  add_item("stream","The water looks lovely!\n");
  add_item("water","What shouldn't you give to dive into that water!\n");
  add_item("vegetation","Just some low bushes and grass, but better than nothing.\n");

  OUTSIDE;
  WATER;

  add_exit(NOMADS+"r05","northwest");
  add_exit(NOMADS+"r03","south");
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
