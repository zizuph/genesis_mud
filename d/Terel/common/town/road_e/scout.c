/*
    A scout soldier. Mortricia 920727
 */

inherit "/std/monster";

inherit "/std/act/seqaction";

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

#define PATH "/d/Terel/common/town/road_e/"

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
    set_alignment(random(100)-50);
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
    object cloak, knife;

    seteuid(getuid(this_object()));
    cloak = clone_object(PATH + "cloak");
    cloak -> set_short("dusty cloak");
    cloak -> set_long("A dusty cloak.\n");
    cloak -> set_adj("dusty");
    cloak -> move(this_object());

    knife = clone_object(PATH + "knife");
    knife -> move(this_object());

    command("wear cloak");
    command("wield knife");
}
