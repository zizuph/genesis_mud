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

    set_living_name("locker");
    set_name("locker");
    set_title("Warden of Bree");
    set_race_name("hobbit");
    set_short("tough hobbit");
    set_long("This is one of the hobbits who guards the gate. He looks quite "
    	    +"strong and agile.\n");
    set_adj("tough");
    set_stats(({30,50,50,50,60,30}));
    MAKE_MONEY;
    set_alignment(100);
    
    set_skill(SS_WEP_KNIFE,50);
    set_skill(SS_DEFENCE,50);
    
    add_prop(CONT_I_WEIGHT, 60*1000);
    add_prop(CONT_I_HEIGHT, 120);
    add_prop(LIVE_I_NEVERKNOWN,1);
    set_gender(G_MALE);
    
    set_act_time(3);	    
    add_act("How are you today master?");
    add_act(({"emote takes some tobacco from a pouch.","emote stuffs his pipe with some tobacco.",
              "emote lights his pipe.","emote gets a big smile all over his face as he inhales some smoke from his fine pipe."}));
    add_act("say My, is it not a nice weather we have today?");
    add_act("say Those wolves are dangerous!");
    add_act("say Be careful, there are many thieves around here, better watch out.");
    add_act("say Don't try to fight our champ wrestler, He is real good.");
    add_act("sniff");
    add_act("armpit");
    add_act("sneeze");
    add_act("emote sings a merry little tune.");
    add_act("emote looks up in the sky with a suspicious face.");
    
    set_cact_time(3);
    add_cact(({"scream","say WHY me?? WHY, tell me, WHY??!"}));
    add_cact("shout HELP HELP, a filthy "+TP->query_race_name()+" is trying to kill me!!!");
    add_cact("knee all");
    add_cact("emote screams: STOP IT, or i will call for more guards!!");    
        
    set_alarm(0.5,0.0,"arm_me");

}

arm_me()
{
    object knife,tunic;
    
    FIXEUID;

    knife = clone_object(BREE_DIR + "wep/" + "bknife");
    tunic = clone_object(BREE_DIR + "arm/" + "ltunic");
    knife->move(TO);
    tunic->move(TO);
    command("wear all");
   
}

void
attacked_by(object obj)
{
    ::attacked_by(obj);
    command("say You would not mess with me, I have mighty friends.");
    command("say You son of an easterling, leave at once!");
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
    command("say Hope the other guards will be here soon.");
    remove_alarm(alarm_id);
}
  