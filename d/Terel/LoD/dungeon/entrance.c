/*
 * entrance.c
 *
 * A generic dungeon below the Legion of Darkness quarters.
 */

#include "/d/Terel/include/Terel.h"
inherit LOD_DIR + "dungeon/dungeon_room";

#include <stdproperties.h>
#include <macros.h>

#define DUNG_DIR   (LOD_DIR + "dungeon/")

int guard_say=1;

public string*
query_moving_object_list()
{
    return ({LOD_DIR + "monster/dark_guard",
             LOD_DIR + "monster/dark_guard"});
}

public void
create_room()
{
    ::create_room();
    
    set_long(query_long() + "South you see the start of a dark corridor. " +
             "East you see nothing but darkness. To the west you " +
             "see the beginning of some stairs. A single torch lights up " +
             "this place.\n");

    add_item(({"torch"}), "It's a simple looking torch, firmly attached " +
	     "to the wall.\n");
    
    add_exit(DUNG_DIR + "stairs2", "west", 0);
    add_exit(DUNG_DIR + "at_pit", "east", 0);
    add_exit(DUNG_DIR + "dung1", "south", "@@check_south");
    
    add_prop(ROOM_I_LIGHT, 1);
    
    reset_room();
}

public void
reset_guard_say()
{
    guard_say = 1;
}

public int
check_south()
{
    object guard = present("dark_guard");
    
    if (!guard || TP->query_npc() || !CAN_SEE(guard, TP)) return 0;
    
    TP->catch_msg(QCTNAME(guard) + " stops you from going there.\n");
    if (guard_say) {
        guard->command("say No, you don't! We don't know what's in " +
                       "those cells and we don't like nasty surprises!");
        guard_say = 0;
        set_alarm(5.0, -1.0, reset_guard_say);
    }
    say(QCTNAME(TP) + " tries to go south but is stopped by " +
        QTNAME(guard) + ".\n");
    
    return 1;
}
