/*
    castle_lady.c
 
    Code by Sarr,
    Recoded by Fysix, March 1998
 */
#pragma strict_types

inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";

#include "default.h"
#include <money.h>

void
create_kalad_monster()
{
    object ob;
    
    set_name("elana");
    add_name("lady");
    set_adj("pale");
    add_adj("luminous");
    set_race_name("human");
    set_gender(1);
    set_short("pale luminous lady");
    set_long("Your gaze falls upon this pale, yet strangely radiant "+
        "lady dressed in fine clothes, and valuable jewelry. Her sparkling "+
        "hazel eyes regard you with calm wonder. She rests her hands in "+
        "her lap as she sits.\n");
    set_alignment(500);
    set_knight_prestige(-500);

    // I am a Kabal citizen
    add_prop(LIVE_I_KABAL_NPC_TYPE, KABAL_CITIZEN);

    add_speak("I wish someone would help my daughter, she has many "+
        "problems....\n");
    set_stats(({60,65,57,77,67,51}));
    set_skill(SS_DEFENSE,46);
    set_skill(SS_AWARENESS,55);

    set_act_time(3);
    add_act("say Greetings, how are you?");
    add_act("say What a lovely day it is.");
    add_act("emote powders her face.");
    add_act("emote straightens her hair.");
    add_act("say I wonder how my husband manages!");
    add_act("say I really dislike goblins...they are so messy!");
    set_cact_time(5);
    add_cact("shout Help! Someone save me!");
    set_title("the Lady of Kabal, wife of the High-Lord");

    setuid();
    seteuid(getuid());
    
    /* These gloves are buggy
    ob = clone_object(NOBLE + "lingerie_shop/gloves");
    ob->set_color("white");
    ob->move(TO);
    */

    ob = clone_object(NOBLE + "arm/pair_rings");
    ob->set_ring_metal("mithril");
    ob->set_ring_metal("diamond", 1);
    ob->set_ring_value(8640);
    ob->move(TO);

    add_equipment(({
        NOBLE + "arm/pierce3",
        NOBLE + "arm/ring",
        NOBLE + "arm/high-heels",
        NOBLE + "arm/pearl_necklace",
        NOBLE + "arm/lady_dress",
        NOBLE + "arm/ring",
        }));

    MONEY_MAKE_GC(random(35))->move(TO);
    command("insert rings in both ears");
}

void
attacked_by(object enemy)
{
    set_alarm(1.0,0.0, "yaya", enemy);
    command("shout Guards! Help! Help!");
    ::attacked_by(enemy);
}

void
yaya(object enemy)
{
    ENV(TO)->call_help(enemy);
}
