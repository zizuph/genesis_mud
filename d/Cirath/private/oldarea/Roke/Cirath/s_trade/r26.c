inherit "/std/room";
#include "/d/Roke/common/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <language.h>
#include "/d/Roke/Cirath/defs.h"
#include <macros.h>

void create_room()
{
  set_short("On the southern trade-route");
  
  set_long(break_string(
           "You're travelling a large road near the southern coast "+
           "of Athas. The surroundings are dominated by green grassy, "+
           "not so very high, hills and in the distance you can hear "+
           "seagulls.\n"
           ,60));  

  add_item("road","This is the southern trade-route that leads between "+
           "the cities Tyr and Ciubori.\n");
  add_item(({"brick","bricks"}),"The road is made of them.\n");
  add_item("seagulls","You can just hear them, not see them.\n");

  OUTSIDE;

  add_exit(S_TRADE+"r25","northeast");
  add_exit(S_TRADE+"r27","southwest");

}
