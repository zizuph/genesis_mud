inherit "/std/room";
#include <stdproperties.h>
#include "../local.h"

void
create_room()
{
    set_short("In the bay of Palanthas");
    set_long("You are surrounded by hills on your west and east side, but " +
	     "to the north you can make out the sparkling of the endless " +
	     "ocean. Looking to the south you see a beautiful city, the " +
	     "peaceful city of Palanthas, spreading out before you, " +
	     "encompassing every inch of space that is left up to the " +
	     "foot the mountains towering over the city to the south " +
	     "and east. Fisherboats are everywhere around you in the " +
	     "bay idling away and hoping for the next catch.\n");
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

    add_item("mountains",
	     "The high mountains tower over the city and let you feel " +
	     "very tiny inside. Even the city, one of the larger cities " +
	     "you have seen, appears small compared to the impressive " +
	     "mountains.\n");
}
