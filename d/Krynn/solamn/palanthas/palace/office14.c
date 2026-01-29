/* created by Aridor 09/14/93 */

#include "../local.h"

inherit CITY_ROOMBASE;

string
query_to_jail()
{
  return "south";
}

void
create_palan_room()
{
    set_short("Treasury");
    set_long("This is the treasury. Strange, no treasury is in here. You "
            +"wonder what you should make of that.\n");

    clone_object(OBJ + "door14")->move(TO);
}

 
