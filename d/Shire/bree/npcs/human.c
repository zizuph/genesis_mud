inherit "/std/monster";
#include "/d/Shire/sys/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Shire/common/make_money.h"

void arm_me();

int alarm_id;

create_monster()
{

    int x,y;
    string *descr, *age;

    descr = ({"happy", "dark-skinned", "tanned", "weathered", "bushy-haired", "strong", "friendly"});
    age  = ({"young", "juvenile", "old", "middle-aged", "weathered", "elderly", });
 
    x = random(sizeof(descr));
    y = random(sizeof(age));
  
    if (!IS_CLONE)
        return;	

    set_race_name("human");
    set_adj(({descr[x],age[y]}));
    set_short(descr[x] + " " + age[y] + " human");
    set_long("This is a "+short()+" and a citizen of Bree. He has " +
        "probably spent most of his life here but looks a little " +
        "scarred from battles unknown.\n");
    set_stats(({65,50,70,30,40,95}));
    MAKE_MONEY;
    set_alignment(0);
    
    set_skill(SS_WEP_AXE,70);
    set_skill(SS_WEP_SWORD, 70);
    set_skill(SS_PARRY,70);
    set_skill(SS_DEFENCE,60);
    
    add_prop(CONT_I_WEIGHT, 60*1000);
    add_prop(CONT_I_HEIGHT, 120);
    set_gender(G_MALE);
    
    set_chat_time(5);	    
    add_chat("It seems no one comes to live here anymore.");
    add_chat("I'm sure you have a tale or two to tell.");
    add_chat("Be sure and visit Barliman. He has the best food anywhere.");
    add_chat("Do I know you from somewhere?");
    add_chat("I love Bree. It is a great place.");
   
    set_cact_time(5);
    add_cact("I can't believe you are attacking me!");
    add_cact("emote dances around you dangerously.");
    add_cact("What have I done to deserve this?");
    add_cact("emote hammers you hard with his sword.");
    add_cact("You won't live to see another day now!");
     
    set_cchat_time(3);
    add_cchat("Who do you think you are attacking me?");
    add_cchat("You are mean!");
    add_cchat("Run now and I will let you live!");
    
    /*Triggers*/
        

    arm_me();
}

arm_me()
{
    object axe,tunic,boots;
    
    FIXEUID;

    axe = clone_object(WEP_DIR+ "sword.c");
    tunic = clone_object(ARM_DIR+ "ltunic");

    axe->move(TO);
    tunic->move(TO);
    command("wear all");
    command("wield sword");
   
}
