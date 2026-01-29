inherit "/d/Cirath/ak_wela/inherit/outside";
#include "/d/Cirath/common/defs.h"

void
create_room()
{
    set_short("A busy, crowded boardwalk near the docks.");
    set_long("This is the intersection of the boardwalk and Szun Moon " +
        "Boulevard, which leads westwards out of the city.  North of here " +
        "is the massive, squat warehouse of Phiringy Trading.  Southwards " +
        "stands the local temple, and more piers are to the east.\n");
    add_exit(AK_WELA_DIR + "pier5", "east", 0, 2 /* crowds */ );
    add_exit(AK_WELA_DIR + "szun_moon1", "west", 0, 2 /* crowds */ );
    add_exit(AK_WELA_DIR + "brdwlk4", "north", 0, 2 /* crowds */ );
    add_exit(AK_WELA_DIR + "brdwlk6", "south", 0, 2 /* crowds */ );
    ::create_room();
}
