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
           "You are travelling on a well-kept road. The gap between "+
           "the river bank and the thick jungle is narrow here. To "+
           "the south is a bridge which leads to the other side of the "+
           "river, where the jungle continues. The road continues in a "+
           "north-south direction.\n"
           ,60));  

  add_item("road","This is the southern trade-route "+
           "that leads to Tyr.\n");
  add_item(({"river","water","stream","durni","Durni"}),"The river "+
           "Durni flows west of you.\n");
  add_item("jungle","This is the jungle that covers the southern "+
           "part of Cirath.\n");
  add_item("bridge","It's a stone bridge that leads over the river Durni./n");

  OUTSIDE;

  add_exit(S_TRADE+"r10","north");
  add_exit(S_TRADE+"r08","south");

}
