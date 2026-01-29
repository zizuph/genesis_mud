/* created by Aridor 09/14/93 */

#include "../local.h"

inherit ROOM_BASE

object cutter;

void
create_moor_room()
{

    set_short("Moor");
    set_long(BS("You are in the middle of the moor walking along dams "
         +   "that are remains of the digging here. Water holes, "
         +   "rectangular, are definitely not natural, but must have "
         +   "been hard labor.",SL));

    add_exit(ROOM + "moor4","southwest",0,3);
    add_exit(ROOM + "moor6","south",0,3);

    set_alarm(1.0,0.0,"reset_room");
}

void
reset_moor_room()
{
    seteuid(getuid(TO));
    if (!cutter)
    {
        cutter = clone_object(LIV + "cutter");
        cutter->move_living("xx",TO);
    }
}
