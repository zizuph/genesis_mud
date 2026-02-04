/*
    A standard swordsman. Mortricia 920729
 */

inherit "/std/monster";

inherit "/std/act/seqaction";

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

#define PATH "/d/Terel/common/town/road_e/"

create_monster()
{
    if (!IS_CLONE)
        return;

    set_name("swordsman");
    set_pname("swordsmen");
    set_short("plain swordsman");
    set_pshort("plain swordsmen");
    set_long(break_string(
        "It's a plain swordsman, although you shouldn't play around with " +
        "him too much.\n", 70));
    set_adj("plain");
    set_race_name("human");
    set_gender(0);
    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_stats(({35,35,35,35,35,35}));
    set_hp(9999);
    set_mana(9999);
    set_alignment(-200);
    set_skill(SS_DEFENCE, 30 + random(11));
    set_skill(SS_UNARM_COMBAT, 30 + random(11));
    set_skill(SS_PARRY, 30 + random(11));
    set_skill(SS_WEP_SWORD, 30 + random(11));

    set_all_hitloc_unarmed(25);
    set_all_attack_unarmed(30, 30);

    seq_new("do_stream");
    seq_addfirst("do_stream", ({"@@dress_me"}));
}

dress_me() {
    seteuid(getuid(this_object()));
    clone_object(PATH + "plain_mail") -> move(this_object());
    clone_object(PATH + "plain_helmet") -> move(this_object());
    clone_object(PATH + "plain_sword") -> move(this_object());

    command("wield sword");
    command("wear armours");
}
