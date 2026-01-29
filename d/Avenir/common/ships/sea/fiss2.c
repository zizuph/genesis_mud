inherit "/std/room";

#include "../ship.h"

void
create_room()
{
    set_short("Inside the Rift of Sybarus");
    set_long("The ship is gliding swiftly through the jagged walls " +
             "of the fissure rent deep into the mountain.  The mouth "+
             "of a large cave can be seen ahead.\n");

    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

    AI(({"wall","walls "}),
             "The walls if the fissure rent into the mountainside are " +
             "steep and unclimbable.\n");
    AI("cave", "It looks to be quite large.\n");

} 

