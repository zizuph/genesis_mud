inherit "/std/room";
#include "/d/Roke/common/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <language.h>
#include "/d/Roke/Cirath/defs.h"
#include <macros.h>

void create_room()
{
  set_short("In a stream");
  
  set_long(break_string(
           "This is a stream. The water is cold and refreshing. A large wall stops "+
           "the stream west, and east, the stream continues.\n"
           ,60));  

  add_item("stream","This stream is rather small, but it's nice to swim in\n");
  add_item("water","The water has the right temperature.\n");
  add_item("wall","As you look at the wall, you realizes that the water must pass "+
           "somewhere beneath the surface.\n");
  add_item("surface","You examine the surface and beneath it, you discover a way through "+
           "the wall, a hole which you could dive through.\n");
  OUTSIDE;
  WATER;
}

void
init()
{
  ::init();
  add_action("swimmer","swim");
  add_action("diver","dive");
}

int swimmer(string str)
{
  if (str=="east" && TP->query_skill(SS_SWIM) > 35)
  {
    write("You swim east.\n");
    TP->move_living("swimming",NOMADS+"w4");
    return 1;
  }
  return 0;
}

int diver(string str)
{
  if (str=="through hole" && TP->query_skill(SS_SWIM) > 35)
  {
    write("You catch your breath and dive through the hole.\n");
    TP->move_living("",NOMADS+"w2");
    return 1;
  }
  return 0;
}
