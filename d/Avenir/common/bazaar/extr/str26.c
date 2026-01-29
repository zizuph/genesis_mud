/* /extr/str26.
 * Lilith Sept 1997
 */
inherit "/std/room";
#include "/d/Avenir/common/common.h"

void 
create_room()
{
    set_short("North to Bazaar, South to Tribunal");
    set_long("This stone path follows a high mud-brick wall to a "+
        "courtyard and a cluster of stately buildings in the south. "+
        "The crowd seems a bit different here, a little more sub"+
        "dued perhaps, and definitely more wary.\n");
    AI(({"path", "stone path", "south path" }),
        "It looks like it is made of slabs of flawed semi-precious "+
        "stones such as jasper and carnelian. It curves away to the "+
        "south.\n");
    AI(({"wall", "mud-brick wall" }),
        "It is a mud-brick wall, very high, and so smooth as to be "+
        "fairly impossible to climb.\n");
    AI(({"buildings", "cluster", "cluster of buildings", "courtyard",
         "stately buildings"}),
        "A cluster of stately buildings have been built around a "+
        "broad courtyard.\n");
    AI(({"mud-brick hut", "hut", "back entrance", "rear-entrance" }),
        "It is a simple mud-brick hut, with a rear-entrance.\n");

	IN;       // Avenir is an undergound domain.

    AE(BAZAAR+"extr/str25", "north");
    AE(BAZAAR+"admin/a1", "south");
}
