inherit "/d/Cirath/ak_wela/inherit/outside.c";
#include "/d/Cirath/common/defs.h"

void
create_room()
{
    set_short("Szun Moon Boulevard");
    set_long("Looking east along Szun Moon Boulevard, you can still glimpse " +
             "the docks every now and then through the crowd, and west you " +
             "see the gate set in the city wall. North seems to be a private " +
             "house, perhaps the home of some merchant. Southward however, is " +
             "a house with a huge gate for a door, currently open. In there " +
             "a forge is blazing, and you can hear the steady clanking of the " +
             "smiths heavy hammering.\n");
    add_exit(AK_WELA_DIR + "cottage1", "north", 0, 2);
    add_exit(AK_WELA_DIR + "szun_moon8", "east", 0, 2);
    add_exit(AK_WELA_DIR + "szun_moon10", "west", 0, 2);
    add_exit(AK_WELA_DIR + "smithy", "south", 0, 2);
}
