/*
 * File Name        : stab_special_attack.c
 * By               : Elmore.
 * Inspiration from : The Neidar Guild by Arman.
 *                    Occ_fighter Guild by Unknow.
 * Date             : Nov. 2000.
 * Description      : Contrains the special attack for the pirates
 *                    guild.
 *
 */

#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"

/* A global variable to hold the id for the alarm used for the special */
static private int stab_alarm = 0;

/* Prototypes */
void stab2(object target);

/*
 * Function name: can_attack_with_lay_special
 * Description:   See if we are allowed to attack someone
 * Arguments:     object target - the thing we want to attack
 *                string attack - a name for the attack we want to use
 * Returns:       A string describing why we cannot attack or 0 if
 *                we can attack
 */
mixed
can_attack_with_lay_special(object target, string attack)
{
    mixed why;
    object who = query_shadow_who();

    if (!target || !living(target) || !present(target, environment(who)))
    {
	return attack + " whom?\n";
    }

    if (who->query_prop(LIVE_I_ATTACK_DELAY) ||
      who->query_prop(LIVE_I_STUNNED))
    {
	return "You are too stunned to " + attack + ".\n";
    }

    if (stringp(why = target->query_prop(OBJ_M_NO_ATTACK)) ||
      stringp(why = environment(target)->query_prop(ROOM_M_NO_ATTACK)))
    {
	return why;
    }
    else if (why)
    {
	return "You sense a force protecting " + 
	target->query_the_name(who) + ".\n";
    }

    /* Someone might try defining this to block all special attacks */
    if (target->query_not_attack_me(who, -1))
    {
	/* A message should be given by query_not_attack_me(), so
	 * no need to specify one here.
	 */
	return "";
    }

    if ((!who->query_npc()) && (who->query_met(target)) &&
      !(who == target->query_attack()) &&
      (who->query_prop(LIVE_O_LAST_KILL) != target))
    {
	who->add_prop(LIVE_O_LAST_KILL, target);
	return "Attack " + target->query_the_name(who) + 
	"?!? Please confirm by trying again.\n";
    }

    if (!F_DARE_ATTACK(who, target))
    {
	return "You don't dare attack.\n";
    }
    return 0;
}

void
reset_stab()
{
    object who = query_shadow_who();
    if(who->AXEWIELDR || who->AXEWIELDL || who->AXEWIELDB)
	who->catch_tell("You feel ready to stab your enemy again.\n");
    else
	who->catch_tell("You feel ready to stab your enemy again.\n");
    stab_alarm = 0;
}

/*
 * Description:   Start up the guild's special attack
 * Arguments:     object target - the person to attack
 */
void
stab(object target)
{
    object who = query_shadow_who();

    if(!sizeof(who->query_weapon(-1)))
    {
	write("You can not stab someone without a weapon.\n");
	return;
    }

    if(stab_alarm != 0)
    {
	write("You are already preparing such an attack.\n");
	return;
    }

    who->catch_msg("You prepare to stab at a weak point in "
      +target->query_the_name(who)+"'s armour.\n");

    stab_alarm = set_alarm(
      itof(15 - who->query_skill(SS_GUILD_SPECIAL_SKILL) / 10),
      0.0, &stab2(target));

    /* Initiate battle with the target */
    who->attack_object(target);

    /* reveal the player if he is hiding */
    who->reveal_me(0);
}
 /*
* Description:   Perform the actual special attack.
* Arguments:     object target - the target of the attack
*/
void
stab2(object target)
{
    mixed hitres;
    int hitsuc, phurt, att, atts;
    int wielding_weapon;
    string how, why, weapon, hdesc, wdtype, watype;
    string *attack_type;
    string *attack_types;
    string *attack_message;
    object attacker = query_shadow_who();
    object wep;

    set_alarm(5.0, 0.0, "reset_stab");

    /* make sure the target is still in the same room as the attacker */
    if (!target || (environment(target) != environment(attacker)))
    {
	attacker->catch_msg("The target of your attack seems to " +
	  "have slipped away.\n");
	return;
    }

    if(!sizeof(attacker->query_weapon(-1)))
    {
	write("You have been disarmed! You cannot " +
	  "continue your stab.\n");
	return;
    }
    if(member_array(W_SWORD, TP->query_weapon(-1)->query_wt()) < 0 &&
       member_array(W_POLEARM, TP->query_weapon(-1)->query_wt()) < 0 &&
       member_array(W_KNIFE, TP->query_weapon(-1)->query_wt()) < 0 &&
       member_array(W_AXE, TP->query_weapon(-1)->query_wt()) < 0)
    {
	write("Without a weapon, you find yourself unable to continue " +
	  "with your stab!\n");
	return;
    }

    /* Has target become invalid somehow? */
    if (stringp(why = can_attack_with_lay_special(target, "stab")))
    {
	attacker->catch_msg(why);
	return;
    }

    if(TP->query_weapon(-1)[0]->query_wt() == W_AXE ||
       TP->query_weapon(-1)[0]->query_wt() == W_SWORD ||
       TP->query_weapon(-1)[0]->query_wt() == W_POLEARM ||
       TP->query_weapon(-1)[0]->query_wt() == W_KNIFE)
    {
	weapon = attacker->query_weapon(-1)[0]->short();
	wep = attacker->query_weapon(-1)[0];
    }  
    wielding_weapon = 1;


    /* Test to see if the attacker hits.  cb_tohit() is the routine
     * used by the combat system to determine if a regular attack
     * hits, but it also works nicely for our purposes.
     */
    if ((hitsuc = attacker->query_combat_object()->cb_tohit(-1, 90,
	  target)) > 0)
    {
        hitres = target->hit_me(F_PENMOD(
	    (attacker->query_stat(SS_STR) /2 + (wep->query_pen() * 5/4)) /2,
	    attacker->query_skill(SS_GUILD_SPECIAL_SKILL)),
	    wep->query_dt(), attacker, -1);
    }
    else
    {
	/* attack missed. */
	hitres = target->hit_me(hitsuc, 0, attacker, -1);
    }
    phurt = hitres[0];
    hdesc = hitres[1];

    /* add fatigue */
    if (attacker->query_fatigue() < 5)
    {
	attacker->heal_hp(-(5 - attacker->query_fatigue()));
	attacker->set_fatigue(0);
	attacker->catch_msg("The strain of the attack drains you.\n");
    }
    else
    {
	attacker->add_fatigue(-5);
    }

    if (phurt >= 0) 
    {
	/* remove some of the attacker's panic */
	attacker->add_panic(-3 - phurt / 5);


	switch (phurt)
	{
	case 0:
	    attack_message = ({
	      "You attempt " +
	      "to stab your " +weapon+ " into " +target->query_the_name(attacker)+
	      " but he manage to dodge your attack.\n",
	      attacker->query_the_name(target)+ " attempts to stab you " +
	      "with "+HIS(attacker)+" "+weapon+", but you manage to dodge "+
              HIS(attacker)+" attack.\n",
	      QCTNAME(attacker)+ " attempts to stab at "+QTNAME(target)+
	      " with "+HIS(attacker)+" "+weapon+ " but "+QTNAME(target)+
              " manage to dodge the attack.\n"});
	    break;
	case 1..2:
	    attack_message = ({
	      "You stab at "+QTNAME(target)+" with your " +weapon+ ", inflicting " +
	      "a small graze on " +target->query_the_name(attacker)+
	      "'s " +hdesc+ ".\n",
	      attacker->query_the_name(target)+ " stabs " +
	      "at you with " +HIS(attacker)+ " " +weapon+ ", inflicting a small " +
	      "graze on your " +hdesc + ".\n",
	      QCTNAME(attacker)+ " stabs at " +QTNAME(target)+
	      "with " +HIS(attacker)+ " " +weapon+ ", inflicting a small graze " +
	      "on " +QTNAME(target)+ "'s " +hdesc+ ".\n"});
	    break;
	case 3..5:
	    if(wielding_weapon)
		wdtype = "making a bleeding wound";
	    else
		wdtype = "Bug! Please mail Elmore about this!";

	    attack_message = ({
	      "You cackle slightly as you stab your " +weapon+
	      " into " +target->query_the_name(attacker)+ "'s " +
	      hdesc+ ", " +wdtype+ ".\n",
	      attacker->query_the_name(target)+ " cackles slightly as " +HE(attacker)+
	      " stabs " +HIS(attacker)+ " " +weapon+ " into your " +hdesc+
	      ", " +wdtype+ ".\n",
	      QCTNAME(attacker)+ " cackles slightly as " +HE(attacker)+ " stabs " +
	      HIS(attacker)+ " " +weapon+ " into " +QTNAME(target)+ "'s " +hdesc+
	      ", " +wdtype+ ".\n"});              
	    break;
	case 6..10:
	    attack_message = ({
	      "With great skill, you easily parry " +target->query_the_name(attacker)+ "'s " +
	      "attack, and quickly stab "+HIM(target)+" in "+HIS(target)+" "+hdesc+
        " with your " +weapon+ ".\n",
	      attacker->query_the_name(target)+ " easily parries your attack and quickly " +
	      "stabs you in your "+hdesc+ " with " +HIS(attacker)+ " " +weapon+ ".\n",
	      QCTNAME(attacker)+ " easily parries " +QTNAME(target)+ "'s attack and stabs " +
	      HIM(target)+ " in "+HIS(target)+ " "+hdesc+" with "+HIS(attacker)+ " " +weapon+
        ".\n"});
	    break;
	case 11..20:
	    attack_message = ({
	      "You manage to bypass "+target->query_the_name(attacker)+
	      "'s armour and stab "+HIM(target)+" hard in "+HIS(target)+
              " " +hdesc+ " with your " +weapon+ ".\n",
	      attacker->query_the_name(target)+ " manage to bypass your armour and "+
              "stab you hard in " +
	      "your " +hdesc+ " with " +HIS(attacker)+ " " +weapon+ ".\n",
	      QCTNAME(attacker)+ " manage to bypass " +QTNAME(target)+ " armour and "+
	      "stabs " +HIM(target)+ " hard in "+HIS(target)+ " " +hdesc+ " with " +
              HIS(attacker)+ " " +weapon+ ".\n"});
	    break;
	case 21..40:
	    attack_message = ({
	      "You stab at " +
	      target->query_the_name(attacker)+ " with your " +
	      weapon + ", making a serious wound in "+HIS(target)+ " "+hdesc+".\n",
	      attacker->query_the_name(target)+ " stabs you in your " +
	      hdesc+ " with " +HIS(attacker)+ " " +weapon+ ", making a "+
              "serious wound.\n",
	      QCTNAME(attacker)+ " stabs at " +QTNAME(target)+ " " +
	      "'s " +hdesc+ " with " +
	      HIS(attacker)+ " " +weapon+ ", making a serious wound.\n"});
	    break;
	case 41..75:
	    attack_message = ({
	      "Straining your muscles to the extreme, you forcefully stab your "+
              weapon+ " into " +target->query_the_name(attacker)+ "'s " +hdesc+
	      ". Blood begin to pour from the deep wound.\n",
	      attacker->query_the_name(target)+ " strains "+HIS(attacker)+" muscles as "+
              HE(attacker)+ " stabs you in your "+hdesc+" with "+HIS(attacker)+
	      " " +weapon+ ". The "+weapon+ "makes a deep wound and blood begins "+
              "to pour from it.\n",
	      QCTNAME(attacker)+ " strains his muscles as "+HE(attacker)+" stabs "+
              HIS(attacker)+ " " +weapon+
	      " into " +QTNAME(target)+ "'s " +
	      hdesc+ ", making a deep, bleeding wound.\n"});
	    break;
	case 76..99:
	    attack_message = ({
	      "Your stab your "+weapon+" at "+target->query_the_name(attacker)+". "+
        "The "+weapon+" buries itself in "+HIS(target)+ " "+hdesc+".\n",
	      attacker->query_the_name(target)+ " stabs "+HIS(attacker)+" "+
              weapon+ " at you! "+HIS(attacker)+" " +weapon+ " buries "+
        "itself in your "+hdesc+".\n",
	      QCTNAME(attacker)+ " stabs at "+QCTNAME(target)+". The "+
              weapon+ " buries itself in "+HIS(target)+
	      " " +hdesc+".\n"});
	    break;
	default:
	    attack_message = ({
	      "You smile viciously as you stab at " +
	      target->query_the_name(attacker)+ " "+hdesc+". Your " +weapon+
        " completely penetrates "+QTNAME(target)+"'s skin, making a "+
        "mortal wound.\n"+QTNAME(target)+" collaps in agony!\n",
	      attacker->query_the_name(target)+ " smiles viciously as " +
	      HE(attacker)+ " stabs you in the "+hdesc+" with " +HIS(attacker)+
	      " " +weapon+ ". The "+weapon+ " completely penetrates your skin, "+
        "making a lethal wound.\nYou collaps in agony!\n",
	      QCTNAME(attacker)+ " smiles viciously as he stabs at "+QTNAME(target)+
        "'s "+hdesc+". The "+weapon+" completely penetrates "+QTNAME(target)+
        "'s skin, making a mortal wound.\n"+QTNAME(target)+ " collaps in "+
        "agony!\n"});
	    break;
	}


	/* message to the attacker */

	attacker->catch_tell(attack_message[0]);

	/* message to the target */
	target->catch_tell(attack_message[1]);

	/* message to onlookers */
	attacker->tell_watcher(attack_message[2], target);

	if (target->query_hp() <= 0)
	{
	    target->do_die(attacker);
	}

	return;
    }

    /* We get here if the attack missed */

    /* add some panic to the attacker */
    attacker->add_panic(1);
    attacker->add_attack_delay(5);

    /* message to attacker */
    attacker->catch_msg("You stab at "+QCTNAME(target)+ " with your "+
      weapon+ " but miss.\n");

    /* message to target */
    target->catch_msg(QCTNAME(attacker) + " stabs at you with "
      +HIS(attacker)+ " " +weapon+ " but misses.\n");

    /* message to onlookers */
    attacker->tell_watcher(QCTNAME(attacker) + " stabs at " +
      QCTNAME(target)+ " with "+HIS(attacker)+ " "+weapon+
      "but misses.\n", target);
}

/*
* Description:   See if we are currently preparing to perform
*                the special attack
* Returns:       1 / 0 - preparing / not preparing
*/
int
query_stab()
{
    return !!stab_alarm;
}
