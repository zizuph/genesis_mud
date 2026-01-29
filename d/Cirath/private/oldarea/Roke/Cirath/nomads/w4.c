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
           "This is a stream. The water is cold and refreshing. There is a way out "+
           "of the water here. The stream continues east and west, but east it becomes "+
           "impossible to swim.\n"
           ,60));  

  add_item("stream","This stream is rather small, but it's nice to swim in\n");
  add_item("water","The water has the right temperature.\n");

  OUTSIDE;
  WATER;

  add_exit(NOMADS+"p01","up");
}

void
init()
{
  ::init();
  add_action("swimmer","swim");
}

int swimmer(string str)
{
  if (str=="west" && TP->query_skill(SS_SWIM) > 35)
  {
    write("You swim west.\n");
    TP->move_living("swimming",NOMADS+"w3");
    return 1;
  }
  return 0;
}
