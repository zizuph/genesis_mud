/*
   Diamond. Board Room of the City

    board.c 
    --------

    Coded ........: April 1997
    By ...........: Kentari

    Latest update : April 1997
    By ...........: Kentari

*/

#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit IN_BASE;

/* 
 * This loads the main diamond city bulletin board 
 */

static void
load_board()
{
    clone_object(DIOBJ + "city_board")->move(TO);
}

void
create_dim_room()
{
    set_short("The Public Board of Diamond City");
    set_long("You are in the public board room of Diamond City " +
	"where you can post notes. The room is plain, with a " +
	"tapestry on the wall as the only decoration.\n");
    AI(({"tapestry","wall"}),
	"The tapestry shows a rough map of the city, showing how " +
	"it is in the layout of a diamond, with the streets in " +
	"symmetry. Quite beautiful simplicity.\n");    

    AE(DIROOM + "s2", "east", 0);
    AE(DIROOM + "common", "down", 0);

    seteuid(getuid(TO));
    load_board();
}

