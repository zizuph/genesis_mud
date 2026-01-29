inherit "/d/Cirath/ak_wela/inherit/outside";
#include "/d/Cirath/common/defs.h"

void
create_room()
{
    set_short("A busy, crowded boardwalk near the docks.");
    set_long("This northern part of the boardwalk lies between the " +
        "armoury to the west and the docks to the east.  North of " +
        "here, the two-story building housing the Sea Serpent Saloon " +
        "stands above the other buildings in the area.  To the south, " +
        "the squat and massive warehouse of Phiringy Trading dominates " +
        "the view.\n");
    add_exit(AK_WELA_DIR + "pier2", "east", 0, 2 /* crowds */ );
    add_exit(AK_WELA_DIR + "armoury", "west", 0, 2 /* crowds */ );
    add_exit(AK_WELA_DIR + "brdwlk1", "north", 0, 2 /* crowds */ );
    add_exit(AK_WELA_DIR + "brdwlk3", "south", 0, 2 /* crowds */ );
    ::create_room();
}
