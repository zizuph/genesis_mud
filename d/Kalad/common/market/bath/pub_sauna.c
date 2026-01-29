inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

create_room()
{
    ::create_room();
    add_prop(ROOM_I_INSIDE,1);

    set_short("Public Sauna");
    set_long(BS(
      "This is the public sauna room of the Dirty Swine.\n" +
      ""));

    add_exit(MARKET(bath/hall),"west",0,0); /*inside:no tired*/

    add_prop(MRKT_IN_NO_HEAR,1);
}
