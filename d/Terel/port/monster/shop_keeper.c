/* This comment tells emacs to use c++-mode -*- C++ -*- */

/* A shop keeper. Mortricia 920927 */
#include "/d/Terel/include/Terel.h"
inherit STDMONSTER;
inherit "/std/act/action";
inherit "/std/act/seqaction";
inherit "/std/act/domove";

#include <ss_types.h>
#include <wa_types.h>
#include <money.h>

#define ALIGN           1000

/*
 * Function name: create_monster
 * Description:   Create the monster. (standard)
 */
public void
create_monster()
{
    if (!IS_CLONE) return;

    ::create_monster();
    set_name("Kamlon");
    add_name("kamlon");
    set_short("Kamlon");
    set_long("It's an old and very fat man. He used to be a fisherman but " +
	     "nowadays he takes care of the shop.\n");
    set_adj(({"old", "fat"}));
    set_gender(MALE);
    set_race_name("human");

    set_stats(({80, 80, 80, 80, 80, 80}));
    SET_MAX_HP;
    SET_MAX_MANA;
    set_alignment(ALIGN);

    set_skill(SS_UNARM_COMBAT, 80);
    set_all_hitloc_unarmed(10);
    set_all_attack_unarmed(80, 80);
    add_prop(LIVE_I_ALWAYSKNOWN,1);

    set_act_time(20),
    add_act(({"sigh", "ponder"}));
}
