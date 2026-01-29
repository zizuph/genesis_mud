/* created by Aridor 06/21/93 */

#include "../local.h"

inherit STREET_BASE

object cap;

string
query_to_jail()
{
  return "west";
}

void
reset_palan_room()
{
    if (cap)
      return;
    cap = clone_object(LIV + "ret_captain");
    cap->move(TO);
}

void
create_palan_room()
{

    set_short("Harbour of Palanthas");
    set_long(BS("You are standing in the eastern part of the harbour. "
        +    "This area is mainly used for storing all the goods that "
        +    "are to be shipped to far away places and goods that have "
        +    "just arrived.",SL));

    add_exit(ROOM + "knight1","southeast",0,1);
    add_exit(ROOM + "street7","north",0,1);
    add_exit(ROOM + "street12","west",0,1);

    add_item(({"goods","good","merchandise"}),BS("There are many "
         +   "different types of goods, but you don't dare touch "
         +   "anything since there are guards around.",SL));

    reset_room();
}
