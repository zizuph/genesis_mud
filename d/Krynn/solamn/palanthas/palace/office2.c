/* created by Aridor 09/14/93 */

#include "../local.h"

inherit CITY_ROOMBASE;

object supervisor;

string
query_to_jail()
{
  return "east";
}

void
create_palan_room()
{
    set_short("Supervisor's office");
    set_long("This is the supervisor's office. It is very comfortable "
	    + "inside, the walls are not even visible anymore from the "
            + "tapestries decorating them. The desk is made of stone, "
            + "but, as well as the chair behind it, has a cushion lying "
            + "on top.\n");

    add_exit(PALACE + "hall2","east",0,0);

    reset_room();
}

void 
reset_palan_room()
{
  if (supervisor)
    return;
  supervisor = clone_object(LIV + "supervisor");
  supervisor->move_living(0,TO);

}
