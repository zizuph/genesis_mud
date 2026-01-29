//
// Board of Sean-Rhian guild, abbey at MacDunn
//
#pragma save_binary
 
inherit  "/std/board.c";
#include "/d/Khalakhor/sys/defs.h"
#include <std.h>
#include "defs.h"
 
void create_board()
{
    set_name("board");
    set_short("Seanchan Tor Abbey board");
    set_long("It is the bulletin board of Seanchan Tor Abbey of the "+
             "Order of Sean-Rhian.\n");
    set_board_name(OBJ+"board/abbey");
    set_num_notes(30);
    set_show_lvl(0);
    set_remove_rank(WIZ_NORMAL);
    set_remove_str("You can't do that.\n");
}
 
public nomask int allow_remove()
{
  /* Allow Khalakhor wizards to remove. */
    if (SECURITY->query_wiz_dom(TIQRN) == "Khalakhor")
        return 1;
  /* Allow arches + to remove. */
    if (SECURITY->query_wiz_rank(TIQRN) >= WIZ_ARCH)
        return 1;
    if (SECURITY->valid_write_all_sanction(TIQRN, "Khalakhor"))
        return 1;
  /* Disallow anyone else to remove. */
    return 0;
}
