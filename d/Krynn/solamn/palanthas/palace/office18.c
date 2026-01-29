/* created by Aridor 09/14/93 */

#include "../local.h"

inherit CITY_ROOMBASE;

object clerk;

query_to_jail()
{
  return "west";
}

void
reset_palan_room()
{
    seteuid(getuid(TO));
    if (clerk)
      return;
    clerk = clone_object(LIV + "clerk_a_m");
    clerk->move_living(0,TO);
}

void
create_palan_room()
{
    set_short("Public office");
    set_long("This is the public office. There is a huge sign hanging "
          +  "from the ceiling, and a wooden counter divides the room. "
          +  "Through the doorway to the south you can see another "
          +  "office exactly like this one.\n");

    add_exit(PALACE + "office19","south",0,0);
    add_exit(PALACE + "hall9","west",0,0);

    add_item("sign","The sign has 'A - M' written in big letters on it.\n");
    add_cmd_item("sign","read","The sign has 'A - M' written in big letters on it.\n");
    add_item("counter","The counter is made entirely of wood and runs "
          +  "from north to south through the office.\n");

    reset_palan_room();
}
