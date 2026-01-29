#pragma save_binary

#include <stdproperties.h>
#include "/d/Genesis/gsl_ships/ships.h"
#include "../ship.h"

inherit STDSHIPROOM;

void
create_room()
{
    ::create_shiproom();

    set_short("Inside a small cabin");
    set_long("This is a small cabin, passengers are not allowed inside. " +
        "There is nothing to see here, just stacks of boxes and crates " +
        "which seem to keep supplies for the ship.\n");
    
    add_item(({"boxes", "crates"}), 
        "There are many different stacks of boxes and crates crammed " +
        "into every corner of the cabin here. You notice that various " +
        "sailors come in to grab supplies from one stack or another.");


    add_exit(DECK, "out",0,3);
    add_prop(ROOM_I_LIGHT, 10);
}
