/*
 * Board for the realtor office
 *
 * Varian 9/24/2021
 *
 */

#pragma strict_types

inherit "/std/board";

#include <macros.h>
#include <std.h>

public nomask void
create_board()
{
    seteuid(getuid(this_object()));
    set_board_name("/d/Genesis/houses/realtor_board");
    set_num_notes(30);
    set_silent(1);
    set_show_lvl(1);
    set_no_report(1);
    set_keep_discarded(0);
}