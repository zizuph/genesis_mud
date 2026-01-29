/**********************************************************************
 * - cboard.c                                                       - *
 * - The Gladiator common board room                                - *
 * - Created by Damaris 9/2005                                      - *
 **********************************************************************/
#pragma strict_types

#include <stdproperties.h>

inherit "/std/room";
inherit "/d/Cirath/std/Cirath_magic_room_std";

#include "defs.h"


/* Prototype function */
public void load_board();

void
create_room()
{
	set_short("a dim room");
        set_long("This small dim room has been set-aside for those " +
	"who might be interested in knowing what is considered "+
	"common information. Not much here other than a small "+
	"torch upon the wall and the large common board that "+
	"immortals have posted on. There is a large notice that is "+
	"is firmly attached to the front of the board.\n");
	add_item(({"room", "area", "small room", "dim room", "common room"}), query_long);
	add_item(("notice"),
	"The notice reads:\n"+
	"Only immortals can write on this board.\n"+
	"It is to help in the communication between immortals and "+
	"mortals concerning this realm.\n");
	add_cmd_item("notice", "read", "The notice reads:\n"+
	"Only immortals can write on this board.\nIt is to help in "+
	"the communication between immortals and mortals "+
	"concerning this realm.\n");
	add_cmd_item(({"board", "parchment", "countertop", "inkwell", "quills"}),(({"get","take","burn","climb"})),
	"You fail to do so and should be ashamed for even trying.\n");
	add_cmd_item(({"board"}),(({"get","take","burn","climb"})),
	"You fail to do so and should be ashamed for even trying.\n");
	load_board();
	add_exit("startspt", "west");
  
}

public void
load_board()
{
	object bb;
	seteuid(getuid(this_object()));
	bb = clone_object("/d/Genesis/obj/board");
	bb->move(this_object());
	return;
}
