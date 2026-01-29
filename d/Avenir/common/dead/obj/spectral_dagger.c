// spectral anelas   /d/Avenir/common/holm/dead/obj/spectral_dagger.c
// creator(s):       Lilith, July 2021
// purpose:          Gear for Spectral Guardians
//                   Trade -10 Haste penalty for hit/pen boost based on charge.
//                   This is a weapon of spectral energy with a re-charge 
//                   cycle--its energy is used up and it can't be used
//                   until it has re-charged.
//         Effects:  Charge of the weapon improves/reduces hit/pen
//       Drawbacks:  Runs out of "energy" and needs to recharge. 
//                   Adds -10 quickness when wielded.
//    Requirements:  KNIFE >= 55. Cannot be Infidel.
//    Assoc. Files:  /d/Avenir/common/dead/mon/spectral_guardian                              
// 
// to-do:  perhaps have a special for the weapon where the 
//         player feels a biting cold where it hits them.
//       
//        should feel a biting cold when the weapon hits.
// updates:

inherit "/std/weapon";
inherit "/lib/keep";
#include "../dead.h"
#include "/d/Avenir/include/basic.h"
#include "/d/Avenir/include/relation.h"
#include <wa_types.h>
#include <ss_types.h>
#include <formulas.h>

#define WIELDED   "_Avenir_i_wield_spectral_dagger"
#define SHADOW    "/d/Avenir/common/dead/obj/spectral_d_sh.c"

#define RECHARGE_DELAY  (1800)
int charged = 4;  
int recharge_time;                  
object wielder = query_wielded();

void recharge_weapon();

string crystal_state()
{
	string str;
	switch (charged)
	{
	   case 0: 
	        str = "A crystal in the cup-end of the bone hilt has a "
		       +"very faint greenish glow to it.\n";
			return str;
		    break;   
	   case 1: 
	        str = "A crystal in the cup-end of the bone hilt glows "
			   +"with a green energy that seems to be flickering, "
			   +"as if it is going to fade soon.\n";
	        return str;
			break;
	   case 2:
	        str = "The crystal inset into the cup-end of the bone "
		       +"from which the hilt was made glows with greenish "
			   +"spectral energy that emerges from the center of "
			   +"bone.\n";
			return str;
			break;
	  case 3:
	        str = "A crystal glows bright green with spectral energy "
		       +"from its setting in the cup-end of the bone hilt. "
			   +"This energy emerges from the center of the bone "
			   +"and extends beyond to form a magical dagger.";
		    return str;
			break;
	  case 4:
	        str = "Pulsing rapidly, the crystal in the hilt of the "
               +"anelas focuses bright green spectral energy down "
               +"the center of the bone hilt with such intensity "
               +"that your eyes cannot focus on it.\n";
            return str;
            break;
	}
    // Shouldn't get here, but just in case.	
    return "A faintly glowing crystal in the bone hilt of the anelas.\n";
}	
	
string my_short()
{
	string str;
	if (charged)
        str = "spectral green anelas";
   	else	
		str ="spectral anelas";
    return str;
}	

string my_long()
{
	string str, gem;
	
	switch (charged)
    {
	    case 0: gem ="faint";
		  break;
		case 1: gem ="flickering";
		 break;
		case 2: gem = "steady";		
	      break;
		case 3: gem = "bright";
		  break;
		case 4: gem = "pulsing";
		  break;
		default:
		 gem = "faintest";
	}	 
		
	str = "Once the possession of a spectral guardian, the blade "
        +"of this anelas is comprised entirely of spectral energy " 
        +"whose source is a large crystal with a "+ gem +" glow in "
	    +"the cupped end of the bone hilt. The greenish glow is "
		+"channeled down through the center of the bone, flat and "
		+"wide, and tapers to an infinitessimal point. Obviously "
		+"magical in nature, it is doubtful that anything this " 
		+"blade encounters will be able to resist its power. " 
		+".\n";
	
    return str;
	
}

string exa_hilt()
{
	string str;
	if (charged)
	{
		str = "The hilt of this anelas is made from the bone of "
		    +"an unknown but probably powerful magical creature. "
		    +"It has been inscribed with arcane symbols which glow "
		    +"with the same greenish tint as the spectral blade "
		    +"that extends beyond the guard for a length about "
		    +"that of your forearm.\n";
    }
	else
		str = "It is a hilt made from a bone. There are arcane symbols "
	        +"carved into it, and the pommel is really the end of the "
            +"bone with a large crystal set into the cupped end.\n";		
	
	return str;
			
}

string exa_pommel()
{
    string str;
    str = "This pommel is the joint-end of the bone "
		+"that the hilt was made from. There is a very large "
	    +"crystal inset in the cupped knuckle area.\n";
    
    return str;
}

string exa_symbols()
{
    string str;
	if (charged)
        str = "They glow with greenish spectral energy.\n";
	else
		str = "\n";
	
	return "The arcane symbols carved into the hilt are completely "
	    +"foreign to you. " +str;	
}

void config_it()
{
	if (!charged)	   
        remove_adj(({"glowing", "spectral", "green"}));
	else
        set_adj(({"glowing", "spectral", "green"}));
	
    
    if (charged) // max 40/40 at fully charged.
    {
        set_hit(36 + charged); 
        set_pen(36 + charged);
        wielder->update_weapon(this_object());
        return;
    }
    set_hit(1);
    set_pen(1);
	if (wielder)
        wielder->update_weapon(this_object());
    
    recharge_time = time() + RECHARGE_DELAY;
    set_alarm(itof(RECHARGE_DELAY), 0.0, recharge_weapon);
}

public void recharge_weapon()
{
 // put catch_msg in here about it being recharged.
    charged = 4;
    recharge_time = 0;
    config_it();
    // since it won't be wielded while it's recharging, need to send
	// the message to the living in whose inventory it is.
	if (living(ENV(TO)))
		(ENV(TO))->catch_msg("The large crystal on the spectral anelas "
	      +"suddenly begins pulsing bright green!\n"); 
		
  
}

public void set_weapon_hits(int hits)
{
    if (charged > 0 && !random(1))
    {
        charged--;
        config_it();
		if (wielder)
		    wielder->catch_msg("The large crystal on the spectral anelas "
		        +"seems to dim a bit.\n");
    }
    ::set_weapon_hits(hits);
}

	
void create_weapon()
{
    set_name("_Avenir_spectral_dagger");    
    add_name(({"anelas", "anlace", "knife", "dagger", "blade", "hilt"}));
	add_adj("bone");
    set_long(my_long);
	set_short(my_short);
	config_it();
	set_keep(1);
	set_wt(W_KNIFE);
    set_wf(this_object());	
    set_hands(W_ANYH);	
	set_hit(36 + charged); // calling update_weapon in the living when hit/pen change.
    set_pen(36 + charged);
	set_dt(W_SLASH | W_IMPALE); 
	add_prop(OBJ_I_IS_MAGIC_WEAPON , 1);  
 	add_prop(MAGIC_AM_MAGIC, ({"death", 90}));
//	add_prop(MAGIC_AM_ID_INFO,
// 	add_prop(OBJ_S_WIZINFO,
	add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(36, 36) * 2);
	add_prop(OBJ_I_WEIGHT, 1000); // Very lightweight: It's a bone and a crystal.
	add_prop(OBJ_I_VOLUME, 1000); // Energy dagger. Not much volume to it.

    /* Setting these to zero. The cool-down period of the blade means
     * it cannot be continuously used. Since the blade is spectral energy
     * not physical matter it doesn't make sense for these to happen as
	 * rapidy as for "normal" weapons.
     */	 
	set_likely_break(0);
    set_likely_dull(0);
    set_likely_corr(0);    

	add_item(({"hilt", "bone hilt"}), "@@exa_hilt");
	add_item(({"pommel"}), "@@exa_pommel");
	add_item(({"crystal"}), "@@crystal_state");
	add_item(({"arcane symbols"}), "@@exa_symbols"); 
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
	
    /* If the energy is exhausted its just an empty hilt */
    if (!charged)
	    return "Wielding a bladeless hilt is a worthless endeavor.\n";
	
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
	
    /* Do I have the skills needed? */
    if (TP->query_skill(SS_WEP_KNIFE) <= 54)
	{
		return "You lack the level of skill needed to wield "
		    +"the "+ short() +"\n";
	}
	      
    /* All checks have passed, proceed with wielding */
    TP->catch_tell("Your fingers curl around the bone grip of the "+ 
	    short() +". The spectral energy begins running a slow loop "+
		"up and down your arm.\n");
    say(QCTNAME(TP)+" grips the "+ short() +".\n");
	
	/* Add wield penelty and property */
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

public void init_recover(string arg)
{
    string foobar;
  
    sscanf(arg, "%s#CHG#%d#TIME#%d#%s",
        foobar, charged, recharge_time, foobar);
  
    if (recharge_time < time() && !charged)
    {
        recharge_weapon();  
    } 
    else if (!charged)
    {
        set_alarm(itof(recharge_time-time()), 0.0, recharge_weapon);
    }

    ::init_recover(arg);
}

public string query_recover()
{
    return ::query_recover() + "#CHG#" + charged +
        "#TIME#" + recharge_time + "#";
}
