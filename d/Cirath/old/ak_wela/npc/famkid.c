


inherit "/d/Cirath/std/monster";


#include "defs.h"

#define KIDNAME (({"biltof","wang","piou-bing","ma-wong","bajing","so-tang","pejlon","milt","jotti","smikor"}))
#define KIDADJ (({"snotty","sniveling","big-eyed","crying","sulking","happy","screaming","doddering","running","dirty","giggling","angry","sad","smiling","nose-picking","coughing","mischievous","smart","mischievous","snickering","yawning"}))
#pragma strict_types

void
create_monster()
{
    ::create_monster();	
    set_name(KIDNAME[random(10)]);
    set_adj(KIDADJ[random(20)]);   		
    add_adj(KIDADJ[random(20)]);		
    set_title(", the little kid");
    set_race_name("human");     
    add_name("kid");
    set_gender(random(2));
    set_long("This is a "+TO->query_nonmet_name()+" who tumbles around "+
            "the home, doing kid stuff. " +CAP(HE_SHE(TO))+
            " looks as if "+HE_SHE(TO)+" is completely unaware " +
	    "of your presence.\n");
    
    SET_MAX_HP
    default_config_npc(30);
    set_base_stat(SS_DIS, 60+random(20));	
    set_skill(SS_WEP_SWORD, 60 + random (40));
	
    set_skill(SS_UNARM_COMBAT, 20+random(5));
    set_skill(SS_DEFENSE, 10 + random(10));						
    
    set_assist_cry("Stop attacking my family, dummmy.");
    set_chat_time(60+random(20));
    add_chat("I am prince Imolian, you be the nasty Igraine!");
    add_chat("Molben said I was a fatso today, am I fat ?");
    add_chat("You look funny, are you from far away ?.");
    
    set_act_time(4);
    add_act("emote runs around in a circle.");
    add_act("emote plays some with some sticks "+HE_SHE(TO)+" has found somewhere.");
    add_act("emote mutters something about dragons and the hero Piddlefoot.");

    set_cact_time(6);
    add_cact("emote bites your knee.");
    add_cact("emote screams in outrage and fear.");
    add_cact("cry");

    set_cchat_time(14);
    add_cchat("I don't wanna die.");
    add_cchat("Leave, you stupid dummy you!");

    set_default_answer("How would I know, I am just a kid.\n");
}


void
arm_me()
{
    
}


