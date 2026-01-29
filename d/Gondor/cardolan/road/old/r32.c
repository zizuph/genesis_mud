inherit "/d/Gondor/common/lib/road";
#include "/d/Gondor/defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>


create_room() 
{
   street = "ramshackle old bridge";
   where = "southeast";
   county = "Cardolan";
   land = "the lost realm of Arnor";
   mountain = "Greyflood valley";
   vegetation = "birch trees and cat-tails";
   extraline = "You are on an old bridge over a deep stream running through"
   + " a ruined town. Looking around you see the " +vegetation
   + " covering the land of " +county+ ". You see"
   + " an old paved road climbing to the northwest and also"
   + " climbing southeast.";
   
   add_item((({"bridge","old bridge","wooden bridge"})),"This bridge is built on the pilings of an older massive stone\n"+"structure which apparently collapsed long ago. The bridge itself\n"+"is constructed from hand-hewn wood held together with pitch and\n"+"hempen ropes.\n\n");
   add_item((({"rope","ropes","hemp rope","hempen rope","hemp ropes","hempen ropes"})),"These ropes are skillfully woven from native hemp. It looks like\n"+"they cannot be removed without damaging the bridge and yourself.\n\n");
   add_item((({"town","ruin"})),"You see nothing of interest in the old buildings.\n");
   add_exit(CARD_DIR + "road/r33", "northwest", 0, 2);
   add_exit(CARD_DIR + "road/r31","southeast",0,1);
   
   make_the_room();
}

reset_room();

query_road()
{
   return 1;
}

