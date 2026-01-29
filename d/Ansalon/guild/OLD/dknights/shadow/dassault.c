/* This file contains one of the special attacks that the Death Knights
 * have. It is kept in a seperate file for easy debugging.
 * It controls the damage and messages for the "assault" special and
 * also handles which weapon the Death Knight is wielding and
 * give a different message depending on if the DK is wielding a club
 * a sword or two weapons.
 * 
 * - Elmore, 8/10-2001
 */

#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include "/d/Ansalon/common/defs.h"

static private int dassault_alarm = 0;

int wielding_one_club,
    wielding_one_sword,
    wielding_two_club,
    wielding_two_sword;

object weapon, weapon2;

string first_weapon_desc,
       secon_weapon_desc;

/* Prototypes */
void dassault2(object target);

mixed
can_attack_with_dassault(object target, string attack)
{
    mixed why;
    object who = query_shadow_who();
 
    if (!target || !living(target) || !present(target, environment(who)))
	return attack + " whom?\n";

    if (who->query_prop(LIVE_I_ATTACK_DELAY) || who->query_prop(LIVE_I_STUNNED))
        return "You are too stunned to " + attack + ".\n";

    if (  stringp(why = target->query_prop(OBJ_M_NO_ATTACK)) 
       || stringp(why = environment(target)->query_prop(ROOM_M_NO_ATTACK)))
        return why;
    else if (why)
	return "You sense a devine force protecting "+target->query_the_name(who)+".\n";

    /* Someone might try defining this to block all special attacks */
    if (target->query_not_attack_me(who, -1))
	return "";

    if (!F_DARE_ATTACK(who, target))
	return "You don't dare attack.\n";

    if ((!who->query_npc()) && (who->query_met(target)) &&
      !(who == target->query_attack()) &&
      (who->query_prop(LIVE_O_LAST_KILL) != target))
    {
	who->add_prop(LIVE_O_LAST_KILL, target);
	return "Attack " + target->query_the_name(who) + 
	"?!? Please confirm by trying again.\n";
    }

    return 0;

}

void
reset_dassault()
{
    object who = query_shadow_who();
    who->catch_tell("You can once again assult your enemies.\n");
    dassault_alarm = 0;
}

/*
 * Description:   Start up the guild's special attack
 * Arguments:     object target - the person to attack
 */
void
dassault(object target)
{
    object who = query_shadow_who();

   object *weapons = who->query_weapon(-1);
    wielding_one_club  = 0;
    wielding_one_sword = 0;
    wielding_two_club  = 0;
    wielding_two_sword = 0;
    first_weapon_desc  = "";
    secon_weapon_desc  = "";

    switch (sizeof(weapons))
    {
        case 0:
            write("But you are not wielding a weapon!\n");
            return;
            break;

        case 1:
            weapon = weapons[0];
  
            if (objectp(weapon))
            {
                if (weapon->query_wt() == 4)
                    wielding_one_club = 1;
                else
                    wielding_one_sword = 1;

                first_weapon_desc = weapon->short();
            }
        break;

        case 2:
            weapon  = weapons[0];
            weapon2 = weapons[1];
  
            if (objectp(weapon) && objectp(weapon2))
            {
                if (weapon->query_wt() == 4)
                {
                    first_weapon_desc = weapon->short();
                    secon_weapon_desc = weapon2->short();
                    wielding_two_club = 1;
                }
                else
                {
                    if (weapon2->query_wt() == 4)
                    {
                        first_weapon_desc = weapon2->short();
                        secon_weapon_desc = weapon->short();
                        wielding_two_club = 1;
                    }
                    else
                    {
                        first_weapon_desc  = weapon2->short();
                        secon_weapon_desc  = weapon->short();
                        wielding_two_sword = 1;
                    }
                }
            }
        break;
    }

    who->catch_msg("You prepare to assult " +target->query_the_name(target)+
      " with your "+first_weapon_desc+".\n");

    dassault_alarm = set_alarm(
      itof(10 - who->query_skill(SS_GUILD_SPECIAL_DASSAULT) / 10),
      0.0, &dassault2(target));

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
dassault2(object target)
{
    mixed hitres;
    int hitsuc, phurt, att, atts, weapon_damage, multiplier;
    string how, why, weapon, hdesc, wdtype, watype;
    string *attack_type;
    string *attack_types;
    string *attack_message;
    object attacker = query_shadow_who();

    set_alarm(5.0, 0.0, "reset_dassault");

    /* make sure the target is still in the same room as the attacker */
    if (!target || (environment(target) != environment(attacker)))
    {
	      attacker->catch_msg("Your enemy has disappeared, so you "+
                        "abandon your assult.\n");
	      return;
    }

    /* Has target become invalid somehow? */
    if (stringp(why = can_attack_with_dassault(target, "dassault")))
    {
        attacker->catch_msg(why);
      	return;
    }

    if ((hitsuc = attacker->query_combat_object()->cb_tohit(-1, 95,
	  target)) > 0)
    {

        /* attack successful! */
        /* Find the avg. pen of the weapon(s) that the DK is using. */
        if (objectp(weapon))
            weapon_damage += weapon->query_pen();

        if (objectp(weapon2))
        {
            weapon_damage += weapon2->query_pen();
            weapon_damage = weapon_damage / 2;
        }
 
        multiplier = 2;       
    
// Find the targets encumberance in % and add some damage if he's encumbered.
        switch (target->query_encumberance_weight())
        {
            case 0..40:
            {
                multiplier = 2;
                break;
            }
            case 41..50:
            {
                multiplier = 3;
                break;
            }
            case 51..60:
            {
                multiplier = 4;
                break;
            }
            default:
            {
                multiplier = 5;
                break;
            }
        }

        hitres = target->hit_me(F_PENMOD(
                 (attacker->query_stat(SS_DEX) * 1,5 +
                  attacker->query_stat(SS_STR) + (weapon_damage * multiplier)) /2,
                  attacker->query_skill(SS_GUILD_SPECIAL_DASSAULT)),
                  weapon->query_dt(), attacker, -1);
    }
    else
    {     
        /* attack missed. */
      	hitres = target->hit_me(hitsuc, 0, attacker, -1);
    }

    phurt = hitres[0];
    hdesc = hitres[1];

    /* add fatigue drain */
    attacker->add_fatigue(-5);
    
    if (phurt >= 0) 
    {
        /* remove some of the attacker's panic */
        attacker->add_panic(-25 - phurt / 5);

        /* NOTE! ATTACK ARRAY: { CLUB  MSG
                                ,CLUB  MSG
                                ,CLUB  MSG
                                ,SWORD MSG
                                ,SWORD MSG
                                ,SWORD MSG } */
        switch (phurt)
        {

        case 0..4:
        attack_message = ({
                    "Your attack slightly bruises "+
                    HIS(target)+ " " +hdesc+ ".\n",
 
                    HIS(attacker)+ " attack slightly bruises "+
                    "your " +hdesc+ ".\n",

                    HIS(attacker)+ " attack slightly bruises "+
                    target->query_The_name(attacker)+ "'s " +hdesc+ ".\n",

                    "Your attack makes a small wound in "+
                    HIS(target)+ " " +hdesc+ ".\n",

                    HIS(attacker)+ " attack makes a small wound in your "+
                    hdesc+ ".\n",

                    HIS(attacker)+ " attack makes a small wound in "+
                    target->query_The_name(attacker)+ "'s " +hdesc+ ".\n"

	    });
        break;

        case 5..10:
        attack_message = ({
                    HIS(target)+ " " +hdesc+ " begins to "+
                    "bleed as your weapon makes contact with the flesh and bones.\n",    
 
                    "Your "+hdesc+" feels numb as the weapon makes contact with "+  
                    "your flesh and bones.\n",    

                    target->query_The_name(attacker)+ "'s " +hdesc+ " begins to "+
                    "bleed as "+HIS(attacker)+"'s weapon makes contact with the "+
                    "flesh and bones.\n",        

                    "Blood begins to pour out from "+HIS(target)+ " " +hdesc+
                    ", covering the ground in a deep red color.\n",   

                    "Blood begins to pour out from your " +hdesc+ ", covering "+      
                    "the ground in a deep red color.\n",   

                    "Blood begins to pour out from "+target->query_The_name(attacker)+
                    "'s " +hdesc+ " covering the ground in a deep red color.\n"   
	    });
        break;

        case 11..20:
        attack_message = ({
                    "Your weapon smashes the muscles in "+HIS(target)+ " "+hdesc+".\n",
 
                    HIS(attacker)+ " weapon smashes your muscles in your "+hdesc+
                    ", making you scream in agony.\n",

                    HIS(attacker)+ " weapon smashes the muscles in "+target->query_The_name(attacker)+ "'s " +hdesc+
                    ", as "+HE(target)+ " screams in agony.\n", 

                    "Your attack makes a deep gash in "+HIS(target)+ " "+hdesc+".\n",

                    HIS(attacker)+ " attack makes a deep gash in your "+hdesc+".\n",

                    HIS(attacker)+ " attack makes a deep gash in "+
                    target->query_The_name(attacker)+ "'s "+hdesc+".\n"
	    });
        break;

        case 21..40:
        attack_message = ({
                    "A loud crack can be heard as the bones in " +HIS(target)+
                    " " +hdesc+ " breaks.\n", 
 
                    "A loud crack can be heard as the bones in your " +hdesc+ " breaks.\n", 

                    "A loud crack can be heard as the bones in "+
                    target->query_The_name(attacker)+ "'s "+hdesc+" breaks.\n", 

                    "The force of the attack almost severes " +HIS(target)+ " " +hdesc+ ".\n",   

                    "The force of the attack almost severes your "+hdesc+".\n",   

                    "The force of the attack almost severes "+
                    target->query_The_name(attacker)+ "'s " +hdesc+ ".\n"
 	    });
        break;

        case 41..75:
        attack_message = ({
                    "A loud crack can be heard as the bones in " +HIS(target)+
                    " " +hdesc+ " breaks.\n", 
 
                    "A loud crack can be heard as the bones in your " +hdesc+ " breaks.\n", 

                    "A loud crack can be heard as the bones in "+
                    target->query_The_name(attacker)+ "'s "+hdesc+" breaks.\n", 

                    "Your weapon completely penetrates "+HIS(target)+ " "+hdesc+         
                    " protruding on the other side!\n",    

                    HIS(attacker)+ " weapon completely penetrates your "+hdesc+         
                    " protruding on the other side!\n",   

                    HIS(attacker)+ " weapon completely penetrates "+
                    target->query_The_name(attacker)+ "'s " +hdesc+       
                    " protruding on the other side!\n"   
        });
        break;

        default:
        attack_message = ({
                    "Time seems to stand still as your weapon crashes into "+
                    HIS(target)+ " "+hdesc+", causing the tisue and muscles to be separated "+
                    "from "+HIS(target)+" bones, blood gush out in every direction from "+
                    HIS(target)+ " mortal wound!\n",
 
                    "Time seems to stand still as "+target->query_the_name(attacker)+
                    "'s weapon crashes into your "+hdesc+", causing the tisue and "+
                    "muscles to be separated from your bones, blood gush out in every "+
                    "direction from your mortal wound!\n",

                    "Time seems to stand still as "+target->query_the_name(attacker)+
                    "'s weapon crashes into "+target->query_The_name(attacker)+ "'s " +
                    hdesc+ " causing the tisue and muscles to be separated from "+HIS(target)+
                    " bones, blood gush out in every direction from the mortal wound!\n",

                    "You weapon enters the soft flesh in " +HIS(target)+ " " +hdesc+
                    ". With the weapon still in "+HIS(target)+ " limb, you lift "+
                    HIM(target)+ " several feet into the air, before throwing "+HIS(target)+
                    " bleeding body into the ground.\n",

                    HIS(attacker)+ " weapon enters the soft flesh in your "+hdesc+
                    ". With the weapon still in your limb, "+
                    target->query_the_name(attacker)+" lifts you several feet into "+
                    "the air, before throwing your bleeding body into the ground.\n",

                    target->query_the_name(attacker)+ "'s weapon enters the soft flesh "+
                    "in "+target->query_The_name(attacker)+"'s "+hdesc+ ". With the "+
                    "weapon still in "+HIS(target)+" limb, "+
                    target->query_the_name(attacker)+" lifts "+HIM(target)+ 
                    " several feet into the aid, before throwing "+HIS(target)+
                    " bleeding body into the ground.\n"
        });
        break;
        }

        if (wielding_one_club == 1)
        /* THE DK IS ONLY WIELDING A CLUB IN EITHER HIS LEFT, RIGHT OR BOTH HANDS */
        {
            attacker->catch_tell("You deflect " +
                      target->query_the_name(attacker)+ "'s blow with your "+
                      first_weapon_desc+ " and with an prodigious force you "+
                      "bring your weapon down upon " +
                      target->query_the_name(attacker)+ "'s " +hdesc+ ".\n"+
                      attack_message[0]);
            target->catch_tell(attacker->query_The_name(target)+
                    " deflects your blow with his "+first_weapon_desc+" and with an "+
                    "prodigious force brings " +HIS(attacker)+ " weapon "+
                    "down upon your " +hdesc+ ".\n"+
                    attack_message[1]);
            attacker->tell_watcher(QCTNAME(attacker)+ " deflects "+QTNAME(target)+
                      "'s blow and with an prodigious force "+HE(attacker)+ " brings "+
                      HIS(attacker)+ " "+first_weapon_desc+" upon "+HIS(target)+ " "+
                      hdesc+".\n"+
                      attack_message[2], target);
        }

        if (wielding_one_sword == 1)
        /* THE DK IS ONLY WIELDING A SWORD IN EITHER HIS LEFT, RIGHT OR BOTH HANDS */
        {
            attacker->catch_tell("You deflect " +
                      target->query_the_name(attacker)+ "'s blow with your "+
                      first_weapon_desc+ " and quickly stab at "+HIS(target)+ " "+
                      hdesc + " with your "+first_weapon_desc+".\n"+
                      attack_message[3]);
            target->catch_tell(attacker->query_The_name(target)+
                    " deflects your blow with his "+first_weapon_desc+" and quickly "+
                    "stabs at your " +hdesc+ " with "+HIS(attacker)+
                    first_weapon_desc+".\n"+
                    attack_message[4]);
            attacker->tell_watcher(QCTNAME(attacker)+ " deflects "+QTNAME(target)+
                      "'s blow with "+HIS(attacker)+ " "+first_weapon_desc+" and quickly stabs "+
                      "at " +target->query_the_name(attacker)+ "'s "+hdesc+
                      " with "+HIS(attacker)+ " "+first_weapon_desc+".\n" +
                      attack_message[5], target);
        }

        if (wielding_two_club == 1)
        /* THE DK IS WIELDING A CLUB IN EITHER HIS LEFT, RIGHT OR BOTH HANDS AND
           ANOTHER WEAPON. */
        {
            attacker->catch_tell("You deflect " +
                      target->query_the_name(attacker)+ "'s blow with your "+
                      secon_weapon_desc+
                      "and with an prodigious force you bring your "+first_weapon_desc+
                      " down upon " +target->query_the_name(attacker)+ "'s "+
                      hdesc+ ".\n"+
                      attack_message[0]);
            target->catch_tell(attacker->query_The_name(target)+
                    " deflects your blow with his "+secon_weapon_desc+ " and with an "+
                    "prodigious force brings " +HIS(attacker)+ " "+first_weapon_desc+
                    " down upon your " +hdesc+ ".\n"+
                    attack_message[1]);
            attacker->tell_watcher(QCTNAME(attacker)+ " deflects "+QTNAME(target)+
                      "'s blow and with "+HIS(attacker)+ " "+ secon_weapon_desc+ " and "+
                      "with an prodigious force "+HE(attacker)+ " brings "+
                      HIS(attacker)+ " "+secon_weapon_desc+" upon "+HIS(target)+ " "+
                      hdesc+".\n" +
                      attack_message[2], target);
        }

        if (wielding_two_sword == 1)
        /* THE DK IS WIELDING TWO WEAPONS. */
        {
            attacker->catch_tell("You deflect " +
                      target->query_the_name(attacker)+ "'s blow with your "+first_weapon_desc+  
                      " and quickly stab at "+HIS(target)+ " "+ hdesc +
                      " with your "+secon_weapon_desc+".\n"+
                      attack_message[3]);
            target->catch_tell(attacker->query_The_name(target)+
                    " deflects your blow with "+HIS(attacker)+ " "+first_weapon_desc+" and quickly "+
                    "stabs at your " +hdesc+ " with "+HIS(attacker)+
                    " "+secon_weapon_desc+".\n"+
                    attack_message[4]);
            attacker->tell_watcher(QCTNAME(attacker)+ " deflects "+QTNAME(target)+
                      "'s blow with "+HIS(attacker)+ " "+first_weapon_desc+" and quickly stabs "+
                      "at " +target->query_the_name(attacker)+ "'s "+hdesc+
                      " with "+HIS(attacker)+ " "+secon_weapon_desc+".\n" +
                      attack_message[5], target);
        }
        if (target->query_hp() <= 0)
            target->do_die(attacker);

        return;
    }

   /* We get here if the attack missed */

   /* add some panic to the attacker */
   attacker->add_panic(1);
   attacker->add_attack_delay(1);

    if (wielding_one_club == 1)
    /* THE DK IS WIELDING A CLUB IN EITHER HIS LEFT, RIGHT OR BOTH HANDS */
    {
            attacker->catch_tell("You deflect " +
                      target->query_the_name(attacker)+ "'s blow with your "+
                      first_weapon_desc+ " and with an prodigious force you "+
                      "bring your weapon down upon " +
                      target->query_the_name(attacker)+ "'s " +hdesc+ ".\n"+
                      "Your attack is deflected by "+HIS(target)+ " armour.\n");
            target->catch_tell(attacker->query_The_name(target)+
                    " deflects your blow with his "+first_weapon_desc+" and with an "+
                    "prodigious force brings " +HIS(attacker)+ " weapon "+
                    "down upon your " +hdesc+ ".\n"+
                    HIS(attacker)+ " attack is deflected by your armour.\n");
            attacker->tell_watcher(QCTNAME(attacker)+ " deflects "+QTNAME(target)+
                      "'s blow and with an prodigious force "+HE(attacker)+ " brings "+
                      HIS(attacker)+ " "+first_weapon_desc+" upon "+HIS(target)+ " "+
                      hdesc+".\n"+
                      HIS(attacker)+ " attack is deflected by "+HIS(target)+
                      "armour\n", target);

    }

    if (wielding_one_sword == 1)
    /* THE DK IS WIELDING A SWORD IN EITHER HIS LEFT, RIGHT OR BOTH HANDS */
    {
            attacker->catch_tell("You deflect " +
                      target->query_the_name(attacker)+ "'s blow with your "+
                      first_weapon_desc+ " and quickly stab at "+HIS(target)+ " "+
                      hdesc + " with your "+first_weapon_desc+".\n"+
                      "Your attack is deflected by "+HIS(target)+ " armour.\n");
            target->catch_tell(attacker->query_The_name(target)+
                    " deflects your blow with his "+first_weapon_desc+" and quickly "+
                    "stabs at your " +hdesc+ " with "+HIS(attacker)+
                    first_weapon_desc+".\n"+
                    HIS(attacker)+ " attack is deflected by your armour.\n");
            attacker->tell_watcher(QCTNAME(attacker)+ " deflects "+QTNAME(target)+
                      " blow with "+HIS(attacker)+ " "+first_weapon_desc+" and quickly stabs "+
                      "at " +target->query_the_name(attacker)+ "'s "+hdesc+
                      " with "+HIS(attacker)+ " "+first_weapon_desc+".\n" +
                      HIS(attacker)+ " attack is deflected by "+HIS(target)+
                      "armour.\n", target);

    }

    if (wielding_two_club == 1)
    /* THE DK IS USING TWO WEAPONS */
    {
            attacker->catch_tell("You deflect " +
                      target->query_the_name(attacker)+ "'s blow with your "+
                      secon_weapon_desc+
                      "and with an prodigious force you bring your "+first_weapon_desc+
                      " down upon " +target->query_the_name(attacker)+ "'s "+
                      hdesc+ ".\n"+
                      "Your attack is deflected by "+HIS(target)+ " armour.\n");
            target->catch_tell(attacker->query_The_name(target)+
                    " deflects your blow with his "+secon_weapon_desc+ " and with an "+
                    "prodigious force brings " +HIS(attacker)+ " "+first_weapon_desc+
                    " down upon your " +hdesc+ ".\n"+
                    HIS(attacker)+ " attack is deflected by your armour.\n");
            attacker->tell_watcher(QCTNAME(attacker)+ " deflects "+QTNAME(target)+
                      "'s blow and with "+HIS(attacker)+ " "+ secon_weapon_desc+ " and "+
                      "with an prodigious force "+HE(attacker)+ " brings "+
                      HIS(attacker)+ " "+secon_weapon_desc+" upon "+HIS(target)+ " "+
                      hdesc+".\n" +
                      HIS(attacker)+ " attack is deflected by "+HIS(target)+
                      "armour.\n", target);
    }
    if (wielding_two_sword == 1)
    {
            attacker->catch_tell("You deflect " +
                      target->query_the_name(attacker)+ "'s blow with your "+first_weapon_desc+  
                      " and quickly stab at "+HIS(target)+ " "+ hdesc +
                      " with your "+secon_weapon_desc+".\n"+
                      "Your attack is deflected by "+HIS(target)+ " armour.\n");
            target->catch_tell(attacker->query_The_name(target)+
                    " deflects your blow with "+HIS(attacker)+ " "+first_weapon_desc+" and quickly "+
                    "stabs at your " +hdesc+ " with "+HIS(attacker)+
                    " "+secon_weapon_desc+".\n"+
                    HIS(attacker)+ " attack is deflected by your armour.\n");
            attacker->tell_watcher(QCTNAME(attacker)+ " deflects "+QTNAME(target)+
                      "'s blow with "+HIS(attacker)+ " "+first_weapon_desc+" and quickly stabs "+
                      "at " +target->query_the_name(attacker)+ "'s "+hdesc+
                      " with "+HIS(attacker)+ " "+secon_weapon_desc+".\n" +
                      HIS(attacker)+ " attack is deflected by "+HIS(target)+
                      "armour.\n", target);
    }
}

/*
* Description:   See if we are currently preparing to perform
*                the special attack
* Returns:       1 / 0 - preparing / not preparing
*/
int
query_dassault()
{
    return !!dassault_alarm;
}
