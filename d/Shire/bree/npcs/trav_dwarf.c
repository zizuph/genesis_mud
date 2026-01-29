inherit "/std/monster";
#include "/d/Shire/sys/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Shire/common/make_money.h"

int alarm_id;

create_monster()
{

    int x,y;
    string *descr, *age;

    descr = ({"white-bearded", "travelled", "long-bearded", "tired", "strong", "haggard", "jolly"});
    age  = ({"young", "old", "middle-aged", "aged"});
 
    x = random(sizeof(descr));
    y = random(sizeof(age));
  
    if (!IS_CLONE)
        return;	

    set_race_name("dwarf");
    set_adj(({descr[x],age[y]}));
    set_short(descr[x] + " " + age[y] + " dwarf");
    set_long("This "+short()+" is one of the many travellers that has " +
		"come to Bree. He is strong looking and battle worn. The dwarf " +
		"looks like a formidable foe and could probably defend himself well.\n");
    set_stats(({65,50,70,30,40,95}));
    MAKE_MONEY;
    set_alignment(100);
    
    set_skill(SS_WEP_AXE,70);
    set_skill(SS_PARRY,70);
    set_skill(SS_DEFENCE,60);
    
    add_prop(CONT_I_WEIGHT, 60*1000);
    add_prop(CONT_I_HEIGHT, 120);
    set_gender(G_MALE);
    
    set_chat_time(5);	    
    add_chat("I have travelled far and seen many things.");
    add_chat("The world is a wild place. Be careful out there.");
    add_chat("Where are you going today?");
    add_chat("Have you been to the Prancing Pony? It's a wonderful inn.");
    add_chat("Bree is a nice place to visit.");
   
    set_cact_time(5);
    add_cact("Defend yourself, rouge!");
    add_cact("emote dances around you dangerously.");
    add_cact("You won't live to tell of this battle!");
    add_cact("emote hammers you hard with his axe.");
    add_cact("emote attacks you with renewed vigor.");
     
    set_cchat_time(3);
    add_cchat("Who do you think you are attacking me?");
    add_cchat("You stinking spawn of an orc!");
    add_cchat("Alas! I will have to kill you now.");
    
    /*Triggers*/
        
    set_alarm(0.5,0.0,"arm_me");

}

arm_me()
{
    object axe,tunic,boots;
    
    FIXEUID;

    axe = clone_object(WEP_DIR+ "daxe.c");
    tunic = clone_object(ARM_DIR+ "ltunic");

    axe->move(TO);
    tunic->move(TO);
    command("wear all");
    command("wield axe");
   
}

void
attacked_by(object obj)
{
    ::attacked_by(obj);
    command("say You should not mess with me, I am stronger than I look.");
    command("emote grips the hilt of his sharp axe!");
    command("wield all");
    command("wear all");   
}
