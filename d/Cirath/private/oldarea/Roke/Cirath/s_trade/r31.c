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
           "You're on a road on the plains of central Athas. The plains "+
           "are covered with green, healthy grass. Far away to the west, you "+
           "can see a mountain ridge and east, low hills exchanges the plains.\n"
           ,60));  

  add_item("road","This is the southern trade-route that leads between "+
           "the cities Tyr and Ciubori.\n");
  add_item(({"brick","bricks"}),"The road is made of them.\n");
  add_item("seagulls","You can just hear them, not see them.\n");
  add_item("sea","The sea that Athas is surrounded by.\n");
  add_item(({"hill","hills"}),"They are quite low and not difficult "+
           "to climb.\n");
  add_item(({"plain","plains"}),"They're flat.\n");
  add_item(({"mountain","mountains","ridge"}),"The mountains looks quite "+
    "massive.\n");

  OUTSIDE;

  add_exit(S_TRADE+"r30","southeast");
  add_exit(S_TRADE+"r32","west");

}
