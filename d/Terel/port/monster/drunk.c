/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
  A drunk. Mortricia 920927
 */
#include "/d/Terel/include/Terel.h"
inherit STDMONSTER;
inherit "/std/act/action";
inherit "/std/act/seqaction";
inherit "/std/act/domove";

#include <ss_types.h>
#include <wa_types.h>
#include <money.h>

#define ALIGN           100

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
    set_name("sailor");
    set_short("drunken sailor");
    set_long("It's a drunken sailor.\n");
    set_adj("drunken");
    set_race_name("human");
    set_gender(0);

    set_stats(({15, 15, 15, 10, 10, 15}));
    SET_MAX_HP;
    SET_MAX_MANA;
    set_alignment(ALIGN);
    set_intoxicated(5);

    set_skill(SS_UNARM_COMBAT, 10);

    set_all_hitloc_unarmed(5);
    set_all_attack_unarmed(10, 10);

    set_chat_time(18);
    add_chat("Gee, two bartenders!?");

    set_act_time(40);
    add_act(({"buy beer", "drink beer", "burp"}));

    MONEY_MAKE_SC(15)->move(TO);

    set_cact_time(8);
    add_cact("giggle");
}
