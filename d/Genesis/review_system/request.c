/*
 * A room that contains a board for use by people who want
 * a review made.
 *                              Napture.
 */

inherit "/std/room";
#include <stdproperties.h>
#include "review.h"

#define TO this_object()

create_room()
{
    set_short("The review board room");
    set_long(break_string("This is a bare room, empty except for a " +
        "small note pinned on the wall and an area that looks like " +
        "it is reserved for a bulletin board. The note says:\n", 75) +
        break_string("This board has been set aside for anyone to ask " +
        "for a review of an area. It is not for discussion of reviews " +
        "nor areas. You may ask for a review of any area, but please " +
        "specify who wrote the review, where the area is - either a " +
        "directory name or start place - and a brief outline of " +
        "what the place is about. If the area is not your own nor " +
        "partly your own (joint effort), then please state why you " +
        "want the area reviewed.", 51, 6) + "\n" +
        break_string("Thank you.\n", 63, 10) + "\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);

    add_exit("/d/Debug/debugwiz/workroom", "east", 0);
    add_exit("/d/Debug/debugwiz/comment",  "west", "@@reviewers_only");
    
    reset_room();
}

reset_room()
{
    if (!present("board", TO))  {
        my_board();
    }
}

my_board()
{
    object board;

    board = clone_object(PATH + "boards/req_board");
    board->move(this_object());
}

/* Let anyone in.... */
reviewers_only()
{
    if (member_array(this_player()->query_real_name(), GLOBAL_READ) != -1)  {
        write("Welcome reviewer!\n");
        return 0;
    }
    return 0;
}
        
