/*
   An eremite. Mortricia 920717
 */

inherit "/std/monster";

inherit "/std/act/seqaction";
#include <ss_types.h>

#define ARM_DIR "/d/Terel/mortricia/armours/"

create_monster()
{
    set_name("eremite");
    set_short("eremite");
    set_long("A very old man.\n");
    set_adj("old");
    set_race_name("human");
    set_gender(0);

    set_stats(({15,15,15,15,20,15}));
    set_hp(1000);
    set_skill(SS_DEFENCE, random(10) + 20);
    set_skill(SS_UNARM_COMBAT, random(5) + 10);

    set_act_time(30);
    add_act(({"sigh", "cough"}));

    set_all_hitloc_unarmed(5);
    set_all_attack_unarmed(10, 10);

    seq_new("do_stream");
    seq_addfirst("do_stream", ({"@@dress_me"}));
}

dress_me() {
    seteuid(getuid(this_object()));
    clone_object(ARM_DIR + "nightshirt") -> move(this_object());
    command("wear nightshirt");
}
