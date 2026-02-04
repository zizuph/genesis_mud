/*
    An officer. Mortricia 920729
 */

inherit "/std/monster";

inherit "/std/act/seqaction";

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

#define ARM_DIR "/d/Terel/mortricia/armours/"
#define WEP_DIR "/d/Terel/mortricia/weapons/"
#define OBJ_DIR "/d/Terel/mortricia/objects/"

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

    set_stats(({55,55,55,55,55,55}));
    set_hp(9999);
    set_skill(SS_DEFENCE, 50 + random(11));
    set_skill(SS_UNARM_COMBAT, 50 + random(11));
    set_skill(SS_PARRY, 50 + random(11));
    set_skill(SS_WEP_SWORD, 50 + random(11));

    set_all_hitloc_unarmed(45);
    set_all_attack_unarmed(40, 40);

    seq_new("do_stream");
    seq_addfirst("do_stream", ({"@@dress_me"}));
}

dress_me() {
    seteuid(getuid(this_object()));
    clone_object(ARM_DIR + "blue_cloak") -> move(this_object());
    clone_object(ARM_DIR + "blue_helmet") -> move(this_object());
    clone_object(WEP_DIR + "blue_sword") -> move(this_object());

    command("wield sword");
    command("wear armours");
}
