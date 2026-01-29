inherit "/d/Gondor/common/room";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define	OFFICE	(PELAR_DIR + "misc/pel_office")

object  board;

public int	check_killer();

void
create_room()
{
    set_short("the City Hall of Pelargir");
    set_long(BSN("This is the Great Hall in the City Hall of "
      + "Pelargir. Here the citizen assemble when they are summoned "
      + "by the Lord Councillor or by the admiral of the Royal "
      + "Gondorian Fleet. The hall has a circular outline, and the "
      + "roof is formed by a giant cupola. At the northern end of "
      + "the hall is a doorway leading into an annex that houses "
      + "the offices of the Royal Council of Pelargir and of the Lord "
      + "Councillor and his staff."));

    add_exit(PELAR_DIR + "misc/pel_office", "north", check_killer,0);
    add_exit(PELAR_DIR + "streets/belfalas09", "east", 0);

//  add_item("poster","@@read_poster");
//  add_cmd_item("poster", "read", "@@read_poster");

    add_prop(ROOM_I_INSIDE,1);

    board = clone_object(STD_DIR + "board");
    board->set_board_name(BOARD_DIR + "pelargir");
    board->set_num_notes(30);
    board->set_silent(0);
    board->set_show_lvl(0);
    board->set_remove_lvl(15);
    board->set_remove_str("The note is stuck, you can't do that.");
    board->move(TO);

}

/*
 * Function name:	check_killer
 * Description	:	don't let known killers of the quest master in
 * Returns	:	int -- 0 if exit allowed, 1 if not
 */
public int
check_killer()
{

    FIX_EUID;
    if (!OFFICE->query_killer(TP))
    {
	return 0;
    }
    write("You find yourself mysteriously unable to move in that direction.\n");
    return 1;
}
