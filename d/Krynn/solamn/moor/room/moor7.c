/* created by Aridor 09/14/93 */

#include "../local.h"

inherit ROOM_BASE

object body;

void
create_moor_room()
{

    set_short("Moor");
    set_long(BS("You curse the blasted moor, It's just grass, water in "
         +   "your shoes and nothing else. Not even a path is visible "
         +   "here.",SL));

    add_exit(ROOM + "moor1","west",0,3);
    add_exit(ROOM + "moor6","north",0,3);

    set_alarm(6.0,0.0,"reset_room");
}

void
reset_moor_room()
{
    seteuid(getuid(TO));
    if (!body)
    {
        body = clone_object(LIV + "bog_body");
        tell_room(TO,"A bog body rises from the depths of the moor.\n");
        body->move_living(0,TO);
    }
}
