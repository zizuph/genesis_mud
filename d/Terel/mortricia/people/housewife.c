/*
    The farmer's housewife. Mortricia 920729
 */

inherit "/std/monster";

inherit "/std/act/seqaction";

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

#include "/d/Terel/common/terel_defs.h"

create_monster()
{
    if (!IS_CLONE)
        return;
    set_name("housewife");
    set_short("angry housewife");
    set_long(break_string(
        "A human that must be the farmer's wife.\n", 70));
    set_adj("angry");

    set_race_name("human");
    set_gender(1);

    set_stats(({22,22,22,25,25,24}));
    set_hp(9999);
    set_skill(SS_DEFENCE, random(10) + 15);
    set_skill(SS_UNARM_COMBAT, random(5) + 15);
    set_skill(SS_WEP_CLUB, random(5) + 30);

    set_act_time(30);
    add_act(({"sigh"}));

    set_chat_time(30);
    add_chat("You are late again! You bastard!\n");

    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_all_hitloc_unarmed(20);
    set_all_attack_unarmed(20, 20);

    seq_new("do_first");
    seq_addfirst("do_first", "@@dress_me");
}

dress_me()
{
    object pin, apron;

    seteuid(getuid(this_object()));
    apron = clone_object(TOWNDIR + "farms/apron");
    apron -> move(this_object());

    pin = clone_object(TOWNDIR + "farms/rolling_pin");
    pin -> move(this_object());

    command("wear apron");
    command("wield pin");
}
