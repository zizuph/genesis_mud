/*
 * Recode Discussion Room
 *
 * This room will house a board where members of the Dragon Order can
 * discuss their future recode.
 *
 * Created by Petros, December 2010
 */

#pragma save_binary
#pragma strict_types

#include <time.h>
#include <macros.h>
#include <stdproperties.h>

#include "../defs.h"

inherit M_ROOM_BASE;

inherit DG_OBJ_LIBS;

void load_board();
 
public void
create_room()
{
    set_short("Discussion alcove");
    set_long("This small alcove is rather bare, reflecting the serenity of "
        + "the temple. The only thing of note in this alcove is a discussion "
        + "board. Here, members of the Dragon Order can discuss ideas "
        + "regarding the future guild recode. To the south is the meeting "
        + "room."        
        + "\n");

    add_prop (ROOM_I_INSIDE, TRUE);

    add_exit("meeting", "south");

    load_board();
}

public void
load_board()
{
    object bb;
    seteuid(getuid(this_object()));
    bb = clone_object(M_OBJ_BOARD_RECODE);
    bb->move(this_object());
}
