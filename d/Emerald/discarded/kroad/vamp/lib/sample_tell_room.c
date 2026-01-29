/*
 * This is a sample use of tell room
 * - Alaron Feb 12, 1997
 */

#include <macros.h>
#include <stdproperties.h>

inherit "/d/Emerald/lib/room_tell";
inherit "/std/room";

void
create_room()
{
    set_short("Tell room");
    set_long("Duh, this is uh like a tell room or something.\n\n");

    set_tell_time(20);
    add_tell("This is a tell.\n");
    add_tell("This is another tell.\n");
    add_tell("No way! Its yet another tell!!\n");
    add_tell("Alaron wishes he could think of a tell here.\n");
    add_tell("Zoiks!\n");

    add_prop(ROOM_I_INSIDE, 1);

    add_exit("/d/Wiz/alaron/workroom", "alaron");
}

enter_inv(object ob, object from)
{
    start_room_tells();
    ::enter_inv(ob, from);
}


leave_inv(object ob,object to)
{
    stop_room_tells();
    ::leave_inv(ob, to);
}
