/*
 * Evaluation of weapons.
 */
#include "defs.h"
#include <wa_types.h>
#include <composite.h>
#include <language.h>
#include <formulas.h>

#define RATIO_STR(a,b) ("/d/Shire/imladris/lib/extra"->ratio_str(a, b))

#define PEN_VAL 0
#define HIT_VAL 1

varargs int
calc_skill(object wep, object wep2)
{
    int weapon_skill_first;
    int weapon_skill_second;
    int evaluate_skill;
    int appraise_skill;
    int skill;

    evaluate_skill = TP->query_skill(SS_EVAL_WEP);
    appraise_skill = TP->query_skill(SS_APPR_OBJ);

    weapon_skill_first = TP->query_skill(SS_WEP_FIRST + (wep->query_wt() - W_FIRST));

    if (!wep2)
	weapon_skill_second = TP->query_skill(SS_UNARM_COMBAT);
    else
	weapon_skill_second = TP->query_skill(SS_WEP_FIRST + (wep2->query_wt() - W_FIRST));

    skill = (20 * evaluate_skill + 20 * appraise_skill + 
	     30 * weapon_skill_first + 30 * weapon_skill_second) / 100;

    if (skill <= 0)
	skill = 0;
    if (skill > 100)
	skill = 100;
    if (TP->query_wiz_level())
	write("skill = " + skill + "\n");
    return skill;
}

string
dam_type(object wep)
{
    string *str=({});

    if(wep->query_dt() & W_IMPALE)
	str += ({ "impaling" });
    if(wep->query_dt() & W_SLASH)
	str += ({ "slashing" });
    if(wep->query_dt() & W_BLUDGEON)
	str += ({ "crushing" });
    return COMPOSITE_WORDS(str);
}

string
weapon_type(object wep)
{
    switch(wep->query_wt())
    {
	case W_SWORD:
	    return "sword";
	case W_POLEARM:
	    return "pole-arm";
	case W_AXE:
	    return "axe";
	case W_KNIFE:
	    return "knife";
	case W_CLUB:
	    return "club/hammer";
	case W_MISSILE:
	    return "missile";
	case W_JAVELIN:
	    return "javelin";
	default:
	    return "unknown";
    }
}

int
checksum(string str)
{
    int i, sum = 0;
    for (i=0; i<strlen(str); i++)
	sum += str[i];
    return sum;
}

/*
 * The core of this object. It calculates the seen armour weapon for
 * this_player(). It is made with random's based on seed. The same
 * player will always get the same answer when evaluate a certain
 * weapon, since the seed is based on the players name (sum of ascii
 * values) and the objects filename (also summed). The error will 
 * always be in the range +/- 5 WC. An unwise and unskilled 
 * player will have an +/- 60 WC error. 
 */
varargs int
calculate_wc(object wep, int hit = 0, object wep2 = 0)
{
    int seed_player, seed_object;
    int seed, skill, wc, wc_deviation;

    if (hit)
	wc = wep->query_hit();
    else
	wc = wep->query_pen();

    skill = calc_skill(wep, wep2);

    seed_player = checksum(TP->query_name()); // The players checksum.
    seed_object = checksum(MASTER_OB(wep));   // The filenames checksum.    
    seed = seed_player + seed_object + hit;   // Plus hit to get another seed for the hit.

    skill = 55 - skill / 2;                          /* Min:  5  Avg: 20 Max: 55 */
    wc_deviation = MAX(random(skill, seed), 5);      /* Min:  5  Avg: 10 Max: 50 */

    if (wc < wc_deviation)
	wc = wc_deviation + 1; /* So that a WC 1 with 10 deviation is really WC 11 +/- 10. 
                                  WC20 with 40 deviation gets WC 41 +/- 40, i.e.: 1..81    */
    
    wc = wc + ((random(200, seed)-100) * wc_deviation) / 100;
    /*
     * This will make the same random number on each check with the result being:
     *
     *   wc = wc +/- random wc_deviation. 
     *
     */
    return wc;
}

varargs int
calc_hand(int hit = 0)
{
    int wc;
    int unarmed_skill = TP->query_skill(SS_UNARM_COMBAT);
    int seed;

    if (hit)
	wc = W_HAND_HIT;
    else
	wc = W_HAND_PEN;

    seed = checksum(TP->query_name()) + hit + unarmed_skill;

    if (unarmed_skill)
	wc += F_UNARMED_HIT(unarmed_skill, DEX(TP));

    wc += (random(40, seed)-20) * wc / 100;

    return wc;
}

varargs string
hit_value(object wep1, object wep2 = 0)
{
    int hit1, hit2;
    string cshort;

    hit1 = calculate_wc(wep1, HIT_VAL, wep2);

    if (!wep2)
    {
	hit2 = calc_hand(HIT_VAL);
	cshort = "your fists";
    }
    else
    {
	hit2   = calculate_wc(wep2, HIT_VAL, wep1);
	cshort = LANG_THESHORT(wep2);
    }

    find_player("rogon")->catch_msg("Player: " + TP->query_name() + "\n" +
				    "WCHIT1: " + hit1 + "  WCHIT2: " + hit2 + "\n"); 

    if(hit1 > hit2)
	return "It is " + RATIO_STR(hit1, hit2) + " easier to hit with "+
	       LANG_THESHORT(wep1) + " than using " + cshort + ".";
    else if(hit1 == hit2)
	return CAP(LANG_THESHORT(wep1)) + " and " + LANG_THESHORT(wep2) +
	       " are indifferent when concerning how easy it is to hit with.";
    else
	return "It is " + RATIO_STR(hit2, hit1) + " harder to hit with "+
	       LANG_THESHORT(wep1) + " than using " + cshort + ".";
}

varargs string
pen_value(object wep1, object wep2 = 0)
{
    int pen1, pen2;
    string cshort;

    pen1 = calculate_wc(wep1, PEN_VAL, wep2);

    if (!wep2)
    {
	pen2   = calc_hand(PEN_VAL);
	cshort = "your fists";
    }
    else
    {
	pen2   = calculate_wc(wep2, PEN_VAL, wep1);
	cshort = LANG_THESHORT(wep2);
    }

    find_player("rogon")->catch_msg("Player: " + TP->query_name() + "\n" +
				    "WCPEN1: " + pen1 + "  WCPEN2: " + pen2 + "\n"); 
    if (pen1 > pen2)
	return "The " + dam_type(wep1) + " damage inflicted by " +
	       LANG_THESHORT(wep1) + " is " + RATIO_STR(pen1, pen2) +
	       " as more severe than if you used " + cshort + ".";
    else if (pen1 == pen2)
	return "The " + dam_type(wep1) + " damage inflicted by " +
	       LANG_THESHORT(wep1) + " is as severe as " +
	       LANG_POSS(LANG_THESHORT(wep2)) + ".";
    else
	return "The " + dam_type(wep1) + " damage inflicted by " +
	       LANG_THESHORT(wep1) + " is " + RATIO_STR(pen1, pen2) +
	       " of that of " + cshort + ".";
}


varargs string
eval_weapon(object wep, object wep2)
{
    string str="";
    string wt1, wt2;

    if(!wep2)
    {
	str = "As you do not compare the weapon against another, you "
	    + "compare it against using your hands. "
	    + CAP(LANG_THESHORT(wep)) + " is "
	    + LANG_ADDART(weapon_type(wep)) + ". ";
    }
    else
    {
	if (wep == wep2)
	    return "You can't compare a weapon with itself.\n";

	wt1 = weapon_type(wep);
	wt2 = weapon_type(wep2);

	if (wt1 == wt2)
	    str += CAP(LANG_THESHORT(wep)) + " and " + LANG_THESHORT(wep2)
		 + " are both " + LANG_PWORD(wt1) + ". ";
	else
	    str += CAP(LANG_THESHORT(wep)) + " is " + LANG_ADDART(wt1)
		 + ", while " + LANG_THESHORT(wep2) + " is "
		 + LANG_ADDART(weapon_type(wep2)) + ". ";
    }

    str += hit_value(wep, wep2) + " " + pen_value(wep, wep2) + "\n";

    return str;
}
