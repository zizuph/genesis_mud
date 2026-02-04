/*
    A scout soldier. Mortricia 920727
 */

inherit "/std/monster";

inherit "/std/act/seqaction";

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

#define ARM_DIR "/d/Terel/mortricia/armours/"

create_monster()
{
    if (!IS_CLONE)
        return;
    set_name("scout");
    set_short("scout");
    set_long("It's a scout. He is probably here on a reconnaisance mission.\n");
    set_adj("slim");

    set_race_name("human");
    set_gender(0);

    set_stats(({25, 25, 25, 25, 25, 25}));
    set_hp(9999);
    set_mana(9999);
    set_skill(SS_DEFENCE, random(10) + 20);
    set_skill(SS_UNARM_COMBAT, random(5) + 20);

    set_act_time(30);
    add_act(({"stare"}));

    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_all_hitloc_unarmed(15);
    set_all_attack_unarmed(20, 20);

    seq_new("do_first");
    seq_addfirst("do_first", "@@dress_me");
}

dress_me()
{
    object cloak;

    seteuid(getuid(this_object()));
    cloak = clone_object(ARM_DIR + "cloak");
    cloak -> set_short("dusty cloak");
    cloak -> set_long("A dusty cloak.\n");
    cloak -> set_adj("dusty");
    cloak -> move(this_object());

    command("wear cloak");
}
