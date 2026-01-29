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

    set_name("petunia");
    set_race_name("hobbit");
    set_adj(({"short","kindly"}));
    set_long("This old hobbit woman seems sad and lonely. "+
    "You wonder if there is anything you can do for her.\n");
    set_stats(({70,60,65,80,100,95}));
    MAKE_MONEY;
    set_alignment(-163);
    
    set_skill(SS_WEP_SWORD,70);
   set_skill(SS_PARRY,70);
    set_skill(SS_DEFENCE,60);
    
    add_prop(CONT_I_WEIGHT, 60*1000);
    add_prop(CONT_I_HEIGHT, 120);
    set_gender(G_MALE);
    


   add_ask(({"task","help","job","quest"}), VBFC_ME("ask_job"));
    set_chat_time(5);	    
   add_chat("They don't make tobacco like Old Toby anymore.");
   add_chat("Have you seen my husband?");
   add_chat("My husband went to Michel Delving but has not returned.");


    set_act_time(5);
    add_act("glare");
    add_act("emote eyes you up carefully.");
    
    set_cact_time(5);
    add_cact("shout Help, call the Shiriffe, "+QCTNAME(TP)+" is trying to kill me!!!");
    add_cact("knee all");
     
    set_cchat_time(3);
    add_cchat("You think you are tough attacking a woman like me eh?");
    add_cchat("You stinking snob of an Shireling!!");
    add_cchat("My husband will save me, I hope.");
    
    /*Triggers*/
        
    set_alarm(0.5,0.0,"arm_me");

}

arm_me()
{
    object knife,tunic,boots;
    
    FIXEUID;

    knife = clone_object(BREE_DIR + "wep/" + "rsword");
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
    command("emote grips the hilt of her longsword!");
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
    command("say I am too good for them!!");
    command("say I hope my husband will come soon.");
    remove_alarm(alarm_id);
}

string
ask_job()
{
   command("say Need help? Me? No.");
   command("ponder");
   command("emote looks at you carefully.");
   command("say I think you need help though.");
   command("say Help out of my house!");
   write("The short human pushes you outside with a great shove!\n");
   TP->move_living("M","/d/Shire/common/bree/nroad1",1);
   command("emote pushes someone out of the house so fast, you can't see who it was.");
   command("say There, that showed 'em.");
   return "";

}
