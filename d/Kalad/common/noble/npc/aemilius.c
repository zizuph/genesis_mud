/* 
 * /d/Kalad/common/noble/npc/aemilius.c
 * Purpose    : The head lord of the House of Aemilius
 * Located    : /d/Kalad/common/noble/aemilius/
 * Created By : Sarr ??.??.96
 * Modified By: Fysix, 02-98, recoded
 */ 

inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";

#include "default.h"

void
create_kalad_monster()
{
    set_name("Lord Aemilius");
    add_name("aemilius");
    add_name("lord");
    set_adj("lord");
    add_adj("grey-haired");
    add_adj("dark-eyed");
    add_name("noble");
    set_race_name("human");
    set_short("grey-haired dark-eyed noble");
    set_long("You look at an elderly looking man, with grey hair. His "+
    "dark eyes, however, look very sharp and keen. He is still "+
    "well built, and regards you with proud stance.\n");

    set_alignment(600);
    set_knight_prestige(-400);
    set_stats(({70,70,60,80,80,70}));

    set_skill(SS_PARRY, 70);
    set_skill(SS_DEFENSE, 70);
    set_skill(SS_WEP_KNIFE, 80);
    set_skill(SS_BLIND_COMBAT, 50);

    set_act_time(3);
    add_act("say Greetings, old boy.");
    add_act("emote studies his ring.");
    add_act("yawn");
    add_act("snore");
    add_act("say What can I do for you?");
    add_act("emote ponders the state of things in the district.");
    set_title("the Earl of Uthantia");

    add_equipment(({
        NOBLE + "arm/silk_tunic",
        NOBLE + "arm/e_leather_pants",
        NOBLE + "arm/ring",
        NOBLE + "arm/ring",
        NOBLE + "arm/gold_chain",
        NOBLE + "arm/leather_shoes",
        NOBLE + "arm/gold_chain",
        NOBLE + "wep/jeweled_dagger"
        }));
}

void
attacked_by(object ob)
{
    command("shout Help! Guards!");
    call_other(NOBLE + "aemilius/m16", "emergency", ob);
    ::attacked_by(ob);
}
