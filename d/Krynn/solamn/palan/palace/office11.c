/* created by Aridor 09/14/93 */

#include "../local.h"

inherit ROOM_BASE

object clerk;

string
query_to_jail()
{
  return "east";
}

void
create_palan_room()
{
    set_short("Archive");
    set_long(BS("This is the Archive. There are books and scrolls flying "
          +  "around everywhere. You wonder how anyone can keep track of "
          +  "things here.", SL));

    add_item(({"book","books","scroll","scrolls"}),
	     BS("There are books and scrolls of all types and kinds. You decide there is " +
		"nothing of interest for you here and refrain from taking a closer look.",SL));
    add_exit(PALACE + "office12","north","@@blocked",0);
    add_exit(PALACE + "hall6","east",0,0);
    reset_room();
}

reset_palan_room()
{
    seteuid(getuid(TO));
    if (!clerk)
    {
       clerk = clone_object(LIV + "archive_clerk");
       clerk->move_living(0,TO);
    }
}


int
blocked()
{
    if (clerk)
    {
        write("The clerk stops you from going in there.\n");
        return 1;
    }
    return 0;
}


