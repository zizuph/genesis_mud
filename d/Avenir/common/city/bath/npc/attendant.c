#pragma strict_types
/*
 * ~/attendant.c
 *
 * NPC for the bath.
 * Based upon cleaning woman /d/Avenir/common/mon/cleaner.c    
 *
 * Revisions:
 *   Lilith, Feb 2002: Created.
 *   Lucius, Jul 2017: Code Cleanups.
 *
 */
inherit "/d/Avenir/inherit/monster";

#include <stdproperties.h>               /* properties */
#include <macros.h>                      /* macros like VBFC and QNAME */
#include <wa_types.h>                    /* weapon and armour defs */
#include <ss_types.h>                    /* skill and stat defs */

#include "../bath.h"

#define FOOD	(CITY + "obj/food/")
#define TPQRN	this_player()->query_real_name()

public string *randadj = ({
    "little", "dark-eyed", "tall", "graceful", "slender",
    "delicate", "sweet-smelling", "willowy", "concerned",
    "accomodating", "smiling", "wide-eyed", "innocent",
    "pleasant", "exquisite", "gentle", "lovely",
});

public string
my_long(void)
{
    return "A "+ query_adj() +" bathhouse attendant.\n"+
           "She is demure and obedient, a typical "+
           "sybarite servant shrouded in a quiet dignity.\n"+
           "She appears to be carrying towels, soaps, and "+
           "a tray of food and drink.\n";
}

public void
create_monster(void)
{
    setuid(); 
    seteuid(getuid());

    set_long(my_long);
    set_short("female bathhouse attendant");
    add_name(({"woman", "attendant"}));
    set_adj(({"bathhouse", "female", one_of_list(randadj)}));

    set_race_name("human");
    set_gender(G_FEMALE);
    set_stats(({60,60,60,40,40,50}));
 
    set_alignment(0);
    set_pick_up(1);
    set_all_hitloc_unarmed(5);
    set_all_attack_unarmed(20, 11);

    set_skill(SS_DEFENCE, 30);
    set_skill(SS_WEP_CLUB, 50);
    set_skill(SS_AWARENESS, 20);
    set_skill(SS_UNARM_COMBAT, 20);

    add_prop(CONT_I_HEIGHT, 180); 
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_act_time(30);
    add_act("emote balances a silver tray on her hand.");
    add_act("emote folds a fluffy white towel over her arm.");
    add_act("emote smells a scented soap.");
    add_act("emote watches you with calm disinterest.");
    add_act("say Would you care for something to drink? A towel? "+
        "Or perhaps some soap?");
    add_act("say I've a tray filled with food and drink, so "+
        "if you want anything, just ask.");

    set_restrain_path(({ BATH }));
    set_monster_home(BATHRM +"arc_n");
    set_random_move(10, 0);

    set_default_answer(VBFC_ME("what_me"));
    add_ask(({"help","task","job","errand","quest","assignment"}), 
        VBFC_ME("give_job"), 1);
    add_ask(({"tray", "silver tray"}), 
        VBFC_ME("give_tray"), 1);
    add_ask(({"food","anything"}),
        "say I have canapes, cucumber sandwiches, and shaved ices", 1);
    add_ask(({"drink", "kahve", "iced kahve"}), 
        VBFC_ME("give_drink"), 1);
    add_ask(({"canape", "salmon", "smoked salmon", "mascarpone"}), 
        VBFC_ME("give_canape"), 1);
    add_ask(({"sandwich", "cucumber", "cucumber sandwich"}), 
        VBFC_ME("give_sandwich"), 1);
    add_ask(({"ice", "shaved ice", "cup", "cup of shaved ice"}), 
        VBFC_ME("give_ice"), 1);
    add_ask(({"towel", "towels", "fluffy towel", "fluffy white towel"}), 
        VBFC_ME("give_towel"), 1);
    add_ask(({"soap", "soaps", "scented soap"}), 
        VBFC_ME("give_soap"), 1);
}

public void
equip_me()
{
    clone_object(BATHOB +"soap")->move(this_object(), 1);
    clone_object(BATHOB +"towel")->move(this_object(), 1);    
}

public string
what_me(void)
{
    switch(random(5))
    {
        case 0:
            command("say I am not permitted to answer that question.");
            break;
        case 1:
            command("say I provide food and drink to our patrons.");
            break;
        case 2:
            command("emote struggles to answer, but does not seem able "+
                "to get the words out.");
            break;
        case 3:
            command("say Would that I could, but I cannot say.");
            break;
        case 4:
            command("say I am not worthy of your attention.");
            break;
    }
    return "";    
}

public string
give_job(void)
{
    command("smile " + TPQRN);
    command("say Thank you, but I do not need help.");
    return "";
}

public string
give_tray(void)
{
    object ob;

    if (ob = present("tray", this_player()))
    {
        command("say But you already have a tray.");
        return "";
    }

    ob = clone_object(BATHOB +"tray");
    ob->fill_tray();
    ob->move(this_object(), 1);

    command("say Of course.");
    command("give tray to "+ TPQRN);
    command("say Enjoy!");
    return "";
}

public string
give_drink(void)
{
    object ob;

    if (ob = present("ave:iced:kahve", this_player()))
    {
        command("say I see you have a kahve already.");
        return "";
    }

    ob = clone_object(FOOD +"iced_coffee");
    ob->move(this_object(), 1);

    command("say Of course I have kahve!");
    command("give coffee to "+ TPQRN);
    command("say Enjoy! It's wonderful.");
    return "";
}

public string
give_canape(void)
{
    object ob;

    if (ob = present("canape", this_player()))
    {
        command("say I see you have some of our wonderful "+
            "canapes already.");
        return "";
    }
 
    ob = clone_object(FOOD +"salmon");
    ob->move(this_object(), 1);

    command("say I do have that.");
    command("give canape to "+ TPQRN);
    command("say I hope you enjoy it.");
    return "";
}

public string
give_sandwich(void)
{
    object ob;

    if (ob = present("sandwich", this_player()))
    {
        command("say I see you have some of our tasty "+
            "cucumber sandwiches already. Is it not "+
            "good?");
        return "";
    }
 
    ob = clone_object(FOOD +"cucumber");
    ob->move(this_object(), 1);

    command("say I do have cucumber sandwiches.");
    command("give sandwich to "+ TPQRN);
    command("say I hope you enjoy it.");
    return "";
}

public string
give_ice(void)
{
    object ob;

    if (ob = present("snack", this_player()))
    {
        command("say I see you have some of our wonderful "+
            "shaved ices already.");
        return "";
    }
 
    ob = clone_object(FOOD +"shaved_ice");
    ob->move(this_object(), 1);

    command("say Yes, I do.");
    command("give ice to "+ TPQRN);
    command("say I hope you enjoy it.");
    return "";
}

public string
give_towel(void)
{
    object ob;

    if (ob = present("towel", this_player()))
    {
        command("say I see you already have a towel.");
        return "";
    }
 
    ob = clone_object(BATHOB +"towel");
    ob->move(this_object(), 1);

    command("say I do happen to have that.");
    command("give towel to "+ TPQRN);
    command("curtsey");
    return "";
}

public string
give_soap(void)
{
    object ob;

    if (ob = present("soap", this_player()))
    {
        command("say I see you have some of our scented "+
            "soaps already.");
        return "";
    }
 
    ob = clone_object(BATHOB +"soap");
    ob->move(this_object(), 1);

    command("say I do have one.");
    command("give soap to "+ TPQRN);
    command("curtsey");
    return "";
}
