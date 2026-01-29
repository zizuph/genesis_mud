#pragma strict_types

inherit "/d/Gondor/lebennin/sroad/sroad.c";

#include <stdproperties.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

void
create_road()
{
   set_extraline("The city of Pelargir lies close to the north "
     + "and northeast just beyond the southern branch of the "
     + "river Sirith that flows into the Anduin east of here. "
     + "A smaller road runs off westwards from the main road, "
     + "on the south bank of the Sirith. "
     + "The main road is crossing the river on an old stone bridge "
     + "and enters the city through a gate in the city walls.");

   add_exit(LEB_DIR + "sroad/sirithb", "northeast", 0, 2);
   add_exit(LEB_DIR + "sroad/sr2", "southwest", 0, 2);
   add_exit(LEB_DIR + "rroad/rr1", "west", 0, 2);

   add_item(({"city","pelargir", "gates", "city gates", }), BSN(
       "Pelargir upon Anduin is the second largest city of Gondor "
     + "and the largest harbour of the realm. The city gates are "
     + "to the northeast just across the bridge over the Sirith."));
    add_item(({"sirith", "river", "river sirith", "branch", 
        "southern branch", }), BSN(
        "The city of Pelargir lies in between the two arms into "
      + "which the Sirith river splits just before joining the "
      + "Anduin. The larger and southern branch is just north "
      + "of here, flowing south of the city walls."));
    add_item(({"bridge", "stone bridge", "old bridge", "old stone bridge", }),
        BSN("The road crosses the Sirith on an old stone bridge "
      + "just outside the city walls. The bridge is wide enough "
      + "for ox carts to use it. It spans the river in three arches "
      + "that rest on the banks on both sides of the river and on "
      + "two mighty stone pillars built into the river."));
    add_item(({"gate", "city gate", "wall", "walls", "city walls", }), BSN(
        "The city walls of Pelargir tower high above the river Sirith "
      + "and the fields and meadows on this side of the river. There "
      + "are battlements on top of the walls, and to both sides of the "
      + "city gates there are mighty towers."));
    add_anduin("The Sirith river flows into the Anduin a short way "
      + "to the east.");
}

