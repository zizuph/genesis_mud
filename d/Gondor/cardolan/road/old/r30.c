inherit "/d/Gondor/common/lib/road";
#include "/d/Gondor/defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>


create_room() 
{
   street = "overgrown road";
   where = "southeast";
   county = "Cardolan";
   land = "the lost realm of Arnor";
   mountain = "Greenway slopes";
   vegetation = "sparse brown bushes and tall yellow grass";
   extraline = "You are on a treelined road which is overgrown with tall grass."
   + " Looking around you see the " +vegetation
   + " covering the land of " +county+ ". The road runs down from"
   + " the central plains southeast toward Tharbad.";
   
   add_exit(CARD_DIR + "road/r31","northwest",0);
   add_exit(CARD_DIR + "road/r29","southeast",0);
   
   make_the_room();
}

reset_room();

query_road()
{
   return 1;
}

