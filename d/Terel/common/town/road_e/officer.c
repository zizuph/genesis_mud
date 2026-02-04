/*
    An officer. Mortricia 920729
 */

inherit "/std/monster";

inherit "/std/act/seqaction";

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <money.h>

#define PATH "/d/Terel/common/town/road_e/"

create_monster()
{
    if (!IS_CLONE)
        return;

    set_name("officer");
    set_short("robust officer");
    set_long(break_string(
        "It's a robust officer. He looks powerful.\n", 70));
    set_adj("robust");
    set_race_name("human");
    set_gender(0);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_I_QUICKNESS, 70);

    set_chat_time(25);
    add_chat("The river has flooded and we cannot go back.");

    set_stats(({65,65,65,65,65,65}));
    set_hp(9999);
    set_mana(9999);
    set_alignment(-500);
    set_skill(SS_DEFENCE, 60 + random(11));
    set_skill(SS_UNARM_COMBAT, 40 + random(11));
    set_skill(SS_PARRY, 60 + random(11));
    set_skill(SS_WEP_SWORD, 60 + random(11));

    set_all_hitloc_unarmed(40);
    set_all_attack_unarmed(35, 35);

    MONEY_MAKE_SC(10) -> move(this_object());

    seq_new("do_stream");
    seq_addfirst("do_stream", ({"@@dress_me"}));
}

dress_me() {
    seteuid(getuid(this_object()));
    clone_object(PATH + "blue_cloak") -> move(this_object());
    clone_object(PATH + "blue_helmet") -> move(this_object());
    clone_object(PATH + "blue_sword") -> move(this_object());

    command("wield sword");
    command("wear armours");
}
