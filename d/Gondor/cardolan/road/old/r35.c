inherit "/d/Gondor/common/lib/road";
#include "/d/Gondor/defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>


create_room() 
{
   street = "grass-grown road";
   where = "southeast";
   county = "Cardolan";
   land = "the lost realm of Arnor";
   mountain = "South Downs";
   vegetation = "leafy green bushes and undergrowth";
   extraline = "You are on a treelined road which is overgrown with tall grass."
   + " Looking around you see the " +vegetation
   + " covering the land of " +county+ ". The road runs down from"
   + " the central plains southeast toward the horizon.";
   
  add_exit(CARD_DIR+"road/r36","northwest", 0, 3);
  add_exit(CARD_DIR+"road/r34","southeast", 0, 3);
   
   make_the_room();
}

query_road()
{
   return 1;
}

