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
           "You are standing outside a impressive wall that is built at the base "+
           "of a mountain. Inside the wall, further east, you can spot a large "+
           "gate covers a tunnel that leads through the mountain. West, the road "+
           "leads into a dry desert.\n"
           ,60));  

  add_item("road","This is the southern trade-route that leads between "+
           "the cities Tyr and Ciubori.\n");
  add_item(({"brick","bricks"}),"The road is made of them.\n");
  add_item(({"mountain","mountains","ridge"}),"The mountains looks quite "+
    "massive.\n");
  add_item(({"cave","tunnel","opening"}),"The tunnel doesn't seem natural. "+
    "Someone or something have made it.\n");
  add_item("gate","The gate leads into the kingdom of Cirath.\n");
  add_item("wall","This is the wall that splits Athas into two. It was built "+
    "to protect the cirathian citizens from the nomads that lives in the desert "+
    "west of the kingdom. However, the nomads, and later on, the barbarians from "+
    "Gont have found a way past it and are now populating the desert east of the "+
    "mountain ridge.\n");
  add_item("desert","You get thirsty just thinking on it...\n");

  OUTSIDE;

  add_exit(S_TRADE+"gate","east");
  add_exit(S_TRADE+"r38","northwest");

}
