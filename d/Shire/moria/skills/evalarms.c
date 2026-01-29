/*
 * Evaluation of Armours.
 */

#include "defs.h"
#include <wa_types.h>
#include <composite.h>
#include <language.h>
#include <stdproperties.h>

#define RATIO_STR(a,b) ("/d/Shire/imladris/lib/extra"->ratio_str(a, b))

mapping type_map =
    ([ A_SHIELD : "shield",
       A_TORSO	: "torso protecting",
       A_HEAD	: "head covering",
       A_LEGS	: "leg coverings",
       A_R_ARM	: "right greaves",
       A_L_ARM	: "left greaves",
       A_ROBE	: "robe/cloak",
       A_MAGIC	: "magical/special",
       A_NECK	: "neck protecting",
       A_WAIST	: "waist protecting",
       A_ARMS	: "greaves",
       A_R_FINGER: "finger protective",
       A_L_FINGER: "finger protective",
       A_FINGERS: "finger protective",
       A_FEET	: "feet covering",
       A_TORSO | A_ARMS | A_LEGS : "body protecting",
       A_TORSO | A_ARMS | A_LEGS | A_HEAD : "full body protecting",
       A_TORSO | A_LEGS : "torso/legs protecting",
       A_TORSO | A_ARMS : "torso/arms protecting",
       A_TORSO | A_ARMS | A_HEAD : "upper body and head protecting"
    ]);

mapping slots_map = ([	
    TS_TORSO : "torso",
    TS_HEAD  : "head",
    TS_LEGS  : "legs",
    TS_RARM  : "right arm",
    TS_LARM  : "left arm",
    TS_ROBE  : "outer covering",
    TS_RHAND : "right hand",
    TS_LHAND : "left hand",
    TS_RWEAPON : "right weapon arm",
    TS_LWEAPON : "left weapon arm",
    TS_RFOOT : "right foot",
    TS_LFOOT : "left foot",
    TS_WAIST : "waist",
    TS_NECK  : "neck",
    TS_LFINGER : "left finger",
    TS_RFINGER : "right finger"
]);

string
type_desc(object arm)
{
    string type;

    type = type_map[arm->query_at()];
    if(stringp(type))
	return type;
    else
	return "unknown";
}

int *
occupies(object arm)
{
    int at = arm->query_at();
    int i;
    int *ret = ({});
    
    if (arm->query_worn())
	return arm->query_slots();

    if (at == A_SHIELD)
    {
	if (TP->query_armour(W_LEFT) == 0)
	    at = W_LEFT;
	else if (TP->query_armour(W_RIGHT) == 0)
	    at = W_RIGHT;
	else
	    return ({ -1 });
    } else if (at == A_ANY_FINGER) {
	if (TP->query_armour(A_L_FINGER) == 0)
	    at = A_L_FINGER;
	else if (TP->query_armour(A_R_FINGER) == 0)
	    at = A_R_FINGER;
	else
	    return ({ -2 });
    }

    for (i = TS_TORSO; i <= at; i *= 2)
    {
	if (at & i)
	    ret += ({ i });
    }

    return ret + ({});
}

string
slots_desc(object arm)
{
    int *slots = occupies(arm);
    int i;
    string *ret = ({});

    for (i=0; i<sizeof(slots); i++)
	ret += ({ slots_map[slots[i]] });

    return COMPOSITE_WORDS(ret);
}

string
protects_desc(object arm)
{
    int *slots;
    int i;
    string *ret = ({});

    if (arm->query_prop(OBJ_I_IS_MAGIC_ARMOUR))
	slots = arm->query_shield_slots();
    if (!sizeof(slots))
	slots = arm->query_protects();
    if (!sizeof(slots))
	slots = occupies(arm);

    for (i=0;i<sizeof(slots);i++)
	ret += ({ slots_map[slots[i]] });

    if(!sizeof(ret))
	return 0;
    else
	return COMPOSITE_WORDS(ret);
}

string
how_good(int good)
{
    switch(good/10)
    {
	case 0: return "some";
	case 1: return "fair";
	case 2: return "proper";
	case 3: return "superb";
	case 4: return "extreme";
	case 5: return "exceptional";
	case 6: return "magical";
	case 7: return "superior magical";
	case 8: return "phenomonal";
	case 9: return "supernatural";
	default: return "godly";
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
 * The core of this object. It calculates the seen armour class for
 * this_player(). It is made with random's based on seed. The same
 * player will always get the same answer when evaluate a certain
 * object, since the seed is based on the players name (sum of ascii
 * values) and the objects filename (also summed). The error will 
 * always be in the range +/- 5 AC. An unwise and unskilled 
 * player will have an +/- 50 AC error. 
 */
int
calculate_ac(object arm)
{
    int seed_player, seed_object;
    int seed, skill, ac, ac_deviation;

    ac = arm->query_ac();

    skill = (40 * TP->query_skill(SS_APPR_OBJ) + 
	     40 * TP->query_stat(SS_WIS) +
	     30 * TP->query_skill(SS_EVAL_ARM)) / 100;

    if (skill > 100)
	skill = 100;
    if (skill < 0)
	skill = 0;

    seed_player = checksum(TP->query_name()); // The players checksum.
    seed_object = checksum(MASTER_OB(arm));   // The filenames checksum.    
    seed = seed_player + seed_object;

    skill = 55 - skill/2;                            /* Min:  5  Avg. 25 Max: 55 */
    ac_deviation = MAX(random(skill, seed), 5);      /* Min:  5  Avg. 25 Max: 55 */

    if (ac < ac_deviation)
	ac = ac_deviation + 1; /* So that a AC 1 with 10 deviation is really AC 11 +/- 10. */
    
    ac = ac + ((random(200, seed)-100) * ac_deviation) / 100;
    /*
     * This will make the same random number on each check with the result being:
     *
     *   ac = ac +/- random ac_deviation. 
     *
     */
    return ac;
}


varargs string
ac_desc(object arm, object arm2)
{
    int ac = calculate_ac(arm);
    int ac2;

    if (!arm2)
    {
	return "it will protect you " + RATIO_STR(ac, 1 + random(10, checksum(TP->query_name()))) +
	       " better than using no armour.";
    }
    else
    {
	ac2 = calculate_ac(arm2);
	return LANG_THESHORT(arm) + " will protect " + RATIO_STR(ac, ac2) +
	       " as much as " + LANG_THESHORT(arm2) + ".";
    }
}

string
mod_good(int mod)
{
    if (mod<-4)
	return "pathetically";
    if (mod>4)
	return "excelently";
    switch(mod)
    {
	case -4: return "miserably";
	case -3: return "poorly";
	case -2: return "badly";
	case -1: return "unsatisfactory";
	case 0:  return "normally";
	case 1:  return "fairly well";
	case 2:  return "adequately";
	case 3:  return "quite well";
	case 4:  return "very well";
    }
}

string
mod_desc(object arm)
{
    int *mods = arm->query_am();
    string str;

    if (sizeof(mods)!=3)
	return "It protects equally against different hit types.";

    if (mods[0] == mods[1] && mods[1]==mods[2])
	return "It protects " + mod_good(mods[0]) + " against " +
	       "all puncture, slashing and crushing attacks.";

    str = "Comparing against it's overall quality, it recieves "
	+ "puncture hits " + mod_good(mods[0])
	+ ", slashing attacks " + mod_good(mods[1])
	+ ", and crushing attempts " + mod_good(mods[2]) + ".";

    return str;
}

string eval_arms(object arm)
{
    int ac = calculate_ac(arm);
    int at = arm->query_at();
    string good = how_good(ac);
    string type = type_desc(arm);
    string str = "";
    string prots, slots;
    int worn = (arm->query_worn() == TP);

    str += CAP(LANG_THESHORT(arm)) + " is " + LANG_ADDART(type_desc(arm))
	 + " type of armour. ";

    str += "It gives the wearer " + good + " protection. ";
    str += "In fact, you would estimate that " + ac_desc(arm) + " ";
    str += mod_desc(arm) + " ";

    slots = slots_desc(arm);
    prots = protects_desc(arm);

    str += CAP(LANG_THESHORT(arm));

    if (!strlen(slots) && !strlen(prots)) {
	if (at == A_SHIELD)
	    str += " will occupy one of your arms if you wear it";
        else if (at == A_ANY_FINGER)
	    str += " can be worn on a finger";
    } else if (slots == prots) {
	if (worn)
	    str += " occupies and protects your " + slots;
        else
	    str += " will occupy and protect the " + slots + " of the wearer";
    } else {
	if (worn)
	    str += " occupies your";
        else if (at == A_SHIELD)
	    str += " will occupy one of the arms";
        else if (at == A_ANY_FINGER)
	    str += " can be worn on a finger";
        else
	    str += " will occupy the";
	str += " " + slots;

	if (worn)
	    str += ", but it protects the " + prots ;
	else
	    str += " of the wearer, but it will protect the " + prots;
    }

    if (at == A_MAGIC)
	str += " and it seems to possess some special or magical abilities";
    
    return str + ".\n";
}
