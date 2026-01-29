#pragma strict_types
#pragma no_clone

#include "/d/Faerun/defs.h"
#include "defs.h"

inherit FAERUN_NPC_BASE;

/*
 * Basic setup of the NPC. This file is only meant to be inherited !
 *  
 * by Kehr, March 2007
 */

void npc_basic_setup()
{
    seteuid(getuid());

    set_race_name("human");
    set_short("base smart npc");
    set_pshort("base smart npcs");
    set_long("This is Kehr's base smart npc.\n");

    add_prop(CONT_I_WEIGHT,80000+random(20000));
    add_prop(CONT_I_HEIGHT,160+random(20)+random(20));
    add_prop(LIVE_I_SEE_DARK,0);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_M_NO_ACCEPT_GIVE, "Don't try to bribe me!\n");
    add_prop(LIVE_I_ATTACK_THIEF,1);
    add_prop(NPC_I_NO_RUN_AWAY,1);
    add_prop(NPC_I_NO_UNARMED, 1);
    
    set_alignment(0);
    
    set_alarm(1.0, 0.0, "equip_me");
 }
 
/* Sets stats and some skills around given averages
 * sta - stats average
 * ska - skill average
 *
 * WARNING - biased to create "warrior-type" npc's (higher str,dex,con and dis, lower wis and int)
 *           actual stat average might be up to 10% higher
 *			 
 */

void set_level(int sta, int ska) {
	
	int tmp;

	tmp = sta/10;
	
    set_base_stat(0, 110*sta/100 + random(tmp));
    set_base_stat(1, 120*sta/100 + random(tmp));
    set_base_stat(2, 120*sta/100 + random(tmp));
    set_base_stat(3,  70*sta/100 + random(tmp));
    set_base_stat(4,  80*sta/100 + random(tmp));
    set_base_stat(5, 100*sta/100 + random(tmp));
	
	tmp = ska/10;
    set_skill(SS_UNARM_COMBAT,	 80*ska/100 + random(tmp));
    set_skill(SS_DEFENCE,	 90*ska/100 + random(tmp));
    set_skill(SS_WEP_AXE,	100*ska/100 + random(tmp));
    set_skill(SS_WEP_CLUB,	100*ska/100 + random(tmp));
    set_skill(SS_WEP_SWORD,	100*ska/100 + random(tmp));
    set_skill(SS_WEP_POLEARM,	100*ska/100 + random(tmp));
    set_skill(SS_PARRY, 	 90*ska/100 + random(tmp));
    set_skill(SS_AWARENESS, 	 80*ska/100 + random(tmp));
    set_skill(SS_2H_COMBAT, 	 90*ska/100 + random(tmp));

	// ok, thats a cheat - but lets just make them a little bit more difficult ;)
	// up to +60 in AC on all hit locations ;)
	set_all_hitloc_unarmed(min(60, 60*sta/200));
}

void equip_me()
{
    object torch;
    
    torch = clone_object("/std/torch");
    torch -> set_short("wooden torch");
    torch -> set_long("It is a plain wooden torch that will burn for a while.\n");
    torch -> move (this_object());
}
 
/* --------------------------------------------------------------------------
 * Light management
 */ 
