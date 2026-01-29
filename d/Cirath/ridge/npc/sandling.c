/*
* Created by: Luther
* Date: Sept 2001
*
* File: /d/Cirath/ridge/npc/sandling.c
* Comments: Creatures in the valley
*/

inherit "/d/Cirath/std/monster.c";
inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/action";
#include <wa_types.h>
#include <const.h>
#include "defs.h"

#define A_BITE  0
#define A_LCLAW 1
#define A_RCLAW 2
#define H_HEAD 0
#define H_BODY 1
#define TDESC ({"pale", "dark", "transparent", "wavy"})[random(4)]
 
void
create_creature()
{
    	set_name("sandling");
    	set_race_name("sandling");
    	set_adj(TDESC);
    	set_long("This is a sandling who roams the valley.\n");
    	set_short(TDESC + " sandling");
    	
    	set_stats(({25+random(50),25+random(50),25+random(50),
        25+random(50),25+random(50),25+random(50)}));
   	
   	set_attack_unarmed(A_BITE,  50, 30, W_IMPALE, 20, "glass teeth");
        set_attack_unarmed(A_LCLAW, 25, 15, W_SLASH,  40, "sanded fist");
        set_attack_unarmed(A_RCLAW, 25, 15, W_SLASH,  40, "sanded fist");
        
    	set_hitloc_unarmed(H_HEAD, 40, 30, "head");
    	set_hitloc_unarmed(H_BODY, 30, 70, "body");
   	
    	set_skill(SS_BLIND_COMBAT, 50+random(25));
    	set_skill(SS_DEFENCE, 60+random(15));
    	add_prop(LIVE_I_SEE_DARK,100);
	add_prop(NPC_I_NO_RUN_AWAY, 1);
	add_prop (LIVE_I_NEVERKNOWN, 1);
    	add_prop(MAGIC_I_RES_FIRE, 80);
    	add_prop(MAGIC_I_RES_ACID, 80);
    	add_prop(MAGIC_I_RES_COLD, 80);
    	add_prop(MAGIC_I_RES_ELECTRICITY, 80);
    	add_prop(LIVE_I_NO_CORPSE, 1);
}
  