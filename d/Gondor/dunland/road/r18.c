inherit "/d/Gondor/common/lib/road";
#include "/d/Gondor/defs.h"

create_room() 
{
 street = "ramshackle old bridge";
 where = "central";
 county = "Dunland";
 land = "old Gondor";
 mountain = "Misty Mountains";
 vegetation = "willow trees and tall swamp grass";
 extraline = "You are on a old bridge over a deep stream running through"
           + " a small marsh. Looking around you see the " +vegetation
           + " covering the land of " +county+ ". You see"
           + " an old paved road climbing to the northwest and also"
           + " climbing east.";

 add_item((({"bridge","old bridge","wooden bridge"})),BSN(
        "This bridge is built on the pilings of an older massive stone structure "+
        "which apparently collapsed long ago. The bridge itself is constructed from "+
        "hand-hewn wood held together with pitch and hempen ropes."));
 add_item((({"rope","ropes","hemp rope","hempen rope","hemp ropes","hempen ropes"})),BSN(
        "These ropes are skillfully woven from native hemp. It looks like they cannot " +
        "be removed without damaging the bridge and yourself."));

 add_exit(DUN_DIR + "road/r19", "northwest", 0, 3);
 add_exit(DUN_DIR + "road/r17", "east", 0, 3);

 make_the_room();
}

query_road()
{
 return 1;
}

