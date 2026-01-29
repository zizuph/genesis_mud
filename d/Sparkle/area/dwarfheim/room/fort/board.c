/*
 * Copyright notice, please read.
 *
 * Copyright Chalmers Datorf|rening, 1992
 *
 * You are welcome to read this file for information & education purposes.
 * However, you are expressly forbidden to copy this code for use in any
 * other mud. This code is part of Genesis and we want Genesis to remain
 * unique. You must invent your own world on your own mud.
 *
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>

#include "defs.h"

static void create_board();

object duck;

void
create_room()
{
    set_short("Board room");
    set_long("\nThis is a small round room with two exits, one leading "+
             "east to the temple and the other leading south towards "+
             "the rest of the dwarven cave. In this room the king "+
             "has put a bulletin board, to be used for information, "+
             "discussions and suggestions from the players. There "+
             "is a bench just below the board.\n");

    add_item(({ "bench" }),
             BS("The bench is just the right height to sit comfortably on. However, it's made of stone, so don't expect TOO much comfort.\n"));

    add_exit("corr6", "south");
    add_exit(S_DOMAIN_START_DIR + "dwarf/start","east");

    create_board();

    reset_room();
}

public void
reset_room()
{
    if (duck)
        return;

    duck = clone_object(S_LOCAL_NPC_DIR + "duck");
    duck->move_living("skjsdjh", TO);
}

static void
create_board()
{
    object board;

    if ((board = clone_object("/std/board")))
    {
        board->set_board_name(S_VAR_BOARD_DIR + "dwarfheim");
        board->set_num_notes(25);
        board->set_anonymous(0);
        board->set_silent(1);
        board->set_show_lvl(1);
        board->set_remove_lvl(10);
        board->set_remove_str("Sorry, mortals are not allowed to remove notes.");
        board->set_err_log(S_LOG_BOARD_DIR + "dwarfheim");

        board->move(TO);
    }
    return 0;
}

