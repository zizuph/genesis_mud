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

    set_name("dravan");
    set_race_name("human");
    set_adj(({"stinky","hairy"}));
    set_long("This human is hidden beneath a tangled beard of massive proportions which " +
        "mingles with his greasy long hair. There is a strong odour of fish all around him.\n");
    set_stats(({95, 85, 105, 45, 45, 120}), 20);
    MAKE_MONEY;
    set_alignment(100);

    set_skill(SS_WEP_KNIFE,100);
    set_skill(SS_PARRY,70);
    set_skill(SS_DEFENCE,60);

    add_prop(CONT_I_WEIGHT, 60*1000);
    add_prop(CONT_I_HEIGHT, 120);
    set_gender(G_MALE);

    set_chat_time(20);
    
    add_chat("I really wish Bill would shut-up sometimes.");
    add_chat("I love the food here, but I really wish it was a little quieter.");
    add_chat("It was a great day for fishing and it's a better night for some drinking.");
    add_chat("Are you talking to me? Just leave me alone.");
    add_chat("Haestur, I need another beer!");
    add_chat("Ahh, these taters have been roasted just right!");
    add_chat("I had better not stay up too late tonight, there is another day of fishing tomorrow.");
    add_chat("Ahh, I miss my poor lass Greta. This one is for you love!");
    add_chat("Just ignore Bill, he had a little too much to drink.");


    set_act_time(10);

    add_act(({"emote cries out: Would you shut-up Bill?","poke billington"}));
    add_act("emote orders some food from the bar.");
    add_act("cough");
    add_act("emote drinks a mug of brown beer.");
    add_act("sigh");
    add_act("emote scratches his belly.");
    add_act("emote picks some fish out of his beard.");
    add_act("emote burps and rubs his stomach.");
    add_act("emote wanders over to the fire to warm himself up a little.");
    add_act("emote sits back in his chair and takes a sip of beer.");
    add_act("stretch");
    add_act("frown");
    add_act("emote drinks a mug of brown beer.");
    add_act("emote eagerly digs into a plate of roasted potatoes.");
    add_act("grimace");
    add_act("brood");
    add_act("curse");
    add_act("sneeze");
    add_act("swear");


    set_cact_time(5);

    add_cact("emote narrows his eyes dangerously.");
    add_cact("emote trips you, putting you off balance for a moment.");

    set_cchat_time(3);
    add_cchat("I think you might have bitten off more than you can chew.");
    add_cchat("Get lost!");
    add_cchat("You are going to have to try harder than that!");

    /*Triggers*/

    set_alarm(0.5,0.0,"arm_me");

}

arm_me()
{
    object knife,shirt,pants,belt,hat,boots;

    FIXEUID;

    knife = clone_object("/d/Shire/sarnford/wep/dravan_knife.c");
    shirt = clone_object("/d/Shire/sarnford/arm/dravan_shirt.c");
    pants = clone_object("/d/Shire/sarnford/arm/dravan_pants.c");
    belt = clone_object("/d/Shire/sarnford/arm/dravan_belt.c");
    hat = clone_object("/d/Shire/sarnford/arm/dravan_hat.c");
    boots = clone_object("/d/Shire/sarnford/arm/dravan_boots.c");

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
    command("say Who, me? Really?");
    command("emote pulls out a short, jagged fishing knife.");
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
    command("say Well, I am glad that is done with.");
    command("sigh");
    remove_alarm(alarm_id);
}


void
add_introduced(string str)
{
    if (!interactive(TP) || TP->query_met(query_name()))
        return;

    command("introduce me to " + TP->query_real_name() + "");
}