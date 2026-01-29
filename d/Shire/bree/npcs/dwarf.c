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

    set_name("gloin");
    set_race_name("dwarf");
    set_adj(({"wrinkled","white-bearded"}));
    set_long("This is one of the visitors to the Prancing Pony. He looks like "
    	    +"he wishes to appear unconcerned about other's affairs, but he is listening.\n");
    set_stats(({65,50,70,30,40,95}));
    MAKE_MONEY;
    set_alignment(100);

    set_skill(SS_WEP_AXE,70);
   set_skill(SS_PARRY,70);
    set_skill(SS_DEFENCE,60);

    add_prop(CONT_I_WEIGHT, 60*1000);
    add_prop(CONT_I_HEIGHT, 120);
    set_gender(G_MALE);

    set_chat_time(3);
    add_act(({"emote takes out his tobacco.","emote stuffs his pipe with some tobacco.",
              "emote lights his pipe.","emote gets a big smile all over his face as he inhales some smoke from his fine pipe."}));
   add_chat("The fire could use some stoking, I think.");
   add_chat("Where the pick is sharp, the will is strong, and where the gold is good, the heart is warm.");
   add_chat("I'd be careful if I were you, lots of eyes and ears around.");
   add_chat("The shadow of the East has returned.");


    set_act_time(5);
    add_act("emote drinks a pint of ale.");
    add_act("smile sli");
    add_act("emote perks his ears up at the last bit of conversation.");
    add_act("emote stares at the firelight a while.");

    set_cact_time(5);
//  add_cact("shout Barliman, call the Shiriffe, "+QCTNAME(TP)+" is trying to kill me!!!");
    add_cact("knee all");
    add_cact("emote screams: STOP IT, or i will start getting angry at you!");

    set_cchat_time(3);
    add_cchat("You think you are tough attacking a dwarf eh?");
    add_cchat("You stinking snob of an easterling!!");
    add_cchat("Alas! I will have to kill you now.");

    /*Triggers*/

    set_alarm(0.5,0.0,"arm_me");

}

arm_me()
{
    object knife,tunic,boots;

    FIXEUID;

    knife = clone_object(BREE_DIR + "wep/" + "daxe.c");
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
    command("say You should not mess with me, I am stronger than I look.");
    command("emote grips the hilt of his sharp axe!");
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
    command("say Ha!, i managed to scare those scoundrels away!");
    command("say I hope Dain will come soon.");
    remove_alarm(alarm_id);
}


void
add_introduced(string str)
{
    if (!interactive(TP) || TP->query_met(query_name()))
        return;

    command("introduce me to " + TP->query_real_name() + "");
}