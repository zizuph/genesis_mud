/* created by Aridor 09/14/93 */

#include "../local.h"

inherit ROOM_BASE

object collector;

string
query_to_jail()
{
  return "west";
}

void
create_palan_room()
{
    set_short("Tax Collector");
    set_long(BS("This is the tax collector's office. It is an expensively "
           + "furnished room with a counter dividing it. This place looks "
           + "very much like a bank, but you doubt money has ever left "
           + "this room again.", SL));

    add_exit(PALACE + "hall3","west",0,0);

    add_item("counter","It's a solid wooden counter displaying intricate " +
	     "craftmanship.\n");

    reset_room();
}


reset_palan_room()
{
    seteuid(getuid(TO));
    if (!collector)
      {
	collector = clone_object(LIV + "collector");
        collector->move_living(0,TO);
      }
}
