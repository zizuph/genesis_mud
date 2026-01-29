inherit "/std/room";
#include "/d/Roke/common/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <language.h>
#include "/d/Roke/Cirath/defs.h"
#include <macros.h>

object guard1,guard2;

void
reset_room()
{

  if (!guard1 && !guard2)
  {
    guard1=clone_object(MONSTER+"c_guard");
    guard1->move(this_object());
    guard2=clone_object(MONSTER+"c_guard");
    guard2->move(this_object());
    tell_room(TO,"Two guardians take their posts.\n");
  }
}

void create_room()
{
  set_short("On the southern trade-route");
  
  set_long(break_string(
           "This is the southern trade-route, the road that leads from "+
           "the city of Tyr to the "+
           "cirathian city Ciubori. The road is well-kept and made of "+
           "stone bricks, which makes it comfortable to walk on. "+
           "Northeast, you can see a vast jungle and to your west flows "+
           "the river Durni.\n"
           ,60));  

  add_item("road","This is the southern trade-route "+
           "that leads to Tyr.\n");
  add_item(({"river","water","stream","durni","Durni"}),"The river "+
           "Durni flows west of you.\n");
  add_item("jungle","This is the jungle that covers the southern "+
           "part of Cirath.\n");
  add_item(({"brick","bricks"}),"The bricks are flat and polished by the "+
           "many feet that have walked on them.\n");

  OUTSIDE;

  add_exit(S_TRADE+"r06","northwest");
  add_exit(S_TRADE+"r04","south");

  reset_room();
}
