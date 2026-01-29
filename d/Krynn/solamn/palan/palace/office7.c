/* created by Aridor 09/14/93 */

#include "../local.h"

inherit ROOM_BASE

string
query_to_jail()
{
  return "west";
}

void
create_palan_room()
{
    set_short("Estate Agent");
    set_long(BS("This is the future office of the local Estate Agent. "
         +   "It is completely empty at the moment.", SL));

    add_exit(PALACE + "hall5","west",0,0);
}

 
