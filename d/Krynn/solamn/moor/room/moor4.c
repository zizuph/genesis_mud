/* created by Aridor 09/14/93 */

#include "../local.h"

inherit ROOM_BASE

#define LIVE_I_CAN_FISH  "_live_i_can_fish"

void
create_moor_room()
{

    set_short("Moor");
    set_long(BS("You have reached a small natural pond which blocks your "
         +   "way to the north. A rectangular hole in the ground shows "
         +   "traces of another living being stupid enough to venture "
         +   "in this area. The hole is filled with brownish water.",SL));

    add_item(({"pond","small natural pond","natural pond"}),
        "To your north is a small natural pond, its calm surface " +
        "occasionally broken by the feeding of small fish.\n");

    // Small bait fish can be caught here.
    add_prop(LIVE_I_CAN_FISH, "default");

    add_exit(ROOM + "moor3","northwest",0,3);
    add_exit(ROOM + "moor2","west",0,3);
    add_exit(ROOM + "moor1","south",0,3);
    add_exit(ROOM + "moor6","east",0,3);
    add_exit(ROOM + "moor5","northeast",0,3);

}



