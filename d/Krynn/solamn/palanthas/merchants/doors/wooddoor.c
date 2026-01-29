/* created by Aridor 06/19/93 */

inherit "/std/door";
#include "../../local.h"

create_door()
{
    set_door_id("outsidedoor");
    set_pass_command(({"s","south","enter","go through","in"}));
    set_door_name(({"wooden door","door"}));
    set_other_room(MERCH + "inn1");
    set_open(0);

}
