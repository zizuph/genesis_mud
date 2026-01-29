
#pragma save_binary
#pragma strict_types

inherit "/std/board";

#include <macros.h>
#include <files.h>
#include <std.h>
#include "defs.h"
#include SPIRIT_HEADER
#include COUNCIL_HEADER

void
create_board()
{
    seteuid(getuid(TO));
    set_board_name(SPIRIT_TEMPLE+"elder_board");
    set_num_notes(30);
    set_silent(1);
    set_show_lvl(1);
    set_no_show_composite(1);

    set_name(({"pile", "papers", "pile of papers"}));
    set_short("pile of papers");
    set_long("They are a pile of papers, some with notes on them, " +
        "others are blank.\n");

    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VOLUME, 500);
}

void
reset_board()
{
   
}

int
council_board_check()
{
    return (COUNCIL_CODE->is_spirit_elder(capitalize(TP->query_real_name()))
        || COUNCIL_CODE->is_calian_wiz(TP) || (WIZ_CHECK >= WIZ_ARCH));
}


/* Stop unwanted people reading, writing or removing notes */
varargs int 
block_reader()
{
    return !council_board_check();
}


varargs int 
allow_remove()
{
    return council_board_check();
}


varargs int 
block_writer()
{
    return !council_board_check();
}
