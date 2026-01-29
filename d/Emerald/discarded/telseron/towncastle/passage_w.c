inherit "/std/room";
 
#include "default.h"
 
void
create_room()
{
    set_short("Secret passage");
    set_long( "Here the passage turns sharply from the south to east. " +
              "Further to the east it looks like the passage is coming to " +
              "an end and to the south there appears to be a ladder leading "+
              "upwards.\n" );
 
    add_item("ladder", "From here it looks like it is flush with the wall.\n");
 
    add_prop(ROOM_I_INSIDE, 1);
 
    add_exit(TCASTLE_DIR + "passage_d", "east");
    add_exit(TCASTLE_DIR + "passage_s", "south");
}
