/*************************************************************************/
/* <kattack> : the new damage special by Morrigan 11/12/96               */
/* <kattack> replaces bash and ckick.                                    */
/* Addition of percentages based on Knight level and two handed combat   */
/* added to make it more realistic. Addition of the <primary left/right> */
/* command to make it even more realistic. Percentages are outlined in   */
/* the documentation files in /d/Krynn/info/GUILDS/KNIGHTS/             */
/*************************************************************************/

/********************* kattack *******************************************/
object
query_shield(object liv)
{
    object *worn_armours;
    object shield;
    int i;

    worn_armours = liv->query_armour(-1);

    for (i = 0; i < sizeof(worn_armours); i++)
    {
	if (worn_armours[i]->query_at() == A_SHIELD)
	    shield = worn_armours[i];
    }

    return shield;
}

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

/* Added by Morrigan 11/14/1996 to make two-handed fighting more realistic */
/* See /d/Krynn/vin/knight/text/TAX_CHART for more information             */

object *
query_two_weapons(object liv)
{
    object sup_wep, inf_wep;
    int i = random(100) + 1;
    int j, pr, sen;
    object medal = P("pal_med", TP);

    pr = medal->query_primary();

    if (pr == 1)
    {
	sup_wep = liv->query_weapon(W_LEFT);
	inf_wep = liv->query_weapon(W_RIGHT);
    }
    else
    {
	sup_wep = liv->query_weapon(W_RIGHT);
	inf_wep = liv->query_weapon(W_LEFT);
    }

    if (liv->query_knight_level() == 3)
	j = (liv->query_skill(20) + 3 * liv->query_knight_sublevel() - 
	  random(liv->query_knight_sublevel()));
    else if (liv->query_knight_level() > 3)
    {
	if (liv->query_knight_sublevel() < 10)
	    j = (liv->query_skill(20) + 30 - random(10));
	else
	    j = (liv->query_skill(20) + 3 * liv->query_knight_sublevel() -
	      random(liv->query_knight_sublevel()));
    }
    else if (liv->query_knight_level() == 2)
    {
	if (liv->query_skill(20) > 50)
	    sen = 50;
	else
	    sen = liv->query_skill(20);
	j = (liv->query_skill(20) + 2 * liv->query_knight_sublevel() -
	  random(liv->query_knight_sublevel()));
    }

    if (pr = 2)
	if (random(2))
	    return ({ sup_wep, inf_wep });
	else
	    return ({ inf_wep, sup_wep });

    if (i < j)
	return ({ sup_wep, inf_wep });
    else
	return ({ inf_wep, sup_wep });
}

int
special(string str)
{
    object ob, *obj, weapon, *weapons;
    object liv = TP, medal = P("pal_med", TP);
    string how;
    int tmp;

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

    how = c_can_attack(ob, query_verb());
    if (stringp(how)) 
    {
	NF(how);
	return 0;
    }

    if (tmp = liv->query_prop("_kspecial_resetting"))
    {
	NF("You are not ready to attack again.\n");
	/* Safeguard to fix locked special attacks */
	if (time() > tmp + 20)
	    set_alarm(12.0, 0.0, "reset_special", liv);
	return 0;
    }

    if (liv->query_prop(LIVE_I_ATTACK_DELAY) || liv->query_prop(LIVE_I_STUNNED))
    {
	NF("You are too stunned to attack.\n");
	return 0;
    }

    if (tmp = liv->query_prop("_kspecial_preparing")) 
    {
	NF("You are already preparing to attack.\n");
	/* Safeguard to fix locked special attacks */
	if (time() > tmp + 20)
	{
	    NF("You are not ready to attack again.\n");
	    liv->remove_prop("_kspecial_preparing");
	    liv->add_prop("_kspecial_resetting",time());
	    set_alarm(12.0,0.0, "reset_special", liv);
	}
	return 0;
    }      
    else
    {
	if (sizeof(liv->query_weapon(-1)) == 2)
	    weapons = query_two_weapons(liv);
	else
	    weapon = query_weapon(liv);

	if (!weapon && !weapons)
	{
	    NF("You cannot attack without a weapon.\n");
	    return 0;
	}

	if (!weapon)
	{
	    if (medal->query_primary() == 0)
		weapon = liv->query_weapon(W_RIGHT);
	    else if (medal->query_primary() == 1)
		weapon = liv->query_weapon(W_LEFT);
	    else
		weapon = weapons[random(2)];
	}

	liv->add_prop("_kspecial_preparing", time());
	set_alarm(3.0, 0.0, "do_special", ob, liv);
	if (ob != liv->query_attack())
	{
	    say(QCTNAME(liv)+" raises "+POSSESSIVE(liv)+" "+weapon->short()+
	      " aloft, giving "+QTNAME(ob)+" a traditional salute as "+
	      PRONOUN(liv)+" rushes forward to do battle with "+OBJECTIVE(ob)+
	      "!\n", ({ ob, liv }));
	    ob->catch_msg(QCTNAME(liv)+" raises "+POSSESSIVE(liv)+" "+
	      weapon->short()+" aloft, giving you a traditional " +
	      "salute as "+PRONOUN(liv)+" rushes forward to do " +
	      "battle with you!\n");
	    liv->catch_msg("You raise your "+weapon->short()+" aloft, saluting "+
	      QTNAME(ob)+" traditionally as you rush forward to " +
	      "do battle with "+OBJECTIVE(ob)+"!\n");
	    liv->attack_object(ob);
	}
	else
	{
	    switch(random(5))
	    {
	    case 4:
		{
		    liv->catch_msg("You duck a fierce swing from "+QTNAME(ob)+
		      ", leaving "+OBJECTIVE(ob)+" off balance...\n");
		    break;
		}
	    case 3:
		{
		    liv->catch_msg(QCTNAME(ob)+" swings clumsily, leaving an opening "+
		      "in "+POSSESSIVE(ob)+" defence which you move to exploit...\n");
		    break;
		}
	    case 2:
		{
		    liv->catch_msg("You skillfully parry "+QTNAME(ob)+"'s attack, "+
		      "leaving "+OBJECTIVE(ob)+" open for a strike...\n");
		    break;
		}
	    case 1:
		{
		    liv->catch_msg("Dodging "+QTNAME(ob)+"'s blow, you move in to "+
		      "counterattack...\n");
		    break;
		}
	    default:
		{
		    liv->catch_msg("You feign an attack with your "+weapon->short()+
		      ", distracting "+QTNAME(ob)+", and follow through with the "+
		      "true attack...\n");
		    break;
		}
	    }
	}
	return 1;
    }
}

void
do_special(object ob, object liv)
{
    mixed hitresult;
    object weapon, shield, horse;
    object *weapons;
    int hitres, weaponmod, statmod, pen, skill, weaponstat, levmod;
    int wt, ht, rcry, rcry2, horsemod;
    string tar, att, aud, cry, hdesc, *dam;
    int i = random(2);

    tar = "";
    att = "";
    aud = "";

    if (!present(ob, environment(liv))) 
    {
	write("You are unable to attack your target.\n");
	liv->remove_prop("_kspecial_preparing");
	return;
    }

    if (sizeof(liv->query_weapon(-1)) == 2)
    {
	weapons = query_two_weapons(liv);
	weapon = weapons[0];
    }
    else
	weapon = query_weapon(liv);

    shield = query_shield(liv);

    if (!weapon && !weapons)
    {
	write("You cannot attack without a weapon.\n");
	liv->remove_prop("_kspecial_preparing");
	return;
    }

    /* New checks added - unseen opponent and opponents without bodies */
    if (!CAN_SEE(liv, ob) &&
      (random(100) > random(liv->query_skill(SS_BLIND_COMBAT) * 2)))
    {
	liv->catch_msg("Unable to see your opponent, you fail to connect with "+
	  "your "+weapon->short()+".\n");
	if (CAN_SEE(ob, liv))
	    ob->catch_msg(QCTNAME(liv)+" swings blindly with "+POSSESSIVE(liv)+
	      " "+weapon->short()+", missing you completely.\n");
	liv->tell_watcher(QCTNAME(liv)+" swings blindly with "+POSSESSIVE(liv)+
	  " "+weapon->short()+", missing "+QTNAME(ob)+" completely.\n");
	liv->remove_prop("_kspecial_preparing");
	liv->add_prop("_kspecial_resetting", time());
	set_alarm(12.0, 0.0, "reset_special", liv);
	return;
    }

    if (ob->query_prop(LIVE_I_NO_BODY) && !weapon->query_prop(OBJ_I_IS_MAGIC_WEAPON))
    {
	liv->catch_msg("Your "+weapon->short()+" passes through "+QTNAME(ob)+
	  ", leaving "+OBJECTIVE(ob)+" unharmed.\n");
	ob->catch_msg(QCTNAME(liv)+"'s "+weapon->short()+" passes through you, "+
	  "leaving you unharmed.\n");
	liv->tell_watcher(QCTNAME(liv)+"'s "+weapon->short()+" passes through "+
	  QTNAME(ob)+", leaving "+OBJECTIVE(ob)+" unharmed.\n");
	liv->remove_prop("_kspecial_preparing");
	liv->add_prop("_kspecial_resetting", time());
	set_alarm(12.0, 0.0, "reset_special", liv);
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
    /* Horse riders may gain up to 15 points benefit as well.  */
    /* 4- The total is used in F_PENMOD along with the skill level.      */
    /* 5- The result of F_PENMOD is used for pen in the hit_me function. */

    switch(liv->query_knight_level)
    {
    case 5:
	if (liv->query_knight_sublevel() == 11)
	    levmod = 11;
	else
	    levmod = 10;
	break;
    case 4:
	if (liv->query_knight_sublevel() == 11)
	    levmod = 11;
	else
	    levmod = 10;
	break;
    case 3:
	levmod = liv->query_knight_sublevel();
	break;
    case 2:
	levmod = (liv->query_knight_sublevel() / 2);
	break;
    case 1:
	levmod = (liv->query_knight_sublevel() / 2);
	break;
    default:
	levmod = 0;
	break;
    }

    /* Weapon stat formula */
    weaponstat = ((weapon->query_hit()+weapon->query_pen()) / 2);
    weaponmod = (weaponstat * 10 / 8);

    /* Stat formula */
    statmod = ((liv->query_stat(SS_STR)*2 + liv->query_stat(SS_INT) + 
	liv->query_stat(SS_DIS))/8);

    /* Stat cap, currently at 200 (perhaps to be lowered?) */
    if (statmod >= 100)
	statmod = 100;

    /* Bonus for riding on horseback */
    if (liv->query_mount() && liv->query_skill(SS_MOUNTED_COMBAT) > 15)
	horsemod = (liv->query_skill(SS_MOUNTED_COMBAT) - 15) / 4;

    /* Final formula */
    skill = TP->query_skill(SS_KATTACK);
    pen = (statmod + weaponmod) /2 + levmod;
    hitres = F_PENMOD(pen, skill);
    wt = weapon->query_wt();
    ht = weapon->query_dt();
    hitresult = ob->hit_me(hitres, ht, liv, -1);
    hdesc = hitresult[1];
    /* 1, 5, 10, 20, 35, 50 --  add 40 ? */

    if (wt == W_SWORD)
    {
	switch(hitresult[0])
	{
	case 0:
	    {
		att = "You swing your "+weapon->short()+" towards "+
		QTNAME(ob)+"'s "+hdesc+", but "+PRONOUN(ob)+" evades "+
		"the attack.";
		tar = QTNAME(liv)+" swings "+POSSESSIVE(liv)+" "+ weapon->short()+
		" towards your "+hdesc+", but you evade the attack.";
		aud = QTNAME(liv)+" swings "+POSSESSIVE(liv)+" "+ weapon->short()+
		" towards "+QTNAME(ob)+"'s "+hdesc+", but "+QTNAME(ob)+" evades "+
		"the attack.";
		break;
	    }
	case 1..5:
	    {
		att = "You lash out quickly with your "+weapon->short()+" and " +
		"lightly cut "+QTNAME(ob)+"'s "+hdesc+".";
		tar = QCTNAME(liv)+" lashes out quickly with "+POSSESSIVE(liv)+" "+
		weapon->short()+", lightly cutting your "+hdesc+".";
		aud = QCTNAME(liv)+" lashes out quickly with "+POSSESSIVE(liv)+" "+
		weapon->short()+", lightly cutting the "+hdesc+" of "+
		QTNAME(ob)+".";
		break;
	    }
	case 6..10:
	    {
		att = QCTNAME(ob)+" grabs your wrist as you attempt to bring your "+
		weapon->short()+" down upon "+POSSESSIVE(ob)+" "+hdesc+", but "+
		"you bring your leg up and kick "+OBJECTIVE(ob)+" hard in the "+
		"chest.";
		tar = "You grab "+QTNAME(liv)+"'s wrist as "+PRONOUN(liv)+" attempts "+
		"to bring "+POSSESSIVE(liv)+" down upon your "+hdesc+", but "+
		PRONOUN(liv)+" brings up his leg, kicking you hard in the chest.";
		aud = QCTNAME(liv)+" swings downward with "+POSSESSIVE(liv)+" "+
		weapon->short()+", but "+QTNAME(ob)+" grabs "+POSSESSIVE(liv)+
		" wrist. "+QCTNAME(liv)+" steps back and brings "+POSSESSIVE(liv)+
		" foot up, kicking "+QTNAME(ob)+" hard in the chest.";
		break;
	    }
	case 11..15:
	    {
		att = "You bash "+QTNAME(ob)+" with the hilt of your "+
		weapon->short()+", sending "+OBJECTIVE(ob)+" staggering "+
		"backwards.";
		tar = QCTNAME(liv)+" bashes you with the hilt of "+POSSESSIVE(liv)+
		" "+weapon->short()+", sending you staggering from the blow.";
		aud = QCTNAME(ob)+" is sent staggering backwards as "+QTNAME(liv)+
		" bashes "+OBJECTIVE(ob)+" with the hilt of "+POSSESSIVE(liv)+" "+
		weapon->short()+".";
		break;
	    }
	case 16..22:
	    {
		att = "You slash deeply into "+QTNAME(ob)+"'s "+hdesc+" with your "+
		weapon->short()+".";
		tar = QCTNAME(liv)+" slashes deeply into your "+hdesc+" with "+
		POSSESSIVE(liv)+" "+weapon->short()+".";
		aud = QCTNAME(liv)+" slashes deeply into "+QTNAME(ob)+"'s "+hdesc+
		" with "+POSSESSIVE(liv)+" "+weapon->short()+".";
		break;
	    }
	case 23..29:
	    {
		att = "Spotting an opening in "+QTNAME(ob)+"'s defence, you stab " +
		"forward and pierce "+POSSESSIVE(ob)+" "+hdesc+" with your "+
		weapon->short()+".";
		tar = QCTNAME(liv)+" stabs forward, spotting an opening in your " +
		"defence, and pierces your "+hdesc+" with "+POSSESSIVE(liv)+" "+
		weapon->short()+".";
		aud = QCTNAME(liv)+" stabs forward, spotting an opening in "+
		QTNAME(ob)+"'s defence, and pierces "+POSSESSIVE(ob)+" "+hdesc+
		" with "+POSSESSIVE(liv)+" "+weapon->short()+".";
	    }
	case 30..36:
	    {
		att = "You slash into "+QTNAME(ob)+"'s "+hdesc+" with your "+
		weapon->short()+", then bring it around again in a fierce "+
		"backhand swing, cutting deeply into "+POSSESSIVE(ob)+" body.";
		tar = QCTNAME(liv)+" slashes into your "+hdesc+" with "+POSSESSIVE(liv)+
		" "+weapon->short()+", then brings it around again in a "+
		"fierce backhand swing, cutting deeply into your body.";
		aud = QCTNAME(liv)+" slashes into "+QTNAME(ob)+"'s "+hdesc+" with "+
		POSSESSIVE(ob)+" "+weapon->short()+", then brings it around "+
		"again in a fierce backhand swing, cutting deeply into "+
		POSSESSIVE(ob)+" head.";
		break;
	    }
	case 37..43:
	    {
		att = "Side-stepping a wayward blow from "+QTNAME(ob)+", you "+
		"twirl and bring your "+weapon->short()+" around in a wide "+
		"arc, tearing a deep wound into "+POSSESSIVE(ob)+" "+hdesc+".";
		tar = QCTNAME(liv)+" side-steps your wayward blow and twirls, "+
		"bringing "+POSSESSIVE(liv)+" "+weapon->short()+" around in "+
		"a wide arc and tearing a deep wound into your "+hdesc+".";
		aud = QCTNAME(liv)+" side-steps "+QTNAME(ob)+"'s wayward blow and "+
		"twirls, bringing "+POSSESSIVE(liv)+" "+weapon->short()+
		" around in a wide arc and tearing a deep wound into "+QTNAME(ob)+
		"'s "+hdesc+".";
		break;
	    }
	case 44..50:
	    {
		att = "With a skillful swing, you open a large gash on "+QTNAME(ob)+
		"'s "+hdesc+" with the blade of your "+weapon->short()+".";
		tar = QCTNAME(liv)+" opens a large gash on your "+hdesc+" with a " +
		"skillful swing of "+POSSESSIVE(liv)+" "+weapon->short()+".";
		aud = QCTNAME(liv)+" opens a large gash on "+QTNAME(ob)+"'s "+hdesc+
		" with a skillful swing of "+POSSESSIVE(liv)+" "+
		weapon->short()+".";
		break;
	    }
	default:
	    {
		att = "You confidently lunge forward, driving the blade of your "+
		weapon->short()+" deep into "+QTNAME(ob)+"'s "+
		hdesc+".";
		tar = QCTNAME(liv)+" confidently lunges forward, driving the blade " +
		"of "+POSSESSIVE(liv)+" "+weapon->short()+" deep into "+
		"your "+hdesc+".";
		aud = QCTNAME(liv)+" confidently lunges forward, driving the blade " +
		"of "+POSSESSIVE(liv)+" "+weapon->short()+" deep into "+
		"the "+hdesc+" of "+QTNAME(ob)+".";
		break;
	    }
	}
    }
    else if (wt == W_POLEARM)
    {
	switch(hitresult[0])
	{
	case 0:
	    {
		att = "You swing your "+weapon->short()+" towards "+
		QTNAME(ob)+"'s "+hdesc+", but "+PRONOUN(ob)+" evades "+
		"the attack.";
		tar = QTNAME(liv)+" swings "+POSSESSIVE(liv)+" "+ weapon->short()+
		" towards your "+hdesc+", but you evade the attack.";
		aud = QTNAME(liv)+" swings "+POSSESSIVE(liv)+" "+ weapon->short()+
		" towards "+QTNAME(ob)+"'s "+hdesc+", but "+QTNAME(ob)+" evades "+
		"the attack.";
		break;
	    }
	case 1..5:
	    {
		att = "You thrust with your "+weapon->short()+", and stab the "+
		"point into "+QTNAME(ob)+"'s "+hdesc+".";
		tar = QCTNAME(liv)+" thrusts with "+POSSESSIVE(liv)+" "+
		weapon->short()+", and stabs the point into your "+hdesc+".";
		aud = QCTNAME(liv)+" thrusts with "+POSSESSIVE(liv)+" "+
		weapon->short()+", and stabs the point into "+QTNAME(ob)+
		"'s "+hdesc+".";
		break;
	    }
	case 6..10:
	    {
		att = "You swing your "+weapon->short()+" at "+QTNAME(ob)+
		", striking "+POSSESSIVE(ob)+" "+hdesc+".";
		tar = QCTNAME(liv)+" swings "+POSSESSIVE(liv)+" "+weapon->short()+
		" at you, striking your "+hdesc+".";
		aud = QCTNAME(liv)+" swings "+POSSESSIVE(liv)+" "+weapon->short()+
		" at "+QTNAME(ob)+", striking "+POSSESSIVE(ob)+" "+hdesc+".";
		break;
	    }
	case 11..20:
	    {
		att = QCTNAME(ob)+" grabs your wrist as you attempt to bring your "+
		weapon->short()+" down upon "+POSSESSIVE(ob)+" "+hdesc+", but "+
		"you bring your leg up and kick "+OBJECTIVE(ob)+" hard in the "+
		"chest.";
		tar = "You grab "+QTNAME(liv)+"'s wrist as "+PRONOUN(liv)+" attempts "+
		"to bring "+POSSESSIVE(liv)+" down upon your "+hdesc+", but "+
		PRONOUN(liv)+" brings up his leg, kicking you hard in the chest.";
		aud = QCTNAME(liv)+" swings downward with "+POSSESSIVE(liv)+" "+
		weapon->short()+", but "+QTNAME(ob)+" grabs "+POSSESSIVE(liv)+
		" wrist. "+QCTNAME(liv)+" steps back and brings "+POSSESSIVE(liv)+
		" foot up, kicking "+QTNAME(ob)+" hard in the chest.";
		break;
	    }
	case 21..30:
	    {
		att = "You drive your "+weapon->short()+" into "+QTNAME(ob)+
		"'s "+hdesc+" with a forceful blow.";
		tar = QCTNAME(liv)+" drives "+POSSESSIVE(liv)+" "+weapon->short()+
		" into your "+hdesc+" with a forceful blow.";
		aud = QCTNAME(liv)+" drives "+POSSESSIVE(liv)+" "+weapon->short()+
		" into "+QTNAME(ob)+"'s "+hdesc+" with a forceful blow.";
		break;
	    }
	case 31..40:
	    {
		att = "You drive your "+weapon->short()+" deep into "+QTNAME(ob)+
		"'s "+hdesc+", causing a severe injury.";
		tar = QCTNAME(liv)+" drives "+POSSESSIVE(liv)+" "+weapon->short()+
		" deep into your "+hdesc+", causing a severe injury.";
		aud = QCTNAME(liv)+" drives "+POSSESSIVE(liv)+" "+weapon->short()+
		" deep into "+QTNAME(ob)+"'s "+hdesc+", causing a severe injury.";
		break;
	    }
	case 41..50:
	    {
		att = "You raise your "+weapon->short()+" aloft, letting it fall "+
		"with a crushing blow upon "+QTNAME(ob)+"'s "+hdesc+".";
		tar = QCTNAME(liv)+" raises "+POSSESSIVE(liv)+" "+weapon->short()+
		" aloft, letting it fall with a crushing blow upon your "+hdesc+
		".";
		aud = QCTNAME(liv)+" raises "+POSSESSIVE(liv)+" "+weapon->short()+
		" aloft, letting it fall with a crushing blow upon "+QTNAME(ob)+
		"'s "+hdesc+".";
		break;
	    }
	default:
	    {
		att = "You deliver a mortal wound to "+QTNAME(ob)+", impaling "+
		POSSESSIVE(ob)+" "+hdesc+" with your "+
		weapon->short()+".";
		tar = QCTNAME(liv)+" mortally wounds you, impaling your "+
		hdesc+" with "+POSSESSIVE(liv)+" "+weapon->short()+".";
		aud = QCTNAME(liv)+" mortally wounds "+QTNAME(ob)+", "+
		"impaling "+POSSESSIVE(ob)+" "+hdesc+" with "+POSSESSIVE(liv)+
		" "+weapon->short()+".";
		break;
	    }
	}
    }
    else if (wt == W_CLUB) 
    {
	switch(hitresult[0])
	{
	case 0:
	    {
		att = "You swing your "+weapon->short()+" harmlessly at "+
		QTNAME(ob)+"'s "+hdesc+".";
		tar = QCTNAME(liv)+" swings "+POSSESSIVE(liv)+" "+weapon->short()+
		" harmlessly at your "+hdesc+".";
		aud = QCTNAME(liv)+" swings "+POSSESSIVE(liv)+" "+weapon->short()+
		" harmlessly at "+QTNAME(ob)+"'s "+hdesc+".";
		break;
	    }
	case 1..5:
	    {
		att = "Swinging hard with your "+weapon->short()+", you hit "+
		QTNAME(ob)+" lightly on the "+hdesc+".";
		tar = "Swinging hard with "+POSSESSIVE(liv)+" "+weapon->short()+
		", "+QTNAME(liv)+" hits you lightly on the "+hdesc+".";
		aud = "Swinging hard with "+POSSESSIVE(liv)+" "+weapon->short()+
		", "+QTNAME(liv)+" hits "+QTNAME(ob)+" lightly on the "+
		hdesc+".";
		break;
	    }
	case 6..10:
	    {
		att = "You thrust forward, bashing "+QTNAME(ob)+" with the hilt "+
		"of your "+weapon->short()+".";
		tar = QCTNAME(liv)+" thrusts forward, bashing you with the hilt "+
		"of "+POSSESSIVE(liv)+" "+weapon->short()+".";
		aud = QCTNAME(liv)+" thrusts forward, bashing "+QTNAME(ob)+" with "+
		"the hilt of "+POSSESSIVE(liv)+" "+weapon->short()+".";
		break;
	    }
	case 11..20:
	    {
		att = "With a fierce swing, you hurt "+QTNAME(ob)+"'s "+hdesc+
		" with your "+weapon->short()+".";
		tar = "With a fierce swing, "+QTNAME(liv)+" hurts your "+hdesc+
		" with "+POSSESSIVE(liv)+" "+weapon->short()+".";
		aud = "With a fierce swing, "+QTNAME(liv)+" hurts "+QTNAME(ob)+
		"'s "+hdesc+" with "+POSSESSIVE(liv)+" "+ 
		weapon->short()+".";
		break;
	    }
	case 21..30:
	    {
		att = "You raise your "+weapon->short()+" above your head "+
		"and bring it crashing down on "+QTNAME(ob)+"'s "+hdesc+".";
		tar = QCTNAME(liv)+" raises "+POSSESSIVE(liv)+" "+
		weapon->short()+" above "+POSSESSIVE(liv)+" head and "+
		"brings it crashing down on your "+hdesc+".";
		aud = QCTNAME(liv)+" raises "+POSSESSIVE(liv)+" "+
		weapon->short()+" above "+POSSESSIVE(liv)+" head and "+
		"brings it crashing down upon "+QTNAME(ob)+"'s "+hdesc+".";
		break;
	    }
	case 31..40:
	    {
		att = "You strike "+QTNAME(ob)+"'s "+hdesc+" with your "+
		weapon->short()+", then bring it around again in a powerful "+
		"backhand stroke, smashing it into "+QTNAME(ob)+"'s head.";
		tar = QCTNAME(liv)+" strikes your "+hdesc+" with " +
		POSSESSIVE(liv) +
		" "+weapon->short()+", then brings it around again in a "+
		"powerful backhand stroke, smashing it into your head.";
		aud = QCTNAME(liv)+" strikes "+QTNAME(ob)+"'s "+hdesc+" with "+
		POSSESSIVE(liv)+" "+weapon->short()+", then brings it around "+
		"again in a powerful backhand stroke, smashing it into "+
		QTNAME(ob)+"'s head.";
		break;
	    }
	case 41..50:
	    {
		att = "You nearly shatter "+QTNAME(ob)+"'s "+hdesc+" with a "+
		"devastating swing of your "+weapon->short()+".";
		tar = QCTNAME(liv)+" nearly shatters your "+
		hdesc+" with a devastating swing of "+POSSESSIVE(liv)+
		" "+weapon->short()+".";
		aud = QCTNAME(liv)+" nearly shatters "+QTNAME(ob)+"'s "+hdesc+
		" with a devastating swing of "+POSSESSIVE(liv)+" "+
		weapon->short()+".";
		break;
	    }
	default: 
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
		break;
	    }
	}
    }
    else if (wt == W_AXE)
    {
	switch(hitresult[0])
	{
	case 0:
	    {
		att = "You swing your "+weapon->short()+" towards "+
		QTNAME(ob)+"'s "+hdesc+", but "+PRONOUN(ob)+" evades "+
		"the attack.";
		tar = QTNAME(liv)+" swings "+POSSESSIVE(liv)+" "+ weapon->short()+
		" towards your "+hdesc+", but you evade the attack.";
		aud = QTNAME(liv)+" swings "+POSSESSIVE(liv)+" "+ weapon->short()+
		" towards "+QTNAME(ob)+"'s "+hdesc+", but "+QTNAME(ob)+" evades "+
		"the attack.";
		break;
	    }
	case 1..5:
	    {
		att = "You lash out with your "+weapon->short()+" and lightly "+
		"slash "+QTNAME(ob)+"'s "+hdesc+".";
		tar = QCTNAME(liv)+" lashes out with "+POSSESSIVE(liv)+" "+
		weapon->short()+", lightly slashing your "+hdesc+".";
		aud = QCTNAME(liv)+" lashes out with "+POSSESSIVE(liv)+" "+
		weapon->short()+", lightly slashing the "+hdesc+" of "+
		QTNAME(ob)+".";
		break;
	    }
	case 6..10:
	    {
		att = "You bash "+QTNAME(ob)+"'s "+hdesc+" with the flat side of " +
		"your "+weapon->short()+".";
		tar = QCTNAME(liv)+" bashes your "+hdesc+" with the flat side of "+
		POSSESSIVE(ob)+" "+weapon->short()+".";
		aud = QCTNAME(liv)+" bashes "+QTNAME(ob)+"'s "+hdesc+" with the " +
		"flat side of "+POSSESSIVE(liv)+" "+weapon->short()+".";
		break;
	    }
	case 11..20:
	    {
		att = QCTNAME(ob)+" grabs your wrist as you attempt to bring your "+
		weapon->short()+" down upon "+POSSESSIVE(ob)+" "+hdesc+", but "+
		"you bring your leg up and kick "+OBJECTIVE(ob)+" hard in the "+
		"chest.";
		tar = "You grab "+QTNAME(liv)+"'s wrist as "+PRONOUN(liv)+" attempts "+
		"to bring "+POSSESSIVE(liv)+" down upon your "+hdesc+", but "+
		PRONOUN(liv)+" brings up his leg, kicking you hard in the chest.";
		aud = QCTNAME(liv)+" swings downward with "+POSSESSIVE(liv)+" "+
		weapon->short()+", but "+QTNAME(ob)+" grabs "+POSSESSIVE(liv)+
		" wrist. "+QCTNAME(liv)+" steps back and brings "+POSSESSIVE(liv)+
		" foot up, kicking "+QTNAME(ob)+" hard in the chest.";
		break;
	    }
	case 21..30:
	    {
		att = "You rip deeply into "+QTNAME(ob)+"'s "+hdesc+" with your "+
		weapon->short()+".";
		tar = QCTNAME(liv)+" rips deeply into your "+hdesc+" with "+
		POSSESSIVE(liv)+" "+weapon->short()+".";
		aud = QCTNAME(liv)+" rips deeply into "+QTNAME(ob)+"'s "+hdesc+
		" with "+POSSESSIVE(liv)+" "+weapon->short()+".";
		break;
	    }
	case 31..40:
	    {
		att = "Swinging hard with your "+weapon->short()+", you slice a "+
		"nasty gash into "+QTNAME(ob)+"'s "+hdesc+".";
		tar = "Swinging hard with "+POSSESSIVE(liv)+" "+weapon->short()+
		", "+QTNAME(liv)+" slices a nasty gash into your "+hdesc+".";
		aud = "Swinging hard with "+POSSESSIVE(liv)+" "+weapon->short()+
		", "+QTNAME(liv)+" slices a nasty gash into "+QTNAME(ob)+"'s "+
		hdesc+".";
		break;
	    }
	case 41..50:
	    {
		att = "With a mighty swing, you cut to the bone of "+QTNAME(ob)+
		"'s "+hdesc+" with the blade of your "+weapon->short()+".";
		tar = QCTNAME(liv)+" cuts to the bone of your "+hdesc+" with a " +
		"mighty blow of "+POSSESSIVE(liv)+" "+weapon->short()+".";
		aud = QCTNAME(liv)+" swings "+POSSESSIVE(liv)+" "+weapon->short()+
		" mightily, cutting to the bone of "+QTNAME(ob)+"'s "+hdesc+".";
		break;
	    }
	default:
	    {
		att = "You almost tear "+QTNAME(ob)+"'s "+hdesc+" off with a "+
		"tremendous blow of your "+weapon->short()+".";
		tar = QCTNAME(liv)+" almost tears your "+hdesc+" off with a "+
		"tremendous blow of your "+weapon->short()+".";
		aud = QCTNAME(liv)+" almost tears "+QTNAME(ob)+"'s "+hdesc+
		" off with a tremendous blow of "+POSSESSIVE(liv)+" "+
		weapon->short()+".";
		break;
	    }
	}
    }
    else if (wt == W_KNIFE)
    {
	switch(hitresult[0])
	{
	case 0:
	    {
		att = "You swing your "+weapon->short()+" harmlessly at "+
		QTNAME(ob)+"'s "+hdesc+".";
		tar = QCTNAME(liv)+" swings "+POSSESSIVE(liv)+" "+weapon->short()+
		" harmlessly at your "+hdesc+".";
		aud = QCTNAME(liv)+" swings "+POSSESSIVE(liv)+" "+weapon->short()+
		" harmlessly at "+QTNAME(ob)+"'s "+hdesc+".";
		break;
	    }
	case 1..5:
	    {
		att = "You nick "+QTNAME(ob)+"'s "+hdesc+" with the tip of your "+
		weapon->short()+".";
		tar = QCTNAME(liv)+" nicks your "+hdesc+" with the tip of "+
		POSSESSIVE(liv)+" "+weapon->short()+".";
		aud = QCTNAME(liv)+" nicks "+QTNAME(ob)+" "+hdesc+" with the tip of "+
		POSSESSIVE(liv)+" "+weapon->short()+".";
		break;
	    }
	case 6..10:
	    {
		att = "You cut a shallow wound into "+QTNAME(ob)+" "+hdesc+
		" with your "+weapon->short()+".";
		tar = QCTNAME(liv)+" cuts a shallow wound into your "+hdesc+
		" with "+POSSESSIVE(liv)+" "+weapon->short()+".";
		aud = QCTNAME(liv)+" cuts a shallow wound into "+QTNAME(ob)+"'s "+
		hdesc+" with "+POSSESSIVE(liv)+" "+weapon->short()+".";
		break;
	    }
	case 11..20:
	    {
		att = "You slice into "+QTNAME(ob)+"'s "+hdesc+" with your "+
		weapon->short()+".";
		tar = QCTNAME(liv)+" slices into your "+hdesc+" with "+
		POSSESSIVE(liv)+" "+weapon->short()+".";
		aud = QCTNAME(liv)+" slices into "+QTNAME(ob)+"'s "+hdesc+
		" with "+POSSESSIVE(liv)+" "+weapon->short()+".";
		break;
	    }
	case 21..35:
	    {
		att = "Your "+weapon->short()+" bites deeply into "+
		QTNAME(ob)+"'s "+hdesc+".";
		tar = QCTNAME(liv)+"'s "+weapon->short()+" bites "+
		"deeply into your "+hdesc+".";
		aud = QCTNAME(liv)+"'s "+weapon->short()+" bites "+
		"deeply into your "+hdesc+".";
		break;
	    }
	case 36..50:
	    {
		att = "You carve a deep wound into the "+hdesc+" of "+
		QTNAME(ob)+" with your "+weapon->short()+".";
		tar = QCTNAME(liv)+" carves a deep wound into your "+hdesc+
		" with "+POSSESSIVE(liv)+" "+weapon->short()+".";
		aud = QCTNAME(liv)+" carves a deep wound into the "+hdesc+
		" of "+QTNAME(ob)+" with "+POSSESSIVE(liv)+" "+
		weapon->short()+".";
		break;
	    }
	default: 
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
		break;
	    }
	}
    }

    if (shield && !random(3))
    {
	switch(hitresult[0])
	{
	case 5..10:
	    {
		att = "You bash "+QTNAME(ob)+" with your "+shield->short()+", "+
		"sending "+OBJECTIVE(ob)+" staggering backwards.";
		tar = QCTNAME(liv)+" bashes you with "+POSSESSIVE(liv)+
		" "+shield->short()+", sending you staggering backwards.";
		aud = QCTNAME(ob)+" is sent staggering backwards as "+QTNAME(liv)+
		" bashes "+OBJECTIVE(ob)+" with "+POSSESSIVE(liv)+" "+
		shield->short()+".";
		break;
	    }
	case 11..20:
	    {
		att = "You send "+QTNAME(ob)+" sprawling as you fiercely slam "+
		"your "+shield->short()+" into "+POSSESSIVE(ob)+" chest.";
		tar = QCTNAME(liv)+" sends you sprawling as "+PRONOUN(liv)+
		" fiercely slams "+POSSESSIVE(liv)+" "+shield->short()+
		"into your chest.";
		aud = QCTNAME(liv)+" sends "+QTNAME(ob)+" sprawling as "+
		PRONOUN(liv)+" fiercely slams "+POSSESSIVE(liv)+" "+
		shield->short()+" into "+POSSESSIVE(ob)+" chest.";
		break;
	    }
	case 40..50:
	    {
		att = QCTNAME(ob)+"'s knees buckle and "+PRONOUN(ob)+" swoons "+
		"under the tremendous impact of your "+shield->short()+" as "+
		"you smash it into his body with a bone crushing sound.";
		tar = "You feel your knees buckle and you swoon under the trem"+
		"endous impact of "+QTNAME(liv)+"' "+shield->short()+" as "+
		PRONOUN(liv)+" smashes it into your body, with a bone "+
		"crushing sound.";
		aud = QCTNAME(ob)+"'s knees buckle and "+PRONOUN(ob)+" swoons "+
		"under the tremendous impact of "+QTNAME(liv)+"'s "+
		shield->short()+" as "+PRONOUN(liv)+" smashes it into "+
		POSSESSIVE(liv)+" body with a bone crushing sound.";
		break;
	    }
	}
    }

    if (weapons && TP->query_weapon(W_RIGHT)->query_wt() != W_POLEARM &&
      TP->query_weapon(W_LEFT)->query_wt() != W_POLEARM && !random(3))
    {
	switch(hitresult[0])
	{
	case 1..5:
	    {
		switch(wt)
		{
		case W_SWORD:
		    dam = ({ "quickly lash out with your "+weapon->short()+", "+
		      "lightly cutting "+QTNAME(ob)+"'s "+hdesc+".\n",
		      "quickly lashes out with "+POSSESSIVE(liv)+" "+weapon->short()+
		      ", lightly cutting your "+hdesc+".",
		      "quickly lashes out with "+POSSESSIVE(liv)+" "+weapon->short()+
		      ", lightly cutting "+QTNAME(ob)+"'s "+hdesc+"." });
		    break;
		case W_CLUB:
		    dam = ({ "swing hard with your "+weapon->short()+", "+
		      "hitting "+QTNAME(ob)+"'s "+hdesc+" lightly.",
		      "swings hard with "+POSSESSIVE(liv)+" "+weapon->short()+
		      ", hitting your "+hdesc+" lightly.",
		      "swings hard with "+POSSESSIVE(liv)+" "+weapon->short()+
		      ", hitting "+QTNAME(ob)+"'s "+hdesc+" lightly." });
		    break;
		case W_AXE:
		    dam = ({ "lash out with your "+weapon->short()+", lightly "+
		      "slashing "+QTNAME(ob)+"'s "+hdesc+".",
		      "lashes out with "+POSSESSIVE(liv)+" "+weapon->short()+
		      ", lightly slashing your "+hdesc+".",
		      "lashes out with "+POSSESSIVE(liv)+" "+weapon->short()+
		      ", lightly slashing "+QTNAME(ob)+"'s "+hdesc+"." });
		    break;
		case W_KNIFE:
		    dam = ({ "nick "+QTNAME(ob)+"'s "+hdesc+" with the tip of "+
		      "your "+weapon->short()+".",
		      "nicks your "+hdesc+" with the tip of "+POSSESSIVE(liv)+
		      " "+weapon->short()+".",
		      "nicks "+QTNAME(ob)+"'s "+hdesc+" with the tip of "+
		      POSSESSIVE(liv)+" "+weapon->short()+"." });
		    break;
		}

		att = "You bring up your "+weapons[1]->short()+" to parry "+
		"a blow from "+QTNAME(ob)+", and "+dam[0];
		tar = QCTNAME(liv)+" brings up "+POSSESSIVE(liv)+" "+
		weapons[1]->short()+" to parry a blow, and "+dam[1];
		aud = QCTNAME(liv)+" brings up "+POSSESSIVE(liv)+" "+
		weapons[1]->short()+" to parry a blow from "+QTNAME(ob)+
		", and "+dam[2];
		break;
	    }
	case 11..15:
	    {
		switch(wt)
		{
		case W_SWORD:
		    dam = ({ "slice into "+POSSESSIVE(ob)+" "+hdesc+" with your "+
		      weapon->short()+".",
		      "slices into your "+hdesc+" with "+POSSESSIVE(liv)+" "+
		      weapon->short()+".",
		      "slices into "+POSSESSIVE(ob)+" "+hdesc+" with "+
		      POSSESSIVE(liv)+" "+weapon->short()+"." });
		    break;
		case W_CLUB:
		    dam = ({ "strike "+POSSESSIVE(ob)+" "+hdesc+" hard with your "+
		      weapon->short()+".",
		      "strikes your "+hdesc+" hard with "+POSSESSIVE(liv)+" "+
		      weapon->short()+".",
		      "strikes "+QTNAME(ob)+"'s "+hdesc+" with "+POSSESSIVE(liv)+
		      weapon->short()+"." });
		    break;
		case W_AXE:
		    dam = ({ "tear a wound into "+POSSESSIVE(ob)+" "+hdesc+
		      " with your "+weapon->short()+".",
		      "tears a wound into your "+hdesc+" with "+POSSESSIVE(liv)+
		      " "+weapon->short()+".",
		      "tears a wound into "+QTNAME(ob)+"'s "+hdesc+" with "+
		      POSSESSIVE(liv)+" "+weapon->short()+"." });
		    break;
		case W_KNIFE:
		    dam = ({ "stab "+POSSESSIVE(ob)+" "+hdesc+" with your "+
		      weapon->short()+".",
		      "stabs into your "+hdesc+" with "+POSSESSIVE(liv)+" "+
		      weapon->short()+".",
		      "stabs into "+QTNAME(ob)+"'s "+hdesc+" with "+
		      POSSESSIVE(liv)+" "+weapon->short()+"." });
		    break;
		}

		att = "You swing at and miss "+QTNAME(ob)+" with your "+weapons[1]->short()+", but "+
		dam[0];
		tar = QCTNAME(liv)+" swings at you and misses with "+POSSESSIVE(liv)+
		" "+weapons[1]->short()+", but "+dam[1];
		aud = QCTNAME(liv)+" misses "+QTNAME(ob)+" with "+POSSESSIVE(liv)+
		" "+weapons[1]->short()+", but "+dam[2];
		break;
	    }
	case 25..33:
	    {
		switch(wt)
		{
		case W_SWORD:
		    dam = ({ "slash deeply into "+POSSESSIVE(ob)+" "+hdesc+" with your "+
		      weapon->short()+".",
		      "slashes deeply into your "+hdesc+" with "+POSSESSIVE(liv)+" "+
		      weapon->short()+".",
		      "slashes deeply into "+QTNAME(ob)+"'s "+hdesc+" with "+
		      POSSESSIVE(liv)+" "+weapon->short()+"." });
		    break;
		case W_CLUB:
		    dam = ({ "hurt "+POSSESSIVE(ob)+" "+hdesc+" badly with a fierce "+
		      "swing of your "+weapon->short()+".",
		      "hurt your "+hdesc+" badly with a fierce swing of "+
		      POSSESSIVE(liv)+" "+weapon->short()+".",
		      "hurts "+QTNAME(ob)+"'s "+hdesc+" badly with a fierce swing of "+
		      POSSESSIVE(liv)+" "+weapon->short()+"." });
		    break;
		case W_AXE:
		    dam = ({ "rips into "+POSSESSIVE(ob)+" "+hdesc+" with your "+
		      weapon->short()+".",
		      "rips into your "+hdesc+" with "+POSSESSIVE(liv)+" "+
		      weapon->short()+".",
		      "rips into "+QTNAME(ob)+"'s "+hdesc+" with "+POSSESSIVE(liv)+
		      " "+weapon->short()+"." });
		    break;
		case W_KNIFE:
		    dam = ({ "stab deeply into "+POSSESSIVE(ob)+" "+hdesc+" with your "+
		      weapon->short()+".",
		      "stabs deeply into your "+hdesc+" with "+POSSESSIVE(liv)+" "+
		      weapon->short()+".",
		      "stabs deeply into "+QTNAME(ob)+"'s "+hdesc+" with "+
		      POSSESSIVE(liv)+" "+weapon->short()+"." });
		    break;
		}     
		switch(weapons[1]->query_wt())
		{
		case W_SWORD:
		    att = "You slice a shallow wound in "+QTNAME(ob)+"'s body with "+
		    "your "+weapons[1]->short()+", and "+dam[0];
		    tar = QCTNAME(liv)+" slices a shallow wound into your body with "+
		    POSSESSIVE(liv)+" "+weapons[1]->short()+", and "+dam[1];
		    aud = QCTNAME(liv)+" slices a shallow wound into "+QTNAME(ob)+
		    "'s body with "+POSSESSIVE(liv)+" "+weapons[1]->short()+", "+
		    "and "+dam[2];
		    break;
		case W_CLUB:
		    att = "You strike "+QTNAME(ob)+"'s body with your "+
		    weapons[1]->short()+", and "+dam[0];
		    tar = QCTNAME(liv)+" strikes your body with "+POSSESSIVE(liv)+
		    weapons[1]->short()+", and "+dam[1];
		    aud = QCTNAME(liv)+" strikes "+QTNAME(ob)+"'s body with "+
		    POSSESSIVE(liv)+" "+weapons[1]->short()+", and "+dam[2];
		    break;
		case W_AXE:
		    att = "You slash into "+QTNAME(ob)+"'s body with your "+
		    weapons[1]->short()+", and "+dam[0];
		    tar = QCTNAME(liv)+" slashes into your body with "+
		    POSSESSIVE(liv)+" "+weapons[1]->short()+", and "+dam[1];
		    aud = QCTNAME(liv)+" slashes into "+QTNAME(ob)+"'s body "+
		    "with "+POSSESSIVE(liv)+" "+weapons[1]->short()+", and "+
		    dam[2];
		    break;
		case W_KNIFE:
		    att = "You stab "+QTNAME(ob)+"'s body with your "+
		    weapons[1]->short()+", and "+dam[0];
		    tar = QCTNAME(liv)+" stabs your body with "+POSSESSIVE(liv)+
		    " "+weapons[1]->short()+", and "+dam[1];
		    aud = QCTNAME(liv)+" stabs "+QTNAME(ob)+"'s body with "+
		    POSSESSIVE(liv)+" "+weapons[1]->short()+", and "+dam[2];
		    break;
		}
	    }
	case 43..50:
	    {
		switch(wt)
		{
		case W_SWORD:
		    dam = ({ "tear a gaping wound in "+POSSESSIVE(ob)+" "+hdesc+" with "+
		      "your "+weapon->short()+".",
		      "tears a gaping wound in your "+hdesc+" with "+POSSESSIVE(liv)+" "+
		      weapon->short()+".",
		      "tears a gaping wound in "+QTNAME(ob)+"'s "+hdesc+" with "+
		      POSSESSIVE(liv)+" "+weapon->short()+"." });
		    break;
		case W_CLUB:
		    dam = ({ "smash "+POSSESSIVE(ob)+" "+hdesc+" with a mighty "+
		      "blow of your "+weapon->short()+".",
		      "smashes your "+hdesc+" with a mighty blow of "+
		      POSSESSIVE(liv)+" "+weapon->short()+".",
		      "smashes "+QTNAME(ob)+"'s "+hdesc+" with a mighty blow of "+
		      POSSESSIVE(liv)+" "+weapon->short()+"." });
		    break;
		case W_AXE:
		    dam = ({ "cut to the bone of "+POSSESSIVE(ob)+" "+hdesc+" in a "+
		      "tremendous strike of your "+weapon->short()+".",
		      "cuts to the bone of your "+hdesc+" in a tremendous strike "+
		      "of "+POSSESSIVE(liv)+" "+weapon->short()+".",
		      "cuts to the bone of "+QTNAME(ob)+"'s "+hdesc+" with a "+
		      "tremendous strike of "+POSSESSIVE(liv)+" "+weapon->short()+"." });
		    break;
		case W_KNIFE:
		    dam = ({ "bury your "+weapon->short()+" to the hilt in "+
		      POSSESSIVE(ob)+" "+hdesc+".",
		      "buries "+POSSESSIVE(liv)+" "+weapon->short()+" to the "+
		      "hilt in your "+hdesc+".",
		      "buries "+POSSESSIVE(liv)+" "+weapon->short()+" to the "+
		      "hilt in "+QTNAME(ob)+"'s "+hdesc+"." });
		    break;
		}
		switch(weapons[1]->query_wt())
		{
		case W_SWORD:
		    att = "Driving the blade of your "+weapons[1]->short()+" deeply "+
		    "into "+ QTNAME(ob)+"'s arm, you also "+dam[0];
		    tar = "As "+PRONOUN(liv)+" drives the blade of " +
		    POSSESSIVE(liv) + " " + weapons[1]->short() +
		    " into your arm, " + QTNAME(liv) + " " + dam[1];
		    aud = "As " + QTNAME(liv) + " drives the blade of " +
		    POSSESSIVE(liv) + " " + weapons[1]->short() +
		    " into " + QTNAME(ob) + "'s arm, " + PRONOUN(liv) +
		    " also "+dam[2];
		    break;
		case W_CLUB:
		    att = "Bringing your "+weapons[1]->short()+" crashing down upon "+
		    QTNAME(ob)+"'s shoulder, you also "+dam[0];
		    tar = "As "+PRONOUN(liv)+" brings "+POSSESSIVE(liv)+" "+
		    weapons[1]->short()+" crashing down upon your shoulder, "+
		    QTNAME(liv)+" also "+dam[1];
		    aud = "As "+PRONOUN(liv)+" brings "+POSSESSIVE(liv)+" "+
		    weapons[1]->short()+" crashing down upon "+QTNAME(ob)+"'s "+
		    "shoulder, "+PRONOUN(liv)+" also "+dam[2];
		    break;
		case W_AXE:
		    att = "Nearly slashing through "+QTNAME(ob)+"'s arm with your "+
		    weapons[1]->short()+", you also "+dam[0];
		    tar = "As "+PRONOUN(liv)+" nearly slashes through your arm with "+
		    POSSESSIVE(liv)+" "+weapons[1]->short()+", "+QTNAME(liv)+
		    " also "+dam[1];
		    aud = "As "+PRONOUN(liv)+" nearly slashes through "+QTNAME(ob)+
		    "'s arm with "+POSSESSIVE(liv)+" "+weapons[1]->short()+", "+
		    QTNAME(liv)+" also "+dam[2];
		    break;
		case W_KNIFE:
		    att = "Plunging the length of your "+weapons[1]->short()+" into "+
		    QTNAME(ob)+"'s shoulder, you also "+dam[0];
		    tar = "As "+PRONOUN(liv)+" plunges the length of "+POSSESSIVE(liv)+
		    " "+weapons[1]->short()+" into your shoulder, "+QTNAME(liv)+
		    " also "+dam[1];
		    aud = "As "+PRONOUN(liv)+" plunges the length of "+POSSESSIVE(liv)+
		    " "+weapons[1]->short()+" into "+QTNAME(ob)+"'s shoulder, "+
		    QTNAME(ob)+" also "+dam[2];
		}
	    }
	}

    }

    if (liv->query_mount() && !random(1)) 
    {
	horse = liv->query_mount();

	switch(hitresult[0])
	{
	case 5..10:
	    {
		att = "You whirl your "+horse->short()+" around and "+
		POSSESSIVE(horse)+" flank slams into "+QTNAME(ob)+".";
		tar = QCTNAME(liv)+" whirls "+POSSESSIVE(liv)+" "+horse->short()+
		" around and slams its flank into you.";
		aud = QCTNAME(liv)+" whirls "+POSSESSIVE(liv)+" "+horse->short()+
		" around and slams its flank into "+QTNAME(ob)+".";
		break;
	    }
	case 11..18:
	    {
		att = "You spur your "+horse->short()+" forward and "+
		PRONOUN(horse)+" jerks "+POSSESSIVE(horse)+" head "+
		"upwards, nearly knocking "+QTNAME(ob)+" to the ground.";
		tar = QCTNAME(liv)+" spurs "+POSSESSIVE(liv)+" "+horse->short()+
		" forward and it jerks its head upwards, nearly knocking you "+
		"to the ground.";
		aud = QCTNAME(liv)+" spurs "+POSSESSIVE(liv)+" "+horse->short()+
		" forward and it jerks its head upwards, nearly knocking "+
		QTNAME(ob)+" to the ground.";
		break;
	    }
	case 30..40:
	    {
		att = "Your "+horse->short()+" rears back on "+POSSESSIVE(horse)+
		" hindlegs, smacking "+QTNAME(ob)+" heavily with its front "+
		"hooves, and knocking "+OBJECTIVE(ob)+" back a few steps.";
		tar = QCTNAME(liv)+"'s "+horse->short()+" rears back on its "+
		"hindlegs, smacking its front hooves into you heavily, and "+
		"knocking you backwards.";
		aud = QCTNAME(liv)+"'s "+horse->short()+" rears back on its "+
		"hindlegs, smacking "+QTNAME(ob)+" heavily with its front "+
		"hooves, and knocking "+OBJECTIVE(ob)+" backwards.";
		break;
	    }
	case 41..50:
	    {
		att = "Your bring your "+horse->short()+" around, and the well-"+
		"trained mount kicks "+QTNAME(ob)+" tremendously hard with its "+
		"hindlegs. "+QCTNAME(ob)+" looks dazed.";
		tar = QCTNAME(liv)+" brings "+POSSESSIVE(liv)+" "+horse->short()+
		" around, and the steed kicks you tremendously hard with its "+
		"hindlegs. You see stars.";
		aud = QCTNAME(liv)+" brings "+POSSESSIVE(liv)+" "+horse->short()+
		" around, and the steed kicks "+QTNAME(ob)+" tremendously hard "+
		"with its hindlegs. "+QCTNAME(ob)+" looks dazed.";
	    }
	}
    }

    rcry = random(3);
    if (!rcry && hitresult[0] >= 20)
    {
	switch(random(10))
	{
	case 0:
	    cry = "For Vingaard and the Orders!";
	    break;
	case 1:
	    switch(liv->query_knight_level())
	    {
	    case 5:
		cry = "For the Order of the Rose!";
		break;
	    case 4:
		cry = "For the Order of the Sword!";
		break;
	    case 3:
		cry = "For the Order of the Crown!";
		break;
	    default:
		cry = "For the Knighthood!";
		break;
	    }
	    break;
	case 2:
	    switch(liv->query_knight_level())
	    {
	    case 4:
		cry = "Kiri-Jolith!";
		break;
	    case 3:
		cry = "Habbakuk!";
		break;
	    default:
		cry = "Paladine!";
		break;
	    }
	    break;
	case 3:
	    cry = "By the Measure!";
	    break;
	case 4:
	    cry = "For Vingaard!";
	    break;
	case 5:
	    cry = "By the Oath and the Measure!";
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
	    switch(liv->query_knight_level())
	    {
	    case 5:
		cry = "In the name of justice!";
		break;
	    case 4:
		cry = "In the name of courage!";
		break;
	    case 3:
		cry = "In the name of honour!";
		break;
	    default:
		cry = "In the name of Solamnia!";
		break;
	    }
	    break;
	}
	if (!TP->query_prop("_i_quiet_knight"))
	    liv->command("$shout "+cry);
    }

    liv->catch_msg(att+"\n");
    ob->catch_msg(tar+"\n");
    liv->tell_watcher(aud+"\n", ob);
    liv->remove_prop("_kspecial_preparing");
    if (liv->query_wiz_level())
	liv->catch_msg("Hitresult = "+hitresult[0]+" : Damage = "+hitresult[3]+"\n");
    liv->add_prop("_kspecial_resetting", time());
    set_alarm(12.0, 0.0, "reset_special", liv);
    if (ob->query_hp() <= 0)
    {
	switch(random(3))
	{
	case 0:
	    liv->catch_msg("You wipe the blood from your "+weapon->short()+
	      " as you regard "+QTNAME(ob)+" solemnly, knowing "+
	      POSSESSIVE(ob)+" end is near.\n");
	    ob->catch_msg(QCTNAME(liv)+" wipes the blood from "+POSSESSIVE(liv)+
	      " "+weapon->short()+" as "+PRONOUN(liv)+" regards " +
	      "you solemnly.");
	    liv->tell_watcher(QCTNAME(liv)+" wipes the blood from "+
	      POSSESSIVE(liv)+" "+weapon->short()+" as "+
	      PRONOUN(liv)+" regards "+QTNAME(ob)+
	      " solemnly.\n", ob);
	    break;
	case 1:
	    if (ob->query_race_name() == "draconian")
	    {
		liv->catch_msg("You feel no remorse as you strike the killing blow, "+
		  "but rather you look with disgust at "+QTNAME(ob)+".\n");
		liv->tell_watcher(QCTNAME(liv)+" looks with disgust at "+QTNAME(ob)+
		  " as "+PRONOUN(liv)+" strikes the killing blow.\n", ob);
	    }
	    else
	    {
		liv->catch_msg("You feel a brief twinge of remorse as you strike "+
		  "the killing blow, but quickly regain your composure.\n");
		liv->tell_watcher(QCTNAME(liv)+"'s face softens briefly as "+
		  PRONOUN(liv)+" looks at "+QTNAME(ob)+", but "+PRONOUN(liv)+
		  " quickly regains "+POSSESSIVE(liv)+" cool composure.\n", ob);
		ob->catch_msg(QCTNAME(liv)+"'s face softens briefly as "+
		  PRONOUN(liv)+" he looks at you, but "+PRONOUN(liv)+" quickly "+
		  "regains "+POSSESSIVE(liv)+" cool composure.\n");
	    } 
	    break;
	case 2:
	    if (liv->query_mounted() && !random(3))
	    {
		liv->catch_tell("Your "+horse->short()+" rears back on "+POSSESSIVE(horse)+
		  " hindlegs, sending "+ob->query_the_name(liv)+" crashing to the ground "+
		  "with a crushing blow of its front hooves.\n");
		ob->catch_tell(liv->query_The_name(ob)+"'s "+horse->short()+" rears back "+
		  "on its hindlegs, sending you crashing to the ground with a crushing "+
		  "blow of its front hooves.\n");
		liv->tell_watcher(QCTNAME(liv)+"'s "+horse->short()+" rears back on its "+
		  "hindlegs, sending "+QTNAME(ob)+" crashing to the ground with a "+
		  "crushing blow of its front hooves.\n", ob);
	    }
	    else
	    {
		liv->catch_msg("Your blood surges with adrenaline as you realize "+
		  "you've survived yet another battle!\n");
		liv->tell_watcher(QCTNAME(liv)+" begins to calm down from the "+
		  "excitement of battle, having survived yet again.\n", ob);
	    }
	    break;
	}
	ob->do_die(TP);
    }
    return;
}

void
reset_special(object liv)
{
    liv->catch_msg("\nYou feel able to focus yourself towards your opponent " +
      "again.\n\n");
    liv->remove_prop("_kspecial_resetting");
}
