inherit "/std/board";

#include <std.h>

#include "defs.h"

void create_board()
{
 set_board_name(SCHEDULER_DIR+"board");
 set_num_notes(50);
 set_silent(0);
 set_remove_rank(WIZ_ARCH);
 set_remove_str("Only ArchWizards can remove notes here!\n");
}

