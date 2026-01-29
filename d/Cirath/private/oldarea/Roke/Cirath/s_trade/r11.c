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
           "You're standing on the southern trade-route. A smaller road "+
           "leads into a little village to the northeast. To the north"+
           "west lies a small wooden pier where Krull ship travellers over "+
           "the river Durni. Southwest, the road continues towards the "+
           "city Ci'u'bori.\n"
           ,60));  

  add_item("road","This is the southern trade-route "+
           "that leads to Tyr.\n");
  add_item(({"river","water","stream","durni","Durni"}),"The river "+
           "Durni flows west of you.\n");
  add_item("jungle","This is the jungle that covers the southern "+
           "part of Cirath.\n");
  add_item("village","It's a small village, dominated by low, wooden buildings./n");
  add_item(({"city","ciubori"}),"A cirathian city that lies south of here.\n");
  add_item("pier","It's a wooden pier nortwest of you.\n");

  OUTSIDE;

  add_exit(S_VILLAGE+"r01","northeast");
  add_exit(S_TRADE+"r12","northwest");
  add_exit(S_TRADE+"r10","southwest");

  reset_room();
}
