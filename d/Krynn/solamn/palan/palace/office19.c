/* created by Aridor 09/14/93 */

#include "../local.h"

inherit ROOM_BASE

object clerk;

string
query_to_jail()
{
  return "west";
}

void
create_palan_room()
{
    set_short("Public office");
    set_long(BS("This is the public office. There is a huge sign hanging "
          +  "from the ceiling, and a wooden counter divides the room. "
          +  "Through the doorway to the north you can see another "
          +  "office exactly like this one.", SL));

    add_exit(PALACE + "office18","north",0,0);
    add_exit(PALACE + "hall8","west",0,0);

    add_item("sign","The sign has 'N - Z' written in big letters on it.\n");
    add_cmd_item("sign","read","The sign has 'N - Z' written in big letters on it.\n");
    add_item("counter",BS("The counter is made entirely of wood and runs "
          +  "from north to south through the office.",SL));

    reset_room();
}

void
reset_palan_room()
{
    seteuid(getuid(TO));
    if (clerk)
      return;
    clerk = clone_object(LIV + "clerk_n_z");
    clerk->move_living(0,TO);
}
