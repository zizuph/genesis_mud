/*
 * /d/Faerun/highroad/farms/npcs/egg_npc.c
 *
 * Egg collecting NPC/Farm Wife
 * by Finwe, August, 2006
 */

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>

inherit FAERUN_NPC_BASE;
inherit "/d/Faerun/lib/assist_friend";
inherit "/d/Faerun/lib/gems";

#define QUEST_NAME_PROP "_egg_quest"

void arm_me();

void create_monster()
{
    int i;

    seteuid(getuid());
    remove_prop(LIVE_M_NO_ACCEPT_GIVE);

    npc_name = "_farm_human";

    add_adj("jovial");
    add_adj("hard-working");
    set_short("jovial hard-working human");
    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_race_name("human");
    add_name(npc_name);
    set_long("This is a " + query_short() + ". She has long, sun-bleached hair " +
        "and brown skin. She looks like the mother of the house and a " +
        "fine woman. Her face is creased with wisdom, but a hint of humor " +
        "marks her lips. Nonetheless, living out on the farm has toughened " +
        "her, and she looks able to defend herself.\n");

    set_gender(G_FEMALE);
    add_prop(CONT_I_WEIGHT,65000);
    add_prop(CONT_I_HEIGHT,175);
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
    set_act_time(5);
    set_cact_time(5);
    add_act("emote scurries around the kitchen.");
    add_act("emote cleans a pot.");
    add_act("emote wipes down the counter.");
    add_act("emote chases a child out of the kitchen.");
    add_act("emote brushes out her apron.");
    add_chat("This family is a hungry bunch.");
    add_chat("I am always running low on eggs.");
    add_chat("Don't you just love the smell of fresh bread baking?");
    add_chat("Beware the Mere of Dead Men. It's a spooky place.");
    add_chat("All these kids eat so much, you would think they each have a hollow leg!");
    add_chat("Please don't make a mess, I'll have to clean it up later.");

    set_cchat_time(5);
    add_cchat("Die, you scabrous mongrel!");
    add_cchat("What are you fighting me for?");
    add_cchat("You will die for this crime!");
    add_cchat("Just wait until my husband hears about this, he will kill you!");
    add_cchat("Take that, and that, and that!");
    add_cchat("I can't believe you are doing this!");

    add_prop(LIVE_I_NEVERKNOWN, 1);

    arm_me();

    set_pick_up_team(({npc_name}));
    add_ask(({"eggs", "quest", "help", "task", "egg"}),
        VBFC_ME("ask_eggs"));
}



void
arm_me()
{
    object arm, wep, gem;

    make_gems(TO, 1);

    wep = clone_object(FWEP_DIR + "butcher");
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


/* This routine gives out the quest to the player when they ask for it */
string ask_eggs()
{
    object bucket;
//these are defined in /d/Faerun/sys/qbits.h
// DOMAIN = Faerun
// EGG_QUEST_GROUP = which bit group to use, in this case, GROUP1
// EGG_QUEST_BIT = The bit number to use, inm this case, number 1

/* This checks to see if the player has done the quest already. if they have,
 * they cant do it again
 */
    if(TP->test_bit(DOMAIN, EGG_QUEST_GROUP, EGG_QUEST_BIT))
    {
        command("emote wipes the sweat from her forehead.");
	    command("say Thanks for asking, but you helped me already.");
	    return "";
    }

// QUEST_NAME_PROP is defined at the top here

/* This checks to see if the player has been given the quest already */
    if (TP->query_prop(QUEST_NAME_PROP))
    {
	    command("say Have you found all the eggs I need yet?");
	    command("say If you haven't, please try some more. I need fresh eggs.");
	    return "";
    }

/* Here is where the player is given the quest and instructions */
    command("say I have run out of eggs, and I use them all the time " +
        "for baking. Sadly, I don't have time to go gather more.");
    command("say I know those chickens are laying eggs and they are " +
        "scattered all over the farm and in the chicken coop. Would you " +
        "please go gather me a dozen of them?");
    command("say Here's a basket. Please gather me twelve eggs. When you " +
        "have them, bring them back to me. Thanks a lot!");
    command("emote places a basket on the floor.");

/*for this quest, a bucket is cloned for the player */
    bucket = clone_object(FOBJ_DIR+ "egg_basket");
    bucket->move(ENV(TO));

/* This adds the prop to the player saying they asked for the quest */
    TP->add_prop(QUEST_NAME_PROP,1);
    return "";

}


void
test_quest(object player, object obj)
{

    if(player->test_bit(DOMAIN, EGG_QUEST_GROUP, EGG_QUEST_BIT))
    {
	    command("say Thanks for the offer, but you helped me already.");
	    return;
    }


// has prop?
    if (player->query_prop(QUEST_NAME_PROP))
    {
// bucket full?
        if(!obj->query_bucket_full())
        {
            command("say You haven't gathered a dozen eggs. I need twelve " +
                "of them. Try again. The hens may be hiding them somewhere.");
            command("say When you have found them all, please come back!");
            command("emote places the basket on the floor.");
            obj->move(environment(this_object()));
            return;
        }
    }

/* The quest is successfully done. 
 * Let's give them exp.
 */
    command("grin broadly");
    command("say Ahh, I hope those chickens didn't give you too much " +
        "trouble. They can be so bothersome sometimes!");
    command("say Thank you for the eggs. I am very grateful for your help.");
/* We remove the quest prop. */
    player->remove_prop(QUEST_NAME_PROP);
/* We tell them they got exp */
    tell_object(player,"You feel more experienced!\n");
    say(QCTNAME(player) + " was rewarded.\n");

/* We set the bits in the player */
    player->set_bit(EGG_QUEST_GROUP, EGG_QUEST_BIT);

// EGG_QUEST_BIT = the amt of exp this quest is worth. 
// This is also defined in qbits.h
/* We give them exp */
    player->add_exp_quest(EGG_QUEST_EXP);

// EGG_QUEST_LNG = the long descr of the quest
// This is also defined in qbits.h
/* Let's log the quest and exp */
    QUEST_LOG_FILE(EGG_QUEST_LNG, EGG_QUEST_EXP);
    obj->remove_object();

}


/* This routine is here in case playrs give stuff to the npc that the
 * NPC doesnt need. Naturally, the NPC keeps any money given to them. :)
 */
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

/* Rejects any container other than the egg basket */ 
public void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);
    if (!living(from))
	    return;

    if (obj->id("_faerun_egg_basket"))
	    set_alarm(1.0,0.0, &test_quest(from, obj));
    else
    {
	    set_alarm(1.0,0.0, &return_object(from, obj));
	    return;
    }
}

void
clearbit()
{
    TP->clear_bit(EGG_QUEST_GROUP, EGG_QUEST_BIT);
}