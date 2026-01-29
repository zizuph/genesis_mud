/* created by Aridor 06/25/93 */

#include "../local.h"
inherit SOBJ + "portcullis3";

void
create_door()
{
    ::create_door();
    set_pass_command(({"se","southeast","enter","go through","in"}));
    set_other_room(ROOM + "hall5");
}
