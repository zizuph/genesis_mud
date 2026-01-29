/* created by Aridor 09/14/93 */

#include "../local.h"

inherit ROOM_BASE

string
query_to_jail()
{
  return "east";
}

void
create_palan_room()
{
    set_short("Hallway");
    set_long(BS("It's an ordinary hallway which is a little dark since "
         +   "there is only one window far to the south. On the east "
         +   "doorway, a sign reads '20'. The hallway runs north "
         +   "and south.", SL));

    add_exit(PALACE + "office20","east",0,0);
    /*add_exit(PALACE + "office12","west",0,0);*/
    clone_object(OBJ + "door12h7")->move(TO);
    add_exit(PALACE + "hall8","north",0,0);
    add_exit(PALACE + "hall6","south",0,0);
}

