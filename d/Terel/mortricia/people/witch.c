/*
   A witch. Mortricia 920720
 */

inherit "/std/monster";

inherit "/std/act/seqaction";
#include <ss_types.h>

#define ARM_DIR "/d/Terel/mortricia/armours/"
#define WEP_DIR "/d/Terel/mortricia/weapons/"

create_monster()
{
    set_name("witch");
    set_pname("witches");
    set_short("witch");
    set_pshort("witches");
    set_long("A bitchy old witch. All her clothes are black.\n");
    set_adj(({"bitchy", "old"}));
    set_race_name("human");
    set_gender(1);

    set_stats(({20,20,20,25,25,25}));
    set_hp(1000);
    set_skill(SS_DEFENCE, random(10) + 20);
    set_skill(SS_WEP_KNIFE, random(10) + 20);

    set_act_time(10);
    add_act(({"moan", "grin"}));

    set_chat_time(5);
    add_chat("Woe betide you!");
    add_chat("Beware, I might turn you into a toad.");

    seq_new("do_stream");
    seq_addfirst("do_stream", ({"@@dress_me"}));
}

dress_me() {
    seteuid(getuid(this_object()));
    clone_object(ARM_DIR + "cloak") -> move(this_object());
    clone_object(ARM_DIR + "hat") -> move(this_object());
    clone_object(WEP_DIR + "knife") -> move(this_object());
    command("wear armours");
    command("wield knife");
}
