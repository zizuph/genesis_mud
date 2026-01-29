/* created by Aridor 06/21/93 */

#include "../local.h"

inherit STREET_BASE

string
query_to_jail()
{
  return "west";
}

void
create_palan_room()
{

    set_short("Harbour of Palanthas");
    set_long(BS("This is where the harbour is divided into two parts. "
         +   "To the east you can see mainly fishing boats, whereas "
         +   "in the western harbour passenger ships land from all over the "
         +   "world. To the north is a pier dividing the two "
         +   "harbours. The pier seems cut off by a gate, but the gate is wide open.",SL));

    add_exit(ROOM + "street12","east",0,1);
    add_exit(ROOM + "street17","west",0,1);
    add_exit(PIER1,"north","@@through_gate",1);   /* was:     ROOM + "street14"   */

    add_item("gate",
	     BS("It's an iron gate shutting off the pier from your side of the city. " +
		"The gate is wide open though, so you can pass through.",SL));
}

int
through_gate()
{
  write("You pass through an iron gate.\n");
  return 0;
}

