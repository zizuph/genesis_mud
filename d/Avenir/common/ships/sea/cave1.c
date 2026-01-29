inherit "/std/room";

#include "../ship.h"

void
create_room()
{
    set_short("Nearing the port of Sybarus");
    set_long("The mouth of the cave-like Port of Sybarus looms ahead, a "+
             "save haven at rest in the monstrous rift which splits "+
             "the mountain almost entirely in half. It is impossible "+
             "to see what lies inside it, only that there are lights "+
             "flickering somewhere within.\n");

    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

    AI(({"wall","walls "}),
             "The walls of the fissure rent into the mountainside are " +
             "steep and unclimbable.\n");
    AI(({"cave", "rift", "gash", "fissure"}), 
             "It is a dark, gaping mouth in the mountainside.\n");

}  
