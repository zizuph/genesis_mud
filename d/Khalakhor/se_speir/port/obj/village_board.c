/*
 * village_board.c
 *
 * Area board for Port Macdunn
 *
 * Khail - June 4/97
 */
#pragma save_binary

inherit "/std/board.c";
#include "/d/Khalakhor/sys/defs.h"
#include <std.h>
#include "defs.h"

public void
create_board()
{
    set_name("board");
    set_short("Public board of Port Macdunn");
    set_board_name(OBJ + "boards/village_board");
    set_num_notes(30);
    set_show_lvl(0);
    set_remove_rank(WIZ_NORMAL);
    set_remove_str("You can't do that.\n"); 
}

/*
 * Function name: allow_remove
 * Description  : Restricts removal access to Khalakhor wizards
 *                and admin.
 * Arguments    : n/a
 * Returns      : 0 - Can't remove.
 *                1 - Can remove.
 */
public nomask int
allow_remove()
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
