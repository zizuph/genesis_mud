/*
    A prince, will turn when toad is kissed ;-) Mortricia 920723
 * 
 * Modification Log:
 * Added clone_unique code per AoB's request  -- Tomas  April 2000
 */

#include "/d/Terel/include/Terel.h"
inherit STDMONSTER;

inherit "/std/act/seqaction";
inherit "/lib/unique";

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

#define PATH "/d/Terel/silver/cottage/"

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

    seteuid(getuid(this_object()));
    clone_unique(PATH + "bluebolt",7,PATH + "bluesword")->move(this_object());
    clone_object(PATH + "blue_cloak") -> move(this_object());
    clone_object(PATH + "blue_helmet") -> move(this_object());
    clone_object(PATH + "blue_boots") -> move(this_object());

    gem = clone_object("/d/Genesis/gems/obj/sapphire")->move(TO);

    command("wield sword");
    command("wear armours");
    command("smile");
    command("say Thanks my friend for releasing me. Here is a gift.");
    command("drop gem");
}
