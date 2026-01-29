inherit "/std/room";

#include "../ship.h"

void
create_room()
{
    set_short("Inside the cave-like Port of Sybarus");
    set_long("Torches flicker in a strong breeze coming from deep " +
             "inside the cave-like Port of Sybarus.  The roar of "+
             "water echoes off the walls, nearly deafening you.\n");

    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

    AI(({"wall","walls "}),
             "The walls of the cave are dark and damp.\n");
    AI("cave", "It is too dark to distinguish much.\n");

}  
