/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * bartender.c
 *
 *  A bartender. Mortricia 920927
 *
 */

#include "/d/Terel/include/Terel.h"
inherit STDMONSTER;
inherit "/std/act/action";
inherit "/std/act/seqaction";
inherit "/std/act/domove";

#include <ss_types.h>

/*
 * Function name: create_monster
 * Description:   Create the monster. (standard)
 */
public void
create_monster()
{
    if (!IS_CLONE)
        return;

    ::create_monster();
    set_name("bartender");
    set_short("fat bartender");
    set_long("It's a fat bartender. Don't mess with him.");
    set_adj("fat");
    set_race_name("human");
    set_gender(MALE);

    set_stats(({99, 99, 99, 99, 99, 99}));
    SET_MAX_HP;
    SET_MAX_MANA;
    set_alignment(100);

    set_skill(SS_UNARM_COMBAT, 100);

    set_all_hitloc_unarmed(1);
    set_all_attack_unarmed(20, 100);

    set_act_time(20);
    add_act(({"shout Ahoy matey!", "laugh", "say Bottoms up!"}));

    set_cact_time(11);
    add_cact("grin");
}
