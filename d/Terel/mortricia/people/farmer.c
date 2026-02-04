/*
    A farmer. Mortricia 920729
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
    set_name("farmer");
    set_short("farmer");
    set_long(break_string(
        "A tall human that must be the farmer.\n", 70));
    set_adj("tall");

    set_race_name("human");
    set_gender(0);

    set_stats(({32,28,25,30,30,35}));
    set_hp(9999);
    set_skill(SS_DEFENCE, random(10) + 30);
    set_skill(SS_UNARM_COMBAT, random(5) + 30);
    set_skill(SS_WEP_AXE, random(5) + 40);

    set_act_time(30);
    add_act(({"sigh"}));

    set_chat_time(30);
    add_chat("Gee, I'm tired.\n");

    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_all_hitloc_unarmed(25);
    set_all_attack_unarmed(30, 30);

    seq_new("do_first");
    seq_addfirst("do_first", "@@dress_me");
}

dress_me()
{
    object scythe, cloak;

    seteuid(getuid(this_object()));
    cloak = clone_object(TOWNDIR + "farms/cloak");
    cloak -> set_short("smelling cloak");
    cloak -> set_long("A smelling cloak. Its smell is disgusting.\n");
    cloak -> set_adj("smelling");
    cloak -> move(this_object());

    scythe = clone_object(TOWNDIR + "farms/scythe");
    scythe -> move(this_object());

    command("wear cloak");
    command("wield scythe");
}
