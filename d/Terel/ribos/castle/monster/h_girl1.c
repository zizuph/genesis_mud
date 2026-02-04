/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * h_girl1.c
 *
 * This is a concubine, coded by Vader on 2/16/93
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
    
    set_name("concubine");
    add_name("loosey");
    set_adj("voluptuous");
    add_adj("naked");

    set_race_name("human");
    set_short("naked voluptuous concubine");
    set_long("This young lady is laying on a sofa, rubbing her curvaceous " +
             "body with luscious body oils.\n");

    set_stats(({10, 10, 10, 10, 10, 10}));
    set_all_hitloc_unarmed(15);

    set_act_time(random(10));
    add_act("giggle");
    add_act("smile");
    add_act("gasp");
    add_act("moan");
    set_gender(1);
    set_alignment(50);

    SET_MAX_HP;

    trig_new("%w 'kisses' %s", "hang_on");
    trig_new("%w 'gives' 'you' %s", "hang_on");
}

public void
do_react(string str1, string str2)
{
    command("slap " + str1);
    command("say Shame one you.  I belong to the king!\n");
}

public void
hang_on(string str1, string str2)
{
    set_alarm(2.0, -1.0, &do_react(str1, str2));
}
