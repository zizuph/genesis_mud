/*
    fat_noble.c
    
    Code by Sarr,
    Recoded by Fysix, Feb 1998
 */

inherit "/d/Kalad/std/monster";

#include "default.h"
#include <money.h>

void
create_kalad_monster()
{
    set_name("noble");
    set_adj("rich");
    add_adj("fat");
    set_race_name("human");
    set_short("rich fat noble");
    set_long("This guy is so obese, you can hardly believe he can "+
        "walk. He moves around with his bodyguard, twisting his ring "+
        "on his finger, or playing with his coins in his pocket.\n");
    set_alignment(200);
    set_knight_prestige(-60);
    add_speak("I don't get much food these days, I need to work harder "+
    "they say...\n");
    set_stats(({70,50,40,60,60,100}));
    set_skill(SS_WEP_KNIFE,60);
    set_skill(SS_DEFENSE,60);
    set_random_move(1);

    set_act_time(3);
    add_act("emote twists his ring.");
    add_act("say All these demi-humans coming in the port worries me.");
    add_act("emote feels secure in his wealth.");
    add_act("emote farts.");
    add_act("say Daddy is going to by me one of those prized race horses "+
    "soon.\n");

    add_prop(LIVE_I_NEVERKNOWN,1);

    add_equipment(({
        NOBLE + "arm/silk_tunic",
        NOBLE + "arm/leather_shoes",
        NOBLE + "arm/gold_chain",
        NOBLE + "arm/ring",
        NOBLE + "arm/e_leather_pants",
        }));

    MONEY_MAKE_GC(random(5))->move(TO);

    // wield when attacked
    clone_object(NOBLE + "wep/silver_dagger")->move(TO, 1);
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
    command("say Oooh, look at that little thing!");
    command("giggle");
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
    command("say Oh my! A short, fat little " + man + " like we "+
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

    ::attacked_by(enemy);
    command("wield all");

    bodyguard = query_team();
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
    command("shout Get him Brutus!");
    attack_object(ob);
}

