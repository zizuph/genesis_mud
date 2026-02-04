#pragma save_binary

inherit "std/room";

#include "/d/Terel/common/terel_defs.h"

#define PATH "/d/Terel/common/minstrel/"

create_room(){
   
   set_short("Gateway");
   set_long("Rising up tall into the sky, a gothic white-stone palace\n" +
      "with spiraling minarets, ornate carvings, arches, bas relief,\n" +
      "flying buttresses and immense silver-paned windows.\n" +
      "The palace is guarded by a great gateway, one of decorative\n" +
      "silver, which rests between two towers. Above the silver gates\n" +
      "hangs a banner. A small copse of birch and aspens is\n" +
      "to the north of this place.\n");
   
   add_exit("/d/Terel/common/town/garden/copse2", "north", 0);
   add_exit(CEDRICDIR+"guild/entrance","south",0);
   add_item(({"gateway", "great gateway"}),  "This huge gateway " +
     "looks very sturdy indeed. Fortunately it is open; you may pass " +
	    "right through.\n");
   add_item("banner", "The banner reads, "
	    + "\"Thalia Calliope Melpomene Clio\".\n");
}
