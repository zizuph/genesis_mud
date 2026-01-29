/*
    snooty_noble.c
    
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
    set_name("noble");
    set_adj("rich");
    add_adj("snooty");
    set_race_name("human");
    set_short("snooty rich noble");
    set_long("This tall and lanky guy has a large, beak nose. He "+
        "walks around with an air of confidence. His hair greys at the "+
        "temples, but his eyes still look sharp.\n");

    set_alignment(200);
    set_knight_prestige(-60);
    add_speak("There are times when I think the poor people are fools.\n");

    set_stats(({70,70,70,70,70,100}));
    set_skill(SS_WEP_KNIFE,60);
    set_skill(SS_DEFENSE,60);

    set_random_move(1);

    set_act_time(3);
    add_act("emote twists his ring.");
    add_act("emote looks down upon you.\n");
    add_act("say What do you want, peon?");
    add_act("emote feels secure in his wealth.");

    add_prop(LIVE_I_NEVERKNOWN,1);

    add_equipment(({
        NOBLE + "arm/silk_tunic",
        NOBLE + "arm/leather_shoes",
        NOBLE + "arm/silver_pendant",
        NOBLE + "arm/ring",
        NOBLE + "arm/e_leather_pants",
        NOBLE + "wep/silver_dagger",
        }));

    // Wield when attacked
    command("unwield all");

    MONEY_MAKE_GC(random(5))->move(TO);
}

void
react_goblin()
{
    command("emote pinches his nose.");
    command("say Ew....what IS that!");
    command("point " + OB_NAME(TP));
}

void
react_hobbit()
{
    command("say Oooh, look at that little hobbit!");
    command("chuckle");
    command("point " + OB_NAME(TP));
}

void
react_elf()
{
    command("say Wow! Haven't seen one of those in a while..."+
    "look at its pointy ears!");
    command("laugh " + OB_NAME(TP));
}

void
react_dwarf()
{
    string man = (TP->query_gender() == 1 ? "woman" : "man");
    command("say Oh my! A short, fat little "+man+" like we "+
        "used to see in the circus freak show!");
    command("point " + OB_NAME(TP));
    command("laugh");
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
    bodyguard = query_team();

    ::attacked_by(enemy);
    command("wield all");
    if (sizeof(bodyguard))
    {
        if (present(bodyguard[0], ENV(TO)))
        {
            command("eeks");
            command("emote hides behind his bodyguard.");
            enemy->attack_object(bodyguard[0]);
        }
    }
}

void
help_friend(object ob)
{
    command("shout Get him, Garpo!");
    attack_object(ob);
}

