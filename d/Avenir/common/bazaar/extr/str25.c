/* /extr/str25.
 * Lilith Sept 1997
 */
inherit "/std/room";
#include "/d/Avenir/common/common.h"

void 
create_room()
{
    set_short("North to Museum and Bazaar, South to Tribunal");
    set_long("This stone path follows a high mud-brick wall. Rising to "+
        "the north is a massive edifice of white marble and pillars. "+
        "West is a mud-brick hut, and what appears to be a back "+
        "entrance to it. South you can see a cluster of stately "+
        "buildings.\n");
    AI(({"pillar","pillars"}),
        "They are huge, made from white polished granite.\n");
    AI(({"building","edifice","house","museum"}),
        "It is a massive building, pristine and white.\n");
    AI(({"path", "stone path", "south path" }),
        "It looks like it is made of slabs of flawed semi-precious "+
        "stones such as jasper and carnelian. It curves away to the "+
        "south.\n");
    AI(({"wall", "mud-brick wall" }),
        "It is a mud-brick wall, very high, and so smooth as to be "+
        "fairly impossible to climb.\n");
    AI(({"buildings", "cluster", "cluster of buildings"}),
        "It is a cluster of buildings that look fairly important.\n");
    AI(({"mud-brick hut", "hut", "back entrance", "rear-entrance" }),
        "It is a simple mud-brick hut, with a rear-entrance.\n");

	
	IN;       // Avenir is an undergound domain.

    AE(BAZAAR+"extr/str16", "north");
    AE(BAZAAR+"intr/grdrm", "west");
    AE(BAZAAR+"extr/str26", "south");
}
