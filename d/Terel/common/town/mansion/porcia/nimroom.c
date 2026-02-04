inherit "/d/Terel/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"

#define PORDIR TOWNDIR + "mansion/porcia/"

object guard, nimgame;

public int
check_guard()
{
    if (!guard) return 0;
    if (guard->getfrust()) {
        write("The guards is so distracted he lets you pass.\n");
        return 0;
    }
    write("The guard looks at you carefully and won't let you pass.\n");
    say(QCTNAME(guard) + " stops " + QTNAME(this_player()) +
        " from leaving.\n");
    return 1;
}

public void
reset_room()
{
    add_prop(ROOM_I_NO_ATTACK, 1);
    add_prop(ROOM_I_NO_MAGIC,  1);
    if (!guard) {
        guard = clone_object(PORDIR + "guard");
        guard->move_living("X", this_object());
    }
    if (!nimgame) {
        nimgame = clone_object(PORDIR + "nim");
        nimgame->move(this_object());
    }
    if (nimgame->query_opponent() != guard)
        nimgame->set_opponent(guard);
}

public void
create_room()
{
    set_short("A small room");
    set_long("You find yourself in a very small room. " +
             "The walls are covered with dust, and cobwebs are hanging " +
             "from the ceiling. You feel quite uncomfortable in this " +
             "room... it looks a bit like a trap and you wonder if " +
             "you'll ever be able to leave it again.\n");
    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_NO_ATTACK,1);
    add_prop(ROOM_I_NO_MAGIC, 1);
    add_exit(PORDIR + "entrance", "north", "@@check_guard");
    
    reset_room();
}
