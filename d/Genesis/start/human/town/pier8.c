// /d/Genesis/start/human/town/pier13.c
// Ported to the new ship system by Tapakah, 05/2009

#pragma save_binary
#pragma strict_types


#include <stdproperties.h>                                                   
#include <macros.h>

#include "../defs.h"
#include "/d/Genesis/gsl_ships/ships.h"

inherit STDPIER;

void
create_pier()
{
    set_short("Berth 8 - Sybarus");
    set_long("You are at the midway point along the south pier.\n" +
      "To the north, across the deep waters of Sparkle's harbour," +
      " is a jetty and a cluster of buildings. South, over the" +
      " edge of the pier, can be seen a rugged shoreline" +
      " endlessly pounded by the surf. Numerous warehouses" +
      " line the harbour in the west, while the pier" +
      " continues east into the restless sea.\nThere is a" +
      " sign here that reads: Berth 8 - Sybarus.\n");

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
    add_prop(ROOM_S_MAP_FILE, "sparkle_city_genesis.txt");

    add_pier_entry(MASTER_OB(TO), "Sparkle", "Route to Sybarus");
}                                                                             
