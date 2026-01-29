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
           "You're travelling on a road on the cirathian plains that "+
           "covers the southern part of Athas. The plains are covered "+
           "with grass. West lies a mountain ridge and east, the plains "+
           "continue.\n"
           ,60));  

  add_item("road","This is the southern trade-route that leads between "+
           "the cities Tyr and Ciubori.\n");
  add_item(({"brick","bricks"}),"The road is made of them.\n");
  add_item(({"plain","plains"}),"They're flat.\n");
  add_item(({"mountain","mountains","ridge"}),"The mountains looks quite "+
    "massive.\n");

  OUTSIDE;

  add_exit(S_TRADE+"r33","east");
  add_exit(S_TRADE+"r35","west");

}
