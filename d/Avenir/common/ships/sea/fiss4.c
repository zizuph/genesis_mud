inherit "/std/room";

#include "../ship.h"

void
create_room()
{
    set_short("Leaving the Rift");
    set_long("The opening of the fissure is just ahead.  The weight of "+
             "the cleaved mountain seems to press down on you with an "+
             "eerie moan of pain. You know it is just the wind whist"+
             "ling past the cliffs, but the impresssion still remains. "+
             " The ship is creeping slowly forward against the "+
             "force of the tide, even with the help of a strong "+
             "breeze from behind.\n");

    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

    add_item(({"wall","walls "}),
             "The walls of the fissure rent into the mountainside are " +
             "steep and unclimbable.\n");
    add_item("fissure",
             "It looks like an a huge, deep crack into the mountain.\n"); 

}
