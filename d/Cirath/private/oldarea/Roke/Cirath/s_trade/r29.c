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
           "You are travelling on the southern trade-route, between "+
           "the city Tyr and the cirathian city Ciubori. The road leads "+
           "through grassy plains near the south coast of Athas and to "+
           "the east you can see that the landscape is shifting to low, "+
           "grassy hills.\n"
           ,60));  

  add_item("road","This is the southern trade-route that leads between "+
           "the cities Tyr and Ciubori.\n");
  add_item(({"brick","bricks"}),"The road is made of them.\n");
  add_item("seagulls","You can just hear them, not see them.\n");
  add_item("sea","The sea that Athas is surrounded by.\n");
  add_item(({"hill","hills"}),"They are quite low and not difficult "+
           "to climb.\n");
  add_item(({"plain","plains"}),"They're flat.\n");

  OUTSIDE;

  add_exit(S_TRADE+"r28","east");
  add_exit(S_TRADE+"r30","west");

}
