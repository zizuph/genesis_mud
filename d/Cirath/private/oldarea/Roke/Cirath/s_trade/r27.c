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
           "The bricked road you are currently travelling on, "+
           "goes through low, grassy hills, quite near the south "+
           "coast of Athas. The road is made of stone bricks which "+
           "makes it easier to walk on. The air smells of salt and "+
           "you can hear seagulls in the distance.\n"
           ,60));  

  add_item("road","This is the southern trade-route that leads between "+
           "the cities Tyr and Ciubori.\n");
  add_item(({"brick","bricks"}),"The road is made of them.\n");
  add_item("seagulls","You can just hear them, not see them.\n");

  OUTSIDE;

  add_exit(S_TRADE+"r26","northeast");
  add_exit(S_TRADE+"r28","west");

}
