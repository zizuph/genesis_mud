/* created by Aridor 09/14/93 */

#include "../local.h"

inherit ROOM_BASE

void
create_moor_room()
{

    set_short("Moor");
    set_long(BS("You are at the edge of a moor, which spreads out in "
         +   "all directions but south. There are trees scattered about "
         +   "and water sparkles to the east and north of you. A small "
         +   "path leads to safer grounds in the south but you cannot "
         +   "make out which way the path continues.",SL));

    add_exit(ROOM + "road3","south",0,2);
    add_exit(ROOM + "moor2","northwest",0,3);
    add_exit(ROOM + "moor4","north",0,3);
    add_exit(ROOM + "moor6","northeast",0,3);
    add_exit(ROOM + "moor7","east",0,3);

}



