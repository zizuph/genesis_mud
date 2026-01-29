/* created by Aridor 09/14/93 */

#include "../local.h"

inherit ROOM_BASE

#define LIVE_I_CAN_FISH  "_live_i_can_fish"

object body;

void
create_moor_room()
{

    set_short("Moor");
    set_long(BS("You stand at a small pond with brownish water. A "
         +   "few trees grow here, but it is probably is too wet for "
         +   "them. Grass grows everywhere, but you feel it is too "
         +   "unsafe to continue in any other direction but north, "
         +   "east and southeast.",SL));

    add_item(({"pond","small natural pond","natural pond"}),
        "To your west is a small natural pond, its calm surface " +
        "occasionally broken by the feeding of small fish.\n");

    // Small bait fish can be caught here.
    add_prop(LIVE_I_CAN_FISH, "default");

    add_exit(ROOM + "moor1","southeast",0,3);
    add_exit(ROOM + "moor4","east",0,3);
    add_exit(ROOM + "moor3","north",0,3);

    set_alarm(3.0,0.0,"reset_room");
}


reset_moor_room()
{
    seteuid(getuid(TO));
    if (!body)
    {
        body = clone_object(LIV + "bog_body");
        tell_room(TO, "A bog body rises from the depths of the moor.\n");
        body->move_living(0,TO);
    }
}


