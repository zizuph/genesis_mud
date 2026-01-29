/* -*- Mode: C -*-
 *
 * trade/streets/q-10.c
 *
 * By Skippern 20(c)01
 *
 * A jatta jatta jatta
 */
#include "../../defs.h"

inherit DOL_STD + "city.c";

public void
create_dol_amroth()
{
    object o;

    set_short("a crowded square");
    set_extralines("A large crowd is present here.");
    set_lastline("Old men gather here to discuss the important events of " +
		 "this town.");

    set_sounds("You here the buzzing of old men here.");
    set_sound_detail("You think you can make out words such as: " +
	"War, Prince Imrahil and Minas Tirith.");

    set_no_of_lamps(4);
    reset_room();

    add_item("crowd", "A crowd of old men is gathered here discussing " +
	     "politics and resent events. You can hear their buzzing.\n");

    street_tells();
    square_tells();

    add_exit(DOL_TRADE + "streets/r-10", "east", 0, 1);

    o = clone_object("/std/board");
    o->set_short("Dol Amroth Board");
    o->set_board_name(DOL_BOARD);
    o->set_num_notes(20);
    o->set_silent(1);
    o->set_show_lvl(1);
    o->set_no_report(1);
    o->set_remove_lvl(15);
    o->set_remove_str("The council would not aprove this.\n");
    o->move(this_object());
}




