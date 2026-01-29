/* created by Aridor 09/14/93 */

#include "../local.h"

inherit ROOM_BASE

string
query_to_jail()
{
  return "south";
}

void
create_palan_room()
{
    set_short("Treasury");
    set_long(BS("This is the treasury. Strange, no treasury is in here. You "
            +"wonder what you should make of that.", SL));

    clone_object(OBJ + "door14")->move(TO);
}

 
