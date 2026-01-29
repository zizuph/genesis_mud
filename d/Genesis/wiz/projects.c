/*
 * Creator: Shadowlynx
 * Date   : 29-May-2000
 * File   : /d/Genesis/wiz/projects.c
 * Purpose: This room holds a discussion board for special projects
 * Revised:
 */
#pragma save_binary

#include "default.h"

void
create_room() 
{
    object board;

    set_short("Special Projects discussion room");
    set_long( "Special Projects discussion room.\n" +
      "This is a room for discussions and planning ideas on\n" +
      "any special projects that are being considered or are\n" +
      "being worked on. To the east is the wizard discussion\n" +
      "room.\n");

    add_exit(THIS_DIR + "discuss", "east");

    board = load_board("projects");
    board->set_num_notes(99);

    add_default_exits();
}

