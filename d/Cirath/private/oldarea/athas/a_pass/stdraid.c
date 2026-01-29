/* This is a standard raider for the pass */ 


inherit "/d/Cirath/std/monster";


#include "defs.h"

#define RAIDERNAME (({"kallin","ilareth","terlath","reldak","seldik","fildak","klaared","crebal","neluth","fleurgan"}))
#define RAIDERADJ (({"strinking","smooth","fine-limbed","evil-looking","angry","protective","calm","huge","towering","green-eyed","ragged","scarred","sadistic","leering","sun-scarred","rude","imposing","smart","mischievous","cunning","snickering"}))
#pragma strict_types

void
create_monster()
{
    ::create_monster();	
    set_name(RAIDERNAME[random(10)]);
    set_adj(RAIDERADJ[random(20)]);   		
    add_adj(RAIDERADJ[random(20)]);		
    set_title(", member of the Ilkath Clan");
    set_race_name("elf");     
    add_name("raider");
    set_gender(random(2));
    set_long("This is a "+TO->query_nonmet_name()+" who seems "+
            "determined to defend the water. " +CAP(HE_SHE(TO))+
            " looks as if "+HE_SHE(TO)+" will give you quite a fight," +
	    "if you decide to attack "+HIM_HER(TO)+".\n");
    
    SET_MAX_HP
    default_config_npc(70);

    set_base_stat(SS_STR, 70 +random(40));
    set_base_stat(SS_DEX, 60 +random(40));	
    set_base_stat(SS_CON, 65 +random(40));
    set_base_stat(SS_DIS, 60+random(20));	
    set_skill(SS_WEP_SWORD, 60 + random (40));
	
    set_skill(SS_UNARM_COMBAT, 20+random(40));
    set_skill(SS_DEFENSE, 50 + random(40));						
    
    set_assist_cry("Bleed to death, intruder.");
    set_chat_time(60+random(20));
    add_chat("Stay away from our water!");
    add_chat("Leave now, before you get hurt!");
    add_chat("Get out of here, wretched creature.");
    
    set_act_time(4);
    add_act("emote looks at you with a sneer.");
    add_act("emote turns "+HIS_HER(TO)+" eyes towards you and looks you over.");
    add_act("emote brandishes "+HIS_HER(TO)+" sword and smiles evilly.");

    set_cact_time(6);
    add_cact("emote kicks you hard on your kneecap, causing you to gasp in pain");
    add_cact("emote tries to kick some sand in your eyes, but fails");
   
    set_cchat_time(14);
    add_cchat("Your blood will add to the flavour of this well.");
    add_cchat("Don't die in the water, please.");

    set_default_answer("Do I look like some fortune-teller ? I will "+
                       "not answer your foolish questions!\n");
}


void
arm_me()
{
    clone_object(ATH_WEAPON+"swrd_obs.c")->move(TO);	
    clone_object(ATH_ARMOUR+"body_scl.c")->move(TO);
    command("wear all");
    command("wield all");
}


