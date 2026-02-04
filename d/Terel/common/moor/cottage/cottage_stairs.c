/*
    Modified: 3 May 2003, by Bleys
        - fixed a typo
*/
// updated by Lilith Dec 2021: moved from Sorgum's dir to Terel/common
//    updated to Terel std room, etc

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

void
create_room()
{
    set_short("cottage stairs");
    set_long(
        "The staircase is wide and steep.  It is fashioned from vast blocks " +
        "as if for the feet of giants.  A reek of infinite mustiness " +
        "wells forth from somewhere below. It is so rank that it could "+
        "only be the result of decades of unwholesome decay.\n"
    );

    add_prop(ROOM_I_INSIDE, 1);

    add_exit("cottage_cellar", "down", 0);
    add_exit("cottage_bookroom", "up", 0);
}


