/* created by Aridor 09/14/93 */

#include "../local.h"

inherit CITY_ROOMBASE;

string
query_to_jail()
{
  return "east";
}

void
create_palan_room()
{
    set_short("Meeting Room");
    set_long("This is the meeting room. There is a large wooden table "
          +  "here, filling almost the entire room. Several chairs are "
          +  "lying on the floor, just like the people stormed out "
          +  "recently. Several tapestries hang from the walls.\n");

    add_exit(PALACE + "hall5","east",0,0);

    add_item("table","A large table made from a strange black wood.\n");
    add_item(({"chair","chairs"}),"The chairs are made from the same "
            +"black wood as the table.\n");
    add_item(({"tapestries","tapestry"}),"These tapestries cover almost "
            +"the entire walls. They show scenes from the plaza of "
            +"Palanthas, but also some portraits of the Lords of "
            +"Palanthas can be found, serving as the ancestral hall.\n");
}

