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
           "You're standing on a bricked road in the hostile desert. TThe road is free "+
           "from sand which seems very strange. Someone is appearantly keeping it clean.\n"
           ,60));  

  add_item("road","This is the southern trade-route that leads between "+
           "the cities Tyr and Ciubori.\n");
  add_item(({"brick","bricks"}),"The road is made of them.\n");
  add_item("desert","You get thirsty just thinking on it...\n");
  add_item("sun","It shines on you unmercifully.\n");

  OUTSIDE;

  add_exit(S_TRADE+"r46","east");
  add_exit(S_TRADE+"r48","southwest");

  reset_room();
}
