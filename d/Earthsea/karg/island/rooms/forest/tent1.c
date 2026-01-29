#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include "../../std/defs.h"

inherit ISL_DIR+"/std/room";

object sergeant;
object *guard=allocate(4);

void create_island_room()
{
 set_short("In the tent");
 set_long("The tent is almost empty, besides few bedrolls "+
   "rolled on the bare earth. You also notice packs "+
   "with clothing and provision, and few weapons.\n\n");

 add_item(({"bedroll","bedrolls"}),
   "You count them quickly... five... probably five "+
   "soldiers around...\n\n");

 add_exit(FROOMS+"/path13","out");

 reset_room();
}

void reset_room()
{
 int i;

 if(!sergeant)
  {
   sergeant=clone_object(ISLAND_LIV+"sergeant");
   sergeant->set_help(1);
   sergeant->set_aggressive(1);
   sergeant->move(TO);
   tell_room(TO,QCTNAME(sergeant)+" runs in.\n");
  }

 for(i=0;i<sizeof(guard);i++)
  {
   if(!guard[i])
    {
     guard[i]=clone_object(ISLAND_LIV+"guard");
     guard[i]->set_help(1);
     guard[i]->set_aggressive(1);
     sergeant->team_join(guard[i]);
     guard[i]->move(TO);
     tell_room(TO,QCTNAME(guard[i])+" runs in.\n");
    }
   else sergeant->team_join(guard[i]);
  }
}

