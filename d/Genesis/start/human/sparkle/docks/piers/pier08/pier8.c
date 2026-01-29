// /d/Genesis/start/human/town/pier8.c  (needs to replace the current one)
// Berth 8 to Avenir
#pragma save_binary
#pragma strict_types

inherit "/std/room";                                                          

#include <stdproperties.h>                                         

#include "../defs.h"

void
create_room()                                                                
{                                                                             
    set_short("Berth 8, south pier");
    set_long("You are near the eastern end of the south pier.\n"+
      "To the north, across the deep waters of Sparkle's harbour, "+
      "is a jetty and a cluster of buildings."+
      " South, over the edge of the pier, can be seen a rug"+
      "ged shoreline endlessly pounded by the surf.  "+
      "Numerous warehouses line the harbour in the west, "+
      "while the pier continues east into the restless sea.\n");

    add_item(({"water", "harbour" }),
      "Pieces of fish and other leftovers "+
      "from the fishermens' boats are floating in the water. "+
      "The harbour is deeper here than to the west, able to "+
      "accomodate larger ships. To the north, accross the "+
      "harbour, you can see the jetty and pub, as well a berth"+
      " or two.\n");
    add_item(({"surf", "shoreline", "shore", "coast"}),
      "Huge waves throw themselves incessantly against the "+
      "rocky shore. The southern section of the coast looks "+
      "to be wild and inaccessible both by land and sea.\n");
    add_item(({"warehouse", "warehouses"}),
      "You can see several warehouses west of here. They look "+
      "more than a little weathered by the elements.\n");
    add_item("pier", "The pier extends in an east-west direction."+
      " In the west it heads toward the safety of land, while "+
      "in the east it continues out into the ocean.\n");
    add_item(({"ocean", "sea"}),
      "The water is dark and ominous-looking. The pier seems "+
      "a foolhardy attempt to tame and profit from its wrath.\n");
    add_item("sign", "\n  A perilous journey is ere begun when "+
      "boarding the barque 'twixt here and Sybarus runs.\n"+
      "   Ye cannot say ye've not been warned!\n");

    add_exit(TOWN_DIR + "pier7","west");
    add_exit(TOWN_DIR + "parrot","east");

    add_prop(ROOM_I_TYPE, ROOM_NORMAL);                            
    add_my_desc("An old-looking sign marked 'Berth 8'.\n");
}                                                                             
