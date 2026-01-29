/*
    drash.c
    
    Code by Sarr,
    Recoded by Fysix, Feb 1998
 */
 
inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";

#include "default.h"
#include <money.h>

void
create_kalad_monster()
{
    set_name("drash");
    set_adj("dark");
    add_adj("hooded");
    set_race_name("human");
    add_name("figure");
    set_short("dark hooded figure");
    set_long("You see a dark figure cloak all in black. He "+
        "is slightly hunched over, and peers at you from behind his "+
        "hood. You can barley make out human features from behind "+
        "his hood. His gloved hands clench and unclench as you "+
        "ponders the situation.\n"+
        "He has a black rose pined to his belt.\n");
    set_alignment(-200);
    set_knight_prestige(10);

    add_speak("Hmmm.....so what brings you down here, ehhhh?\n");
    set_stats(({100,120,130,60,80,100}));

    set_skill(SS_WEP_SWORD,100);
    set_skill(SS_DEFENSE,100);
    set_skill(SS_AWARENESS,90);
    set_skill(SS_PARRY,100);

    set_act_time(5);
    add_act("ponder");
    add_act("scratch nose");
    add_act("emote wonders what to do about the medallion.");
    set_default_answer("What is it that you want?\n");
    add_ask(({"medallion","item"}),short()+" says: Yes...indeed "+
        "I have the medallion....but if you want it, you must answer "+
        "this question. Who was the founder of this house that we "+
        "stand under? The name is inscribed on an item in this house. "+
        "just 'mutter' the name to me.\n");
    set_title("the Knight of the Shadows");

    add_prop(LIVE_I_NEVERKNOWN,1);

    add_equipment(({
        NOBLE + "arm/dvest",
        NOBLE + "arm/dgreaves",
        NOBLE + "arm/dgloves",
        NOBLE + "arm/dcloak",
        NOBLE + "wep/katana",
        }));
    MONEY_MAKE_GC(random(2))->move(TO);
}

int
do_mutter(string str)
{
    string answer;
    object drash;

    if (!parse_command("mutter "+str,ENV(TP),
        "'mutter' %s 'to' %o",answer, drash))
    {
        write("Mutter what to whom?\n");
        return 1;
    }

    if(drash != TO)
    {
        write("Mutter what to whom?\n");
        return 1;
    }

    if(answer != "Wistfellow the IV")
    {
        write("Sorry, "+answer+" is not the right answer.\n");
        return 1;
    }

    command("say That is the correct answer!");
    seteuid(getuid());
    command("emote gives you the medallion.");

    if (clone_object(NOBLE + "obj/medallion")->move(TP))
    {
        write("The medallion is too heavy and you drop it.\n");
        say("The medallion is too heavy and " + QTNAME(TP) + " drops it.\n");
    }

    set_alarm(3.0, 0.0, "dissapear");
    return 1;
}

void
init_living()
{
    ::init_living();
    add_action(do_mutter, "mutter");
}

void
dissapear()
{
    command("emote suddenly vanishes!");
    remove_object();
}
