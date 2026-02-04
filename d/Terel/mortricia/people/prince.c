/*
    A prince, will turn when toad is kissed ;-) Mortricia 920723
 */

inherit "/std/monster";

inherit "/std/act/seqaction";
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

#define ARM_DIR "/d/Terel/mortricia/armours/"
#define WEP_DIR "/d/Terel/mortricia/weapons/"
#define COT_DIR "/d/Terel/common/forest/cottage/"
#define OBJ_DIR "/d/Terel/mortricia/objects/"

create_monster()
{
    if (!IS_CLONE)
        return;

    set_name("azure");
    set_short("human");
    set_long(break_string(
        "An impressive human. Judged by his appearance you feel that he " +
        "is some kind of prince.\n", 70));
    set_adj("impressive");
    set_race_name("human");
    set_gender(0);

    set_stats(({60,60,60,60,60,60}));
    set_hp(9999);
    set_skill(SS_DEFENCE, 40 + random(11));
    set_skill(SS_UNARM_COMBAT, 40 + random(11));
    set_skill(SS_PARRY, 55 + random(11));
    set_skill(SS_WEP_SWORD, 55 + random(11));
    set_skill(SS_LANGUAGE, 70);

    set_all_hitloc_unarmed(25);
    set_all_attack_unarmed(40, 40);

    set_chat_time(20);
    add_chat("My friend! My name is the colour of the sky.");

    set_cact_time(1);
    add_cact(({"scream", "cry"}));
    enable_commands();

    seq_new("do_stream");
    seq_addfirst("do_stream", ({"@@dress_me"}));
}

dress_me() {
    object gem;

    seteuid(getuid(this_object()));
    clone_object(ARM_DIR + "blue_cloak") -> move(this_object());
    clone_object(ARM_DIR + "blue_helmet") -> move(this_object());
    clone_object(ARM_DIR + "blue_boots") -> move(this_object());
    clone_object(COT_DIR + "bluebolt") -> move(this_object());

    gem = clone_object(OBJ_DIR + "gem");
    gem -> add_prop(OBJ_I_VALUE, 400 + random(101));
    gem -> set_long("It's a large blue gem. It looks valuable.\n");
    gem -> set_adj(({"large", "blue"}));
    gem -> move(this_object());

    command("wield sword");
    command("wear armours");
    command("say Thanks my friend for releasing me. Here is a gift.");
    command("smile");
    command("drop gem");
    command("read runes");
}
