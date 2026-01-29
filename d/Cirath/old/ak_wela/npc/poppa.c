/* This is a standard raider for the pass */ 


inherit "/d/Cirath/std/monster";


#include "defs.h"

#define POPNAME (({"biltof","wang","piou-bing","ma-wong","bajing","so-tang","pejlon","milt","jotti","smikor"}))
#define POPADJ (({"blue-eyed","smiling","fat","fish-smelling","sweaty","scarred","nervous","sighing","singing","humming","ugly","beutiful","young","old","calloused","wrinkled","dark-skinned","blonde","black-haired","red-haired","slant-eyed"}))
#pragma strict_types

void
create_monster()
{
    ::create_monster();	
    set_name(POPNAME[random(10)]);
    set_adj(POPADJ[random(20)]);   		
    add_adj(POPADJ[random(20)]);		
    set_title(", the fisherman");
    set_race_name("human");     
    add_name("man");
    set_gender(G_MALE);
    set_long("This is a "+TO->query_nonmet_name()+" who seems to be resting "+
            "from a hard day of fishing. He looks at you with " +
	    "obvious displeasure. He obviously wants you to leave. ");
    
    SET_MAX_HP
    default_config_npc(80);
    set_base_stat(SS_DIS, 80+random(20));	
    set_skill(SS_WEP_KNIFE, 70 + random (30));
	
    set_skill(SS_DEFENSE, 60 + random(10));
    set_skill(SS_PARRY,35 + random(10));
    
    set_assist_cry("Stay away from my wife and children you vermin.");
    set_chat_time(60+random(20));
    add_chat("God, I am tired.");
    add_chat("I heard Torblin was taken by the templars today, he could write!");
    add_chat("Whats for dinner ?");
    
    set_act_time(4);
    add_act("emote looks at his family and smiles.");
    add_act("emote gets a carrot from the table and eats it.");
    add_act("emote looks you over.");

    set_cact_time(6);
    add_cact("scream");
    add_cact("fume");
    add_cact("explode");

    set_cchat_time(14);
    add_cchat("Die, vermin.");
    add_cchat("I will gut you like a fish!");

    set_default_answer("Ask a templar, they might know.\n");
}


void
arm_me()
{
    clone_object(AK_WELA_DIR+"obj/l_apron.c")->move(TO);	
    clone_object(AK_WELA_DIR+"obj/l_hat.c")->move(TO);
    clone_object(AK_WELA_DIR+"wep/fknife.c")->move(TO);
    command("wear all");
    command("wield all");
}


