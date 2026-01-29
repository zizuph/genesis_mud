/*
    old_noble.c
    
    Code by Sarr,
    Recoded by Fysix, March 1998
 */
#pragma strict_types

inherit "/d/Kalad/std/monster";

#include "default.h"
#include <money.h>

void
create_kalad_monster()
{
    set_name("noble-woman");
    add_name("noble");
    set_adj("rich");
    add_adj("old");
    set_gender(1);
    set_race_name("human");
    set_short("old rich noble-woman");
    set_long("She gazes at you with narrow eyes, then turns her head. "+
        "This woman looks cold, cruel and calculating.\n");

    set_alignment(200);
    set_knight_prestige(-60);
    add_speak("There are times when I think the poor people are fools.\n");

    set_stats(({70,70,70,70,70,100}));
    set_skill(SS_WEP_KNIFE,60);
    set_skill(SS_DEFENSE,60);

    set_random_move(1);

    set_act_time(3);
    add_act("emote turns her shoulder to you.");
    add_act("say My husband is the richest man in Kabal.");
    add_act("say Begone, peasant, before I call Brutus on you.");
    add_act("wiggle");

    add_prop(LIVE_I_NEVERKNOWN,1);

    add_equipment(({
        NOBLE + "arm/silk_blouse",
        NOBLE + "arm/high-heels",
        NOBLE + "arm/pearl_necklace",
        NOBLE + "arm/ring",
        NOBLE + "arm/silk_skirt",
        NOBLE + "wep/silver_dagger",
        }));

    // Wield when attacked
    command("unwield all");

    MONEY_MAKE_PC(random(2))->move(TO);
}

void
react_goblin()
{
    command("emote pinches her nose.");
    command("say Ew....what IS that!");
    command("point " + OB_NAME(TP));
}

void
react_hobbit()
{
    command("say Disgusting furry feeted creature!");
    command("gag");
    command("point " + OB_NAME(TP));
}

void
react_elf()
{
    command("say Another elf, just what we need.");
    command("sigh");
}

void
react_dwarf()
{
    command("say Yuck! Get that short fat freak out of here!");
    command("point " + OB_NAME(TP));
}

void
react_gnome()
{
    command("say What is that ugly little thing? A gnome?");
    command("point " + OB_NAME(TP));
}

void
init_living()
{
    mapping react_function = ([
        "goblin" : react_goblin,
        "hobbit" : react_hobbit,
        "elf"    : react_elf,
        "dwarf"  : react_dwarf,
        "gnome"  : react_gnome,
        ]);
    function f;
    
    ::init_living();
    if (f = react_function[TP->query_race_name()])
        set_alarm(2.0, 0.0, f);
}

void
attacked_by(object enemy)
{
    object *bodyguard;

    ::attacked_by(enemy);
    bodyguard = query_team();
    command("wield all");
    if (sizeof(bodyguard))
    {
        if (present(bodyguard[0],ENV(TO)))
        {
            command("eeks");
            command("emote hides behind her bodyguard.");
            enemy->attack_object(bodyguard[0]);
        }
        else
        {
            command("eeks");
            command("emote hides behind her bodyguard.");
            enemy->attack_object(bodyguard[1]);
        }
    }
}

void
help_friend(object ob)
{
    command("shout Get em, boys!");
    attack_object(ob);
}

