inherit "/d/Cirath/ak_wela/inherit/outside";
#include "/d/Cirath/common/defs.h"

void
create_room()
{
    set_short("A busy, crowded boardwalk near the docks.");
    set_long("The boardwalk is even more crowded than the piers.  Perhaps " +
        "it's because of all the merchants who have set up shop along " +
        "this walkway.\n");
    add_exit(AK_WELA_DIR + "pier4", "east", 0, 2 /* crowds */ );
    add_exit(AK_WELA_DIR + "ware4", "west", 0, 2 /* crowds */ );
    add_exit(AK_WELA_DIR + "brdwlk5", "south", 0, 2 /* crowds */ );
    add_exit(AK_WELA_DIR + "brdwlk3", "north", 0, 2 /* crowds */ );
    ::create_room();
}
