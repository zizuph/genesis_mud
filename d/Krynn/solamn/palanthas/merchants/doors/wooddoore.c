/* created by Aridor 06/19/93 */

inherit "/std/door";
#include "../../local.h"

create_door()
{
    set_door_id("outsidedoor");
    set_pass_command(({"n","out","north"}));
    set_door_name(({"wooden door","door"}));
    set_other_room(MERCH + "wr4");
    set_open(0);

}
