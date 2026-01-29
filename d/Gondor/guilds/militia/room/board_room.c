/*
 * /d/Gondor/guilds/militia/room/board_room.c
 *
 * This code is copyright (c) 2001 by Scott A. Hardy and Alyssa Hardy.
 * Genesis is a game currently run through Chalmers University.
 * Scott and Alyssa Hardy have seen the 1991 document of Genesis'
 * called 'legal', and they do not forfeit any of their intellectual
 * property rights as that document supposes they would.  They are the
 * sole and complete owners of this code, which as of April 2001 they are
 * loaning to Genesis.  Genesis does not own this code, or
 * have any right to transfer it to anyone.  By its ongoing
 * use and storage of their code, Genesis acknowledges and agrees
 * to all of the above.
 *
 * Coded by Auberon and Gwyneth on 19 February 2001
 */
inherit "/d/Gondor/std/room";

#include "../militia.h"
#include <macros.h>
#include <stdproperties.h>

public void
create_gondor()
{
    set_short("The Militia board room");
    set_long("Like most of the building, this room is rather spartan and " +
        "functional, with bare walls and straw on the floor.  There is, " +
        "however, a board here with some interesting-looking notes to read.\n");
    add_item(({"floor", "ground", "straw"}), "The straw is fresh and " +
        "clean, and has a few herbs mixed in to repel fleas.\n");
    add_item(({"wall", "walls", "bare walls", "ceiling", "brick"}), 
        "The walls and ceiling are made of good quality brick, and the " +
        "workmanship appears to be that of local mason who took great " +
        "pride in his work and making the buildings of his town look nice.\n");
    add_item(({"building", "room", "barracks"}), "You stand in the " +
        "barracks of the Thornlin Militia.\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_exit(MROOM + "join.c", "east", 0, 1, 0);
    add_prop(ROOM_M_NO_ATTACK, 1);
    add_prop(ROOM_M_NO_MAGIC_ATTACK, 1); 
    clone_object(MOBJ + "board")->move(this_object());
}

void
remove_militia_members(object who)
{
    who->catch_tell("A stern looking guard escorts you out of the " +
        "barracks.\n");
    tell_room(this_object(), QCTNAME(who) + " is escorted out of the " +
        "barracks by a stern looking guard.\n", who);
    tell_room(THORN_DIR + "r2a", QCTNAME(who) + " is escorted out from " +
        "the barracks by a stern looking guard.\n");
    who->move_living("M", THORN_DIR + "r2a", 1, 0);
}

int
did_spit(string str)
{
    remove_militia_members(this_player());
    return 1;
}

public void
init()
{
    ::init();

    add_action(did_spit, "spit");
}
