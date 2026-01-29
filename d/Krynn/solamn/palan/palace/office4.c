/* created by Aridor 09/14/93 */

#include "../local.h"

inherit ROOM_BASE

object jan;

string
query_to_jail()
{
  return "east";
}

void
create_palan_room()
{
    set_short("Janitor");
    set_long("@@my_long");

    INSIDE;

    add_exit(PALACE + "hall4","east",0,0);
    add_item(({"bucket","broom"}),"You can't see anything special.\n");

    reset_room();
}

void
reset_palan_room()
{
  if (!random(2))
    {
      jan = clone_object(LIV + "janitor");
      jan->move_living(0, TO);
    }
}


string
my_long()
{
  if (!jan)
    return BS("This is the janitor's room. Except for a broom and a bucket"
          +  " it is empty.", SL);
  else
    return BS("This is the janitor's room. It is completely empty at the moment.",SL);
}
