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
           "This is a small path in a desert canyon. Once was this a river, but it has "+
           "dried out eons ago. South lies a large rock, which ends the path in that "+
           "direction. Past the rock, you can see a pretty large road. The path continues "+
           "northeast through the canyon.\n"
           ,60));  

  add_item("path","It's small and narrow.\n");
  add_item("canyon","It's deep and impressive.\n");
  add_item("road","The road is south of you and leads west through the canyon and "+
           "southeast out of it.\n");
  add_item("desert","You get thirsty just thinking on it...\n");
  add_item(({"rock","rocks"}),"Some are large and many are small and there's a lot of them "+
    "here! The large rock south of you seems climbable.\n");

  OUTSIDE;

  add_exit(NOMADS+"r02","northeast");
}

void
init()
{
  ::init();
  add_action("climber","climb");
}

int climber(string str)
{
  if (str=="rock" && TP->query_skill(SS_CLIMB) > 45)
  {
    write("You climb the rock and slip easily down on the other side.\n");
    TP->move_living("",S_TRADE+"r38");
    return 1;
  }
  return 0;
}
