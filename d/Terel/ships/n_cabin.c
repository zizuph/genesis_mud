/* This comment tells emacs to use c++-mode -*- C++ -*- */

#include "/d/Terel/include/Terel.h"
inherit "/d/Genesis/ship/cabin";

/*
 * Function name: create_cabin
 * Description  : Create the ship cabin
 */
public void
create_cabin()
{
    set_short("The captain's cabin");
    set_long("The captain's cabin.\n");
    add_exit(SHIP_DIR + "n_deck", "deck", 0);
}
