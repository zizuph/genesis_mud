#pragma strict_types
// Akram's Dagger       /d/Avenir/union/obj/akram_dagger.c
// creator(s):           Lilith, Nov 2003
// based upon:           /d/Genesis/genesis/doc/examples/weapons/elf_slayer
// purpose:              reward for post-guru quest in the Union
// notes:                This is a copy of Akram's Dagger, made specially
//                       for Tornu by Hephamenios the Weaponsmith.
//                       This is a magical knife with 35/40 hit/pen.
//                       It is cloned by /d/Avenir/union/npc/hephamenios
//                       The unwielded short() bears the name of the one 
//                       for whom it was made.
//                       Dagger set to recover after first made.
//         Requirements: Wielder must be a Union member who has completed
//                       guru quest.
//            Drawbacks: Wielder cannot be intoxicated, thus player heals 
//                       more slowly. -10 to Union skill SWAY.
//                       Takes 1/5 of max fatigue when unwielded.
//              Effects: SS_2H_COMBAT +10; MAGIC_DT special to infidels.
/*
 * Revisions:
 * 	Lilith, Jul 2004: Added strlen check to config owner, to address problem
 * 			  with 's daggers.
 *  	Lilith, Mar 2015: Updated intox check.
 *  	Lucius, Jul 2017: Minor fixups.
 */
inherit "/std/weapon";
inherit "/lib/keep";
inherit "/d/Genesis/magic/resist";

#include "../defs.h"
#include "/d/Avenir/include/macros.h"
#include "/d/Avenir/include/deities.h"

#include <tasks.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>

#define WIELD_PROP "_union_wield_akram"
#define CLONE_LOG  "/d/Avenir/log/misc/a_dagger"

private string owner;
private int p_bonus = 0, s_bonus = 0;


/* Prototypes */
public string query_owner(void)		{ return owner; }  
public void   set_owner(string str)	{ owner = str;  }  

public string
test_owner()
{
    object tp = environment();
    string trn = tp->query_real_name();

    if (!query_owner())
	return "someone";
    if (trn == query_owner())
	return "you";
    else
	return capitalize(query_owner());
}

public string
my_short(void)
{
    if (query_wielded())
	return "ukku dagger";
    if (!query_owner())
	return "Akram's dagger";
    else
	return capitalize(query_owner()) +"'s dagger";         
}

private void 
config_owner(void)
{
    if (!strlen(owner))
	owner = "akram";

    set_owner(owner);
    add_adj(owner);
    add_adj(owner +"'s");   
}

public void
create_weapon()
{
    set_name("_akram_dagger");
    add_name(({"dagger", "weapon"}));
    set_adj("ukku");
    add_adj(({"damask", "steel", "union", "akram"}));
    set_short(my_short);
    set_long("This weapon was made in the style of Akram's dagger "+
      "especially for @@test_owner@@. "+
      "The steel of this dagger has been forged at a low "+
      "temperature, pounded thin and folded repeatedly, giving "+
      "it both the great strength and the wavy surface pattern "+
      "that is characteristic of ukku. The dagger-and-sphere "+
      "pattern, which looks like tiny serpentine knives "+
      "alternating with little spherical rosettes, is known "+
      "to be produced only by master weaponsmiths of the "+
      "Shadow Union. The blade is nearly long enough to classify "+
      "this dagger as a short-sword, and both edges are keen enough "+
      "to part silk under its own weight. Designed for use in "+
      "close combat, this weapon has an extra-long grip made "+
      "from the bone of a worthy enemy. "+
      "The hilt is inscribed with platinum glyphs that writhe and "+
      "flow before your eyes.\n");

    set_wf(this_object());   

    add_item(({"grip", "hilt", "bone" }),
      "Yellow and smooth as ivory, the hilt is made from the "+
      "bone of a monstrous ogre. In order to take magical "+
      "advantage of the strength inherent to the bone, glyphs "+
      "have been cut into it, and filled with platinum.\n");
    add_item(({"glyphs", "dagger glyphs", "platinum glyphs", 
	"bone glyphs", "glyphs on the hilt"}),
      "Glyphs have been inscribed into the old bone "+
      "from which the hilt was made. You cannot decipher them "+
      "but their meaning is clear: invocation of magic, and "+
      "very potent magic, at that.\n");      
    add_item(({"wavy lines", "wavy pattern", "dagger-and-sphere pattern",
	"pattern", "akram pattern", "ukku", "blade", "rosettes"}),
      "The wavy dagger-and-sphere pattern created during the "+
      "forging process is very distinctive. It identifies "+
      "the maker as a weaponsmith of the Union, and the material "+
      "as ukku steel. \n");

    set_hit(35);
    set_pen(40);
    set_hands(W_RIGHT);  
    set_wt(W_KNIFE);
    set_dt(W_IMPALE);
    set_likely_break(0);
    set_likely_dull(0);
    set_keep(1);

    add_prop(OBJ_M_NO_STEAL, "That which the Gods have provided "+
      "to one person cannot be stolen by another.\n");
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_WEIGHT, 1000); 
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(35, 40) * 3); /* Magical */

    /* Designate this as a magic weapon */
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 80, "transformation" }));
    add_prop(MAGIC_AM_ID_INFO, ({ 
	"The one for whom this dagger was made passed many tests\n", 10,
	"and was proven worthy of such a reward.\n", 20,
	"By grace of Jazur, those priviledged to wield it\n", 30,
	"may find increased skill with two-handed combat,\n", 40,
	"as well as special damage to Enemies of Sybarus.\n", 50}));

    /* Let wizards know what the knife does */
    add_prop(OBJ_S_WIZINFO, "This knife raises 2H COMBAT by 10 levels, "+
      "not to exceed 100. "+
      "It has a special that does MAGIC_DT against "+
      "Enemies of Sybarus: ogres, dark elves, and infidels."+
      "Drawbacks: no alcohol, fatigue penelty, and "+
      "it reduces SWAY by 10 levels.\n");

    seteuid(getuid());
    SCROLLING_LOG(CLONE_LOG, short() +" was cloned.");

    set_alarm(5.0, 0.0, config_owner);
}

/*
 * Function     : wield
 * Description  : Wield a weapon
 * Arguments    : Object what - The weapon to wield
 * Returns      : string - error message (weapon not wielded)
 *                1 - success (weapon wielded)
 */
public mixed 
wield(object what)
{
    int p, f, s;
    object tp = environment();

    /* Is it broken? If so, dont wield */
    if (query_prop(OBJ_I_BROKEN))
	return "It is broken in such a way that you cannot wield it.\n";

    if (!living(tp) || tp->query_prop(WIELD_PROP))
	return 0;

    /* I'm not a Union member, it doesn't like me */
    if (!IS_MEMBER(tp))
    {
	tp->heal_hp(-20);
	return "A dark flame engulfs your hand as you try to "+
	    "wield "+ short() +".\n"; 
    }

    /*  Must be tornu to wield */
    if (!IS_TORNU(tp))
    {
	return "Something within it resists you, probably because "+
	    "you are not yet Tornu.\n";
    }

    /* Does living have alcohol level? If so, don't wield */    
    if (tp->query_intoxicated() > 10)
	return "You are too intoxicated.\n";

    tp->catch_tell("As you wield the ukku dagger a tide of passion "+
      "rises within you, as if called forth by Jazur herself.\n");
    say(QCTNAME(tp)+"'s eyes flash with dark emotion as "+
      tp->query_pronoun() +" wields "+ short() +".\n");

    SCROLLING_LOG(CLONE_LOG, capitalize(tp->query_real_name()) +
      " wielded "+ short());

    if (!tp->query_prop(WIELD_PROP))
    {
	p = tp->query_skill(SS_2H_COMBAT);
	p_bonus = 100 - p;
	if (p_bonus > 10)
	    p_bonus = 10;
	else if (p_bonus < 0)
	    p_bonus = 0;       

	s_bonus = 10;

	tp->add_prop(WIELD_PROP, 1);

	tp->set_skill_extra(SS_2H_COMBAT,
	    tp->query_skill_extra(SS_2H_COMBAT) + p_bonus);
	/* Cost to sway for the benefits, they draw from the
	   flame and Jazur to gain the above */
	tp->set_skill_extra(SS_SWAY,
	    tp->query_skill_extra(SS_SWAY) - s_bonus);
    }

    return 1;
}

/* 
 * Function    : unwield
 * Description : Unwield a weapon
 * Arguments   : object wep - the weapon to unwield
 */
public mixed 
unwield(object wep)
{
    object owner = query_wielded();

    if (owner->query_prop(WIELD_PROP))
    {
	owner->set_skill_extra(SS_2H_COMBAT,
	    owner->query_skill_extra(SS_2H_COMBAT) - p_bonus);
	/* Benefits go away, they get sway back */
	owner->set_skill_extra(SS_SWAY,
	    owner->query_skill_extra(SS_SWAY) + s_bonus);
    }

    owner->remove_prop(WIELD_PROP);
    owner->add_fatigue(-(owner->query_fatigue() / 5));

    if (!interactive(environment()))
	return 0;

    owner->catch_tell("The passion coursing through you abates as "+
      "you unwield the ukku dagger.\n");

    return 0;
}

/*
 * did_hit() is called whenever the weapon is used.  We redefine it
 * to do extra damage when we hit an ogre, dark elf or infidel.
 * This special is similar to the one in the falcata, only it does
 * about half the damage.
 */
public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt,
    	int phit, int dam)
{
    object wielder = query_wielded();
    string Name = QCTNAME(wielder);
    string enem = QTNAME(enemy);
    string his = wielder->query_possessive();
    string knife = short();
    int resistance;

    /* did_hit() is called even when the weapon misses, so we need
     * to check if phurt < 0 before we do any special damage.  If
     * phurt < 0, then it was a missed attack.
     */
    if (phurt < 0)
	return ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);

    /* We only want to do the special damage if the target is 
     * infidel, ogre, or dark elf, 1 in 5 attacks.
     */
    if (!random(5) && enemy->query_race() == "ogre" ||
	enemy->query_race() == "dark elf" ||
	ENEMY(enemy) || IS_INFIDEL(enemy))
    {
	wielder->catch_msg("A wave of passionate blood-lust "+
	  "surges through you as your dagger penetrates deep into "+ 
	  enem +"'s flesh.\n"); 
	wielder->tell_watcher(Name +" flushes with a passion akin to blood-"+
	  "lust.\n", enemy);
	enemy->catch_tell(knife +" pulses with blood-lust as it "+
	  "penetrates your flesh.\n");

	/* Check the target's magic resistance */
	resistance = spell_resist_basic(this_object(), enemy,
	    SS_ELEMENT_DEATH, TASK_DIFFICULT);

	/* Do the extra damage, taking the magic resistance into account */
	enemy->hit_me(100 * (100 - resistance) / 100, MAGIC_DT, wielder, -1);

	/* Kill the target, if appropriate */
	if (enemy->query_hp() <= 0)
	{
	    query_wielded()->catch_msg("Your ukku dagger throbs in your "+
	      "hand as it absorbs "+ enem +"'s soul.\n");
	    wielder->tell_watcher(Name +" quenches "+ his +" "+ knife +
	      "in "+ enem +"'s flesh.\n", enemy);
	    enemy->catch_msg(Name +" quenches "+ his +" "+ knife +
	      "in your flesh, feeding it with your spirit.\n");
	    enemy->do_die(wielder);
	}
    }

    return ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
}

/*
 * Function name: query_recover
 * Description  : Called to check whether this weapon is recoverable.
 *                If you have variables you want to recover yourself,
 *                you have to redefine this function, keeping at least
 *                the filename and the weapon recovery variables, like
 *                they are queried below.
 *                If, for some reason, you do not want your weapon to
 *                recover, you should define the function and return 0.
 * Returns      : string - the default recovery string.
 */
public string
query_recover()
{
    return MASTER + ":#OWNER#" + owner + "#NONE#" +
	query_wep_recover();
}

/*
 * Function name: init_recover
 * Description  : When the object recovers, this function is called to set
 *                the necessary variables. 
 * Arguments    : string argument - the arguments to parse
 */
public void
init_recover(string arg)
{
    sscanf(arg, "#OWNER#%s#NONE#%s", owner, arg);
    init_wep_recover(arg);
}
