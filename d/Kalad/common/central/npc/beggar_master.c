/* the master beggar in the Beggars club */
/* Made by Korat */
/* 2017-06-04 Malus: Fixed question handling */ 

/* This npc gives out a small quest needed to become member of the club here. */
/* She also sells a robe to fellow members of the club. The code for the */
/* club can be found in the room the npc stands in. */

inherit "/d/Kalad/std/monster";
inherit "/lib/trade";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/ss_types.h"
#include "/sys/money.h"
#define NUM sizeof(MONEY_TYPES)
#define QUEST_NAME "beggarsclubquest"

create_monster()
{
    ::create_monster();
    set_name("snike");
    add_name("master-beggar");
    add_name("beggar");
    set_race_name("human");
    set_gender(G_FEMALE);
    set_adj("wretched");
    set_long("This wretched human peers at you with a hunger-stricken "+
      "expression, but also with a look of interest. "+
      "It seems like she has some filthy robes behind "+
      "her back that she wants to sell. Maybe she will sell one to you?\n");
    set_stats(({30,40,25,30,40,25}));
    set_alignment(100);
    set_act_time(2);
    add_act("peer all");
    add_act("emote looks at the wooden board on the wall with an "+
      "expression of sincere pride.");
    add_act("say Maybe you want to buy one of my robes?");
    add_act("emote smiles greedily at you.");
    add_act("say Maybe I will let you join my club?");
    add_act(({"say I can train you to be a better beggar! I can show you "+
            "how to see if someone has any coins at all. I can also teach "+
            "you how to make sure you are not "+
            "begging from the wrong person ...","wink"}));
    add_act("robepolish");
    add_act("robewipe");
    add_act("robeshiver");
    add_act("bbeg");
    add_act("bempty");
    add_act("bnap");
    add_act("bsearch");
    set_knight_prestige(-8);
    set_title("Master Almsman of the Beggars Club");
    add_speak("Hmm, maybe I will let you join my club ...\n");
    set_default_answer("say What? Are you interested in my club?", 1);
    add_ask(({"leave","end"}),"says " +
      "Well, if you want to leave my club, if you are a member that is, " +
      "because you can't leave my club if you aren't a..." +
      "yes, of course, if you want to leave, then just... " +
      "Hmmm, what was it again...hmmm...ahhh, yes! Just 'end' ... or was it " +
      "'end club'...no, 'end membership'...oh well, something " +
      "like that.", 1);
    add_ask(({"join","become","club"}),"say " +
      "All you need to do is to is " +
      "'become member' and, pronto, you will join! " +
      "Well...not that easily. First you must answer a " +
      "simple question and afterwards, if I feel like it, " +
      "I will let you join. Thats fair, I think.", 1);
    add_ask("question","say " +
      "The question is simple ... " +
      "What feeling does a beggar need to create in their " +
      "target to make them give away their coins? " +
      "If you think you know the answer, just say it to me.", 1);
    add_ask("pity","say Is that a question? If you know it, say it to me with confidence!", 1);
    add_ask(({"help","job","task"}), "say You could join my club!", 1);
    add_prop(OBJ_M_NO_ATTACK,"You decide not to attack her.\n");
    config_default_trade();
}

void
arm_me()
{
    object wep;
    object arm;
    seteuid(getuid(this_object()));
    arm = clone_object("/d/Kalad/common/central/arm/bgrobe");
    arm -> move(this_object());
    wep = clone_object("/d/Kalad/common/central/obj/club_bowl");
    wep -> move(this_object());
    command("wear all");
}

void
speech_hook(string verb, object actor, string adverb,
    object *oblist, string text, int target)
{
    if (verb != "say")
        return;

    if (target != 1)
        return;

    text = lower_case(text);
    if (text != "pity" && text != "pity.")
    {
        command("say Well, that was not what I had in mind.");
        return;
    }
    if (actor->test_bit("Kalad", 1, 1))
    {
        command("emote peers at you and says: You have answered this "+
            "before, haven't you?");
        return;
    }

    write("Snike congratulates you!\n");
    write("You feel a little more experienced.\n");
    actor->add_exp(100);
    actor->set_bit(1,1);
    seteuid(getuid(TO));
    log_file(QUEST_NAME, extract(ctime(time()),4,15) + " "+
    capitalize(actor->query_real_name()) + " rewarded with 100 xp,"+
        "<"+actor->query_average_stat()+"> average stats.\n");
    command("say You might be welcome to my club now.");
}

void
init_living()
{
    add_action("buy_robe","buy");
}

int
buy_robe(string str)
{
    object buy_ob;
    string what, for_c, get_c, change;

    int *result, m_res, price;
    if (!str)
    {
        notify_fail("Buy what?\n");
        return 0;
    }
    if (sscanf(str, "%s with %s and get %s", what, for_c, get_c) != 3)
        if (sscanf(str, "%s with %s", what, for_c) != 2)
            what = str;
    if (what != "robe")
    {
        notify_fail("All I have is robes. Buy that or nothing!\n");
        return 0;
    }

    /* member of the club? */
    NF("I will only sell the robes to members of my club!\n");
    if (!present("beggarmember",TP))
        return 0;


    buy_ob=clone_object("/d/Kalad/common/central/arm/bgrobe");
    if (!buy_ob)
    {
      notify_fail("There is none left. Sorry for that...\n");
      return 0;
    }

    price = buy_ob->query_prop(OBJ_I_VALUE);
    result=pay(price,this_player(),for_c,0,0,get_c);
    if (sizeof(result)==1)
    {
        buy_ob->remove_object();
        return 0;
    }
    if (buy_ob->move(this_player())) 
    {
        write("You drop the " + buy_ob->short() + " on the ground.\n");
        say(QCTNAME(this_player()) + " drops one " + buy_ob->short() +
            " on the ground.\n");
        buy_ob->move(environment(this_player()));
    }
    else
    {
        write("You get your " + buy_ob->short() + ".\n");
        say(QCTNAME(this_player()) + " buys a " + buy_ob->short() + ".\n");
    }
    write("You pay " + text(result[0 .. NUM - 1]) + ".\n");
    if (change)
        write("You get " + change + " as change.\n");
    return 1;
}

