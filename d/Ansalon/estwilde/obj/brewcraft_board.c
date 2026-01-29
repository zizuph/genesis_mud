/*
 * This is the board for Brewcraft
 * Vitwitch 2021
 */
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
inherit  "/std/board";

void
create_board()
{
    seteuid(getuid(TO));
    set_short("board of brew stained parchments");
    set_name("parchments");
    add_name("parchment");
    add_name("messages");
    add_name("board");
    add_name("pieces of parchments");
    set_long("The cork board is filled with messages stained with brew, " +
             "shared between brew crafters and brew drinkers.\n");
    set_board_name("/d/Ansalon/estwilde/obj/brewcraft_board");
    set_num_notes(10);
    set_silent(0);
    set_show_lvl(1);
    set_no_report(0);
    set_no_show_composite(1);
    set_keep_discarded(0);
}
