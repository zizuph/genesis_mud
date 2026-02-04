/*
 * A grave with no name Mortricia 930430
 */
inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <language.h>
#include <cmdparse.h>
#include "/d/Terel/common/terel_defs.h"

#define PATH           MANSION + "graveyard/"
#define BS(message)    break_string(message, 70)
#define TP             this_player()
#define TO             this_object()
#define MAX_DEPTH      5

void
create_room()
{
    object coffin, skeleton;
    set_short("In a hole");
    set_long(BS(
        "You are standing at the bottom of a deep hole.\n"
    ));

    add_exit(PATH + "g2", "up", "@@check");

    seteuid(getuid(TO));
    coffin = clone_object(MANSION + "obj/coffin");
    coffin -> move(TO);
    skeleton = clone_object(MANSION + "mon/skel");
    skeleton -> move(coffin);
    coffin -> add_prop(CONT_I_CLOSED, 1);
    coffin -> add_prop(CONT_I_LOCK, 1);
}

int
check()
{
    object room;

    room = find_object(PATH + "g2");
    if (!room) return 1;

    if (room->query_at_coffin()) return 0;

    write("You cannot go there, someone has started to fill the hole...\n");
    return 1;
}
