/* This comment tells emacs to use c++-mode -*- C++ -*- */

#include "/d/Terel/include/Terel.h"
inherit SHIP_DIR + "ship_captain";

/*
 * Function name: create_monster
 * Description:   Create the monster. (standard)
 */
public void
create_monster()
{
    ::create_monster();
    set_name("samlon");
    add_name("captain");
    set_living_name("samlon");
    set_race_name("human");
    set_adj("friendly");
    add_adj("robust");
    set_ticket_file(SHIP_DIR + "t_ticket");
    set_ship_info("It goes between Calathin and Berth 5 in Sparkle.");
    set_title("the experienced captain, son of Kamlon");
}
