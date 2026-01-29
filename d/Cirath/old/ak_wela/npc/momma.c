/* This is a standard raider for the pass */ 


inherit "/d/Cirath/std/monster";


#include "defs.h"

#define WIFENAME (({"biltof","wang","piou-bing","ma-wong","bajing","so-tang","pejlon","milt","jotti","smikor"}))
#define WIFEADJ (({"tired-looking","smiling","fat","buxom","sweaty","cooking","nervous","sighing","singing","humming","ugly","beutiful","young","old","calloused","wrinkled","dark-skinned","blonde","auburn","red-haired","slant-eyed"}))
#pragma strict_types

void
create_monster()
{
    ::create_monster();	
    set_name(WIFENAME[random(10)]);
    set_adj(WIFEADJ[random(20)]);   		
    add_adj(WIFEADJ[random(20)]);		
    set_title(", housewife");
    set_race_name("human");     
    add_name("woman");
    set_gender(G_FEMALE);
    set_long("This is a "+TO->query_nonmet_name()+" who seems busy "+
            "doing the daily household chores. She looks at you with " +
	    "suspicion, following your every move. She holds a rolling-pin "+
            "tightly clutched in her right hand.\n");
    
    SET_MAX_HP
    default_config_npc(60);
    set_base_stat(SS_DIS, 75+random(20));	
    set_skill(SS_WEP_CLUB, 60 + random (40));
	
    set_skill(SS_DEFENSE, 30 + random(10));
    set_skill(SS_PARRY,25 + random(10));
    
    set_assist_cry("Stay away from my husband and children you vermin.");
    set_chat_time(60+random(20));
    add_chat("Behave now kids!");
    add_chat("Can I help you in any way ?");
    add_chat("I suggest you leave, we have nothing to offer.");
    
    set_act_time(4);
    add_act("emote polishes the table with a cloth.");
    add_act("emote dices some vegetables, and puts them in a cauldron");
    add_act("emote looks at her children briefly.");

    set_cact_time(6);
    add_cact("emote claws at your eye.");
    add_cact("emote swings her rolling-pin in a terrifying display of skill .");
    add_cact("back nerv");

    set_cchat_time(14);
    add_cchat("Please spare us, we are poor , you can have all we own.");
    add_cchat("Let my children live, they have done nothing!");

    set_default_answer("I am sorry, if you want anything ask my husband.\n");
}


void
arm_me()
{
    clone_object(AK_WELA_DIR+"obj/shawl.c")->move(TO);
    clone_object(AK_WELA_DIR+"obj/dress.c")->move(TO);
    clone_object(AK_WELA_DIR+"wep/rollpin.c")->move(TO);
    command("wear all");
    command("wield all");
}


