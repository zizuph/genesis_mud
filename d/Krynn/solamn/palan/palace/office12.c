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
    set_short("Archive");
    set_long(BS("This is the backroom of the Archive. The walls and "
           + "even the floor are filled with books, scrolls, and sheets. "
           + "You better be careful or everything will be a total mess. "
           + "- Not that it isn't to you already.", SL));

    /*add_exit(PALACE + "hall7","east",0,0);*/
    clone_object(OBJ + "door12")->move(TO);
    add_exit(PALACE + "office11","south");
}

