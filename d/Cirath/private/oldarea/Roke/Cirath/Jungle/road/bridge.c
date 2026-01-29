inherit "/std/room";
#include "/d/Roke/common/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <language.h>
#include "/d/Roke/Cirath/defs.h"
#include <macros.h>

reset_room()
{
  if(MAL("guard")) return;

  clone_object(MONSTER+"bguard")->move(TO);
  tell_room(TO,"A guard takes post on the bridge.\n");
}
void create_room()
{
  set_short("On a bridge over a river");
  
  set_long(break_string(
           "This is a large stonebridge over the largest river on "+
           "the isle of Cirath. The river is named Durni and flows "+
           "steady and slow towards the southern coast. The bridge "+
           "itself is made of large rocks, neatly put together.\n"
           ,60));  

  add_item("djungle","The djungle lies on both sides of the river.\n");
  add_item(({"river","water","stream","durni","Durni"}),"This is the large river Durni "+
           "which flows down to the south coast of Cirath. It's very "+
           "big.\n");
  add_item(({"bridge","stonebridge"}),"This bridge leads over the "+
           "river. It looks sturdy.\n");
  add_item(({"rock","rocks"}),"The bridge is made of them. It must "+
           "have been a hard work to get them here.\n");

  add_exit(JUNGLE+"road/r3","west","@@stopper");
  add_exit(S_TRADE+"r08","east","@@stopper");

  call_out("reset_room",1);

}

int stopper()
{
  if(MAL("guard"))
  {
    write("The guard stops you!\n");
    return 1;
  }

  return 0;
}
