/*
 * A room inside a coffin
 */
inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>

#include "/d/Terel/common/terel_defs.h"

#define BSN(xx)        break_string(xx+"\n", 70)
#define NF(xx)         notify_fail(xx)
#define TP             this_player()
#define TO             this_object()

static object coffin;

void set_coffin(object ob);
object query_coffin();

create_room()
{
    set_short("Inside coffin");
    set_long(BSN(
        "Your are lying inside a wooden coffin. " +
        "What on earth are you doing here?"
    ));
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);
}

void
set_coffin(object ob)
{
    coffin = ob;
}

object
query_coffin()
{
    return coffin;
}

void
init()
{
    ::init();
    add_action("lock", "lock", 0);
    add_action("do_open", "open", 0);
    add_action("do_close", "close", 0);
    add_action("lock", "unlock", 0);
    add_action("do_leave", "rise", 0);
    add_action("do_sleep", "sleep", 0);
    add_action("do_sleep", "rest", 0);
}

lock(string str)
{
    if (!CAN_SEE_IN_ROOM(TP)) return 0;
    if (str != "coffin") return 0;
    write("What? The lock is on the outside...\n");
    return 1;
}

do_open(string str)
{
    notify_fail("Open what?\n");
    if (str != "coffin") return 0;
    return coffin->do_open(coffin);
}

do_close(string str)
{
    notify_fail("Close what?\n");
    if (str != "coffin") return 0;
    return coffin->do_close(coffin);
}

do_leave(string str)
{
    notify_fail("Rise what?\n");
    if (str != "coffin" && str != "from coffin") return 0;
    if (coffin -> query_prop(CONT_I_CLOSED)) {
        write("The "+coffin->short()+" is closed.\n");
        return 1;
    }
    TP->move_living("M", environment(coffin));
    return 1;
}

do_sleep(string str)
{
     write("You try to rest in the "+coffin->short()+".\n");
    return 1;
}
