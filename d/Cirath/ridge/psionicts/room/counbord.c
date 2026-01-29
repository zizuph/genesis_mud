/* counbord.c: The board of the council. */
#pragma save_binary
#pragma strict_types

inherit "/std/board";
#include "defs.h"
#include <std.h>

#define TPISCOUNCIL (QUERY_COUN_MEMB(lower_case(TP->query_name())) > -1)

void
create_board()
{
    	set_board_name(PSION_LOG+"counboard");
    	set_short("scratch covered table");
    	add_name("table");
    	set_adj("scratch");
    	add_adj("covered");
    	set_long("A solid hexagon of wood, marred by scratches, "+
             "serves as table. Countless messages are spread across it.\n");
    	set_num_notes(50);
    	set_silent(0);
	set_no_report(1);
    	set_remove_str("Kalak has forbidden that.\n");
}

int block_reader() { if (!TPISCOUNCIL) return 1; }

int block_writer() { if (!TPISCOUNCIL) return 1; }
