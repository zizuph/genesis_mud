/*
    A prince, will turn when toad is kissed ;-) Mortricia 920723
 */

inherit "/std/monster";

inherit "/std/act/seqaction";
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

#define PATH "/d/Terel/silver/hag/"

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

    set_stats(({90,105,99,100,100,100}));
    set_hp(9999);
    set_mana(9999);
    set_alignment(0);
    set_skill(SS_DEFENCE, 65 + random(11));
    set_skill(SS_UNARM_COMBAT, 65 + random(11));
    set_skill(SS_PARRY, 65 + random(11));
    set_skill(SS_WEP_SWORD, 88 + random(11));

    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_all_hitloc_unarmed(35);

    set_chat_time(20);
    add_chat("My friend! My name is the colour of the sky.");

    seq_new("do_stream");
    seq_addfirst("do_stream", ({"@@dress_me"}));
}

dress_me() {
    object gem;

    setuid();
    seteuid(getuid(this_object()));
    clone_object(PATH + "blue_cloak") -> move(this_object());
    clone_object(PATH + "blue_helmet") -> move(this_object());
    clone_object(PATH + "blue_boots") -> move(this_object());
    clone_object(PATH + "bluebolt") -> move(this_object());

    gem = clone_object(PATH + "gem");
    gem -> add_prop(OBJ_I_VALUE, 400 + random(101));
    gem -> set_long("It's a large blue gem. It looks valuable.\n");
    gem -> set_adj(({"large", "blue"}));
    gem -> move(this_object());

    command("wield sword");
    command("wear armours");
    command("smile");
    command("say Thanks my friend for releasing me. Here is a gift.");
    command("drop gem");
}
