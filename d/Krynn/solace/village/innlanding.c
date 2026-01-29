/* Solace coded by Nick */

#include "/d/Krynn/common/defs.h"
#include "local.h"
#include <stdproperties.h>

inherit SOLOUTROOM;

create_solace_room() {
    set_short_desc("standing on a landing");
    set_extra_line("In front of you is the legendary Inn of the " +
	     "Last Home. Your view would have " +
	     "been splendid if it weren't for all the branches and " +
	     "leaves in your way. You could enter the Inn or climb " +
	     "down a staircase. East there is a bridge taking you " +
	     "to the local shop. West is another bridge but you can't " +
	     "see where it leads to with all these leaves about.");

    add_exit(TDIR + "solace2", "down");
    add_exit(TDIR + "shop", "east");
    add_exit(TDIR + "inn", "enter");
    add_exit(TDIR + "solace26", "west");
    add_exit(TDIR + "wise_club", "north");

    add_item("leaves", "They look very green and healthy.\n");
    add_item("branches", "They are stuck to a tree.\n");
    add_item("tree", "It has a staircase running down around it.\n");
    add_item(({"stairs","staircase"}),
	"They lead up to the Inn of the Last Home and down to the ground.\n");
    add_item(({"bridge","bridges"}),
        "They're made out of wood and look safe to travel, in fact, most\n" +
        "people do this here in solace.\n");

    seteuid(getuid(TO));
    load_board();

    reset_solace_room();
}

/* This loads the main solace bulletin board */
void
load_board()
{
    clone_object(OBJ + "city_board")->move(TO);
}

reset_solace_room()
{
    if (!present("boy", TO))
    	clone_object(MON + "so_boy")->move_living("xx", TO);
}



