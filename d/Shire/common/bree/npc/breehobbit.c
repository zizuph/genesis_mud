/* Typoed by Vadiem 1:12:94 */

inherit "/std/monster";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Shire/common/make_money.h"

//   Prototypes
void return_introduce(string who);

int alarm_id;

create_monster()
{
    if (!IS_CLONE)
        return;	

    set_living_name("underhill");
    set_name("underhill");
    set_title("Took of Shire");
    set_race_name("hobbit");
    set_short("merry hobbit");
    set_long("This is one of the merry hobbits living in Bree. He looks like "
    	    +"he is full of merriment and joy.\n");
    set_adj("merry");
    set_stats(({30,50,40,80,100,30}));
    MAKE_MONEY;
    set_alignment(100);
    
    set_skill(SS_WEP_KNIFE,50);
    set_skill(SS_DEFENCE,50);
    
    add_prop(CONT_I_WEIGHT, 60*1000);
    add_prop(CONT_I_HEIGHT, 120);
    set_gender(G_MALE);
    
    set_chat_time(4);	    
    add_chat("How are you today master?");
    add_chat(({"emote takes out his tobacco.","emote stuffs his pipe with some tobacco.",
              "emote lights his pipe.","emote gets a big smile all over his face as he inhales some smoke from his fine pipe."}));
    add_chat("My, is it not a nice weather we have today?");
    add_chat("Those wolves are dangerous!");
    add_chat("I hope those birds will stay away from my garden now. I tell you master, those birds are damned!");
    add_chat("Have you met our herbalist? He is real good.");

    set_act_time(5);
    add_act("sniff");
    add_act("smile merri");
    add_act("sneeze");
    add_act("emote looks like he is thinking of food.");
    add_act("giggle merri ");
    add_act("emote sings a merry little tune.");
    add_act("emote looks like he is thinking of food.");
    add_act("emote looks up in the sky with a suspicious face.");
    
    set_cact_time(5);
    add_cact(({"scream","say WHY me?? WHY, tell me, WHY??!"}));
    add_cact("shout HELP HELP, "+QCTNAME(TP)+" is trying to kill me!!!");
    add_cact("knee all");
    add_cact("emote screams: STOP IT, or i will start getting angry at you!");
     
    set_cchat_time(3);
    add_cchat("You think you are tough attacking a hobbit eh?");
    add_cchat("You stinking snob of an easterling!!");
    add_cchat("Hopefully you will run when my frinds are here.");
    
    /*Triggers*/
    trig_new("%w 'introduces' %s", "react_introduce");
        
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
    command("say You should not mess with me, I have mighty friends!");
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
    command("say Puh, i managed to scare those bandits away!");
    command("say I hope master Took will come soon.");
    remove_alarm(alarm_id);
}

int
react_introduce(string who, string dummy)
{
    if (who)
    {
        who = lower_case(who);
set_alarm(3.0,0.0,&return_introduce(who));
        return 1;
    }
}

void
return_introduce(string who)
{
    object obj;
    int    ran;
    
    if (obj = present(who,environment()))
    {
        ran = random(3);
        if (ran == 0)
        {
            command("say Good day master " + obj->query_name() +".");
            command("introduce me");
            command("smile " + who);
            command("shake " + who);
        }
        if (ran == 1)
        {
            command("bow to " + who);
            command("introduce me");
            command("say Hullo there " + who +", how are you today?");
            command("laugh merri " + who);
        }
        if (ran == 2)
        {
            command("introduce me");
            command("say Greetings worthy " + obj->query_race_name() + ".");
            command("bow to " + who);
        }
    }
}
