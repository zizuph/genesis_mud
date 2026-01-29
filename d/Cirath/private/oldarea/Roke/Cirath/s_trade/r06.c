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
           "The road leads close to the eastern bank of the large "+
           "river Durni. You have a jungle to your east and you can "+
           "see that it continues on the other side of the river. "+
           "The road bends here to the southeast and away from the river.\n"
           ,60));  

  add_item("road","This is the southern trade-route "+
           "that leads to Tyr.\n");
  add_item(({"river","water","stream","durni","Durni"}),"The river "+
           "Durni flows west of you.\n");
  add_item("jungle","This is the jungle that covers the southern "+
           "part of Cirath.\n");

  OUTSIDE;

  add_exit(S_TRADE+"r07","north");
  add_exit(S_TRADE+"r05","southeast");

  reset_room();
}
