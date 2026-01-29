/*
* Varian - February 2015
*/

inherit "/std/monster";

#include "/d/Shire/sys/defs.h"
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Shire/common/make_money.h"
#include "/d/Shire/prestige.h"

int alarm_id;

create_monster()
{
    if (!IS_CLONE)
        return;

    set_name("billingsworth");
    add_name("bill");
    set_race_name("human");
    set_adj(({"squinty-eyed","long-nosed"}));
    set_long("With squinting eyes and a very long, pointed nose, this fisherman looks very " +
        "distinctive. And perhaps a little drunk. Probably very drunk.\n");
    set_stats(({85, 65, 95, 45, 45, 110}), 20);
    MAKE_MONEY;
    set_alignment(100);

    set_skill(SS_WEP_KNIFE,100);
    set_skill(SS_PARRY,70);
    set_skill(SS_DEFENCE,60);

    add_prop(CONT_I_WEIGHT, 60*1000);
    add_prop(CONT_I_HEIGHT, 120);
    set_gender(G_MALE);

    set_chat_time(12);
    
    add_chat("The Sleeping Fisherman is what I am going to be tonight! Ha ha.");
    add_chat("There was one time I caught a fish longer than my entire arm! But he got away!");
    add_chat("Whuzzat? Who is there?");
    add_chat("Who wants to buy me a beer!");
    add_chat("Fishing and drinking is all I know how to do!");
    add_chat("Oh dearie me, is that a drink I see in my future?");
    add_chat("I sell my daily catch to Haestur here, he knows how to prepare it just right!");
    add_chat("My boat has a leak, I will fix it after I am finished this drink. Perhaps after the next one.");
    add_chat("Lets all sing a song!");


    set_act_time(2);

    add_act(({"emote staggers over to the bar to place an order.","emote walks back to his table with a bowl of fish stew."}));
    add_act("emote drinks a house special.");
    add_act("cough");
    add_act("emote drinks a mug of brown beer.");
    add_act("emote drunkenly climbs up on the table to dance and sing very awkwardly for a few moments.");
    add_act("emote drinks a house special.");
    add_act("emote stares forlornly at the beer he just mistakenly spilled on the ground.");
    add_act("emote drinks a mug of brown beer.");
    add_act("emote wanders over to the fire to warm himself up a little.");
    add_act("emote is facedown on his table, snoring loudly.");
    add_act("emote drinks a house special.");
    add_act("emote searches his purse, fumbling for some coppers to buy another drink.");
    add_act("emote drinks a mug of brown beer.");
    add_act("emote munches away on some roasted taters.");
    add_act("emote wobbles around very uncertainly as he wanders outside to relieve himself.");
    add_act("emote drinks a house special.");
    add_act("emote tries to drain every last drop out of his mug of beer.");
    add_act(({"emote says: When a fisherman's wife sees him drunk, he was caught hook, line and drinker!", "emote laughs drunkenly at his own joke."}));
    add_act("laugh");


    set_cact_time(5);

    add_cact("emote stumbles around in a failed attempt to run away.");
    add_cact("emote screams: Help! Help! They are trying to kill me!");

    set_cchat_time(3);
    add_cchat("Leave me alone! Who are you?");
    add_cchat("All I want to do is drink in peace!");
    add_cchat("You have the wrong man! Somebody else did it, leave me alone!");

    /*Triggers*/

    set_alarm(0.5,0.0,"arm_me");

}

arm_me()
{
    object knife,shirt,pants,belt,hat,boots;

    FIXEUID;

    knife = clone_object("/d/Shire/sarnford/wep/bill_knife.c");
    shirt = clone_object("/d/Shire/sarnford/arm/bill_shirt.c");
    pants = clone_object("/d/Shire/sarnford/arm/bill_pants.c");
    belt = clone_object("/d/Shire/sarnford/arm/bill_belt.c");
    hat = clone_object("/d/Shire/sarnford/arm/bill_hat.c");
    boots = clone_object("/d/Shire/sarnford/arm/bill_boots.c");

    boots->move(TO);
    knife->move(TO);
    shirt->move(TO);
    hat->move(TO);
    pants->move(TO);
    belt->move(TO);
    command("wear all");

}

void
attacked_by(object obj)
{
    ::attacked_by(obj);
    command("say Leave me alone, go bother someone else! Go home, you're drunk!");
    command("emote pulls out a long, sharp fishing knife.");
    command("wield all");
    command("wear all");

    alarm_id = set_alarm(10.0,20.0,"before_attack");
}

void
before_attack()
{
    if(TO->query_attack())
    {
        return;
    }
    command("unwield all");
    command("say I hope my beer didn't get knocked over!");
    command("emote drinks a brown beer.");
    remove_alarm(alarm_id);
}


void
add_introduced(string str)
{
    if (!interactive(TP) || TP->query_met(query_name()))
        return;

    command("introduce me to " + TP->query_real_name() + "");
}