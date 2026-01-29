// Pierhouse - near the pier
#include "defs.h"
#include <macros.h>
inherit  "/d/Khalakhor/std/room";
 
object ceadha;
 
void reset_room()
{
   if (ceadha) return;
   ceadha=clone_object(NPC+"ceadha");
   ceadha->equip_me();
   ceadha->move(TO);
   tell_room(TO,QCNAME(ceadha)+" walks in from the road.\n");
}
 
create_khalakhor_room()
{
   set_short("In the pierhouse");
   set_long("This is the pierhouse of the village, just a small and "+
            "somewhat messy office and warehouse near the pier. Piles "+
            "of boxes line the walls, along with old fishing nets and "+
            "other discarded ship equipment. There is an old desk and "+
            "chair in the middle of the room.\n");
   add_item(({"office","pierhouse","house","room","warehouse"}),
      "@@query_long");
   add_item(({"box","boxes"}),
      "Boxes made of wood of varying ages and conditions are stacked "+
      "along the walls, probably storing old junk which isn't useful "+
      "but for some reason isn't thrown away.\n");
   add_item(({"nets","fishing nets","equipment","anchor","ropes"}),
      "There are heaps of old ship equipment on top of the piles of "+
      "boxes and along the walls. Old fishing nets, an anchor, "+
      "rotting ropes and other equipment which all looks past its "+
      "use.\n");
   add_item(({"desk","chair"}),
      "There is an old beat-up desk and a rickety chair in the "+
      "center of the room, probably used to transact any business "+
      "which might be necessary, but you can't imagine what.\n");
   add_exit("proad7","south");
   INSIDE;
   reset_room();
}
