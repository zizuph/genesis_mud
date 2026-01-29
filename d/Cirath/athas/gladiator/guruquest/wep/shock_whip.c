/* A magical, shocking whip.

   Code (c) April 2002 to Damian Horton, BKA Casimir.
*/

#pragma strict_types
#pragma save_binary

#include "/sys/wa_types.h"
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Cirath/defs.h"

inherit "/std/weapon";
inherit CIRATH_DIR + "/lib/pct_hurt";
inherit CIRATH_DIR + "/lib/element_damage";
void create_weapon()
{
    set_name("whip");
    add_name("club");
    set_short("long electrified whip");
    set_long("Little bolts of blue electricity course frequently along this "+
	     "five metre length of black leather. The beautifully carved "+
	     "ivory handle shows no sign of being electrified, however.\n");

    set_adj ("long");
    add_adj ("electrified");

    set_hit(51);
    set_pen(8);

    set_wt(W_CLUB);
    set_dt(W_SLASH);
    set_hands(W_ANYH);

    likely_dull = 0;
    likely_corr = 3;
    likely_break = 5;
    set_keep(1); //the weapon is kept by default

    add_prop(OBJ_I_WEIGHT, 1975);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(51, 8) * 2 -  random(100));
    add_prop(OBJ_I_VOLUME, 2150);
 
    add_prop(OBJ_I_IS_MAGIC_WEAPON,1);
    add_prop(MAGIC_AM_MAGIC,( {35, "enchantment"}));
    add_prop(MAGIC_AM_ID_INFO, ({"This whip has been imbued with magical "+
				   "lightning. \n", 10, "The weapon had to "+
				   "be magically enhanced first.\n", 25}));

    //magic resistances
    add_prop(OBJ_I_RES_FIRE, 50);
    add_prop(OBJ_I_RES_COLD, 50);
    add_prop(OBJ_I_RES_ELECTRICITY, 100);
    add_prop(OBJ_I_RES_ACID, 20);

    add_prop(OBJ_S_WIZINFO, "Players with inadequate club skill will have a "+
	     "tendancy to hit themselves with this weapon. It does 10 - 109 "+
	     "extra lightning damage with each strike.\n");
    set_wf(TO);
}


/*
 * Function name: try_hit
 * Description:   Called from living when weapon used.
 * Arguments:     target - Who I intend to hit.
 * Returns:       False if weapon miss. If true it might hit.
 *
 * Modified since this weapon might miss if the wielder is not sufficiently
 * skilled. In fact, it might hit the wielder!
 */
int try_hit(object target) 
{
    int miss_chance, skill, phurt;
    string damage;

    //sanity check, automatically miss if there is no wielder
    if (! wielder) return 0;
    
    miss_chance = 50;//base 50% chance of hitting self,
                         //this chance drops drastically with skill
                         //to 0 at superior professional skill.

    skill = wielder->query_skill(SS_WEP_CLUB);
    if (skill < 30) 
    {
	miss_chance = miss_chance - skill;
    }
    else 
    {
	miss_chance = 20 - (((skill - 30) /2));
    }
    
    if (random(100) < miss_chance)
    {
	//we struck ourselves with the whip
	phurt = element_damage(wielder, OBJ_I_RES_ELECTRICITY,
			       10 + random(100), 0);
	//such a manoever might be fatal!!!
	if (wielder->query_hp() < 1)
	{
	    wielder->catch_tell("Your inept handling of the long "+
				"electrified "+ 
				"results in you being thoroughly tangled "+
				"in it. Unfortunately, the electric shocks "+
				"cause you to pass out before you can free "+
				"yourself...\n");
	    wielder->do_die(TO);
	}

	//it wasn't fatal...;
	wielder->catch_tell("You accidentally strike yourself, instead of "+
			    "your foe with the long electrified whip!\n"+
			    "You are shocked by the whip!\n");
	tell_room(ENV(wielder), QCTNAME(wielder) + " accidentally strikes "
		  + HIM_HER(wielder) + "self with the long electrified whip!\n"+
		  CAP(HE_SHE(wielder)) + " is shocked by it!\n");
	return 0;
    }

    //we strike with the whip as normal
    return 1;
}

//do additional electrical damage with each hit...note that with a pen of ]
//8, we are probably not doing anymore. 10 - 110 electrical damage is dealt
//per hit
int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit,
	int dam)
{
    int new_phurt; //percentage hurt including electrical damage

    //we might have missed with the weapon, in which case do no additional
    //damage, but we will still print our own miss messages
    if (phurt = -1)
    {
	if (interactive(enemy))
	{
	    enemy->catch_msg("The hair on your " + hdesc + " stands on end "+
			     "as " + QTNAME(wielder) + "'s long electrified "+
			     "whip whips past you.\n");
	    wielder->catch_msg("You miss " + QTNAME(enemy) + " with your "+
			       "long electrified whip.\n");
	    wielder->tell_watcher(QCTNAME(wielder) + " misses " +
				  QTNAME(enemy) + " with " + HIS_HER(wielder) +
				  "long electrified whip.\n", enemy, enemy);
	}
	return 1; //we handled messages, dont need to do anymore
    }

    //do additional electrical damage to our foe!
    new_phurt = element_damage(enemy, OBJ_I_RES_ELECTRICITY, 10 + random(100),
			       0);

    //display default messages if the enemy is only being minimally affected
    //by the electricity
    if (enemy->query_magic_res(OBJ_I_RES_ELECTRICITY) > 75)
    {
	return 0;
    }

    //from here on we print special messages!
    
    //calculate the percentage hurt, including regular and electrical damage
    new_phurt += pct_hurt(dam, enemy);

    if (interactive(wielder))
    {
	switch (new_phurt)
	{
	case 0..10:
	    wielder->catch_msg("The long electrified whip shocks "
			       + QTNAME(enemy) + "'s " + hdesc + ".\n");
	case 11..25:
	    wielder->catch_msg(QCTNAME(enemy) + " jumps as the long "+
			       "electrified whip strikes " + HIS_HER(enemy) +
			       hdesc + "!\n");
	case 26..50:
	    wielder->catch_msg("You electrocute " + QTNAME(enemy) + "'s " + 
			       hdesc + " with your long electrified whip!\n");
	default:
	    wielder->catch_msg("You wrap your long electrified whip around "+
			       QTNAME(enemy) + "'s " + hdesc + ". The stench "+
			       "of charred flesh reaches your nostrils as "+
			       "wisps of smoke rise from " + HIS_HER(enemy) + 
			       " flesh!\n");
	}
    }
    
    if (interactive(enemy))
    {
	switch(new_phurt)
	{
	case 0..10:
	    enemy->catch_msg(QCTNAME(wielder) + "'s long electrified whip "+
			     " shocks you as it strikes your " + hdesc + 
			     ".\n");
	case 11..25:
	    enemy->catch_msg("The jolt of electricity which courses "+
			       "through you when " + QTNAME(wielder) + 
			       "strikes your " + hdesc + " with " + 
			       HIS_HER(wielder) + " long electrified whip causes "+
			       "you to jump involountarily.\n");
			       
	case 26..50:
	    enemy->catch_msg(QCTNAME(wielder) + " electrocutes your " +
			       hdesc + " with " + HIS_HER(wielder) + " long "+
			       "electrified whip!\n");
	case 51..99:
	    enemy->catch_msg(QCTNAME(wielder) + " wraps " + HIS_HER(wielder) + 
			       " long electrified whip around your " + hdesc +
			       "! Jolts of electricity course through your "+
			       "body, causing your flesh to smolder!\n");
	default:
	    enemy->catch_msg(QCTNAME(wielder) + " wraps " + HIS_HER(wielder) +
			       " long electrified whip around your " + hdesc +
			       "! Jolts of electricity overwhelm you, "+
			       "causing your heart to stop!!!\n\nYou lose "+
			       "counsciousness...\n\n");
	}
    }
	
    switch(new_phurt)
    {
    case 0..10:
	wielder->catch_msg(QCTNAME(wielder) + "'s long electrified whip "+
			   "shocks " + QTNAME(enemy) + "'s " + hdesc + ".\n",
			   enemy, enemy);
    case 11..25:
	wielder->tell_watcher(QCTNAME(enemy) + " jumps as " + QCTNAME(wielder) +
			   "'s long electrified whip strikes " + HIS_HER(enemy) +
			   hdesc + "!\n", enemy, enemy);
    case 26..50:
	wielder->tell_watcher(QCTNAME(wielder) + "  electrocute " + 
			   QTNAME(enemy) + "'s " + 
			   hdesc + " with " + HIS_HER(wielder) + " long "+
			   "electrified whip!\n", enemy, enemy);
    default:
	wielder->tell_watcher(QCTNAME(wielder) + "  wraps " + HIS_HER(wielder) + 
			   "long electrified whip around "+
			   QTNAME(enemy) + "'s " + hdesc + ". The stench "+
			   "of charred flesh reaches your nostrils as "+
			   "wisps of smoke rise from " + HIS_HER(enemy) + 
			   " flesh!\n", enemy, enemy);
    }
    return 1; //we handled combat messages
}
    

















