#pragma save_binary

inherit "/cmd/std/command_driver";

#include "/d/Krynn/common/defs.h"
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <cmdparse.h>
#include <filter_funs.h>
#include <composite.h>
#include <formulas.h>
#include <options.h>
#include <state_desc.h>
#include "/d/Krynn/open/sys/combat.h"
#include "/d/Krynn/solamn/vin/knight/guild.h"


/********************************************************************
 * Soul identifying and autoloading
 ********************************************************************/

string
get_soul_id()
{
    return "Special tester soul";
}

int
query_cmd_soul()
{
    return 1;
}

/***********************************************************************
 * The list of verbs and functions. Please add new in alphabetical order.
 ***********************************************************************/

mapping
query_cmdlist()
{
    setuid();
    seteuid(getuid());
    return (["sp":"special"]);
}

/********************* slash *******************************************/
object
query_weapon(object liv)
{
    object *wielded_weapons;
    object wep, wep1, wep2;
    int i, wepstat, wep1stat, wep2stat, j;
    wielded_weapons = liv->query_weapon(-1);
   
    if (sizeof(wielded_weapons) == 1)
    {
	for (i = 0; i < sizeof(wielded_weapons); i++)
	  wep = wielded_weapons[i];
    }
   
    if (sizeof(wielded_weapons) == 2)
    {
	wep1 = wielded_weapons[0];
	wep2 = wielded_weapons[1];
    }
   
    if ((wep1) && (wep2))
    {
	wep1stat = ((wep1->query_hit()+wep1->query_pen()) / 2);
	wep2stat = ((wep2->query_hit()+wep2->query_pen()) / 2);
      
	if (wep1stat >= wep2stat)
	{
	    return wep1;
	}
	else
	{
	    return wep2;
	}	
    }
   
    if (wep)
    {
	return wep;      
    }
}

int
special(string str)
{
    object          ob, *obj, weapon;
    object liv = TP;   
    string how;

    if (!str)
      ob = liv->query_attack();
    else 
    {
	obj = parse_this(str, "%l");
	if (sizeof(obj) > 0)
	  ob = obj[0];
	if (sizeof(obj) > 1) 
	{
	    NF("Choose one enemy to attack.\n");
	    return 0;
	}
    }
   
/*
    how = c_can_attack(ob, query_verb());
    if (stringp(how)) 
    {
	NF(how);
	return 0;
    }
*/
   
    if (liv->query_prop("_kspecial_resetting"))
    {
	NF("You are not ready to attack again.\n");
	return 0;
    }
  
    if (liv->query_prop(LIVE_I_ATTACK_DELAY))
    {
	NF("You are too stunned to attack.\n");
	return 0;
    }

    if (liv->query_prop("_kspecial_preparing")) 
    {
	NF("You are already preparing to attack.\n");
	return 0;
    }      
    else
    {
	weapon = query_weapon(liv);
	if (!weapon)
	{
	    NF("You cannot attack without a weapon.\n");
	    return 0;
	}
	if (!ob)
	{
	    NF("There doesn't seem to be an enemy around.\n");
	    return 0;
	}
	liv->add_prop("_kspecial_preparing", 1);
	set_alarm(3.0, 0.0, "do_special", ob, liv);
	if (ob != liv->query_attack())
	{
	    say(QCTNAME(liv)+" raises "+POSSESSIVE(liv)+" "+weapon->short()+
		" aloft, giving "+QTNAME(ob)+" a traditional salute as "+
		PRONOUN(liv)+" rushes forward to do battle with "+OBJECTIVE(ob)+
		"!\n", ({ ob, liv }));
	    ob->catch_msg(QCTNAME(liv)+" raises "+POSSESSIVE(liv)+" "+
			  weapon->short()+" aloft, giving you a traditional salute as "+
			  PRONOUN(liv)+" rushes forward to do battle with you!\n");
	    liv->catch_msg("You raise your "+weapon->short()+" aloft, saluting "+
			   QTNAME(ob)+" traditionally as you rush forward to do battle "+
			   "with "+OBJECTIVE(ob)+"!\n");
	    liv->attack_object(ob);
	}
	else
	  liv->catch_msg("You prepare to attack "+QTNAME(ob)+".\n");
    }
    return 1;
}

void
do_special(object ob, object liv)
{
    mixed hitresult;
    object weapon;
    int hitres, weaponmod, statmod, pen, skill, weaponstat, levmod;
    int wt, ht, rcry, rcry2;
    string tar, att, aud, cry, hdesc;
   
    tar = "";
    att = "";
    aud = "";

    if (!liv || !present(ob, environment(liv))) 
    {
	liv->catch_tell("You are unable to attack your target.\n");
	liv->remove_prop("_kspecial_preparing");
	return;
    }
   
    weapon = query_weapon(liv);
    if (!weapon)
    {
	liv->catch_tell("You cannot attack without a weapon.\n");
	liv->remove_prop("_kspecial_preparing");
	return;
    }
   
    /* Damage formula calculated as follows:                             */
    /* 1- The average of the weapon's pen and hit is calculated, and     */
    /*    125% of that value is what is used based on the weapon.        */
    /* 2- The average of the characters strength twice, intelligence     */
    /*    and discipline is taken, and 50% of that value is what is      */
    /*    used based on stats.                                           */
    /* 3- The average of these two is taken, and the Knight's sublevel   */
    /*    in the guild, a number between 1 and 10 is added to the total. */
    /* 4- The total is used in F_PENMOD along with the skill level.      */
    /* 5- The result of F_PENMOD is used for pen in the hit_me function. */

    weaponstat = ((weapon->query_hit()+weapon->query_pen()) / 2);
    weaponmod = (weaponstat * 10 / 8);
    statmod = ((liv->query_stat(0)*2+liv->query_stat(3)+liv->query_stat(5))/8);
    if (statmod >= 100)
      statmod = 100;
    if (liv->query_knight_level() > 3 && liv->query_knight_sublevel() != 11)
      levmod = 10;
    else
      levmod = 2*(liv->query_knight_level());
    pen = ((statmod + weaponmod)/2 +levmod+10);
    skill = TP->query_skill(67531);
    hitres = F_PENMOD(pen, skill);
    wt = weapon->query_wt();
    ht = weapon->query_dt();
    hitresult = ob->hit_me(hitres, ht, liv, -1);
    hdesc = hitresult[1];
    if (wt == W_SWORD)
    {
	if (hitresult[0] < 1)
	{
	    att = "You swing your "+weapon->short()+" towards "+
	      QTNAME(ob)+"'s "+hdesc+", but "+PRONOUN(ob)+" evades "+
		"the attack.";
	    tar = QCTNAME(liv)+" swings "+POSSESSIVE(liv)+" "+ weapon->short()+
	      " towards your "+hdesc+", but you evade the attack.";
	    aud = QCTNAME(liv)+" swings "+POSSESSIVE(liv)+" "+ weapon->short()+
	      " towards "+QTNAME(ob)+"'s "+hdesc+", but "+QTNAME(ob)+" evades "+
		"the attack.";
	}
	else if (hitresult[0] < 5)
	{
	    att = "You lash out quickly with your "+weapon->short()+" and lightly "+
	      "cut "+QTNAME(ob)+"'s "+hdesc+".";
	    tar = QCTNAME(liv)+" lashes out quickly with "+POSSESSIVE(liv)+" "+
	      weapon->short()+", lightly cutting your "+hdesc+".";
	    aud = QCTNAME(liv)+" lashes out quickly with "+POSSESSIVE(liv)+" "+
	      weapon->short()+", lightly cutting the "+hdesc+" of "+
		QTNAME(ob)+".";
	}
	else if (hitresult[0] < 10)
	{
	    att = "You bash "+QTNAME(ob)+" with the hilt of your "+
	      weapon->short()+", sending "+OBJECTIVE(ob)+" staggering "+
		"backwards.\n";
	    tar = QCTNAME(liv)+" bashes you with the hilt of "+POSSESSIVE(liv)+" "+
	      weapon->short()+", sending you staggering from the blow.";
	    aud = QCTNAME(ob)+" is sent staggering backwards as "+QTNAME(liv)+
	      " bashes "+OBJECTIVE(ob)+" with the hilt of "+POSSESSIVE(liv)+" "+
		weapon->short()+".";
	}
	else if (hitresult[0] < 20)
	{
	    att = "You slash deeply into "+QTNAME(ob)+"'s "+hdesc+" with your "+
	      weapon->short()+".";
	    tar = QCTNAME(liv)+" slashes deeply into your "+hdesc+" with "+
	      POSSESSIVE(liv)+" "+weapon->short()+".";
	    aud = QCTNAME(liv)+" slashes deeply into "+QTNAME(ob)+"'s "+hdesc+
	      " with "+POSSESSIVE(liv)+" "+weapon->short()+".";
	}
	else if (hitresult[0] < 35)
	{
	    att = "Spotting an opening in "+QTNAME(ob)+"'s defence, you stab forward "+
	      "and pierce "+POSSESSIVE(ob)+" "+hdesc+" with your "+
                weapon->short()+".";
	    tar = QCTNAME(liv)+" stabs forward, spotting an opening in your defence, "+
	      "and pierces your "+hdesc+" with "+POSSESSIVE(liv)+" "+
		weapon->short()+".";
	    aud = QCTNAME(liv)+" stabs forward, spotting an opening in "+QTNAME(ob)+
	      "'s defence, and pierces "+POSSESSIVE(ob)+" "+hdesc+" with "+
		POSSESSIVE(liv)+" "+weapon->short()+".";
	}
	else if (hitresult[0] < 50)
	{
	    att = "With a skillful swing, you open a large gash on "+QTNAME(ob)+
	      "'s "+hdesc+" with the blade of your "+weapon->short()+".";
	    tar = QCTNAME(liv)+" opens a large gash on your "+hdesc+" with a skillful "+
	      "swing of "+POSSESSIVE(liv)+" "+weapon->short()+".";
	    aud = QCTNAME(liv)+" opens a large gash on "+QTNAME(ob)+"'s "+hdesc+
	      " with a skillful swing of "+POSSESSIVE(liv)+" "+
		weapon->short()+".";
	}
	else
	{
	    att = "You confidently lunge forward, driving the blade of your "+
	      weapon->short()+" deep into "+QTNAME(ob)+"'s "+
		hdesc+".";
	    tar = QCTNAME(liv)+" confidently lunges forward, driving the blade of "+
	      POSSESSIVE(liv)+" "+weapon->short()+" deep into "+
		"your "+hdesc+".";
	    aud = QCTNAME(liv)+" confidently lunges forward, driving the blade of "+
	      POSSESSIVE(liv)+" "+weapon->short()+" deep into "+
		"the "+hdesc+" of "+QTNAME(ob)+".";
	}
    }
    else if (wt == W_POLEARM)
    {
	if (hitresult[0] < 1)
	{
	    att = "You swing your "+weapon->short()+" towards "+
	      QTNAME(ob)+"'s "+hdesc+", but "+PRONOUN(ob)+" evades "+
		"the attack.";
	    tar = QCTNAME(liv)+" swings "+POSSESSIVE(liv)+" "+ weapon->short()+
	      " towards your "+hdesc+", but you evade the attack.";
	    aud = QCTNAME(liv)+" swings "+POSSESSIVE(liv)+" "+ weapon->short()+
	      " towards "+QTNAME(ob)+"'s "+hdesc+", but "+QTNAME(ob)+" evades "+
		"the attack.";
	}
	else if (hitresult[0] < 5)
	{
	    att = "You thrust with your "+weapon->short()+", and stab the "+
	      "point into "+QTNAME(ob)+"'s "+hdesc+".";
	    tar = QCTNAME(liv)+" thrusts with "+POSSESSIVE(liv)+" "+
	      weapon->short()+", and stabs the point into your "+hdesc+".";
	    aud = QCTNAME(liv)+" thrusts with "+POSSESSIVE(liv)+" "+
	      weapon->short()+", and stabs the point into "+QTNAME(ob)+
		"'s "+hdesc+".";
	}
	else if (hitresult[0] < 10)
	{
	    att = "You swing your "+weapon->short()+" at "+QTNAME(ob)+
	      ", striking "+POSSESSIVE(ob)+" "+hdesc+".";
	    tar = QCTNAME(liv)+" swings "+POSSESSIVE(liv)+" "+weapon->short()+
	      " at you, striking your "+hdesc+".";
	    aud = QCTNAME(liv)+" swings "+POSSESSIVE(liv)+" "+weapon->short()+
	      " at "+QTNAME(ob)+", striking "+POSSESSIVE(ob)+" "+hdesc+".";
	}
	else if (hitresult[0] < 20)
	{
	    att = "You drive your "+weapon->short()+" into "+QTNAME(ob)+
	      "'s "+hdesc+" with a forceful blow.";
	    tar = QCTNAME(liv)+" drives "+POSSESSIVE(liv)+" "+weapon->short()+
	      " into your "+hdesc+" with a forceful blow.";
	    aud = QCTNAME(liv)+" drives "+POSSESSIVE(liv)+" "+weapon->short()+
	      " into "+QTNAME(ob)+"'s "+hdesc+" with a forceful blow.";
	}
	else if (hitresult[0] < 35)
	{
	    att = "You drive your "+weapon->short()+" deep into "+QTNAME(ob)+
	      "'s "+hdesc+", causing a severe injury.";
	    tar = QCTNAME(liv)+" drives "+POSSESSIVE(liv)+" "+weapon->short()+
	      " deep into your "+hdesc+", causing a severe injury.";
	    aud = QCTNAME(liv)+" drives "+POSSESSIVE(liv)+" "+weapon->short()+
	      " deep into "+QTNAME(ob)+"'s "+hdesc+", causing a severe injury.";
	}
	else if (hitresult[0] < 50)
	{
	    att = "You raise your "+weapon->short()+" aloft, letting it fall "+
	      "with a crushing blow upon "+QTNAME(ob)+"'s "+hdesc+".";
	    tar = QCTNAME(liv)+" raises "+POSSESSIVE(liv)+" "+weapon->short()+
	      " aloft, letting it fall with a crushing blow upon your "+hdesc+
		".";
	    aud = QCTNAME(liv)+" raises "+POSSESSIVE(liv)+" "+weapon->short()+
	      " aloft, letting it fall with a crushing blow upon "+QTNAME(ob)+
		"'s "+hdesc+".";
	}
	else
	{
	    att = "You deliver a mortal wound to "+QTNAME(ob)+", impaling "+
	      POSSESSIVE(ob)+"'s "+hdesc+" with your "+
		weapon->short()+".";
	    tar = QCTNAME(liv)+" mortally wounds you, impaling your "+
	      hdesc+" with "+POSSESSIVE(liv)+" "+weapon->short()+".";
	    aud = QCTNAME(liv)+" mortally wounds "+QTNAME(ob)+", "+
	      "impaling "+POSSESSIVE(ob)+" "+hdesc+" with "+POSSESSIVE(liv)+
		" "+weapon->short()+".";
	}
    }
    else if (wt == W_CLUB) 
    {
	if (hitresult[0] < 1)
	{
	    att = "You swing your "+weapon->short()+" harmlessly at "+
	      QTNAME(ob)+"'s "+hdesc+".";
	    tar = QCTNAME(liv)+" swings "+POSSESSIVE(liv)+" "+weapon->short()+
	      " harmlessly at your "+hdesc+".";
	    aud = QCTNAME(liv)+" swings "+POSSESSIVE(liv)+" "+weapon->short()+
	      " harmlessly at "+QTNAME(ob)+"'s "+hdesc+".";
	}
	else if (hitresult[0] < 5)
	{
	    att = "Swinging hard with your "+weapon->short()+", you hit "+
	      QTNAME(ob)+" lightly on the "+hdesc+".";
	    tar = "Swinging hard with "+POSSESSIVE(liv)+" "+weapon->short()+
	      ", "+QTNAME(liv)+" hits you lightly on the "+hdesc+".";
	    aud = "Swinging hard with "+POSSESSIVE(liv)+" "+weapon->short()+
	      ", "+QTNAME(liv)+" hits "+QTNAME(ob)+" lightly on the "+
		hdesc+".";
	}
	else if (hitresult[0] < 10)
	{
	    att = "You thrust forward, bashing "+QTNAME(ob)+" with the hilt "+
	      "of your "+weapon->short()+".";
	    tar = QCTNAME(liv)+" thrusts forward, bashing you with the hilt "+
	      "of "+POSSESSIVE(liv)+" "+weapon->short()+".";
	    aud = QCTNAME(liv)+" thrusts forward, bashing "+QTNAME(ob)+" with "+
	      "the hilt of "+POSSESSIVE(liv)+" "+weapon->short()+".";
	}
	else if (hitresult[0] < 20)
	{
	    att = "With a fierce swing, you hurt "+QTNAME(ob)+"'s "+hdesc+
	      " with your "+weapon->short()+".";
	    tar = "With a fierce swing, "+QTNAME(liv)+" hurts your "+hdesc+
	      " with "+POSSESSIVE(liv)+" "+weapon->short()+".";
	    aud = "With a fierce swing, "+QTNAME(liv)+" hurts "+QTNAME(ob)+
	      "'s "+hdesc+" with "+POSSESSIVE(liv)+" "+ 
		weapon->short()+".";
	}
	else if (hitresult[0] < 35)
	{
	    att = "You raise your "+weapon->short()+" above your head "+
	      "and bring it crashing down on "+QTNAME(ob)+"'s "+hdesc+".";
	    tar = QCTNAME(liv)+" raises "+POSSESSIVE(liv)+" "+
	      weapon->short()+" above "+POSSESSIVE(liv)+" head and "+
		"brings it crashing down on your "+hdesc+".";
	    aud = QCTNAME(liv)+" raises "+POSSESSIVE(liv)+" "+
	      weapon->short()+" above "+POSSESSIVE(liv)+" head and "+
		"brings it crashing down upon "+QTNAME(ob)+"'s "+hdesc+".";
	}
	else if (hitresult[0] < 50)
	{
	    att = "You nearly shatter "+QTNAME(ob)+"'s "+hdesc+" with a "+
	      "devastating swing of your "+weapon->short()+".";
	    tar = QCTNAME(liv)+" nearly shatters your "+
	      hdesc+" with a devastating swing of "+POSSESSIVE(liv)+
		" "+weapon->short()+".";
	    aud = QCTNAME(liv)+" nearly shatters "+QTNAME(ob)+"'s "+hdesc+
	      " with a devastating swing of "+POSSESSIVE(liv)+" "+
		weapon->short()+".";
	}
	else 
	{
	    att = "You swing your "+weapon->short()+" at "+QTNAME(ob)+
	      " with all of your might, crushing "+POSSESSIVE(ob)+" "+
		hdesc+".";
	    tar = QCTNAME(liv)+" swings "+POSSESSIVE(liv)+" "+
	      weapon->short()+" at you with all of "+POSSESSIVE(liv)+
		" might, crushing your "+hdesc+".";
	    aud = QCTNAME(liv)+" swings "+POSSESSIVE(liv)+" "+
	      weapon->short()+" at "+QTNAME(ob)+" with all of "+
		POSSESSIVE(liv)+" might, crushing "+QTNAME(ob)+"'s "+
		  hdesc+".";
	}
    }
    else if (wt == W_AXE)
    {
	if (hitresult[0] < 1)
	{
	    att = "You swing your "+weapon->short()+" towards "+
	      QTNAME(ob)+"'s "+hdesc+", but "+PRONOUN(ob)+" evades "+
		"the attack.";
	    tar = QCTNAME(liv)+" swings "+POSSESSIVE(liv)+" "+ weapon->short()+
	      " towards your "+hdesc+", but you evade the attack.";
	    aud = QCTNAME(liv)+" swings "+POSSESSIVE(liv)+" "+ weapon->short()+
	      " towards "+QTNAME(ob)+"'s "+hdesc+", but "+QTNAME(ob)+" evades "+
		"the attack.";
	}
	else if (hitresult[0] < 5)
	{
	    att = "You lash out with your "+weapon->short()+" and lightly "+
	      "slash "+QTNAME(ob)+"'s "+hdesc+".";
	    tar = QCTNAME(liv)+" lashes out with "+POSSESSIVE(liv)+" "+
	      weapon->short()+", lightly slashing your "+hdesc+".";
	    aud = QCTNAME(liv)+" lashes out with "+POSSESSIVE(liv)+" "+
	      weapon->short()+", lightly slashing the "+hdesc+" of "+
		QTNAME(ob)+".";
	}
	else if (hitresult[0] < 10)
	{
	    att = "You bash "+QTNAME(ob)+"'s "+hdesc+" with the flat side of your "+
	      weapon->short()+".";
	    tar = QCTNAME(liv)+" bashes your "+hdesc+" with the flat side of "+
	      POSSESSIVE(ob)+" "+weapon->short()+".";
	    aud = QCTNAME(liv)+" bashes "+QTNAME(ob)+"'s "+hdesc+" with the flat "+
	      "side of "+POSSESSIVE(liv)+" "+weapon->short()+".";
	}
	else if (hitresult[0] < 20)
	{
	    att = "You rip deeply into "+QTNAME(ob)+"'s "+hdesc+" with your "+
	      weapon->short()+".";
	    tar = QCTNAME(liv)+" rips deeply into your "+hdesc+" with "+
	      POSSESSIVE(liv)+" "+weapon->short()+".";
	    aud = QCTNAME(liv)+" rips deeply into "+QTNAME(ob)+"'s "+hdesc+
	      " with "+POSSESSIVE(liv)+" "+weapon->short()+".";
	}
	else if (hitresult[0] < 35)
	{
	    att = "Swinging hard with your "+weapon->short()+", you slice a "+
	      "nasty gash into "+QTNAME(ob)+"'s "+hdesc+".";
	    tar = "Swinging hard with "+POSSESSIVE(liv)+" "+weapon->short()+
	      ", "+QTNAME(liv)+" slices a nasty gash into your "+hdesc+".";
	    aud = "Swinging hard with "+POSSESSIVE(liv)+" "+weapon->short()+
	      ", "+QTNAME(liv)+" slices a nasty gash into "+QTNAME(ob)+"'s "+
		hdesc+".";
	}
	else if (hitresult[0] < 50)
	{
	    att = "With an mighty swing, you cut to the bone of "+QTNAME(ob)+
	      "'s "+hdesc+" with the blade of your "+weapon->short()+".";
	    tar = QCTNAME(liv)+" cuts to the bone of your "+hdesc+" with a mighty "+
	      "blow of "+POSSESSIVE(liv)+" "+weapon->short()+".";
	    aud = QCTNAME(liv)+" swings "+POSSESSIVE(liv)+" "+weapon->short()+
	      "mightily, cutting to the bone of "+QTNAME(ob)+"'s "+hdesc+".";
	}
	else
	{
	    att = "You almost tear "+QTNAME(ob)+"'s "+hdesc+" off with a "+
	      "tremendous blow of your "+weapon->short()+".";
	    tar = QCTNAME(liv)+" almost tears your "+hdesc+" off with a "+
	      "tremendous blow of your "+weapon->short()+".";
	    aud = QCTNAME(liv)+" almost tears "+QTNAME(ob)+"'s "+hdesc+
	      " off with a tremendous blow of "+POSSESSIVE(liv)+" "+
		weapon->short()+".";
	}
    }
    else if (wt == W_KNIFE)
    {
	if (hitresult[0] < 1)
	{
	    att = "You swing your "+weapon->short()+" harmlessly at "+
	      QTNAME(ob)+"'s "+hdesc+".";
	    tar = QCTNAME(liv)+" swings "+POSSESSIVE(liv)+" "+weapon->short()+
	      " harmlessly at your "+hdesc+".";
	    aud = QCTNAME(liv)+" swings "+POSSESSIVE(liv)+" "+weapon->short()+
	      " harmlessly at "+QTNAME(ob)+"'s "+hdesc+".";
	}
	else if (hitresult[0] < 5)
	{
	    att = "You nick "+QTNAME(ob)+"'s "+hdesc+" with the tip of your "+
	      weapon->short()+".";
	    tar = QCTNAME(liv)+" nicks your "+hdesc+" with the tip of "+
	      POSSESSIVE(liv)+" "+weapon->short()+".";
	    aud = QCTNAME(liv)+" nicks "+QTNAME(ob)+" "+hdesc+" with the tip of "+
	      POSSESSIVE(liv)+" "+weapon->short()+".";
	}
	else if (hitresult[0] < 10)
	{
	    att = "You cut a shallow wound into "+QTNAME(ob)+" "+hdesc+
	      " with your "+weapon->short()+".";
	    tar = QCTNAME(liv)+" cuts a shallow wound into your "+hdesc+
	      " with "+POSSESSIVE(liv)+" "+weapon->short()+".";
	    aud = QCTNAME(liv)+" cuts a shallow wound into "+QTNAME(ob)+"'s "+
	      hdesc+" with "+POSSESSIVE(liv)+" "+weapon->short()+".";
	}
	else if (hitresult[0] < 20)
	{
	    att = "You slice into "+QTNAME(ob)+"'s "+hdesc+" with your "+
	      weapon->short()+".";
	    tar = QCTNAME(liv)+" slices into your "+hdesc+" with "+
	      POSSESSIVE(liv)+" "+weapon->short()+".";
	    aud = QCTNAME(liv)+" slices into "+QTNAME(ob)+"'s "+hdesc+
	      " with "+POSSESSIVE(liv)+" "+weapon->short()+".";
	}
	else if (hitresult[0] < 35)
	{
	    att = "Your "+weapon->short()+" bites deeply into "+
	      QTNAME(ob)+"'s "+hdesc+".";
	    tar = QCTNAME(liv)+"'s "+weapon->short()+" bites "+
	      "deeply into your "+hdesc+".";
	    aud = QCTNAME(liv)+"'s "+weapon->short()+" bites "+
	      "deeply into your "+hdesc+".";
	}
	else if (hitresult[0] < 50)
	{
	    att = "You carve a deep wound into the "+hdesc+" of "+
	      QTNAME(ob)+" with your "+weapon->short()+".";
	    tar = QCTNAME(liv)+" carves a deep wound into your "+hdesc+
	      " with "+POSSESSIVE(liv)+" "+weapon->short()+".";
	    aud = QCTNAME(liv)+" carves a deep wound into the "+hdesc+
	      " of "+QTNAME(ob)+" with "+POSSESSIVE(liv)+" "+
		weapon->short()+".";
	}
	else 
	{
	    att = "You pierce "+QTNAME(ob)+"'s defences with your "+
	      weapon->short()+", driving it deep into "+
		POSSESSIVE(ob)+" "+hdesc+".";
	    tar = QCTNAME(liv)+" pierces your defences with "+
	      POSSESSIVE(liv)+" "+weapon->short()+", driving "+
		"it deep into your "+hdesc+".";
	    aud = QCTNAME(liv)+" pierces "+QTNAME(ob)+"'s defences with "+
	      POSSESSIVE(liv)+" "+weapon->short()+", driving "+
		"it deep into "+POSSESSIVE(ob)+" "+hdesc+".";
	}
    }

    rcry = random(3);
    if (rcry == 2)
    {
	switch(random(10))
	{
	case 0:
	    cry = "For Vingaard and the Orders!";
	    break;
	case 1:
	    cry = "For the Orders!";
	    break;
	case 2:
	    cry = "Paladine!";
	    break;
	case 3:
	    cry = "By the Measure!";
	    break;
	case 4:
	    cry = "For Vingaard!";
	    break;
	case 5:
	    cry = "By the Oath and Measure!";
	    break;
	case 6:
	    cry = "Victory to the Knighthood!";
	    break;
	case 7:
	    cry = "For Solamnia!";
	    break;
	case 8:
	    cry = "For the Knighthood!";
	    break;
	case 9:
	    cry = "For the Triumvirate!";
	    break;
	}
	liv->catch_msg("You cry out: "+cry+"\n");
	liv->tell_watcher(QCTNAME(liv)+" cries out: "+cry+"\n");
    }
      
    liv->catch_msg(att+"\n");
    ob->catch_msg(tar+"\n");
    liv->tell_watcher(aud+"\n", ob);
    liv->remove_prop("_kspecial_preparing");
    liv->catch_msg("   DAMAGE -- "+hitresult[3]+"\n");
    liv->add_prop("_kspecial_resetting", 1);
    set_alarm(12.0, 0.0, "reset_special", liv);
    if (ob->query_hp() <= 0)
    {
	switch(random(2))
	{
	case 0:
	    liv->catch_msg("You wipe the blood from your "+weapon->short()+
			   " as you regard "+QTNAME(ob)+" solemnly, knowing "+POSSESSIVE(ob)+
			   " end is near.\n");
	    ob->catch_msg(QCTNAME(liv)+" wipes the blood from "+POSSESSIVE(liv)+
			  " "+weapon->short()+" as "+PRONOUN(liv)+" regards you solemnly.");
	    liv->tell_watcher(QCTNAME(liv)+" wipes the blood from "+POSSESSIVE(liv)+
			      " "+weapon->short()+" as "+PRONOUN(liv)+" regards "+QTNAME(ob)+
			      " solemnly.\n", ob);
	    break;
	case 1:
	    liv->catch_msg("You pledge anew your life to the Knighthood.\n");
	    liv->tell_watcher(QCTNAME(liv)+" pledges anew "+POSSESSIVE(liv)+
			      " life to the Knighthood.\n", ob);
	    ob->catch_msg(QCTNAME(liv)+" pledges anew "+POSSESSIVE(liv)+" life "+
			  "to the Knighthood.\n");
	    break;
	case 2:
	    liv->catch_msg("You fiercely declare: Est Sularus oth Mithas!\n");
	    liv->tell_watcher(QCTNAME(liv)+" fiercely declares: Est Sularus oth "+
			      "Mithas!\n", ob);
	    ob->catch_msg(QCTNAME(liv)+" fiercely declares: Est Sularus oth Mithas!\n");
	    break;
	}
	ob->do_die(TP);
    }
    return;
}

void
reset_special(object liv)
{
    liv->catch_msg("\nYou are able to attack again.\n\n");
    liv->remove_prop("_kspecial_resetting");
}

