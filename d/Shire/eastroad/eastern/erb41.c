#pragma save_binary
#pragma strict_types

#include "local.h"

inherit EAST_ROAD;

void
create_er_room()
{
    set_area ("on a gradual slope following a bend in");
    set_areaname ("the Great East Road");
    set_land ("Rhudaur");
    set_areatype (AREATYPE_ROAD);
    set_areadesc ("hillside");
    set_grass ("patchy");
    set_treetype ("pine");

    set_extraline ("The forest hills of the Trollshaws fill the eyes to the " +
    "north, giving away only to the sky directly above the road.  " +
    "through the wider spaced trees on the southern side of the road " +
    "offers fleeting glimspes of prairie land slowly rolling towards the " +
    "mini-valleys made by two ancient rivers.  " +
    "The road continues to the west and northeast from here.\n");

add_item (({"forest", "hills", "hill", "trollshaws", "north", "northern trees"}),
"The somber appearing hills of the Trollshaws are blanketed by tall " +
"growing pine trees wherever patches of heather have not already " +
"staked a claim.\n");
add_item (({"trees", "pine trees", "pines"}),
"Fighting for growing space on the hills of the Trollshaws, these high " +
"reaching pines dominate the landscape and allow little light to the " +
"forest floor.\n");
add_item (({"mini-valley", "mini-valleys", "river", "rivers"}),
"Miniature valleys harboring the Hoarwell, to the west, and Bruinen, " +
"to the east, with low rolling hills of prairie encased between them is " +
"the result of eons of those two mighty forces eating deeper into the " +
"earth.\n");
add_item (({"south", "southern trees", "prairie", "prairie land"}),
"Low rolling hills of prairie land sit cradled in the long arms of the " +
"rivers Hoarwell, in the west, and Bruinen, to the east.  It is difficult " +
"to determine any details of the area through the imposing pines.\n");
add_item (({"great east road", "road", "muddy road", "mud"}),
"Offering no signs of other travellers, because recent rains have " +
"turned the hard packed dirt to streams of mud flowing downhill, this " +
"road meanders its way through the southern end of the Trollshaws.\n");

    add_exit (ER_DIR + "erb40", "west", 0, 1);

}
