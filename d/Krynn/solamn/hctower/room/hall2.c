/* created by Aridor 06/21/93 */

inherit "/std/room";

#include "../local.h"


create_room()
{
    set_short("Hallway under the Tower");
    set_long(BS("You are standing in a hallway below the High Clerist "
         +   "Tower.",SL));

    INSIDE;
    DARK;

    add_exit(ROOM + "hall1","northwest",0);
    add_exit(ROOM + "frontdoor","southeast",0);

    add_item("hallway",BS("The hallway extends to the northwest and "
          +  "southeast into darkness. You notice skilled craftsmen "
          +  "must have built this, but strangely enough you cannot "
          +  "see any other exits from the hallway.",SL));
    add_item(({"wall","walls"}),BS("You conclude that there are "
           + "truly "
          +  "no other other exits from this hallway into the tower "
          +  "itself, but hopefully a Krynn wizard will come by soon "
          +  "and do something about it!",SL));
}



