/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * servgirl.c
 *
 * Vader
 * Modified by Sorgum 950707
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
    set_adj("voluptuous");
    
    if (random(2))
	add_name("Melinda");
    else
	add_name("Marta");
    
    add_adj("young");
    set_race_name("human");
    set_short("young voluptuous servant");
    set_long("This young lady is assisting the king " +
	     "in taking a bath.  She is not wearing anything, and looks as " +
	     "if she works out alot.\n");

    set_stats(({10, 10, 10, 10, 10, 10}));
    set_all_hitloc_unarmed(25);
    set_act_time(random(10));
    add_act("giggle");
    add_act("smile");
    add_act("gasp");
    add_act("kiss king");
    add_act("moan");
    set_gender(1);
    set_alignment(100);
    SET_MAX_HP;
}
