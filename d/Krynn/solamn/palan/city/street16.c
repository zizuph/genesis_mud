/* created by Aridor 06/21/93 */

#include "../local.h"

inherit STREET_BASE


query_to_jail()
{
  return "south";
}

void
create_palan_room()
{

    set_short("Northwestern part of Palanthas");
    set_long(BS("You are standing on the north end of a pier. "
        +    "The harbour extends to the east from here "
        +    "and is accessible if you go to the south. "
        +    "Another street starting here leads to the "
        +    "west. There is a sign pointing west also.",SL));

    OUTSIDE;
    add_exit(ROOM + "street17","south",0,1);
    add_exit(ROOM + "street15","west",0,1);

    add_item("harbour","The harbour has several boats in dock.\n");
    add_item("boats","The boats sail in and out of the harbour with " +
             "regularity.\n");
    add_item("pier","It floats on the water of the harbour.\n");
    add_item("water","The water has an ocean green colour.\n");
    add_item("sign","The sign reads:  Circle Street.\n");
    add_cmd_item("sign","read","The sign reads:  Circle Street.\n");
}



