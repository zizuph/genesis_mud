inherit "/std/room";
#include "/d/Roke/common/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <language.h>
#include "/d/Roke/Cirath/defs.h"
#include <macros.h>

object monster;

void
reset_room()
{

  if (!monster)
  {
    monster=clone_object(MONSTER+"traveller");
    monster->move(this_object());
    tell_room(TO,"A traveller arrives.\n");
  }
}

void create_room()
{
  set_short("On the southern trade-route");
  
  set_long(break_string(
           "This is the southern trade-route which is one of "+
           "two large roads that leads through the island of "+
           "Cirath. The southern trade-route goes between the "+
           "cities of Tyr and Ciubori. It's covered with stone "+
           "bricks. The landscape is covered with grassy hills "+
           "and south you can see the sea.\n"
           ,60));  

  add_item("road","This is the southern trade-route that leads between "+
           "the cities Tyr and Ciubori.\n");
  add_item(({"brick","bricks"}),"The road is made of them.\n");
  add_item("seagulls","You can just hear them, not see them.\n");
  add_item("sea","The sea that Athas is surrounded by.\n");
  add_item(({"hill","hills"}),"They are quite low and not difficult "+
           "to climb.\n");

  OUTSIDE;

  add_exit(S_TRADE+"r27","east");
  add_exit(S_TRADE+"r29","west");

  reset_room();
}
