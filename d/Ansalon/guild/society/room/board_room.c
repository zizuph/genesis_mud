/* 
 * /d/Ansalon/guild/society/room/board_room.c
 *
 * Copyright (c) 2001 by Alyssa Hardy
 *
 * Copyright notice, please read.
 * 
 * You are welcome to read this file for information & education purposes.
 * However, you are expressly forbidden to copy this code for use in any
 * other mud. This code is part of Genesis and we want Genesis to remain
 * unique. You must invent your own world on your own mud.
 *
 * Board room/exit to the roof (out the window) 
 * Location for the kender common board.
 *
 * Gwyneth, July to September 1999 
 */
#include "../guild.h"
#include <macros.h>

inherit KENDERMORE_IN;

string
read_scroll()
{
    return (VMASTER->list_members());
}

/* 
 * Function name : climb_window
 * Description   : Gives messages and moves the player to the roof.
 */
string
climb_window()
{
    write("You slip through the window with ease. Seeing a rope " + 
        "hanging from the roof, you quickly climb up it, and " + 
        "find yourself on the roof.\n");
    say(QCTNAME(this_player()) + " slips through the window with ease.\n");
    tell_room(KGROOM + "roof", QCTNAME(this_player()) + " climbs onto " +
        "the roof.\n");
    this_player()->move_living("M", KGROOM + "roof", 1, 0);
    return "";
}

/*
 * Function name : create_kendermore_room
 * Description   : Initialize this room
 */
void
create_kendermore_room()
{
    set_short("Board room");
    set_long("This is a rather sparse room, lacking chairs or many " + 
        "other decorations. One wall draws your attention, as it is " + 
        "covered with various notes and postings. A large window " + 
        "allows some fresh air in to the east, and a set of stairs winds " + 
        "up to the common board room. A scroll hangs beside the " + 
        "window.\n");

    add_item(({"window", "large window"}), "Looking out the window, " + 
        "you can see a rope hanging from the roof.\n");
    add_item("rope", "You can't see much more than the tail end. " + 
        "Perhaps you could climb it if you got a bit closer.\n");
    add_item(({"stairs", "set of stairs"}), "The stairs lead to the " + 
        "common board room.\n");
    add_item("scroll", &read_scroll());

    /* Add a way to the roof. */
    add_cmd_item(({"through window", "out window", "window", 
        "out of window"}), ({"enter", "jump", "climb", "squeeze"}), 
        &climb_window());
    add_cmd_item("scroll", "read", &read_scroll());

    add_exit(KGROOM + "joinroom", "northwest", 0); 
    add_exit(KGROOM + "courtyard", "west", 0);
    add_exit(KGROOM + "train", "south", 0);
    add_exit("/d/Genesis/room/common", "up", 0);

    /* Clone the kender guild board. */
    clone_object(KGOBJ + "kender_board")->move(this_object());    
}

void
remove_ex_members(object who)
{
    if (present(who, this_object()))
    {
        who->catch_tell("A very large looking kender enters the room and " + 
            "escorts you out of the guild.\n");
        say("A very large looking kender enters the room and escorts " + 
            QTNAME(who) + " out of the guild.\n", who);
        tell_room(KGROOM + "joinroom", QCTNAME(who) + " is escorted out " + 
            "of the guild by a very large looking kender.\n");
        who->move_living("M", KGROOM + "joinroom", 0, 0);
        return;
    }
    return;
}
