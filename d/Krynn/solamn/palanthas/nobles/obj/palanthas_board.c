/**
 * The Palanthas city board in the nobles park.
 * Taken from Louie 2004
 *
 * Mortis 12.2005
 */
 
inherit "/std/board";

#include "../../local.h"

void
create_board()
{
    seteuid(getuid(this_object()));
    
    set_short("city announcement board");
    set_long("This is the official announcement and notification board of "
	+ "the City of Palanthas authorized by the Bureaumancers, Adjunct "
	+ "Parliament, and Lord Amothus Palanthas.  It is a great pentagonal "
	+ "pillar of translucent white marble with chiseled frames on each of "
	+ "its five sides for posting notes in an orderly fashion.\n");
    set_num_notes(50);
    set_silent(0);
    set_board_name(PALANTHAS_BOARD);
    
        
}