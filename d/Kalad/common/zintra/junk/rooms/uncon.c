inherit "/std/room.c";
#include <macros.h>
#include <stdproperties.h>
#include "../defs.h"

void
create_room()
{
    set_short( BS(
"you have blacked out.  You cannot see, hear, or do anything.\n"));

    set_long(BS(
"You have blacked out.  You cannot see, hear, or do anything.\n"));

    INSIDE
}

void
init()
{
    add_action("no_cmd", "", 1);
}

int
no_cmd(string str)
{
    write("You cannot do that while unconsious.\n");
    return 1;
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    tell_room(G_ROOMS + "cell", BS("A guard suddenly opens the door, and " +
"throws in " + QCTNAME(TP) + ".  The guard shouts, 'And you can stay there " +
"until hell thaws out!  HAR HAR HAR.'  The guard slams the door shut again, " +
"and your heart sinks as you hear the door being locked again.\n"));
    call_other(G_ROOMS + "cell", "reset_room");
    call_out("wake_up", 10, ob);
}

void
wake_up(object ob)
{
    if (!ob || !present(ob, TO)) return;
    tell_object(ob, "You wake up to find yourself in a strange location.\n");
    tell_room(G_ROOMS + "cell", QCTNAME(TP) + " slowly starts to wake up.\n");
    ob->move(G_ROOMS + "cell");
}
