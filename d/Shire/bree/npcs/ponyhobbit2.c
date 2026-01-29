/*
* Palmer added intro when introed to. Jan 2003
*/

inherit "/std/monster";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Shire/common/make_money.h"

int alarm_id;

create_monster()
{
    if (!IS_CLONE)
        return;

    set_name("goatleaf");
    set_race_name("hobbit");
    set_adj("cheery");
    add_adj("short");
    set_long("This is one of the merry hobbits living in Bree. He looks " +
        "like he seems to be doing more listening than talking, but " +
		"barely. He looks liek a chatty hobbit, who will talk your " +
		"ear off if given half a chance.\n");
    set_stats(({30,50,40,80,100,30}));
    MAKE_MONEY;
    set_alignment(100);

    set_skill(SS_WEP_KNIFE,50);
    set_skill(SS_DEFENCE,60);

    add_prop(CONT_I_WEIGHT, 60*1000);
    add_prop(CONT_I_HEIGHT, 120);
    set_gender(G_MALE);

    set_chat_time(1);
    add_chat("I am doing fine, thanks.");
    add_act(({"emote takes out his tobacco.","emote stuffs his pipe with some tobacco.",
              "emote lights his pipe.","emote gets a big smile all over his face as he inhales some smoke from his fine pipe."}));
   add_chat("The fire could use some stoking, I think.");
   add_chat("They don't make tobacco like Old Toby anymore.");
    add_chat("And just where are you from, stranger?");
   add_chat("I hear there are hordes of orcs closing on Bree.");
   add_chat("Might you know anything interesting?");
   add_chat("There's no accounting for East and West, I always say.");

    set_act_time(2);
    add_act("yawn");
    add_act("smile merri");
   add_act("emote drinks a mug of cold beer.");
    add_act("emote starts snoozing slightly.");
    add_act("giggle merri ");
    add_act("emote sings a merry little tune.");
    add_act("emote looks like he is thinking of food.");
    add_act("emote stares at the firelight a while.");
   add_act("introduce myself");

    set_cact_time(5);
    add_cact(({"scream","say WHY me?? WHY, tell me, WHY??!"}));
    add_cact("knee all");
    add_cact("emote screams: STOP IT, or i will start getting angry at you!");

    set_cchat_time(3);
    add_cchat("You think you are tough attacking a hobbit eh?");
    add_cchat("You stinking snob of an Easterling!!");
    add_cchat("Hopefully you will run when my friends are here.");

    /*Triggers*/

    set_alarm(0.5,0.0,"arm_me");

}

arm_me()
{
    object knife,tunic,boots;

    FIXEUID;

    knife = clone_object(BREE_DIR + "wep/" + "bknife");
    tunic = clone_object(BREE_DIR + "arm/" + "ltunic");
/*    boots = clone_object(BREE_DIR + "arm/" + "boots");
    boots->move(TO);
*/
    knife->move(TO);
    tunic->move(TO);
    command("wear all");

}

void
attacked_by(object obj)
{
    ::attacked_by(obj);
    command("say You should not mess with me, I have mighty friends.");
    command("emote grips the hilt of his long-knife!");
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
    command("say Puh, I managed to scare those bandits away!");
    command("say I hope master Took will come soon.");
    remove_alarm(alarm_id);
}


void
add_introduced(string str)
{
    if (!interactive(TP) || TP->query_met(query_name()))
        return;

    command("introduce me to " + TP->query_real_name() + "");
}

