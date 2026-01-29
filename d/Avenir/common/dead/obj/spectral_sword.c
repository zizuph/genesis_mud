// spectral sword   /d/Avenir/common/dead/obj/spectral_sword.c
// creator(s):       Lilith, July 2021
// purpose:          Gear for Spectral Guardians
//                  
//         Effects:  ice/death damage special
//       Drawbacks:  add_attack_delay on wield and unwield 
//    Requirements:  SS_WEP_SWORD >= 65
//                   Cannot be Infidel.
//    Assoc. Files:  /d/Avenir/common/dead/mon/spectral_guardian                              
// updates:
// note: 
// bug(s):                          
// to-do:          add_attack_delay upon wielding/unwield, 
//                weapon special should feel biting cold when it hits. (ice/death magic)

#pragma strict_types
inherit "/std/weapon";
inherit "/lib/keep";
#include "../dead.h"
#include "/d/Avenir/include/basic.h"
#include "/d/Avenir/include/relation.h"
#include <wa_types.h>
#include <ss_types.h>
#include <formulas.h>

#define WIELDED   "_Avenir_i_wield_spectral_sword"

int charged = 4;

string my_short()
{
	string str;
	if (charged)
        str = "luminous spectral rapier ";
   	else	
		str ="faintly-glowing spectral rapier";
    return str;
}	

string my_long()
{
	string str;
	if (charged)
		str = "several luminous crystals glowing intensely green in "
	        +"settings along the outer rim.\n";
	else
		str = "faintly glowing crystals in settings along the outer "
	        +"edge of it.\n";		
	
    return "This sword once belonged to a spectral guardian from "
	        +"the catacombs of Sybarus.\nIt looks like a rapier of "
            +"sorts, long and thin, with an eerie greenish glow "
			+"down the entire length. "			
		    +"The grip is made from a long bone with runic symbols "
			+"carved into it, and the guard is a metal cup with "
			+ str;
	
}

string exa_hilt()
{
	string str;
	if (charged)
	{
		str = "The hilt of this sword is made from the bone of "
		    +"an unknown but probably powerful magical creature. "
		    +"Runic symbols have been carved into it, and they "
			+"glow with intense, pulsing light.\n";
    }
	else
		str = "It is a hilt made from a bone. There are runic symbols "
	        +"carved into it.\n";		
	
	return str;
			
}

string exa_pommel()
{
    string str;
    str = "The hilt ends in a flat circle, stamped with a sybarun "
	    +"trefoil.\n";
    
    return str;
}

string exa_symbols()
{
    string str;
	if (charged)
        str = "They glow with greenish spectral energy.\n";
	else
		str = "\n";
	
	return "The runic symbols carved into the hilt are completely "
	    +"foreign to you. " +str;
	
}

public void check_charges()
{
    if (charged)
    {
        return;
    }
    
    recharge_time = time() + RECHARGE_DELAY;
}


public void set_weapon_hits(int hits)
{
    if (charged > 0 && !random(100))
    {
        charged--;
        check_charges();
    }
    ::set_weapon_hits();
}

void config_it()
{
	if (!charged)	   
	{  
        remove_adj(({"glowing", "green", "luminous"}));
		set_hit(35);
		set_pen(35);
	    wielder->update_weapon(TO);
    }	
	else
	{
        set_adj(({"glowing", "luminous", "green"}));
		set_hit(43);
		set_pen(47);
	}
	object wielder = query_wielded();	
	if (wielder)
		wielder->update_weapon(TO);
}	
	

void create_weapon()
{
    set_name("_Avenir_spectral_sword");    
    add_name(({"sword", "rapier"}));
	add_adj(({"bone", "spectral"}));
    set_long(my_long);
	set_short(my_short);
	config_it();
	set_keep(1);
	set_wt(W_KNIFE);
    set_wf(this_object());	
    set_hands(W_ANYH);	
	set_hit(45);
    set_pen(47);
	set_dt(W_IMPALE); 

	add_prop(OBJ_I_IS_MAGIC_WEAPON , 1);  
 	add_prop(MAGIC_AM_MAGIC, ({"death", 90}));
//	add_prop(MAGIC_AM_ID_INFO,
// 	add_prop(OBJ_S_WIZINFO,
	add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT, PEN) * 2);
	add_prop(OBJ_I_WEIGHT, 3000); // Very lightweight: It's a bone and a crystal.
	add_prop(OBJ_I_VOLUME, 1000); // Energy sword. Not much volume to it.

    /* Setting these to zero. The cool-down period of the blade means
     * it cannot be continuously used. Since the blade is spectral energy
     * not physical matter it doesn't make sense for these to happen
     */	 
	set_likely_break(0);
    set_likely_dull(0);
    set_likely_corr(0);    

	add_item(({"hilt", "bone hilt"}), "@@exa_hilt");
	add_item(({"pommel"}), "@@exa_pommel");
	add_item(({"crystal", "crystals", "crystals on guard", "guard crystals"}), "@@crystal_state");
	add_item(({"runic symbols", "runes"}), "@@exa_symbols"); 
}

/*
 * Function     : wield
 * Description  : Wield a weapon
 * Arguments    : Object what - The weapon to wield
 * Returns      : string - error message (weapon not wielded)
 *                1 - success (weapon wielded)
 */
mixed 
wield(object what)
{
    /* I'm an npc, so I can by pass checks */
    if (!interactive())
		return 0;
	
    /* Is it broken? If so, dont wield */
    if (query_prop(OBJ_I_BROKEN))
        return "It is broken in such a way that you cannot wield it.\n";

    /* I'm an infidel/enemy of Sybarus */
    if (IS_INFIDEL(TP))
    {
        TP->heal_hp(-50);
        return "The "+ short() +" twists out of your grasp and "
               +"lands on your foot, causing you great pain.\n";
    }
	
	/* Undead "friendly" weapon in an undead area. */
    if (TP->query_prop(LIVE_I_UNDEAD))
    {
        TP->catch_tell("You feel an affinity toward the "+ 
            short() +".\n");
    }

    /* Do I have the skills needed? */
    if (!TP->query_skill(SS_WEP_SWORD) > 70)
	{
		return "You lack the level of skill needed to wield "
		    +"the "+ short() +"\n";
	}
      
    /* All checks have passed, proceed with wielding */
    TP->catch_tell("Your fingers curl around the bone grip of the "+ 
	    short() +". The spectral energy begins running a slow loop "+
		"up and down your arm.\n");
    say(QCTNAME(TP)+" grips the "+ short() +".\n");

    if (!TP->query_prop(WIELDED))
    {
		/* reduce quickness by 10 as "price" of using this dagger */
        TP->add_prop(LIVE_I_QUICKNESS, TP->query_prop(LIVE_I_QUICKNESS) - 10);
        TP->add_prop(WIELDED, 1);
    }
    return 1;
}

/* 
 * Function    : unwield
 * Description : Unwield a weapon
 * Arguments   : object wep - the weapon to unwield
 */
mixed 
unwield(object wep)
{
	object wielder = query_wielded();
	
	if (!query_interactive(environment(this_object())))
	    return 0;

	if (wielder->query_prop(WIELDED))
	{
		/* give them back their quickness */
        wielder->add_prop(LIVE_I_QUICKNESS,
            wielder->query_prop(LIVE_I_QUICKNESS) + 10);
		wielder->remove_prop(WIELDED);
	}
	wielder->catch_tell("As you release your grip on the "+ short()
        +" you feel that slow-loop of spectral energy running "
        +"through you ease off.\n");	
    return 0;
}
