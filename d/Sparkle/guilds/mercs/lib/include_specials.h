/*
 * Mattack damage special for Mercenaries guild, by Morrigan 10/2001
 *    Adapted from kattack by Morrigan, 11/1996
 *
 * Updated and Moved to Sparkle by Lunatari 2006
 *
 * Changelog:
 * 2006-01-18 Lunatari 
 *  Updated set_alarms to use &func(arg) instead of "func", arg.
 *  Moved the special reset into the shadow, since it is also
 *  called from within the shadow on adjust_combat_on_move().            
 *
 * Special Formulas.
 *
 * Damage formula calculated as follows:                                      
 * 1 - weaponmod = 125% of the weapon's hit or pen                             
 * 2 - statmod   = 50% of the average of the str, int, dis, and guild stat for 
 *                 club users, dex, int, dis, and guild stat for sword users   
 * 3 - skillmod  = relevant weapon skill / 10                                 
 * 4 - skill     = SS_MERC_TACTICS skill                                      
 * 5 - pen       = (statmod + weaponmod ) / 2 + skillmod                      
 * 6 - F_PENMOD(pen, skill)                                                  
 *                                                                          
 * Resulting F_PENMOD for char with 100 stats/skills is 388                  
 * which works out to 41% combat aid     
 *                                                                      
 * standard round / time between attacks * pen / normal pen * cb_tohit %
 * (5 / 15 ) * (388 / 280) * 90% formula
 * 
 * The cb_tohit formula using MERC_TOHIT defined below.
 * Maximal at 140 OCC stat and a 40 weapon will be 110.
 *
 */
#define CLUB_STATMOD(x) (((x->query_stat(SS_STR) * 2 + x->query_stat(SS_INT) + x->query_stat(SS_DIS)) / 4 + x->query_stat(SS_OCCUP)) / 2) / 2
#define SWORD_STATMOD(x) (((x->query_stat(SS_DEX) * 2 + x->query_stat(SS_INT) + x->query_stat(SS_DIS)) / 4 + x->query_stat(SS_OCCUP)) / 2) / 2
#define NORM_STATMOD(x) (((x->query_stat(SS_INT) + x->query_stat(SS_DIS)) / 2 + x->query_stat(SS_OCCUP)) / 2) / 2
#define MERC_TOHIT(x,y) (MIN(65,(x->query_stat(SS_OCCUP)/2)) + MIN(45,y->query_hit()))
#define LOG_DIR "/d/Sparkle/guilds/mercs/log/mattack/"
#define LOG_MATTACK(x,y) write_file(LOG_DIR+(x->query_real_name()), ctime(time()) + " mAttack " + y + "\n")
//#define LOG_MATTACK(x,y) x->catch_msg(LOG_DIR+x->query_real_name() +" " + ctime(time()) + " mAttack " + y +"\n")

void reset_special(object ob);
void reset_defend(object ob);
void do_special(object ob, object liv);

/*
 * Function   : query_shield()
 * Description: Is this person wearing a shield?
 * Arguments  : the person to check
 * Returns    : the shield object
 */
public object
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

/*
 * Function   : query_weapon()
 * Description: Is this person wielding a weapon?
 * Arguments  : the person to check
 * Returns    : the weapon object
 */
public object
query_weapon(object liv)
{
    object *wielded_weapons;
    object wep, wep1, wep2;
    wielded_weapons = liv->query_weapon(-1);

    if (!sizeof(wielded_weapons))
	return 0;

    if (sizeof(wielded_weapons) == 1)
    {
       return wep = wielded_weapons[0];
    }

    if (sizeof(wielded_weapons) != 2)
        return 0;

    wep1 = wielded_weapons[0];
    wep2 = wielded_weapons[1];

    /* Mercenary is wielding two weapons, determine which 
     * weapon he will use for the attack. They prefer the 
     * weapon they are specialized in, or a sword or club 
     * over other weapons, if they aren't specialized
     */
    if (MEMBER_CLUB(liv))
    {
        if (wep1->query_wt() == W_CLUB && wep2->query_wt() == W_CLUB)
      	{
            if (random(2) == 0)
                return wep1;
               else
                return wep2;
      	}

        if (wep1->query_wt() == W_CLUB)
	    return wep1;

        if (wep2->query_wt() == W_CLUB)
	    return wep2;

	if (wep1->query_wt() == W_SWORD &&
	    wep2->query_wt() == W_SWORD)
	{
            if (random(2) == 0)
                return wep1;
               else
                return wep2;
	}

        if (wep1->query_wt() == W_SWORD)
	    return wep1;

	if (wep2->query_wt() == W_SWORD)
	    return wep2;
    }
   else if (MEMBER_SWORD(liv))
    {
	if (wep1->query_wt() == W_SWORD &&
	    wep2->query_wt() == W_SWORD)
	{
            if (random(2) == 0)
                return wep1;
               else
                return wep2;
	}

        if (wep1->query_wt() == W_SWORD)
	    return wep1;

	if (wep2->query_wt() == W_SWORD)
	    return wep2;

        if (wep1->query_wt() == W_CLUB &&
	    wep2->query_wt() == W_CLUB)
	{
            if (random(2) == 0)
                return wep1;
               else
                return wep2;
	}

        if (wep1->query_wt() == W_CLUB)
	    return wep1;

        if (wep2->query_wt() == W_CLUB)
	    return wep2;
    }
   else
    {
        if ((wep1->query_wt() == W_SWORD ||
	     wep1->query_wt() == W_CLUB) &&
	    (wep2->query_wt() == W_SWORD ||
	     wep2->query_wt() == W_CLUB))
	{
	    if (random(2) == 0)
		return wep1;
	       else
		return wep2;
	}

        if (wep1->query_wt() == W_SWORD || 
	    wep1->query_wt() == W_CLUB)
	    return wep1;

	if (wep2->query_wt() == W_SWORD ||
	    wep2->query_wt() == W_CLUB)
	    return wep2;
    }

    /* Try to use a knife if all else fails */
    if ((wep1->query_wt() == W_KNIFE ||
        wep1->query_wt() == W_KNIFE) &&
	(wep2->query_wt() == W_KNIFE ||
	 wep2->query_wt() == W_KNIFE))
    {
	if (random(2) == 0)
	    return wep1;
	   else
	    return wep2;
    }

    if (wep1->query_wt() == W_KNIFE || 
        wep1->query_wt() == W_KNIFE)
        return wep1;

    if (wep2->query_wt() == W_KNIFE ||
	wep2->query_wt() == W_KNIFE)
	return wep2;
}

/*
 * Function   : sever_limb()
 * Description: Cut off a limb from this person, at present only a head
 * Arguments  : piece: the body part
 *              metname: the metname of the soon to be corpse
 *              nonmetname: the nonmetname of the soon to be corpse
 *              killer: the killer of this person
 * Returns    : void
 */
void
sever_limb(string piece, string metname, string nonmetname, object killer)
{
    object corpse, part, me = killer;
    string *str, *message, tmp;
    int i;

    corpse = present("corpse", environment(me));
    if (corpse->query_npc())
        corpse = 0;

    if(!corpse)
        return;

    if (piece == "body")
        piece = "head";

    setuid(); seteuid(getuid());

    switch(piece)
    {
    case "head":
        corpse->set_short("headless "+corpse->short());
        corpse->remove_leftover("scalp");
        corpse->remove_leftover("skull");
        part = clone_object(MOBJ + "severed_head");
        part->config(metname, nonmetname);
        part->move(environment(corpse));
        break;
    }

}

/*
 * Function   : set_sever_corpse()
 * Description: set whether or not we will sever the head of this corpse
 * Arguments  : ob: the person, i: 0 if no, 1 if yes
 * Returns    : void
 */
void set_sever_corpse(object ob, int i)
{
    if (i == 0)
	ob->remove_prop("_merc_i_sever_corpse");
       else
	ob->add_prop("_merc_i_sever_corpse", 1);

}

/*
 * Function   : query_sever_corpse()
 * Description: do we sever the head of this corpse?
 * Arguments  : ob: the person
 * Returns    : 1 if yes we do, 0 if no we do not
 */
int query_sever_corpse(object ob)
{
    if (ob->query_prop("_merc_i_sever_corpse"))
	return 1;

    return 0;
}

/*
 * Function   : get_mercattack_death_messages()
 * Description: Get the description of the mattack special on killing someone
 * Arguments  : liv: the attacker
 *              ob: the attacked person
 *              weapon: the weapon used for the attack
 *              hdesc: the body part we are hitting
 * Returns    : an array of strings for the attacker, target, audience
 */
string *get_mercattack_death_messages(object liv, object ob, 
object weapon, string hdesc)
{
    string *messages, att, tar, aud, tmp;

    if (weapon->query_wt() == W_CLUB && ob->query_humanoid())
    {
        switch(random(4))
	{
	case 3:
	    {
		att = "Dodging "+ob->query_the_name(liv)+"'s attack "+
		    "at the last minute, you duck and swing upward "+
		    "with your "+weapon->short()+", catching "+
		    OBJECTIVE(ob)+" under the chin. "+
		    ob->query_The_name(liv)+"'s head snaps back with "+
		    "a sickening crack as "+POSSESSIVE(ob)+" neck breaks "+
		    "and "+PRONOUN(ob)+" falls backward, lifeless.";
		tar = "Dodging your attack at the last minute, "+
		    liv->query_the_name(ob)+" ducks and swings upward "+
		    "with "+POSSESSIVE(liv)+" "+weapon->short()+", "+
		    "catching you under the chin. Your head snaps back "+
		    "violently and you feel yourself falling.";
		aud = "Dodging "+QTNAME(ob)+"'s attack at the last "+
		    "minute, "+QTNAME(liv)+" ducks and swings upward "+
		    "with "+POSSESSIVE(liv)+" "+weapon->short()+", "+
		    "catching "+QTNAME(ob)+" under the chin. "+
		    capitalize(POSSESSIVE(ob))+" head snaps back with "+
		    "a sickening crack as "+POSSESSIVE(ob)+" neck "+
		    "breaks.";
		break;
	    }
	case 2:
	    {
		att = "You leap forward, doubling "+ob->query_the_name(liv)+
		   " over with a solid blow to the body. Standing, you bring "+
		   "your "+weapon->short()+" down upon the back of "+
		   POSSESSIVE(ob)+" neck with a crushing blow, hurling "+
		   OBJECTIVE(ob)+" to the ground in a lifeless heap.";
		tar = "You double over as "+liv->query_the_name(ob)+" leaps "+
		   "forward, striking you with a solid blow to the body. Before "+
		   "you can recover, you feel a crushing blow upon the back "+
		   "of your neck.";
		aud = QCTNAME(liv)+" leaps forward, doubling "+QTNAME(ob)+
		   "over with a solid blow to the body. Standing, "+QTNAME(liv)+
		   " brings "+POSSESSIVE(liv)+" "+weapon->short()+" down upon "+
		   "the back of "+QTNAME(ob)+"'s neck with a crushing blow, "+
		   "hurling "+OBJECTIVE(ob)+" to the ground in a lifeless heap.";
		break;
	    }
	case 1:
	    {
		att = "Anticipating the attack of "+ob->query_the_name(liv)+
		   ", you move faster, and crush "+POSSESSIVE(ob)+" skull with "+
		   "your "+weapon->short()+" before "+PRONOUN(ob)+" can "+
		   "defend "+OBJECTIVE(ob)+"self.";
		tar = "As you move to attack "+liv->query_the_name(ob)+", "+
		   PRONOUN(liv)+" springs into action. You blink confusedly as "+
		   "your vision fades, noting with fear that you cannot feel "+
		   "your legs.";
		aud = "As "+QTNAME(ob)+" moves to attack, "+QTNAME(liv)+
		   " springs into action, crushing "+QTNAME(ob)+"'s skull "+
		   "with "+POSSESSIVE(liv)+" "+weapon->short()+" before "+
		   PRONOUN(ob)+" can react.";
		break;
	     }
	default:
	    {
               tmp = (random(2) ? "left" : "right");

		att = "You render "+ob->query_the_name(liv)+"'s "+tmp+
		    " arm useless with a "+
		    "brutal swing of your "+weapon->short()+". No longer "+
		    "able to defend "+OBJECTIVE(ob)+"self, you end "+
		    POSSESSIVE(ob)+" life with a final, crushing blow "+
		    "to "+POSSESSIVE(ob)+" head.";
		tar = liv->query_The_name(ob)+" renders your "+tmp+" arm "+
		    "with a brutal swing of "+POSSESSIVE(liv)+" "+
		    weapon->short()+". Unable to defend yourself, you "+
		    "watch in horror as the "+weapon->short()+" flies "+
		    "unhindered into your face.";
		aud = QCTNAME(liv)+" renders "+QTNAME(ob)+"'s "+tmp+" arm "+
		    "useless with a brutal swing of "+POSSESSIVE(liv)+" "+
		    weapon->short()+". Unable to defend himself, "+QTNAME(ob)+
		    " stares in disbelief as the "+weapon->short()+" smashes "+
		    "directly into "+POSSESSIVE(ob)+" head.";
            }
	}
    }
   else if (weapon->query_wt() == W_CLUB)
    {
		att = "Seizing your opportunity, you move in for the kill with "+
			"your "+weapon->short()+". Swinging hard, you shatter "+
			ob->query_the_name(liv)+"'s "+hdesc+".";
		tar = liv->query_the_name(ob)+" moves in for the kill with "+
			POSSESSIVE(liv)+" "+weapon->short()+", shattering "+
			"your "+hdesc+".";
		aud = QCTNAME(liv)+"  moves in closer to "+QTNAME(ob)+", "+
			"shattering "+POSSESSIVE(ob)+" "+hdesc+" with a "+
			"devastating swing of "+POSSESSIVE(liv)+" "+
			weapon->short()+".";
    }
   else if (weapon->query_wt() == W_SWORD && ob->query_humanoid())
    {
        switch(random(4))
	{
	case 3:
	    {
		att = "Dodging "+ob->query_the_name(liv)+"'s attack "+
		    "at the last minute, you duck and stab upwards "+
		    "with your "+weapon->short()+", burying it in "+
		    POSSESSIVE(ob)+" chest to the hilt. You pull the "+
		    weapon->short()+" free, and "+ob->query_the_name(liv)+
		    " falls lifeless to the ground at your feet.";
		tar = "Dodging your attack at the last minute, "+
		    liv->query_the_name(ob)+" ducks and stabs upward "+
		    "with "+POSSESSIVE(liv)+" "+weapon->short()+", "+
		    "burying it in your chest. You feel your legs give "+
		    "out beneath you as "+PRONOUN(liv)+" pulls the blade "+
		    "free.";
		aud = "Dodging "+QTNAME(ob)+"'s attack at the last "+
		    "minute, "+QTNAME(liv)+" ducks and stabs upward "+
		    "with "+POSSESSIVE(liv)+" "+weapon->short()+", "+
		    "burying it in "+POSSESSIVE(ob)+"'s chest to the hilt. "+
		    QCTNAME(ob)+" falls lifeless to the ground as "+
		    QTNAME(liv)+" pulls the "+weapon->short()+" free.";
		break;
	    }
	case 2:
	    {
		att = "You leap forward, doubling "+ob->query_the_name(liv)+
		   " over with a vicious cut to the body. Standing, you bring "+
		   "your "+weapon->short()+" down upon the back of "+
		   POSSESSIVE(ob)+" neck with precision and speed. "+
		   capitalize(POSSESSIVE(ob))+" head strikes the ground "+
		   "only a second before "+POSSESSIVE(ob)+" body.";
		tar = "You double over as "+liv->query_the_name(ob)+" leaps "+
		   "forward, "+POSSESSIVE(liv)+" "+weapon->short()+" "+
		   "viciously slashing your body. Before "+
		   "you can recover, you feel a sharp pain on the back of "+
		   "your neck.";
		aud = QCTNAME(liv)+" leaps forward, doubling "+QTNAME(ob)+
		   "over with a vicious cut to the body. Standing, "+QTNAME(liv)+
		   " brings "+POSSESSIVE(liv)+" "+weapon->short()+" down upon "+
		   "the back of "+QTNAME(ob)+"'s neck with precision and speed. "+
		   capitalize(POSSESSIVE(ob))+" head strikes the ground only "+
		   "a second before "+POSSESSIVE(ob)+" body.";
                set_sever_corpse(liv,1);
		break;
	    }
	case 1:
	    {
		att = "Anticipating the attack of "+ob->query_the_name(liv)+
		   ", you move faster, and slash "+POSSESSIVE(ob)+" throat with "+
		   "your "+weapon->short()+" before "+PRONOUN(ob)+" can "+
		   "defend "+OBJECTIVE(ob)+"self.";
		tar = "As you move to attack "+liv->query_the_name(ob)+", "+
		   PRONOUN(liv)+" springs into action. You blink confusedly as "+
		   "your vision fades, noting with fear that you cannot feel "+
		   "your legs.";
		aud = "As "+QTNAME(ob)+" moves to attack, "+QTNAME(liv)+
		   " springs into action, slashing "+QTNAME(ob)+"'s throat "+
		   "with "+POSSESSIVE(liv)+" "+weapon->short()+" before "+
		   PRONOUN(ob)+" can react.";
		break;
	     }
	default:
	    {
		att = "You leap past "+ob->query_the_name(liv)+", reversing your "+
		   "grip on the "+ weapon->short()+" and driving it into "+
		   POSSESSIVE(ob)+" back. You pull the "+weapon->short()+" free "+
		   "as you stand and turn to watch "+OBJECTIVE(ob)+" slump to "+
		   POSSESSIVE(ob)+" knees before falling on "+POSSESSIVE(ob)+
		   " face.";
		tar = QCTNAME(liv)+" suddenly leaps past you, ducking under "+
		   "your attack. Before you can turn around to face "+
		   OBJECTIVE(liv)+", pain erupts from deep within your gut. "+
		   "You feel yourself slump to your knees as your vision "+
		   "slowly fades away.";
		aud = QCTNAME(liv)+" leaps past "+QTNAME(ob)+", reversing "+
		   POSSESSIVE(liv)+" grip on the "+weapon->short()+" and "+
		   "driving it into "+QTNAME(ob)+"'s back. "+
		   capitalize(PRONOUN(ob))+" slowly slumps to "+POSSESSIVE(ob)+
		   " knees before falling on "+POSSESSIVE(ob)+" face.";
		break;
            }
	}
    }
   else if (weapon->query_wt() == W_SWORD)
    {
		att = "Seizing your opportunity, you move in for the kill with "+
			"your "+weapon->short()+". You drive the blade deep "+
			"into "+ob->query_the_name(liv)+"'s "+hdesc+".";
		tar = liv->query_the_name(ob)+" moves in for the kill with "+
			POSSESSIVE(liv)+" "+weapon->short()+", driving the "+
			"blade deep into your "+hdesc+".";
		aud = QCTNAME(liv)+" moves in closer to "+QTNAME(ob)+", "+
			"driving "+POSSESSIVE(liv)+" "+weapon->short()+
			" deep into "+QTNAME(ob)+"'s "+hdesc+".";
    }
   else if (weapon->query_wt() == W_KNIFE && ob->query_humanoid())
    {
        switch(random(4))
	{
	case 3:
	    {
		att = "Dodging "+ob->query_the_name(liv)+"'s attack "+
		    "at the last minute, you duck and stab upwards "+
		    "with your "+weapon->short()+", burying it in "+
		    POSSESSIVE(ob)+" chest to the hilt. You pull the "+
		    weapon->short()+" free, and "+ob->query_the_name(liv)+
		    " falls lifeless to the ground at your feet.";
		tar = "Dodging your attack at the last minute, "+
		    liv->query_the_name(ob)+" ducks and stabs upward "+
		    "with "+POSSESSIVE(liv)+" "+weapon->short()+", "+
		    "burying it in your chest. You feel your legs give "+
		    "out beneath you as "+PRONOUN(liv)+" pulls the blade "+
		    "free.";
		aud = "Dodging "+QTNAME(ob)+"'s attack at the last "+
		    "minute, "+QTNAME(liv)+" ducks and stabs upward "+
		    "with "+POSSESSIVE(liv)+" "+weapon->short()+", "+
		    "burying it in "+POSSESSIVE(ob)+"'s chest to the hilt. "+
		    QCTNAME(ob)+" falls lifeless to the ground as "+
		    QTNAME(liv)+" pulls the "+weapon->short()+" free.";
		break;
	    }
	case 2:
	    {
		att = "You leap forward, doubling "+ob->query_the_name(liv)+
		   " over with a vicious cut to the body. Standing, you bring "+
		   "your "+weapon->short()+" down into the base of "+
		   POSSESSIVE(ob)+" skull with precision and speed.";
		tar = "You double over as "+liv->query_the_name(ob)+" leaps "+
		   "forward, "+POSSESSIVE(liv)+" "+weapon->short()+" "+
		   "viciously slashing your body. Before "+
		   "you can recover, you feel a sharp pain on the back of "+
		   "your neck.";
		aud = QCTNAME(liv)+" leaps forward, doubling "+QTNAME(ob)+
		   "over with a vicious cut to the body. Standing, "+QTNAME(liv)+
		   " brings "+POSSESSIVE(liv)+" "+weapon->short()+" down into "+
		   "the base of "+QTNAME(ob)+"'s skull with precision and speed.";
		break;
	    }
	case 1:
	    {
		att = "Anticipating the attack of "+ob->query_the_name(liv)+
		   ", you move faster, and slash "+POSSESSIVE(ob)+" throat with "+
		   "your "+weapon->short()+" before "+PRONOUN(ob)+" can "+
		   "defend "+OBJECTIVE(ob)+"self.";
		tar = "As you move to attack "+liv->query_the_name(ob)+", "+
		   PRONOUN(liv)+" springs into action. You blink confusedly as "+
		   "your vision fades, noting with fear that you cannot feel "+
		   "your legs.";
		aud = "As "+QTNAME(ob)+" moves to attack, "+QTNAME(liv)+
		   " springs into action, slashing "+QTNAME(ob)+"'s throat "+
		   "with "+POSSESSIVE(liv)+" "+weapon->short()+" before "+
		   PRONOUN(ob)+" can react.";
		break;
	     }
	default:
	    {
		att = "You leap past "+ob->query_the_name(liv)+", reversing your "+
		   "grip on the "+ weapon->short()+" and driving it into "+
		   POSSESSIVE(ob)+" back. You pull the "+weapon->short()+" free "+
		   "as you stand and turn to watch "+OBJECTIVE(ob)+" slump to "+
		   POSSESSIVE(ob)+" knees before falling on "+POSSESSIVE(ob)+
		   " face.";
		tar = QCTNAME(liv)+" suddenly leaps past you, ducking under "+
		   "your attack. Before you can turn around to face "+
		   OBJECTIVE(liv)+", pain erupts from deep within your gut. "+
		   "You feel yourself slump to your knees as your vision "+
		   "slowly fades away.";
		aud = QCTNAME(liv)+" leaps past "+QTNAME(ob)+", reversing "+
		   POSSESSIVE(liv)+" grip on the "+weapon->short()+" and "+
		   "driving it into "+QTNAME(ob)+"'s back. "+
		   capitalize(PRONOUN(ob))+" slowly slumps to "+POSSESSIVE(ob)+
		   " knees before falling on "+POSSESSIVE(ob)+" face.";
		break;
            }
	}
    }
   else if (weapon->query_wt() == W_KNIFE)
    {
		att = "Seizing your opportunity, you move in for the kill with "+
			"your "+weapon->short()+". You drive the blade deep "+
			"into "+ob->query_the_name(liv)+"'s "+hdesc+".";
		tar = liv->query_the_name(ob)+" moves in for the kill with "+
			POSSESSIVE(liv)+" "+weapon->short()+", driving the "+
			"blade deep into your "+hdesc+".";
		aud = QCTNAME(liv)+" moves in closer to "+QTNAME(ob)+", "+
			"driving "+POSSESSIVE(liv)+" "+weapon->short()+
			" deep into "+QTNAME(ob)+"'s "+hdesc+".";
    }

   return messages = ({ att, tar, aud });

}

/*
 * Function   : get_mercattack_messages()
 * Description: Get the messages for a normal mattack special
 * Arguments  : liv: the attacker
 *              ob: the attacked person
 *              weapon: the weapon used for the attack
 *              hitresult: how successful the hit was
 *              hdesc: the body part we are hitting
 * Returns    : an array of strings for the attacker, target, and audience
 */
string *get_mercattack_messages(object liv, object ob, object weapon, int hitresult, string hdesc)
{
    string *messages, att, tar, aud;

    if (weapon->query_wt() == W_CLUB)
    {
        switch(hitresult)
        {
	case 0:
	    {
                att = "You move in to exploit a weakness in "+
		   ob->query_the_name(liv)+"'s defences, but "+PRONOUN(ob)+
		   " sees this and avoids the attack.";
		tar = "You see "+liv->query_the_name(ob)+" moving in close "+
		   "to you, and manage to avoid "+POSSESSIVE(liv)+" attack.";				aud = QCTNAME(ob)+" notices "+QTNAME(liv)+" moving in close, "+
	 	   "and manages to avoid "+POSSESSIVE(liv)+" attack.";
		break;
	    }
	case 1..6:
	    {
		att = "You move in to exploit a weakness in "+
		    ob->query_the_name(liv)+"'s defences, but strike "+
		    "only a glancing blow to "+POSSESSIVE(ob)+" "+hdesc+
		    " with your "+weapon->short()+".";
                tar = "You see "+liv->query_the_name(ob)+" moving in close, "+
		    "but before you can stop "+OBJECTIVE(liv)+", "+PRONOUN(liv)+
		    " strikes your "+hdesc+" with a glancing blow of "+
		    POSSESSIVE(liv)+" "+ weapon->short()+".";
		aud = QCTNAME(liv)+" moves in on "+QTNAME(ob)+", striking "+
		    POSSESSIVE(ob)+" "+hdesc+" with a glancing blow of "+
		    POSSESSIVE(liv)+" "+weapon->short()+".";
		break;
	    }
	case 7..12:
	    {
		att = "You move in to exploit a weakness in "+
		    ob->query_the_name(liv)+"'s defences, and strike "+
		    "a solid blow to "+POSSESSIVE(ob)+" "+hdesc+
		    " with your "+weapon->short()+".";
                tar = "You see "+liv->query_the_name(ob)+" moving in close, "+
		    "and before you can stop "+OBJECTIVE(liv)+", "+PRONOUN(liv)+
		    " strikes your "+hdesc+" with a solid blow of his "+
		    weapon->short()+".";
		aud = QCTNAME(liv)+" moves in on "+QTNAME(ob)+", striking "+
		    POSSESSIVE(ob)+" "+hdesc+" solidly with "+
		    POSSESSIVE(liv)+" "+weapon->short()+".";
		break;
	    }
	case 13..19:
	    {
		att = "You move in to exploit a hole in "+
		    ob->query_the_name(liv)+"'s defences, feeling a satisfying "+			    "thump as your "+weapon->short()+" hurts "+POSSESSIVE(ob)+
		    " "+hdesc+".";
                tar = "You see "+liv->query_the_name(ob)+" moving in close, "+
		    "and before you can stop "+OBJECTIVE(liv)+", you feel "+
		    POSSESSIVE(liv)+" "+weapon->short()+" thump into your "+
		    hdesc+" painfully.";
		aud = QCTNAME(liv)+" moves in on "+QTNAME(ob)+", hurting "+
		    POSSESSIVE(ob)+" "+hdesc+" as "+POSSESSIVE(liv)+" "+
		    weapon->short()+" lands with an audible thump.";
		break;
	    }
	case 20..28:
	    {
		att = "Seeing that "+ob->query_the_name(liv)+" has left "+
		    POSSESSIVE(ob)+" "+hdesc+" vulnerable, you deliver a "+
		    "powerful blow, pounding "+OBJECTIVE(ob)+" with your "+
		    weapon->short()+".";
                tar = "You see "+liv->query_the_name(ob)+" moving in close, "+
		    "and before you can react, "+PRONOUN(liv)+" delivers a "+
		    "powerful blow, pounding your "+hdesc+" with "+
		    POSSESSIVE(liv)+" "+weapon->short()+".";
		aud = QCTNAME(liv)+" moves in on "+QTNAME(ob)+", pounding "+
		    POSSESSIVE(ob)+" "+hdesc+" with a powerful blow of "+
		    POSSESSIVE(liv)+" "+weapon->short()+".";
		break;
	    }
	case 29..39:
	    {
		att = ob->query_The_name(liv)+" leaves "+POSSESSIVE(ob)+" "+
		    hdesc+" wide open. Instinctively, you bring your "+
		    weapon->short()+" smashing down upon "+OBJECTIVE(ob)+
		    " with a fierce swing.";
		tar = "You realize too late that you have left your "+hdesc+
		    " open. "+liv->query_The_name(ob)+" immediately brings "+
		    POSSESSIVE(liv)+" "+weapon->short()+" smashing down upon "+
		    "you with a fierce swing.";
            aud = QCTNAME(ob)+" leaves "+POSSESSIVE(ob)+" "+
                hdesc+" wide open. "+QCTNAME(liv)+" immediately "+
		    "brings "+POSSESSIVE(liv)+" "+weapon->short()+" smashing "+
		    "down upon "+OBJECTIVE(ob)+" with a fierce swing.";
		break;
	    }
	default:
	    {
		att = "You move in close to "+ob->query_the_name(liv)+", "+
		    "pressuring "+OBJECTIVE(ob)+" to make a mistake, which "+
		    PRONOUN(ob)+" does. With all of your might, you swing "+
		    "your "+weapon->short()+", which crushes "+POSSESSIVE(ob)+
		    " "+hdesc+" with a gruesome sound.";
		tar = liv->query_The_name(ob)+" moves in close to you with a "+
		   "series of frenzied attacks, as you attempt to fend them "+
		   "off desperately. You hear the gruesome sound of "+
		   POSSESSIVE(liv)+" "+weapon->short()+" crushing "+
		   "something only an instant before you feel the surge of "+
		   "pain in your "+hdesc+".";
		aud = QCTNAME(liv)+" moves in on "+QTNAME(ob)+" with a series "+
		   "of frenzied attacks, as "+QTNAME(ob)+" desperately tries to "+
		   "fend them off. Suddenly, "+QCTNAME(liv)+"'s "+weapon->short()+
		   " crushes "+QTNAME(ob)+"'s "+hdesc+" with a gruesome sound.";
		break;
	    }
        }
    }
   else if (weapon->query_wt() == W_SWORD)
    {
        switch(hitresult)
	{
	case 0:
	    {
                att = "You move in to exploit a weakness in "+
		   ob->query_the_name(liv)+"'s defences, but "+PRONOUN(ob)+
		   " sees this and avoids the attack.";
		tar = "You see "+liv->query_the_name(ob)+" moving in close "+
		   "to you, and manage to avoid "+POSSESSIVE(liv)+" attack.";				aud = QCTNAME(ob)+" notices "+QTNAME(liv)+" moving in close, "+
	 	   "and manages to avoid "+POSSESSIVE(liv)+" attack.";
		break;
	    }
	case 1..6:
	    {
		att = "You move in to exploit a weakness in "+
		    ob->query_the_name(liv)+"'s defences, but "+
		    "only graze "+POSSESSIVE(ob)+" "+hdesc+
		    " with your "+weapon->short()+".";
                tar = "You see "+liv->query_the_name(ob)+" moving in close, "+
		    "but before you can stop "+OBJECTIVE(liv)+", "+PRONOUN(liv)+
		    " grazes your "+hdesc+" with "+POSSESSIVE(liv)+" "+
		    weapon->short()+".";
		aud = QCTNAME(liv)+" moves in on "+QTNAME(ob)+", grazing "+
		    POSSESSIVE(ob)+" "+hdesc+" with "+
		    POSSESSIVE(liv)+" "+weapon->short()+".";
		break;
	    }
	case 7..12:
	    {
		att = "You move in to exploit a weakness in "+
		    ob->query_the_name(liv)+"'s defences, and cut "+
		    "into "+POSSESSIVE(ob)+" "+hdesc+
		    " with your "+weapon->short()+".";
                tar = "You see "+liv->query_the_name(ob)+" moving in close, "+
		    "and before you can stop "+OBJECTIVE(liv)+", "+PRONOUN(liv)+
                " cuts into your "+hdesc+" with a solid blow of "+
                POSSESSIVE(liv)+" "+
		    weapon->short()+".";
		aud = QCTNAME(liv)+" moves in on "+QTNAME(ob)+", cutting into "+
		    POSSESSIVE(ob)+" "+hdesc+" with "+
		    POSSESSIVE(liv)+" "+weapon->short()+".";
		break;
	    }
	case 13..19:
	    {
		att = "You move in to exploit a hole in "+
		    ob->query_the_name(liv)+"'s defences and lash "+
		    "with your "+weapon->short()+", feeling it bite into "+
		    POSSESSIVE(ob)+" "+hdesc+" with satisfaction.";
                tar = "You see "+liv->query_the_name(ob)+" moving in close, "+
		    "and before you can stop "+OBJECTIVE(liv)+", you feel "+
		    POSSESSIVE(liv)+" "+weapon->short()+" bite into your "+
		    hdesc+" painfully.";
		aud = QCTNAME(liv)+" moves in on "+QTNAME(ob)+", lashing "+
		    "out with "+POSSESSIVE(liv)+" "+weapon->short()+", "+
		    "which bites into "+QTNAME(ob)+"'s "+hdesc+" painfully.";
		break;
	    }
	case 20..28:
	    {
		att = "Seeing that "+ob->query_the_name(liv)+" has left "+
		    POSSESSIVE(ob)+" "+hdesc+" vulnerable, you deliver a "+
		    "skillful thrust, stabbing "+OBJECTIVE(ob)+" with your "+
		    weapon->short()+".";
                tar = "You see "+liv->query_the_name(ob)+" moving in close, "+
		    "and before you can react, "+PRONOUN(liv)+" delivers a "+
		    "skillful thrust, stabbing your "+hdesc+" with "+
		    POSSESSIVE(liv)+" "+weapon->short()+".";
		aud = QCTNAME(liv)+" moves in on "+QTNAME(ob)+", stabbing "+
		    POSSESSIVE(ob)+" "+hdesc+" with a skillful thrust of "+
		    POSSESSIVE(liv)+" "+weapon->short()+".";
		break;
	    }
	case 29..39:
	    {
		att = ob->query_The_name(liv)+" leaves "+POSSESSIVE(ob)+" "+
		    hdesc+" wide open. Instinctively, you slice into "+
		    OBJECTIVE(ob)+" with a fierce swing of your "+
	            weapon->short()+".";
		tar = "You realize too late that you have left your "+hdesc+
		    " open. "+liv->query_The_name(ob)+" immediately slices "+
		    "into you with a fierce swing of "+POSSESSIVE(liv)+" "+
		    weapon->short()+".";
            aud = QCTNAME(ob) + " leaves "+POSSESSIVE(ob)+" "+
                hdesc + " wide open. " + QCTNAME(liv) + " immediately "+
		    "slices into "+OBJECTIVE(ob)+" with a fierce swing of "+
		    POSSESSIVE(liv)+" "+weapon->short()+".";
		break;
	    }
	default:
	    {
		att = "You move in close to "+ob->query_the_name(liv)+", "+
		    "pressuring "+OBJECTIVE(ob)+" to make a mistake, which "+
		    PRONOUN(ob)+" does. With all of your might, you tear a "+
		    "gaping wound into "+POSSESSIVE(ob)+" "+hdesc+" with your "+
		    weapon->short()+".";
		tar = liv->query_The_name(ob)+" moves in close to you with a "+
		   "series of frenzied attacks, as you attempt to fend them "+
		   "off desperately. You feel an intense pain in your "+hdesc+
		   " as "+POSSESSIVE(ob)+" "+weapon->short()+" tears a gaping "+
		   "wound.";
		aud = QCTNAME(liv)+" moves in on "+QTNAME(ob)+" with a series "+
		   "of frenzied attacks, as "+QTNAME(ob)+" desperately tries to "+
		   "fend them off. Suddenly, "+QCTNAME(liv)+"'s "+weapon->short()+
		   " tears a gaping wound in "+QTNAME(ob)+"'s "+hdesc+".";
		break;
	    }
        }
    }
   else if (weapon->query_wt() == W_KNIFE)
    {
        switch(hitresult)
	{
	case 0:
	    {
                att = "You move in to exploit a weakness in "+
		   ob->query_the_name(liv)+"'s defences, but "+PRONOUN(ob)+
		   " sees this and avoids the attack.";
		tar = "You see "+liv->query_the_name(ob)+" moving in close "+
		   "to you, and manage to avoid "+POSSESSIVE(liv)+" attack.";				aud = QCTNAME(ob)+" notices "+QTNAME(liv)+" moving in close, "+
	 	   "and manages to avoid "+POSSESSIVE(liv)+" attack.";
		break;
	    }
	case 1..6:
	    {
		att = "You move in to exploit a weakness in "+
		    ob->query_the_name(liv)+"'s defences, but "+
		    "only graze "+POSSESSIVE(ob)+" "+hdesc+
		    " with your "+weapon->short()+".";
                tar = "You see "+liv->query_the_name(ob)+" moving in close, "+
		    "but before you can stop "+OBJECTIVE(liv)+", "+PRONOUN(liv)+
		    " grazes your "+hdesc+" with "+POSSESSIVE(liv)+" "+
		    weapon->short()+".";
		aud = QCTNAME(liv)+" moves in on "+QTNAME(ob)+", grazing "+
		    POSSESSIVE(ob)+" "+hdesc+" with "+
		    POSSESSIVE(liv)+" "+weapon->short()+".";
		break;
	    }
	case 7..12:
	    {
		att = "You move in to exploit a weakness in "+
		    ob->query_the_name(liv)+"'s defences, and cut "+
		    "into "+POSSESSIVE(ob)+" "+hdesc+
		    " with your "+weapon->short()+".";
                tar = "You see "+liv->query_the_name(ob)+" moving in close, "+
		    "and before you can stop "+OBJECTIVE(liv)+", "+PRONOUN(liv)+
                " cuts into your "+hdesc+" with a quick slash of "+
                POSSESSIVE(liv)+" "+
		    weapon->short()+".";
		aud = QCTNAME(liv)+" moves in on "+QTNAME(ob)+", cutting into "+
		    POSSESSIVE(ob)+" "+hdesc+" with "+
		    POSSESSIVE(liv)+" "+weapon->short()+".";
		break;
	    }
	case 13..19:
	    {
		att = "You move in to exploit a hole in "+
		    ob->query_the_name(liv)+"'s defences and lash out "+
		    "with your "+weapon->short()+", feeling it bite into "+
		    POSSESSIVE(ob)+" "+hdesc+" with satisfaction.";
                tar = "You see "+liv->query_the_name(ob)+" moving in close, "+
		    "and before you can stop "+OBJECTIVE(liv)+", you feel "+
		    POSSESSIVE(liv)+" "+weapon->short()+" bite into your "+
		    hdesc+" painfully.";
		aud = QCTNAME(liv)+" moves in on "+QTNAME(ob)+", lashing "+
		    "out with "+POSSESSIVE(liv)+" "+weapon->short()+", "+
		    "which bites into "+QTNAME(ob)+"'s "+hdesc+" painfully.";
		break;
	    }
	case 20..28:
	    {
		att = "Seeing that "+ob->query_the_name(liv)+" has left "+
		    POSSESSIVE(ob)+" "+hdesc+" vulnerable, you deliver a "+
		    "skillful thrust, stabbing "+OBJECTIVE(ob)+" with your "+
		    weapon->short()+".";
                tar = "You see "+liv->query_the_name(ob)+" moving in close, "+
		    "and before you can react, "+PRONOUN(liv)+" delivers a "+
		    "skillful thrust, stabbing your "+hdesc+" with "+
		    POSSESSIVE(liv)+" "+weapon->short()+".";
		aud = QCTNAME(liv)+" moves in on "+QTNAME(ob)+", stabbing "+
		    POSSESSIVE(ob)+" "+hdesc+" with a skillful thrust of "+
		    POSSESSIVE(liv)+" "+weapon->short()+".";
		break;
	    }
	case 29..39:
	    {
		att = ob->query_The_name(liv)+" leaves "+POSSESSIVE(ob)+" "+
		    hdesc+" wide open. Instinctively, you impale "+
		    OBJECTIVE(ob)+" with a quick thrust of your "+
	            weapon->short()+".";
		tar = "You realize too late that you have left your "+hdesc+
		    " open. "+liv->query_The_name(ob)+" immediately impales "+
		    "into you with a quick thrust of "+POSSESSIVE(liv)+" "+
		    weapon->short()+".";
            aud = QCTNAME(ob) + " leaves "+POSSESSIVE(ob)+" "+
                hdesc + " wide open. " + QCTNAME(liv) + " immediately "+
		    "impales "+OBJECTIVE(ob)+" with a quick thrust of "+
		    POSSESSIVE(liv)+" "+weapon->short()+".";
		break;
	    }
	default:
	    {
		att = "You move in close to "+ob->query_the_name(liv)+", "+
		    "pressuring "+OBJECTIVE(ob)+" to make a mistake, which "+
		    PRONOUN(ob)+" does. With a lightning-fast stab, you bury "+
		    "the "+weapon->short()+" in "+POSSESSIVE(ob)+" "+hdesc+".";
		tar = liv->query_The_name(ob)+" moves in close to you with a "+
		   "series of frenzied attacks, as you attempt to fend them "+
		   "off desperately. You feel an intense pain in your "+hdesc+
		   " as "+POSSESSIVE(ob)+" "+weapon->short()+" buries itself "+
	           "in your flesh.";
		aud = QCTNAME(liv)+" moves in on "+QTNAME(ob)+" with a series "+
		   "of frenzied attacks, as "+QTNAME(ob)+" desperately tries to "+
		   "fend them off. Suddenly, "+QCTNAME(liv)+"'s "+weapon->short()+
		   " is buried in "+QTNAME(ob)+"'s "+hdesc+".";
		break;
	    }
        }
    }

    return messages = ({ att, tar, aud });
}

/*
 * Function   : c_can_attack()
 * Description: Can we attack attack this object with mattack?
 * Arguments  : ob: the person to attack, verb: the verb used (mattack)
 * Returns    : a string with why we cannot attack this person
 */
string
c_can_attack(object ob, string verb)
{
    mixed mess;

    if (!ob || !living(ob) || (ob == TP) || ob->query_ghost())
        return C(verb) + " whom?\n";

    if (mess = ob->query_prop(OBJ_M_NO_ATTACK))
        return (stringp(mess) ? mess :
            "You sense a devine presence protecting the intended victim.\n");

    if (E(ob) && (mess = E(ob)->query_prop(ROOM_M_NO_ATTACK)))
        return (stringp(mess) ? mess :
            "You sense that someone has laid a peace spell over this room.\n");

    if (TP->query_met(ob) && TP->query_enemy(0) != ob) 
    {
          if (TP->query_prop(LIVE_O_LAST_KILL) != ob)
          {   
                TP->catch_msg("Attack " + QTNAME(ob) +
                      "?!? Please confirm by trying again.");
                TP->add_prop(LIVE_O_LAST_KILL, ob);
                return "\n";
          }
    }
    if (!F_DARE_ATTACK(TP, ob) && (member_array(ob, TP->query_enemy(-1)) == -1))
        return "Umm... no, You do not have enough self-discipline to dare!\n";
    
}

/*
 * Function   : special()
 * Description: Begin an mattack
 * Arguments  : str: the string following the verb mattack
 * Returns    : 1 if the mattack will progress, 0 if it will not
 */
int
special(string str)
{
    object ob, *obj, weapon, *weapons;
    object liv = TP;
    string how;
    int tmp;

    if (str == "auto" || str == "automatic")
    {
        TP->set_skill(SS_MERC_AUTOMATTACK, 1);
        write("You enable automatic use of 'mattack'. To disable this, "+
	    "use 'mattack manual'.\n");
	return 1;
    }

    if (str == "manual")
    {
        TP->set_skill(SS_MERC_AUTOMATTACK, 0);
	write("You disable automatic use of 'mattack'. To enable this, "+
	    "use 'mattack auto'.\n");
	return 1;
    }

    if (str == "status")
    {
        how = (TP->query_skill(SS_MERC_AUTOMATTACK) == 1 ? "automatically" :
	    "manually");

        write("You have specified to use mattack "+how+". To change this "+
	    "setting, use 'mattack manual' or 'mattack auto'.\n");
	return 1;
    }

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

    if (tmp = liv->query_prop(PLAYER_I_MATTACK_RESETTING))
    {
      NF("You are not ready to attack again.\n");
	    /* Safeguard to fix locked special attacks */
    	if (time() > tmp + 20)
	      set_alarm(itof(MATTACK_RESET), 0.0, &reset_special(liv));

    	return 0;
    }

    if (liv->query_prop(LIVE_I_ATTACK_DELAY) || liv->query_prop(LIVE_I_STUNNED))
    {
	NF("You are too stunned to attack.\n");
	return 0;
    }

    if (tmp = liv->query_prop(PLAYER_I_MATTACK_PREPARING)) 
    {
	NF("You are already preparing to attack.\n");
	/* Safeguard to fix locked special attacks */
	if (time() > tmp + 20)
	{
	    NF("You are not ready to attack again.\n");
	    liv->remove_prop(PLAYER_I_MATTACK_PREPARING);
	    liv->add_prop(PLAYER_I_MATTACK_RESETTING,time());
	    set_alarm(itof(MATTACK_FAILSAFE),0.0, &reset_special(liv));
	}
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

        if (weapon->query_wt() != W_CLUB &&
	    weapon->query_wt() != W_SWORD &&
	    weapon->query_wt() != W_KNIFE)
        {
            NF("You cannot attack without a mercenary trained weapon!\n");
	    return 0;
        }

	liv->add_prop(PLAYER_I_MATTACK_PREPARING, time());
        liv->reveal_me(1);
        set_alarm(itof(MATTACK_PREPARE), 0.0, &do_special(ob, liv));
	if (ob != liv->query_attack())
	{
	    liv->catch_msg("With the element of surprise on your "+
		"side, you prepare to attack "+ob->query_the_name(liv)+".\n");
            /*
             * Why is this commented away? Lunatari
             *
             * liv->attack_object(ob);
             */
	}
	else
	{
	    switch(random(5))
	    {
	    case 4:
		{
		    liv->catch_msg("You begin looking for an opening in "+
			ob->query_the_name(liv)+"'s defence.\n");
		    break;
		}
	    case 3:
		{
		    liv->catch_msg("You fall back several steps, trying to "+
			"lure "+ob->query_the_name(liv)+" into a trap.\n");
		    break;
		}
	    case 2:
		{
		    liv->catch_msg("You press forward briefly, trying to "+
			"catch "+ob->query_the_name(liv)+" off guard.\n");
		    break;
		}
	    case 1:
		{
		    liv->catch_msg("You gather your nerves as you prepare to "+
			"make a risky move on "+ob->query_the_name(liv)+".\n");
		    break;
		}
	    default:
		{
		    liv->catch_msg("You feign an attack with your "+weapon->short()+
		      ", distracting "+QTNAME(ob)+" as you attempt to create "+
		      "a hole in "+POSSESSIVE(ob)+" defence.\n");
		    break;
		}
	    }
	}
	return 1;
    }
}

/*
 * Function   : do_special()
 * Description: Carry out the mattack that was previously prepared
 * Arguments  : ob: the person we're attacking, liv: us!
 * Returns    : void
 */
void do_special(object ob, object liv)
{
    mixed hitresult;
    object weapon, leader;
    int hitres, weaponmod, statmod, skillmod, pen, hit, skill;
    string *messages, hdesc, metname, nonmetname;
    int i = random(2);

    /* We arent preparing, so we shouldnt continue. */
    if (!liv->query_prop(PLAYER_I_MATTACK_PREPARING)) return;
    
    if (!present(ob, environment(liv))) 
    {
	write("You are unable to attack your target.\n");
	liv->remove_prop(PLAYER_I_MATTACK_PREPARING);
	return;
    }

    weapon = query_weapon(liv);

    if (!weapon)
    {
	write("You cannot attack without a weapon.\n");
	liv->remove_prop(PLAYER_I_MATTACK_PREPARING);
	return;
    }

    if (weapon->query_wt() != W_CLUB &&
        weapon->query_wt() != W_SWORD &&
	weapon->query_wt() != W_KNIFE)
    {
        NF("You cannot attack without a mercenary trained weapon!\n");
	liv->remove_prop(PLAYER_I_MATTACK_PREPARING);
        return 0;
    }

    /* Extra check for query_not_attack_me */
    if(ob->query_not_attack_me(liv, weapon->query_attack_id()))
    {
        /* The function should write it's own message */
        liv->remove_prop(PLAYER_I_MATTACK_PREPARING);
        liv->add_prop(PLAYER_I_MATTACK_RESETTING, time());
        set_alarm(itof(MATTACK_RESET), 0.0, &reset_special(liv));
        return;
    }

    /* New checks added - unseen opponent and opponents without bodies */
    if (!CAN_SEE(liv, ob) &&
      (random(100) > liv->query_skill(SS_BLIND_COMBAT)))
    {
	liv->catch_msg("Unable to see your opponent, you fail to connect with "+
	  "your "+weapon->short()+".\n");
	if (CAN_SEE(ob, liv))
	    ob->catch_msg(QCTNAME(liv)+" swings blindly with "+POSSESSIVE(liv)+
	      " "+weapon->short()+", missing you completely.\n");
	liv->tell_watcher(QCTNAME(liv)+" swings blindly with "+POSSESSIVE(liv)+
	  " "+weapon->short()+", missing "+QTNAME(ob)+" completely.\n");
	liv->remove_prop(PLAYER_I_MATTACK_PREPARING);
	liv->add_prop(PLAYER_I_MATTACK_RESETTING, time());
  set_alarm(itof(MATTACK_RESET), 0.0, &reset_special(liv));
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
	liv->remove_prop(PLAYER_I_MATTACK_PREPARING);
	liv->add_prop(PLAYER_I_MATTACK_RESETTING, time());
  set_alarm(itof(MATTACK_RESET), 0.0, &reset_special(liv));
	return;
    }

    /* Weapon stat formula */
    weaponmod = MAX(weapon->query_hit(), weapon->query_pen()) * 10 / 8;

    /* Stat formula */
    if (MEMBER_CLUB(liv))
        statmod = CLUB_STATMOD(liv);
    else if (MEMBER_SWORD(liv))
        statmod = SWORD_STATMOD(liv);
    else
	statmod = NORM_STATMOD(liv);

    /* Final formula */
    skill = liv->query_skill(SS_MERC_TACTICS);

    /* Give a bonus for using preferred weapon */
    if (MEMBER_CLUB(liv) && weapon->query_wt() == W_CLUB)
        skillmod = liv->query_skill(SS_WEP_CLUB) / 10 + 1;
    else if (MEMBER_SWORD(liv) && weapon->query_wt() == W_SWORD)
        skillmod = liv->query_skill(SS_WEP_SWORD) / 10 + 1;

    pen = (statmod + weaponmod) / 2 + skillmod;

    if (liv->query_npc())
        pen = 350;

    /*
     * Add a bonus if Mercenary is being led by his lord.
     *  +5 bonus for Lord.
     * +10 bonus for Warlord.
     */
    if ((leader = liv->query_leader()) && 
	MCREST->query_members_lord(liv->query_name()) == leader->query_name())
    {
        switch(MCREST->query_lord_status(leader->query_name()))
	{
	    case MERC_STATUS_LORD:
		pen += 5;
		break;
	    case MERC_STATUS_WARLORD:
		pen += 10;
		break;
	    default:
		break;
        }
    }

    hitres = F_PENMOD(pen, skill);
    hit = MERC_TOHIT(liv, weapon);

    if (liv->query_combat_object()->cb_tohit(-1, hit, ob) != 1)
    {
        hitresult = ob->hit_me(0, weapon->query_dt(), liv, -1);
      	liv->update_mattack_stats(0, 0, 0);
    }
    else
    {
        hitresult = ob->hit_me(hitres, weapon->query_dt(), liv, -1);
    }

    liv->attack_object(ob);
    hdesc = hitresult[1];

    if (ob->query_hp() <= 0)
    {
        messages = get_mercattack_death_messages(liv, ob, weapon, hdesc);

        liv->catch_msg(messages[0]+"\n");
	ob->catch_msg(messages[1]+"\n");
	liv->tell_watcher(messages[2]+"\n", ob);

        if (query_sever_corpse(liv))
        {
           metname = ob->query_real_name();
           nonmetname = ob->query_nonmet_name();
        }

        ob->do_die(liv);

        /* Add severed head in one case */
        if (query_sever_corpse(liv))
        {
            sever_limb("head", metname, nonmetname, liv);
	    set_sever_corpse(liv, 0);
        }
    }
    else
    {
        messages = get_mercattack_messages(liv, ob, weapon, hitresult[0], hdesc);
        liv->catch_msg(messages[0]+"\n");
        ob->catch_msg(messages[1]+"\n");
        liv->tell_watcher(messages[2]+"\n", ob);
    }

    liv->remove_prop(PLAYER_I_MATTACK_PREPARING);
    if (liv->query_wiz_level() || liv->query_real_name() == MERC_GMJUNIOR)
	liv->catch_msg(
	    "*************************************************************\n"+
    "Statmod: "+statmod+" | Weaponmod: "+weaponmod+" | Skillmod: "+skillmod+"\n"+
    "Pen: "+pen+" | Skil13l: "+skill+" | Damage: "+hitresult[3]+" | Percent: "+
	hitresult[0]+"\n"+
	    "*************************************************************\n");

    liv->update_mattack_stats(1, hitresult[0], hitresult[3]);
    
    liv->add_prop(PLAYER_I_MATTACK_RESETTING, time());
    set_alarm(itof(MATTACK_RESET), 0.0, &reset_special(liv));

    return;
}

/*
 * Function   : reset_special()
 * Description: Reset the mattack special
 * Arguments  : liv: this person
 * Returns    : void
 */
void
reset_special(object liv)
{
    /* ok we have a new shadow, so this is done from it, 
     * so lets just call our function in the shadow 
     */
    liv->reset_merc_special();
}

/*
 * Function   : stop_def()
 * Description: Stop defending someone else
 * Arguments  : str: the string that follows the verb 'stop'
 * Returns    : 1 if we stop defending, 0 if we do not
 */
int stop_def(string str)
{
    object *obj, ob;

    if (!str)
       return 0;

    if (str == "defending" || str == "defend" || str == "defence")
    {
        TP->stop_defending();
        return 1;
    }

    obj = parse_this(str, "'defending' / 'defend' %i");

    if (!sizeof(obj))
        return 0;

    if (sizeof(obj) > 1)
    {
       NF("Stop defending whom? You are only defending "+
           TP->query_defended()->query_the_name(TP)+"!\n");
       return 1;
    }

    ob = obj[0];

    if (ob != TP->query_defended())
    {
        NF("You are not defending "+ob->query_the_name(TP)+", "+
           "you are defending "+TP->query_defended()->query_the_name(TP)+"!\n");
        return 0;
    }

    TP->stop_defending();
    return 1;
}   

/*
 * Function   : reset_defend()
 * Description: Reset the defend other special
 * Arguments  : ob: us
 * Returns    : void
 */
void reset_defend(object ob)
{
    ob->catch_msg("You recover your position, and are ready to "+
        "defend another.\n");
    ob->remove_prop(PLAYER_I_MDEFEND_RESETTING);
}

/*
 * Function   : defend()
 * Description: Try to defend someone else or start defending me again
 * Arguments  : str: the string that follows the verb 'defend'
 * Returns    : 1 if successful, 0 if not
 */
int defend(string str)
{
    object ob, *obj, shield, shadow;
    object liv = TP;
    string how;
    int tmp;

    NF("Defend whom?\n");
    if (!str)
        return 0;

    if (str == "me" || str == "myself")
    {
        TP->stop_defending();
	return 1;
    }

    obj = parse_this(str, "%l");

    NF("Defend whom?\n");
    if (!sizeof(obj))
        return 0;

    if (sizeof(obj) > 1) 
    {
        NF("Choose one person to defend.\n");
	return 0;
    }

    ob = obj[0];

    if (liv->query_prop(LIVE_I_ATTACK_DELAY) || liv->query_prop(LIVE_I_STUNNED))
    {
	NF("You are too stunned to defend "+ob->query_The_name(TP)+".\n");
	return 0;
    }

    if (liv->query_defending())
    {
	NF("You are already defending "+liv->query_defended()->query_the_name(liv)+
	    "!\n");
	return 0;
    }

    if (tmp = liv->query_prop(PLAYER_I_MDEFEND_RESETTING))
    {
	NF("You are still too far out of position to defend another.\n");
	/* Safeguard to fix locked special attacks */
	if (time() > tmp + 200)
	    set_alarm(itof(MATTACK_FAILSAFE), 0.0, &reset_defend(liv));
	return 0;
    }

    shield = query_shield(liv);

    if (!shield)
    {
	NF("You cannot defend "+ob->query_The_name(TP)+" without a shield.\n");
	return 0;
    }

    if (member_array(ob, TP->query_leader()->query_team()) == -1 &&
	member_array(ob, TP->query_team()) == -1 &&
	TP->query_leader() != ob)
    {
        NF(ob->query_The_name(TP)+" is not on your team.\n");
	return 0;
    }

    if (!sizeof(ob->query_enemy(-1)))
    {
	NF(ob->query_The_name(TP)+" is not currently fighting anyone.\n");
	return 0;
    }

    if (sizeof(ob->query_defenders()) >= 2)
    {
	NF(ob->query_The_name(TP)+" already has two others defending "+
            OBJECTIVE(ob)+".\n");
	return 0;
    }

    if (ob->query_defenders())
    {
	NF("You are already defending "+ob->query_the_name(TP)+"!\n");
        if (ob->query_defenders()[0] == TP)
		return 0;

	TP->defend_other(ob, 2);
	return 1;
    }

    setuid();
    seteuid(getuid());
    (shadow = clone_object(DSHADOW))->shadow_me(ob);
    TP->defend_other(ob, 1);
    return 1;
}
