/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * servgirl.c
 *
 * Vader
 * Modified by Sorgum 950707
 * Modified by Bronco 950718
 */

#include "/d/Terel/include/Terel.h"
inherit STDMONSTER;

/*
 * Function name: create_monster
 * Description:   Create the monster. (standard)
 */
public void
create_monster()
{
    ::create_monster();
    set_name("servant");
    add_name("boy");
    set_adj("timid");
    
    add_adj("young");
    set_race_name("human");
    set_short("timid young serving boy");
    set_long("This small boy performs errands for the king.\n");

    set_stats(({6, 6, 6, 6, 6, 6}));
    set_all_hitloc_unarmed(25);
    set_act_time(random(10));
    add_act("smile");
    add_act("bow to all");
    set_alignment(100);
    SET_MAX_HP;
}
