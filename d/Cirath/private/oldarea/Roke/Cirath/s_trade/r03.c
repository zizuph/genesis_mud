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
           "You are standing on a large road on the east side of "+
           "the river Durni. South it leads into the marches of "+
           "Durni's mouth to the sea where you can see a large city "+
           "surrounded by water. Northeast, the road leaves the river "+
           "and get closer to a jungle.\n"
           ,60));  

  add_item("road","This is the southern trade-route "+
           "that leads to Tyr.\n");
  add_item(({"river","water","stream","durni","Durni"}),"This is the "+
           "mouth of the large river Durni.\n");
  add_item(({"march","marches","swamp"}),"The area is full of water "+
           "and the ground is not very reliable there.\n");
  add_item(({"city","ciubori","town","Ciubori"}),"This is the third "+
           "city of Cirath. It's magnifique.\n");
  add_item("jungle","This is the jungle that covers the southern "+
           "part of Cirath.\n");

  OUTSIDE;

  add_exit(S_TRADE+"r04","northeast");
  add_exit(S_TRADE+"r02","south");

}
