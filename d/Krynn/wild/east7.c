/* eastroad coded by Ashbless */

#include "/d/Krynn/common/defs.h"
#include "local.h"
inherit  OUTWILDROOM

create_wild_room()
{
    set_short("East road");
    set_long(
        "You are on the east road, standing in the shade of a " +
        "dark and ominous wood. The road enters the wood to the " +
        "northeast but the thick growth prevents movement to " +
        "the north. On the west side of the road are fields of " +
        "wheat and a grassy meadow lies to the south and east, nestled " +
        "between the wood and a thick forest south of it. A " +
        "lone peak dominates the sky, far to the south. The road " +
        "continues southwest where it bends and winds west " +
       "through farmland.\n");

    add_exit(TDIR + "east6", "southwest");
    add_exit("/d/Krynn/tant/room/forest1", "northeast", 0, 1);
	add_exit(PLAIN + "meadow", "east");

    add_item(({"wheat","tall wheat","tall golden wheat",
        "farmlands","golden wheat","farmland","field","wheat field"}),BS(
        "Swaying rhythmically " +
        "in the wind, the golden wheat is ready to be " +
        "harvested. The field stretches to the west.",70));
    add_item(({"road","east road"}),BS(
        "You are on the east road of Solace, " +
        "standing in the shadow of a dark wood. " +
        "Southwest of here it turns west and winds " +
        "through farmland.",70));
    add_item(({"dark wood","wood"}),BS(
        "Gnarled and twisted oak trees cast dark " +
        "shadows on the road, which enters the wood " +
        "to the northeast. The dim light makes it " +
        "hard to see very far into it. Thick undergrowth " +
        "makes it impossible to enter to the north." +
        "",70));
    add_item(({"forest","thick forest"}),BS(
        "A thick forest of aspen and pine lies far to " +
        "the south. It stretches for miles in either " +
        "direction.",70));
    add_item(({"meadow","grassy meadow"}),BS(
        "To the south and east, nestled between the dark wood and " +
        "the forest south of here, lies a grassy meadow. " +
        "One of the favorite picnic spots of the " +
        "residents of Solace, it offers a well " +
        "needed escape from the rigors of ordinary " +
        "life.",70));
    add_item(({"peak","mountain peak","lone peak"}),BS(
        "This lone mountain peak stands miles to " +
        "the south. An awesome view from here, you " +
        "can only imagine what it would look like " +
        "up close. The point is shrouded in soft " +
        "white clouds, in sharp contrast with the " +
        "dark clouds to the north.",70));
}

