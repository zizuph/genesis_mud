inherit "/d/Gondor/common/lib/road";
#include "/d/Gondor/defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

create_room() 
{
 street = "grass-covered road";
 where = "central";
 county = "Cardolan";
 land = "the lost realm of Arnor";
 mountain = "South Downs";
 vegetation = "evergreen bushes and pine trees";
 extraline = "You are on a treelined road which is overgrown with tall grass."
           + " Looking around you see the " +vegetation
           + " covering the land of " +county+ ". The road from the"
           + " southeast splits into a 'Y' to the north and northwest northwest of here."
           + " There is a small abandoned village here. Perhaps it will be"
           + " possible to explore it at a later date.";

 add_item((({"town","village","ruins"})),"You see nothing of interest in the broken buildings.\n");

 add_exit("/d/Gondor/common/shirelink","northwest",0,3);
 add_exit(CARD_DIR+"road/r36","southeast",0,3);

 make_the_room();
}

reset_room();

query_road()
{
 return 1;
}

