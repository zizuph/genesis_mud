/* This is a standard raider for the pass */ 


inherit "/d/Cirath/std/monster";


#include "defs.h"

#pragma strict_types

void
create_monster()
{
    ::create_monster();	
    set_name("ignatius");
    set_adj("enormous");   		
    add_adj("evil-looking");		
    set_title(", leader of the Ilkath Clan");
    set_race_name("elf");     
    add_name("raider");
    set_gender(random(2));
    set_long("This is a "+TO->query_nonmet_name()+" who seems "+
            "determined to defend the water. " +CAP(HE_SHE(TO))+
            " looks as if "+HE_SHE(TO)+" will give you quite a fight," +
	    "if you decide to attack "+HIM_HER(TO)+".\n");
    
    default_config_npc(120);

    set_base_stat(SS_STR, 130 +random(40));
    set_base_stat(SS_DEX, 150 +random(40));	
    set_base_stat(SS_CON, 130 +random(40));
    set_base_stat(SS_DIS, 110+random(20));	
    set_skill(SS_WEP_SWORD, 100);
	
    set_skill(SS_UNARM_COMBAT, 50+random(40));
    set_skill(SS_DEFENSE, 60 + random(40));						
    
    set_assist_cry("Bleed to death, intruder.");
    set_chat_time(90+random(20));
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
 
    trig_new("%w ' drinks some water'%s","@@killer");
}


void
arm_me()
{
    clone_object(WILD_WEP+"swrd_obs.c")->move(TO);
    clone_object(WILD_ARM+"body_scl.c")->move(TO);
    command("wear all");
    command("wield all");
}


void
killer()
{
    command("say Stealing or water eh ? You'll regret that....");
    command("kill"+QTNAME(TP));
}
