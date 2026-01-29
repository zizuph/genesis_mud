// file name:    ~Terel/unique/wasp.c
// creator(s):   Lilith, Jan 2022
// purpose:      A second magical knife for Benton the Cannibal Corpse
//               It is basically a cleaver + bonesaw. 
// note:         did_hit has a chance of adding a stinging wound to the enemy.
//               The sting is cosmetic but when it is added, the enemy
//               will get LIVE_I_ATTACK_DELAY added only if there isn't
//               already one in effect.
//
//               Wasp's "stings" can be avoided by wearing the ring of 
//               the ancients (~Terel/common/moor/obj/safe_ring) and
//               reading its runes.
// updates:    Lilith Mar 2022: made kept, reduced break/corr
//
//   THIS WAS DEPRECATED BY LILITH JUNE 2022 AND SHOULD BE DELETED ONCE 
//   THERE ARE NO MORE CLONES IN THE GAME.
//   IT HAS BEEN REPLACED WITH wasp_sword.ca


inherit "/std/weapon";

#include <wa_types.h>   
#include <macros.h>     
#include <filter_funs.h>
#include <formulas.h>   
#include <stdproperties.h>

// This prop is added to the player by the ring of the ancients.
// It provides protection against this weapon's special effect.
#define RUNES_REVEALED "_terel_ring_runes_revealed"
#define STING   "/d/Terel/unique/wasp_sting"
#define ME(x)   if(interactive(wield)) wield->catch_msg(x + ".\n");
#define YOU(x)  if(interactive(enemy)) enemy->catch_msg(x + ".\n");
#define THEM(x) wield->tell_watcher(x + ".\n", enemy);

void
create_weapon()
{
    set_name("wasp");
    add_name(({"cleaver", "knife", "dagger", "blade", "bonesaw",
	"saw", "axeknife", "_bentons_wasp"}));
    set_short("cleaver named Wasp");
    set_adj("benton's");
    add_adj(({"ancient", "mysterious", "serrated", "forked" }));
    set_long("This is Wasp, one of the knives favored by Benton the "+ 
      "cannibal corpse. You're not sure why he calls it Wasp, "+
      "because it looks like someone took a seriously hefty "+
      "meat cleaver or axe and merged it with a saw.\n"+ 
      "   There are two small forked points on the recurved tip, "+ 
      "great for piercing skin and sinew. The thick spine of the "+
      "knife has been beveled and sharpened, while the opposite "+ 
      "edge has many large teeth, each of which is sharpened "+
      "in both directions. The wide, thick blade is made of a "+
      "mysterious alloy inscribed with powerful runes. "+
      "The handle of the cleaver looks like it was made from "+ 
      "a long bone, with grooves etched into it to improve the "+
      "grip.\n"+ 
      "   This weapon can be used for chopping, sawing, and "+
      "piercing, making it a perfect tool for field-dressing "+
      "any kill, probably even a dragon.\n");   

    add_item(({"runes", "powerful runes", "symbols"}),
      "You are unable to discern their exact meaning, but "+
      "something about their configuration is highly "+
      "disturbing.\n");

    add_item(({"configuration", "rune configuration"}),
      "The configuration of the runes on the blade "+
      "causes your mind to flash warnings about blood magick.\n");

    add_item(({"alloy", "mysterious alloy"}),  
      "It is a mysterious alloy from ancient times. The "+
      "means of crafting it was lost many generations ago.\n");

    add_item(({"handle", "bone handle", "grip", "long bone"}),
      "The handle of the cleaver looks like it was made from "+ 
      "a long bone, with grooves etched into it to improve the "+
      "grip.\n");

    // Benton is an unpleasant bugger. He should have superb weapons.
    set_default_weapon(40, 40, W_KNIFE, W_SLASH | W_IMPALE, W_RIGHT, this_object());
    set_wf(this_object());
    set_likely_dull(-10);
    set_likely_corr(-10);
    set_likely_break(-10);
    set_keep(1);

    // A really heavy cleaver is 1kg, lets double it.
    add_prop(OBJ_I_WEIGHT,  2000);  
    add_prop(OBJ_I_VOLUME,  1000); 

    // Magical items cannot be bought at a store.
    add_prop(OBJ_M_NO_BUY, 1); 	
    // Magical, so at least twice as valuable.
    add_prop(OBJ_I_VALUE, (F_VALUE_WEAPON(40, 40) * 2));
    add_prop(OBJ_S_WIZINFO, "This is Benton's 40/40 Wasp, cloned by "+
      "/d/Terel/common/moor/monster/benton at "+
      "/d/Terel/common/moor/tomb/gore_chamber. "+
      "When the phurt on did_hit is 20% or more, a 'sting' will "+
      "trigger. The sting does a short, non-additive "+
      "LIVE_I_ATTACK_DELAY. Wearing the ring of the ancients "+ 	
      "/d/Terel/common/moor/obj/safe_ring and reading the "+		
      "runes will provide protection from Wasp's stings.\n");		

    // Setting the required magical props.
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC, ({50,"enchantment"}));
    add_prop(MAGIC_AM_ID_INFO, 
      ({" Deep under a tomb dwells the cannibal corpse\n", 10,
	" Who dines on the living with knives and forks.\n", 15,
	" His hunger for flesh knows no worldly bounds\n", 20,
	" His depravity and cruelty are far reknowned.\n", 25,
	" This cleaver named Wasp you hold in your hands\n", 30,
	" Belongs to Benton who once was a man,\n", 35,
	" But now is infected with evil so deep\n", 40, 
	" His soul is corrupted and he no longer sleeps.\n", 45,
	" You will know Wasp's bite by it's terrible sting.\n", 50,
	" If its protection you want, wear the ancient ring.\n", 55
      }));

}


/* Let's get some more interesting hitlocs */
private string 
translate_hitloc(object who, string hitloc)
{
    string   str;
    /* We need to be humanoid to use this! */
    if(!who->query_humanoid() && !interactive(who))
	return hitloc;
    if(!strlen(hitloc))
	return hitloc;
    if(hitloc == "legs") // Get rid of the silly plurals
	hitloc = (random(2) ? "right" : "left") + " leg";
    if(hitloc == "head" && random(2))
	hitloc = (random(2) ? "face" : "throat");
    else if(strlen(hitloc) && sscanf(hitloc, "%s arm", str) && random(2))
	hitloc = (random(2) ? "lower " + hitloc : str + " shoulder");
    else if(strlen(hitloc) && sscanf(hitloc, "%s leg", str) && random(2))
	hitloc = (random(2) ? "lower " + hitloc : str + " thigh");
    else if(hitloc == "body" && random(2))
	hitloc = (random(2) ? "chest" : "belly");
    return hitloc;
}

/*
 * Function name: make_it_sting
 * Description:   make a wound on the enemy sting by cloning a
 *                subloc object and moving to the the enemy's
 *                inventory that adds LIVE_I_ATTACK_DELAY.
 * Arguments:     enemy  - the person the make bruised
 *                hitloc - the hitloc of the enemy
 * Returns:       0
 * Note:          
 */
private nomask void
make_it_sting(object enemy, string hitloc)
{
    object wound;

    /* Player is protected by the ring of the ancients */
    if(enemy->query_prop(RUNES_REVEALED, 1))
	return;

    /* We already have been wounded so add on to that one */
    if(wound = present("wasp_stings", enemy))
    {
	wound->add_hurt(hitloc, enemy);
	return;
    }

    /* Else clone a new one into the enemy's inventory */
    seteuid(getuid(this_object()));

    wound = clone_object(STING);
    wound->move(enemy, 1);
    wound->add_hurt(hitloc, enemy);
}


varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit,
  int dam)
{
    ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);

    object wield = query_wielded(); 
    string wep   = QSHORT(this_object()),
    me    = QCTNAME(query_wielded()), 
    targ  = QTNAME(enemy),
    hitloc;

    if (phurt == -1) 
    {
	ME("Your "+ wep +" just misses " +
	  "sawing into "+ targ);
	YOU(me +"'s "+ wep +" nearly saws into you.\n");
    }
    else if (phurt == 0) 
    {
	ME("You land a glancing blow on "+ targ +
	  " with your "+ wep);
	YOU(me +"'s "+ wep +" nearly saws into you.\n");    
    }
    else 
    {
	hitloc = translate_hitloc(enemy, hdesc);

	/* Add wound with attack delay. 
		 * The attack delay is -not- additive and 
	 * does -not- stack with other stuns.
		 * see /d/Terel/unique/wasp_sting.c
		 */
	if(random(5) == 0)
	    make_it_sting(enemy, hitloc); 

	switch (phurt)
	{
	case 0..5:
	    ME("You saw the "+ wep +" lightly against "+ targ +
	      "'s "+ hitloc);
	    YOU(me +" saws the "+ wep +" lightly against your "+ hitloc);
	    THEM(me +" saws "+ wep +" lightly against "+ targ +
	      "'s "+ hitloc);	
	    break;
	case 6..20:
	    ME("You saw the "+ wep +" firmly against "+ targ +
	      "'s "+ hitloc +", making a serious gash");
	    YOU(me +" saws the "+ wep +" firmly against your "+ hitloc +
	      ", cutting a serious gash");
	    THEM(me +" saws the "+ wep +" firmly against "+ targ +
	      "'s "+ hitloc +", cutting a serious gash");	
	    break;
	case 21..45:
	    ME("You saw the "+ wep +" vigorously back and forth against "+
	      targ +"'s "+ hitloc +", cutting a nasty gash");
	    YOU(me +" vigorously saws the "+ wep +" back and forth "+ 
	      "against your "+ hitloc +", cutting a nasty gash");
	    THEM(me +" saws the "+ wep +" vigorously back and forth "+ 
	      "against "+ targ +"'s "+ hitloc +", cutting a nasty gash");	
	    break;
	case 46..65:
	    ME("You pound "+ targ +"'s "+ hitloc +" with the "+ wep +
	      ", opening a deep, life-threatening wound");
	    YOU(me +" pounds the "+ wep +" into your "+ 
	      hitloc +", opening a deep, life-threatening wound");
	    THEM(me +" pounds "+ targ +"'s "+ hitloc +" with the "+ wep +
	      ", opening a deep, life-threatening wound");
	    break;			 
	case 66..85:
	    ME("You carve into "+ targ +"'s "+ hitloc +" with the "+ wep +
	      ", opening a deep, life-threatening wound");
	    YOU(me +" carves the "+ wep +" into your "+ 
	      hitloc +", opening a deep, life-threatening wound");
	    THEM(me +" carves into "+ targ +"'s "+ hitloc +" with the "+
	      wep +", opening a deep, life-threatening wound");
	    break;
	default:
	    ME("You chop deeply into "+ targ +"'s "+ hitloc +
	      " with the "+ wep +
	      "! There is a nauseating crunching noise as you "+
	      "cleave through flesh and bone");
	    YOU(me +" chp deeply into your "+ hitloc +" with the "+
	      wep +"! There is a nauseating crunching noise as you "+
	      "feel it cleave through flesh and bone");
	    THEM(me +" chop deeply into "+ targ +"'s "+ hitloc +
	      " with the "+ wep +
	      "! There is a nauseating crunching noise as it "+
	      "cleaves through flesh and bone");
	    break;					
	}
	return 1;		
    }

    /* shouldn't get here, but just in case, let usual damage go thru */
    return 0;

}
