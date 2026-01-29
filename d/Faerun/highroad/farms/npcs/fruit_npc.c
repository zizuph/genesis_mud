/*
 * Egg collecting NPC/Farm Wife
 * by Finwe, August, 2006
 */

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <filter_funs.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>

inherit FAERUN_NPC_BASE;
inherit "/d/Faerun/lib/assist_friend";
inherit "/d/Faerun/lib/gems";

#define FRUIT_KINDS ({ "fig", "mango", "pear", "peach"})
#define FRUIT_IDENT   927548136 /* the large number. */
#define FRUIT_RANGE   4         /* the number of fruit. */
#define QUEST_NAME_PROP "_fruit_quest"
#define PICKED_FRUIT    "_i_picked_fruit"

string fruit_to_find = ONE_OF_LIST(FRUIT_KINDS);

// int quest_in_progress = 0;

void arm_me();

void create_monster()
{
    int i;

    seteuid(getuid());
    remove_prop(LIVE_M_NO_ACCEPT_GIVE);

    npc_name = "_farm_human";

    add_adj("young");
    add_adj("carefree");
    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_race_name("human");
    set_name("girl");
    add_name(npc_name);

    set_short("young carefree girl");
    set_long("This is a " + query_short() + ". She is freckle-faced with " +
        "long, braided hair and a sunny smile. Her skin is tanned and is " +
        "lanky looking.\n");

    set_gender(G_FEMALE);
    add_prop(CONT_I_WEIGHT,37000);
    add_prop(CONT_I_HEIGHT,160);
    add_prop(LIVE_I_SEE_DARK,10);
            /* STR DEX CON INT WIS DIS */
    for (i = 0; i < 5; i++)
        set_base_stat(i, 80 + random(25));
    set_base_stat(5, 80);

    set_alignment(110 + random(50));

    set_skill(SS_UNARM_COMBAT,20);
    set_skill(SS_DEFENCE,70);
    set_skill(SS_WEP_AXE,50);
    set_skill(SS_WEP_CLUB,50);
    set_skill(SS_WEP_KNIFE,50);
    set_skill(SS_PARRY, 70);
    set_skill(SS_AWARENESS, 50);
    set_skill(SS_2H_COMBAT, 50);

   /* Actions */
    set_act_time(15);
    set_cact_time(15);
    add_act("emote skips around gaily.");
    add_act("emote sticks her tongue out at you.");
    add_act("emote stifles a giggle.");
    add_act("emote smiles happily at you.");
    add_act("emote picks a twig out of her hair.");
    add_act("emote jumps up and down on the bed.");
    add_act("emote jumps off the bed.");
    add_act("emote makes the bed.");
    add_chat("Boy, oh boy. I'm hiding from dad and mom so they don't make " +
        "me do any more chores.");
    add_chat("I love fresh fruit.");
    add_chat("Living on a farm is a lot of hard work.");
    add_chat("Don't you think I'm pretty?");
    add_chat("I love riding horses. It's so much fun.");

    set_cchat_time(5);
    add_cchat("Die, you scabrous mongrel!");
    add_cchat("What are you fighting me for?");
    add_cchat("You will die for this crime!");
    add_cchat("Just wait until my parents hear about this, they will kill you!");
    add_cchat("Take that, and that, and that!");
    add_cchat("I can't believe you are doing this!");

    add_prop(LIVE_I_NEVERKNOWN, 1);

    arm_me();

    set_pick_up_team(({npc_name}));
    add_ask(({"quest", "help", "task", "fruit"}),
        VBFC_ME("ask_fruit"));
}



void
arm_me()
{
    object arm, wep, gem;

    make_gems(TO, 1);

    wep = clone_object(FWEP_DIR + "dagger");
    wep -> move(TO);
    arm = clone_object(FARM_DIR + "dress");
    arm -> move(TO);

    command("wield weapon");
    command("wear all");
}

void
init_living()
{
    ::init_living();
    init_team_pickup();
}

string ask_fruit()
{
    if(TP->test_bit(DOMAIN, FRUIT_QUEST_GROUP, FRUIT_QUEST_BIT))
    {
        command("emote giggles happily.");
        command("say Thank you, but you helped me already.");
        return "";
    }

//    if(quest_in_progress == 1)
//    {
//        write("Thank you for asking, but someone is already helping me.\n");
//        return "";
//    }

    if (TP->query_prop(QUEST_NAME_PROP))
    {
        command("say Have you found that fruit I have been looking for, " +
            "or have you forgotten? I'm looking for a " + fruit_to_find + ".");
        command("say If you haven't, I just know it's from somewhere around here.");
        return "";
    }
// someone is doing the quest already.
//    quest_in_progress = 1;
    command("say I was at a party of one of my neighbors. It was the most " +
        "exciting party. The food was delicious but the best part " +
        "was the fruit.");
    command("say The fruit was marvelous! I've never had anything like " +
        "it before. I would love it if you could find me the fruit. They " +
        "said the fruit was a " + fruit_to_find + " or something like that.");
    command("say Thank you very much!!!");

    TP->add_prop(QUEST_NAME_PROP,1);
    return "";

}


void
test_quest(object player, object obj)
{

    if(TP->test_bit(DOMAIN, FRUIT_QUEST_GROUP, FRUIT_QUEST_BIT))
    {
        command("say Thank you for the offer, but you helped me already.");
        return;
    }
    
    if(!player->query_prop(PICKED_FRUIT))
    {
        command("say Eww, yuck! This fruit looks bruised and gross. I " +
            "don't want this! Go get your own fruit and be more careful " +
            "next time!");
        command("shudder");
        command("drop " + OB_NAME(obj));
        return;
    }



//    quest_in_progress = 0;
    command("grin broadly");
    command("say Oooo, you found the fruit!!!");
    command("say Thank you so much!!!");
    player->remove_prop(QUEST_NAME_PROP);
    player->remove_prop(PICKED_FRUIT);
    tell_object(player,"You feel more experienced!\n");
    say(QCTNAME(player) + " was rewarded.\n");
    TP->set_bit(FRUIT_QUEST_GROUP, FRUIT_QUEST_BIT);
    TP->add_exp_quest(FRUIT_QUEST_EXP);
    QUEST_LOG_FILE(FRUIT_QUEST_LNG, FRUIT_QUEST_EXP);
    command("eat fruits");


// time for a new fruit.
    fruit_to_find = ONE_OF_LIST(FRUIT_KINDS);

}

void
return_object(object from, object obj)
{
    string  obname = OB_NAME(from);

    if (obj->id("coin"))
    {
        command("say Thanks for the money!");
        return;
    }

    command("say Thank you for this, but I do not need it.");
    write("The " + short() + " gives it back to you.\n");
    obj->move(from);
    return;
}


public void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);
    if (!living(from))
        return;

    if (obj->id("_" + fruit_to_find + "_faerun_fruit_"))
    {
/*        if(!from->query_prop(PICKED_FRUIT))
        {
            command("say Eww, yuck! This fruit looks bruised and gross. I " +
                "don't want this! Go get your own fruit and be more careful " +
                "next time!");
            command("shudder");
            command("drop " + OB_NAME(obj));
            return;
        }*/

        set_alarmv(1.0,0.0,"test_quest",({from, obj}));
    }
    else
    {
        set_alarmv(1.0,0.0,"return_object",({from, obj}));
        return;
    }
}

void
clearbit()
{
    TP->clear_bit(FRUIT_QUEST_GROUP, FRUIT_QUEST_BIT);            
}