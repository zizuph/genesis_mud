/*
 * include_emotes.h
 *
 * Emote include file for the Mercenaries of Sparkle
 * Created by Morrigan for Genesis
 * Updated and relocated to Sparkle by Lunatari
 */
public int
madvise(string str)
{
    object *oblist;
    string *how = parse_adverb_with_space(str, ".", 0);
    string tmp3, tmp2;

    /* Find if argument is valid */
    oblist = parse_this(how[0], "[at] [the] %i");

    /* Setup failure message */
    notify_fail("Suggest [how] to [whom] that they take control of their life?\n");

    if (!strlen(how[0]))
    {

        write("You"+how[1] + " advise everyone to take control of "+
	    "their lives, as you have.\n");
        all(""+how[1] + " advises everyone to take control of their lives, "+
	    "as "+PRONOUN(TP)+" has.");
        return 1;
    }

    if (!sizeof(oblist))
    {
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
	tmp3 = "their";
        tmp2 = "lives";
    }
       else
    {
	tmp3 = POSSESSIVE(oblist[0]);
        tmp2 = "life";
    }

    actor("You"+how[1]+" advise", oblist, " to take control of "+tmp3+
	" "+tmp2+", as you have.");
    target(""+how[1]+" advises that you take control of your life, as "+
	PRONOUN(TP)+" has.", oblist);
    all2act(""+how[1]+" advises", oblist, " to take control of "+tmp3+" "+
	tmp2+", as "+PRONOUN(TP)+" has.");
    return 1;
}


/* Merc ability to appraise the fighting skills of a person */
string get_skill_desc(int i)
{
    int tmp;
    string *skill_desc = ({ "unskilled", "barely skilled", "somewhat skilled",
	"fairly skilled", "quite skilled", "very skilled", "extremely skilled",
    "unbelievably skilled" });

    switch(i)
    {
    case -100..0:
        {
	    tmp = 0;
	    break;
	}
	case 1..15:
	{
	    tmp = 1;
	    break;
	}
	case 16..30:
	{
	    tmp = 2;
	    break;
	}
	case 31..45:
	{
	    tmp = 3;
	    break;
	}
	case 46..60:
	{
	    tmp = 4;
	    break;
	}
	case 61..75:
	{
	    tmp = 5;
	    break;
	}
	case 76..90:
	{
	    tmp = 6;
	    break;
	}
	case 91..100:
	default:
	{
	    tmp = 7;
	    break;
	}
    }

    return skill_desc[tmp];
}


public int
mappraise(string str)
{
    object *oblist, ob, wep, weps, merc = this_player();
    int skill, check_skill = 100, check_skill2 = 100, check_parry = 0, 
	two_handed = 0, wep_skill, wep_skill2, parry_skill, defence_skill,
	two_handed_skill, dev, same_weapon = 0;
    string tmp = "";

    /* Find if argument is valid */
    oblist = parse_this(str, "[the] %i");

    /* Setup failure message */
    notify_fail("Appraise which being?\n");

    if (!sizeof(oblist))
    {
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
        notify_fail("You may only appraise one person at a time.\n");
	return 0;
    }

    ob = oblist[0];

    if (!objectp(ob->query_attack()))
    {
	notify_fail("You may only appraise someone if they are in combat.\n");
	return 0;
    }

    if (!sizeof(ob->query_weapon(-1)))
    {
	check_skill = 21;
	check_parry = 0;
	two_handed = 0;
    }
   else if (sizeof(ob->query_weapon(-1)) == 1)
    {
	wep = ob->query_weapon(-1)[0];
        check_skill = wep->query_wt();
        check_parry = 1;
	two_handed = 0;
    }
   else
    {
	weps = ob->query_weapon(-1);
	check_skill = weps[0]->query_wt();
	check_skill2 = weps[1]->query_wt();

        if (check_skill == check_skill2)
	    same_weapon = 1;

	check_parry = 1;
	two_handed = 1;
    }

    skill = merc->query_skill(SS_APPR_MON) + merc->query_stat(SS_WIS) / 10 + 10;
    dev = MAX(0, random(100 - skill));

    if (two_handed == 1)
    {
	two_handed_skill = ob->query_skill(20) + (random(2) == 0 ? -(dev) : (dev));
	wep_skill = ob->query_skill(check_skill) + (random(2) == 0 ? -(dev) : (dev));
	wep_skill2 = ob->query_skill(check_skill2) + 
	    (random(2) == 0 ? -(dev) : (dev));
	parry_skill = ob->query_skill(SS_PARRY) + (random(2) == 0 ? -(dev) : (dev));
	defence_skill = ob->query_skill(SS_DEFENCE) +
	    (random(2) == 0 ? -(dev) : (dev));

        tmp = ob->query_The_name(merc)+" appears to be "+
        get_skill_desc(two_handed_skill)+" at fighting with "+
        "two weapons at the same time. ";

        if (same_weapon == 1)
	    tmp += capitalize(PRONOUN(ob))+" seems to be "+
            get_skill_desc(wep_skill)+" with the "+
        FO_COMPOSITE_DEAD(weps, merc)+". ";
	   else
	    tmp += capitalize(PRONOUN(ob))+" seems to be "+
		get_skill_desc(wep_skill)+" with the "+weps[0]->short()+" and "+
		get_skill_desc(wep_skill2)+" with the "+weps[1]->short()+". ";
	
	tmp += "You notice that "+PRONOUN(ob)+" is "+get_skill_desc(parry_skill)+
	    " at parrying blows and "+get_skill_desc(defence_skill)+" at "+
	    "defending "+ OBJECTIVE(ob)+"self in general.";

        write(tmp+"\n");
    }
   else if (check_skill != 21)
    {
	wep_skill = ob->query_skill(check_skill) + (random(2) == 0 ? -(dev) : (dev));
	parry_skill = ob->query_skill(SS_PARRY) + (random(2) == 0 ? -(dev) : (dev));
	defence_skill = ob->query_skill(SS_DEFENCE) +
	    (random(2) == 0 ? -(dev) : (dev));

        tmp += ob->query_The_name(merc)+" seems to be "+
	    get_skill_desc(wep_skill)+" with the "+wep->short()+". ";

	tmp += "You notice that "+PRONOUN(ob)+" is "+
	    get_skill_desc(parry_skill)+" at parrying blows and "+ 	            get_skill_desc(defence_skill)+" at defending "+
	    OBJECTIVE(ob)+"self in general.";

        write(tmp+"\n");
    }
   else
    {
	wep_skill = ob->query_skill(check_skill) + (random(2) == 0 ? -(dev) : (dev));
	defence_skill = ob->query_skill(SS_DEFENCE) +
	    (random(2) == 0 ? -(dev) : (dev));

        tmp += ob->query_The_name(merc)+" seems to be "+
	    get_skill_desc(wep_skill)+" at fighting unarmed, and "+
	    get_skill_desc(defence_skill)+" at defending "+OBJECTIVE(ob)+"self.";

        write(tmp+"\n");
    }	

    return 1;
}


/* Merc ability to see who in their team is under attack, and by whom */
public int
mbattle(string str)
{
    object *team = ({ }), *enemies = ({ }), *enemy_list = ({ }), me = this_player();
    int i, j, see_fight, see_defend = 0;

    NF("Use mbattle to see who is 'fighting', 'defending', or 'both'?\n");
    if (str && str != "both" && str != "fighting" && str != "defending")
	return 0;

    if (!str || str == "both" || str == "fighting" || str == "fight")
    {
	see_fight = 1;
    }

    if (!str || str == "both" || str == "defending" || str == "defend")
    {
	see_defend = 1;
    } 

    if (sizeof(me->query_team()))
    {
	team += me->query_team();
	team += ({ me });
    }
   else if (me->query_leader())
    {
	team += me->query_leader()->query_team();
	team += ({ me->query_leader() });
    }
   else
    {
	enemies = me->query_enemy(-1);

        if (!sizeof(enemies))
	{
	    write("There are no battles going on relevant to you or your team.\n");
	    return 1;
	}

        for (i=0;i<sizeof(enemies);i++)
	{
	    if (enemies[i]->query_attack() == me)
		enemy_list += ({ enemies[i] });
	}

        if (see_fight && see_defend)
	    write("You are fighting "+me->query_attack()->query_the_name(me)+
	        ", and are under attack from "+COMPOSITE_LIVE(enemy_list)+".\n");
	else if (see_fight && !see_defend)
	    write("You are fighting "+me->query_attack()->query_the_name(me)+".\n");
	else if (see_defend && !see_fight)
	    write("You are under attack from "+COMPOSITE_LIVE(enemy_list)+".\n");
	return 1;
    }

    for (i=0;i<sizeof(team);i++)
        if (sizeof(team[i]->query_enemy(-1)))
	    enemies += team[i]->query_enemy(-1);

    if (!sizeof(enemies))
    {
	write("Your team is not engaged in combat.\n");
	return 1;
    }

    write("Looking around, you take stock of the current battle.\n");

    for (i=0;i<sizeof(team);i++)
    {
        enemies = team[i]->query_enemy(-1);

	for (j=0;j<sizeof(enemies);j++)
	{
	    if (enemies[j]->query_attack() == team[i])
		enemy_list += ({ enemies[j] });
	}

        if (sizeof(enemy_list))
	{
            if (team[i] == me)
	    {
		if (see_fight && see_defend)
		    write("You are fighting "+
		        me->query_attack()->query_the_name(me)+
		        ", and are under attack from "+
		        COMPOSITE_LIVE(enemy_list)+".\n");
		else if (see_fight && !see_defend)
		    write("You are fighting "+
			me->query_attack()->query_the_name(me)+".\n");
		else if (see_defend && !see_fight)
		    write("You are under attack from "+COMPOSITE_LIVE(enemy_list)+
			".\n");
	    }
	   else
	    {
		if (see_fight && see_defend)
		    write(team[i]->query_The_name(me)+" is fighting "+
		        team[i]->query_attack()->query_the_name(me)+", and is "+
		        "under attack from "+
		        COMPOSITE_LIVE(enemy_list)+".\n");
		else if (see_fight && !see_defend)
		    write(team[i]->query_The_name(me)+" is fighting "+
			team[i]->query_attack()->query_the_name(me)+".\n");
		else if (see_defend && !see_fight)
		    write(team[i]->query_The_name(me)+" is under attack from "+
			COMPOSITE_LIVE(enemy_list)+".\n");
            enemy_list -= enemy_list;
	    }
	}
       else
	{
            if (team[i] == me)
	    {
		if (sizeof(me->query_enemy(-1)) && see_fight)
 		    write("You are fighting "+
			me->query_attack()->query_the_name(me)+".\n");
		else if (!sizeof(me->query_enemy(-1)) && see_fight)
		    write("You are not fighting anyone.\n");
	    }		
           else if (sizeof(team[i]->query_enemy(-1)))
	    {
		if (sizeof(team[i]->query_enemy(-1)) && see_fight)
  	            write(team[i]->query_The_name(me)+" is fighting "+
		        team[i]->query_attack()->query_the_name(me)+".\n");
		else if (!sizeof(team[i]->query_enemy(-1)) && see_fight)
		    write(team[i]->query_The_name(me)+" is not fighting anyone.\n");
	    }
	}
    }

    return 1;
}
		

public int
mcheck(string str)
{
    string *how = parse_adverb_with_space(str, "thoroughly", 0);

    write("You"+how[1]+" check to make sure you have everything "+
	"you might need for the day's adventures.\n");
    all(""+how[1]+" checks to make sure "+PRONOUN(TP)+" has everything "+
	"necessary for the day's adventures.");
    return 1;
}


public int
mclean(string str)
{
    object ob;
    string *how = parse_adverb_with_space(str, "dutifully", 1);

    notify_fail("Clean which weapon or armour [how]?\n");
    if (!str)
        return 0;

    if (!parse_command(how[0], TP, "[my] [the] %o", ob))
	return 0;

    /* No argument given */
    if (!str || !objectp(ob))
    {
        notify_fail("Clean which weapon or armour [how]?\n");
        return 0;
    }

    if (IS_WEAPON_OBJECT(ob))
    {
        write("You"+how[1]+" clean your "+ob->short()+", making sure "+
		"it will survive your next battle. "+ob->wep_condition_desc());
	all(""+how[1]+" cleans "+POSSESSIVE(TP)+" "+ob->short()+".");
	return 1;
    }

    if (IS_ARMOUR_OBJECT(ob))
    {
        write("You"+how[1]+" clean your "+ob->short()+", making sure "+
		"it will survive your next battle. "+ob->arm_condition_desc());
	all(""+how[1]+" cleans "+POSSESSIVE(TP)+" "+ob->short()+".");
	return 1;
    }

    notify_fail("Inspect which weapon or armour [how]?\n");
    return 0;
}


public int
mdestiny(string str)
{
    object *oblist;
    string *how = parse_adverb_with_space(str, "defiantly", 1);

    /* Find if argument is valid */
    oblist = parse_this(how[0], "[at] [the] %i");

    /* Setup failure message */
    notify_fail("Let [whom] know [how] that you control your destiny?\n");

    if (!strlen(how[0]))
    {
	SOULDESC("looking defiant");
        write("Your eyes glitter"+how[1] + " as you tell everyone that you, "+
	    "and you alone, determine your destiny.\n");
        all("'s eyes glitter"+how[1] + " as "+PRONOUN(TP)+" tells you that "+
	    PRONOUN(TP)+" alone determines "+POSSESSIVE(TP)+" destiny.");
        return 1;
    }

    if (!sizeof(oblist))
    {
        return 0;
    }

    SOULDESC("looking defiant");
    actor("Your eyes glitter"+how[1]+" as you tell", oblist, " that you, and "+
	"you alone, determine your destiny.");
    target("'s eyes glitter"+how[1]+" as "+PRONOUN(TP)+" tells you that "+
	PRONOUN(TP)+" alone determines "+POSSESSIVE(TP)+" destiny.", oblist);
    all2act("'s eyes glitter"+how[1]+" as "+PRONOUN(TP)+" tells", oblist, 
	" that "+PRONOUN(TP)+" alone determines "+POSSESSIVE(TP)+" destiny.");
    return 1;
}


public int
mface(string str)
{
    object *oblist;
    string *how = parse_adverb_with_space(str, "with recognition", 0);
    string tmp3, tmp2;

    /* Find if argument is valid */
    oblist = parse_this(how[0], "[at] [the] %i");

    /* Setup failure message */
    notify_fail("Your face lights up [how] [at whom]?\n");

    if (!strlen(how[0]))
    {
        SOULDESC("looking around"+how[1]);
        write("Your face lights up"+how[1] + ".\n");
        all("'s face lights up"+how[1] + ".");
        return 1;
    }

    if (!sizeof(oblist))
    {
        return 0;
    }

    SOULDESC("looking around"+how[1]);
    actor("Your face lights up"+how[1]+" as you spot", oblist, ".");
    target("'s face lights up"+how[1]+" as "+PRONOUN(TP)+" spots you.", oblist);
    all2act("'s face lights up"+how[1]+" as "+PRONOUN(TP)+" spots", oblist, ".");
    return 1;
}


/* Mglance is based on the Knight tend emote */
int filter_wep_arm(object ob)
{
    if (IS_WEAPON_OBJECT(ob) && ob->query_wielded() == TP)
	return 1;

    if (IS_ARMOUR_OBJECT(ob) && ob->query_worn() == TP)
	return 1;

    return 0;
}


mglance(string str)
{
    object         *ob, *damaged = ({ });
    int             i, weps = 0, arms = 0;
    string	   tmp, tmp2, oblist = "", damlist = "";

    NF("Glance at which worn armour[s] and/or wielded weapon[s]?\n");

    if (!str)
        str = "all";

    ob = FIND_STR_IN_OBJECT(str, this_player());
    if (!sizeof(ob))
        return 0;

    ob = filter(ob, "filter_wep_arm", this_object());
    if (!sizeof(ob))
        return 0;

    for (i = 0; i < sizeof(ob); i++)
    {
        if (IS_WEAPON_OBJECT(ob[i]))
        {
            weps = 1;

            if ((ob[i]->query_dull() - ob[i]->query_repair_dull()) != 0 ||
		(ob[i]->query_corroded() - ob[i]->query_repair_corr()) != 0)
            {
                if (random(TP->query_skill(SS_APPR_OBJ)) >= 4)
                    damaged += ({ ob[i] });
            }
        }

        if (IS_ARMOUR_OBJECT(ob[i]))
        {
	    arms = 1;

            if ((ob[i]->query_condition() - ob[i]->query_repair()) != 0)
            {
                if (random(TP->query_skill(SS_APPR_OBJ)) >= 4)
                    damaged += ({ ob[i] });
            }
        }

        if (oblist == "")
           oblist = ob[i]->short();
          else if ((i+1) == sizeof(ob))
           oblist += " and "+ob[i]->short();
          else
           oblist += ", "+ob[i]->short();
    }

    for (i=0;i<sizeof(damaged);i++)
    {
        if (damlist == "")
            damlist = damaged[i]->short();
           else if ((i+1) == sizeof(damaged))
            damlist += " and "+damaged[i]->short();
           else
            damlist += ", "+damaged[i]->short();
    }

    if (sizeof(damaged))
       tmp = " You notice signs of damage on your "+damlist+".\n";
      else
       tmp = "\n";

    if (sizeof(ob) > 1)
        tmp2 = "them";
       else
        tmp2 = "it";

    write("You glance down at your "+oblist+", checking "+tmp2+" for "+
	"obvious signs of damage."+tmp);
	return 1;
}


public int
minspect(string str)
{
    object ob;
    string *how;

    if (!str)
        str = "wielded weapon";

    how = parse_adverb_with_space(str, "carefully", 1);

    notify_fail("Inspect which weapon or armour [how]?\n");
    if (!parse_command(how[0], TP, "[my] [the] %o", ob))
	return 0;

    /* No argument given */
    if (!objectp(ob))
    {
        notify_fail("Inspect which weapon or armour [how]?\n");
        return 0;
    }

    if (IS_WEAPON_OBJECT(ob))
    {
        write("You inspect your "+ob->short()+how[1]+", making sure "+
		"it will survive your next battle. "+ob->wep_condition_desc());
	all(" inspects "+POSSESSIVE(TP)+" "+ob->short()+how[1]+".");
	return 1;
    }

    if (IS_ARMOUR_OBJECT(ob))
    {
        write("You inspect your "+ob->short()+how[1]+", making sure "+
		"it will survive your next battle. "+ob->arm_condition_desc());
	all(" inspects "+POSSESSIVE(TP)+" "+ob->short()+how[1]+".");
	return 1;
    }

    notify_fail("Inspect which weapon or armour [how]?\n");
    return 0;
}


public int
mnarrow(string str)
{
    object *oblist, wep, scabbard;
    string *how = parse_adverb_with_space(str, "in anger", 0);
    string tmp, tmp2, tmp3, hands, hands2;

    /* Find if argument is valid */
    oblist = parse_this(how[0], "[at] [the] %i");

    /* Setup failure message */
    notify_fail("Narrow your eyes at whom [how]?\n");
    
    NF("Narrow your eyes at whom [how]?\n");

    if (!strlen(how[0]))
        return 0;

    if (!sizeof(oblist))
        return 0;

    if (sizeof(TP->query_weapon(-1)))
    {
        wep = TP->query_weapon(-1)[0];
        hands = (wep->query_hands() == W_BOTH ? "hands" : "hand");
        hands2 = (wep->query_hands() == W_BOTH ? "their" : "its");
        
        SOULDESC("looking around"+how[1]+" with narrowed eyes");
        actor("Your eyes narrow"+how[1]+" as you look at", oblist,", your "+
		hands+" tightening "+hands2+" grip on your "+wep->short()+".");
        target("'s eyes narrow"+how[1]+" as "+PRONOUN(TP)+" looks at you, "+
		POSSESSIVE(TP)+" "+hands+" tightening "+hands2+" grip on "+
		"the "+wep->short()+".", oblist);
        all2act("'s eyes narrow"+how[1]+" as "+PRONOUN(TP)+" looks at",
		oblist, ", "+POSSESSIVE(TP)+" "+hands+" tightening "+hands2+
		" grip on the "+wep->short()+".");
        return 1;
    }

    SOULDESC("looking around"+how[1]+" with narrowed eyes");
    actor("Your eyes narrow"+how[1]+" as you look at", oblist,".");
    target("'s eyes narrow"+how[1]+" as "+PRONOUN(TP)+" looks at you.", 
	oblist);
    all2act("'s eyes narrow"+how[1]+" as "+PRONOUN(TP)+" looks at",
	oblist, ".");
    return 1;
}


public int
moffer(string str)
{
    object *oblist;
    string *how = parse_adverb_with_space(str, "carefully", 0);

    /* Find if argument is valid */
    oblist = parse_this(how[0], "[at] [the] %i");

    /* Setup failure message */
    notify_fail("[How] consider the offer [of someone]?\n");

    if (!strlen(how[0]))
    {
	SOULDESC("considering an offer");
        write("You"+how[1] + " consider the offer.\n");
        all(""+how[1] + " considers the offer.");
        return 1;
    }

    if (!sizeof(oblist))
    {
        return 0;
    }

    SOULDESC("considering an offer");
    actor("You"+how[1]+" consider the offer of", oblist, ".");
    target(""+how[1]+" considers your offer.", oblist);
    all2act(""+how[1]+" considers the offer of", oblist, ".");
    return 1;
}

    
public int
mresolve(string str)
{
    object *oblist;
    string *how = parse_adverb_with_space(str, "", 1);
    string tmp3;

    /* Find if argument is valid */
    oblist = parse_this(how[0], "[at] [the] %i");

    /* Setup failure message */
    notify_fail("Remind [whom] [how] that there are other ways to solve "+
	"a problem?\n");

    if (how[1] == " ")
	how[1] = "";

    if (!strlen(how[0]))
    {

        write("You remind everyone"+how[1] + " that talking is not the only way "+
	    "resolve a problem.\n");
        all(" reminds everyone"+how[1] + " that talking is not the only way to "+
	    "resolve a problem.");
        return 1;
    }

    if (!sizeof(oblist))
    {
        return 0;
    }

    if (sizeof(oblist) > 1)
	tmp3 = "their";
       else
	tmp3 = POSSESSIVE(oblist[0]);

    actor("You remind", oblist, how[1]+" that talking is not the only way to "+
       "resolve "+tmp3+" problem.");
    target(" reminds you"+how[1]+" that talking is not the only way to resolve "+
       "your problem.", oblist);
    all2act(" reminds", oblist, how[1]+" that talking is not the only way to "+
	"resolve "+tmp3+" problem.");
    return 1;
}


public int
mrest(string str)
{
    write("You find a place to rest, weary from the day's adventures.\n");
    all(" finds a place to rest, weary from the day's adventures.");
    return 1;
}


public int
mserious(string str)
{
    object *oblist;
    string *how = parse_adverb_with_space(str, "slowly", 0);

    /* Find if argument is valid */
    oblist = parse_this(how[0], "[at] [the] %i");

    /* Setup failure message */
    notify_fail("Look serious [how] [at whom]?\n");

    if (!strlen(how[0]))
    {
	SOULDESC("showing no emotion");
        write("Your face"+how[1] + " drains of emotion.\n");
        all("'s face"+how[1] + " slowly drains of emotion.");
        return 1;
    }

    if (!sizeof(oblist))
    {
        return 0;
    }

    SOULDESC("showing no emotion");
    actor("Your face"+how[1]+" drains of emotion as you stare at", oblist, ".");
    target("'s face"+how[1]+" drains of emotion as "+PRONOUN(TP)+" stares "+
	"at you.", oblist);
    all2act("'s face"+how[1]+" drains of emotion as "+PRONOUN(TP)+" stares "+
	"at", oblist, ".");
    return 1;
}


public int
msettle(string str)
{
    object *oblist;
    string *how = parse_adverb_with_space(str, "casually", 0);
    string tmp3;

    /* Find if argument is valid */
    oblist = parse_this(how[0], "[at] [the] %i");

    /* Setup failure message */
    notify_fail("Offer [how] to settle the dispute [with whom] the "+
	"mercenary way?\n");

    if (!strlen(how[0]))
    {

        write("You"+how[1] + " offer to settle the dispute the mercenary way.\n");
        all(""+how[1] + " offers to settle the dispute the mercenary way.");
        return 1;
    }

    if (!sizeof(oblist))
    {
        return 0;
    }

    if (sizeof(oblist) > 1)
	tmp3 = "their";
       else
	tmp3 = POSSESSIVE(oblist[0]);

    actor("You"+how[1]+" offer to settle the dispute with", oblist, " the "+
	"mercenary way.");
    target(""+how[1]+" offers to settle the dispute with you the mercenary "+
	"way.", oblist);
    all2act(""+how[1]+" offers to settle the dispute with", oblist, " the "+
	"mercenary way.");
    return 1;
}


public int
mspit(string str)
{
    object *oblist;
    string *how = parse_adverb_with_space(str, "calmly", 1);

    /* Find if argument is valid */
    oblist = parse_this(how[0], "[at] [the] %i");

    /* Setup failure message */
    notify_fail("Spit on your hands while looking at [whom] [how]?\n");

    if (!strlen(how[0]))
    {

        write("You spit on your hands, rubbing them together as you look "+
	    "around"+ how[1] + ".\n");
        all(" spits on "+POSSESSIVE(TP)+" hands, rubbing them together as "+
 	    PRONOUN(TP)+" looks around"+how[1] + ".");
        return 1;
    }

    if (!sizeof(oblist))
    {
        return 0;
    }

    actor("You spit on your hands, rubbing them together as you regard", oblist,
	how[1]+".");
    target(" spits on "+POSSESSIVE(TP)+" hands, rubbing them together as "+
	PRONOUN(TP)+" regards you"+how[1]+".", oblist);
    all2act(" spits on "+POSSESSIVE(TP)+" hands, rubbing them together as "+
        PRONOUN(TP)+" regards", oblist, how[1]+".");
    return 1;
}


public int
msuggest(string str)
{
    object *oblist;
    string *how = parse_adverb_with_space(str, ".", 0);
    string tmp3;

    /* Find if argument is valid */
    oblist = parse_this(how[0], "[at] [the] %i");

    /* Setup failure message */
    notify_fail("Suggest [how] that [whom] might like the mercenary life?\n");

    if (!strlen(how[0]))
    {

        write("You"+how[1] + " suggest that everyone might find life as "+
	    "a mercenary to their liking.\n");
        all(""+how[1] + " suggests that everyone might find life as a "+
	    "mercenary to their liking.");
        return 1;
    }

    if (!sizeof(oblist))
    {
        return 0;
    }

    if (sizeof(oblist) > 1)
	tmp3 = "their";
       else
	tmp3 = POSSESSIVE(oblist[0]);

    actor("You"+how[1]+" suggest that", oblist, " might find life as a "+
	"mercenary to "+tmp3+" liking.");
    target(""+how[1]+" suggests that you might find life as a mercenary "+
	"to your liking.", oblist);
    all2act(""+how[1]+" suggests that", oblist, " might find life as a "+
	"mercenary to "+tmp3+" liking.");
    return 1;
}


public int
mtalk(string str)
{
    object *oblist;
    object  wep;
    string *how = parse_adverb_with_space(str, "", 1);
    string tmp, tmp2, tmp3;

    /* Find if argument is valid */
    oblist = parse_this(how[0], "[at] [the] %i");

    /* Setup failure message */
    notify_fail("Let [whom] know [how] that the time for talk is over?\n");

    if (sizeof(this_player()->query_weapon(-1)))
    {
        wep = this_player()->query_weapon(-1)[0];
	tmp = "fingers "+POSSESSIVE(TP)+" "+wep->short();
	tmp2 = "finger your "+wep->short();
    }
   else
    {
	tmp = "crosses "+POSSESSIVE(TP)+" arms";
	tmp2 = "cross your arms";
    }

    if (how[1] == " ")
	how[1] = "";

    if (!strlen(how[0]))
    {

        write("You "+tmp2+how[1] + ", letting everone know that the time "+
	    "for talk is over.\n");
        all(" "+tmp+how[1] + ", letting everyone know that the time for "+
	    "talk is over.");
        return 1;
    }

    if (!sizeof(oblist))
    {
        return 0;
    }

    if (sizeof(oblist) > 1)
	tmp3 = "them";
       else
	tmp3 = OBJECTIVE(oblist[0]);

    actor("You "+tmp2+how[1]+" as you look at", oblist, ", letting "+
	tmp3+" know that the time for talk is over.");
    target(" "+tmp+how[1]+" as "+PRONOUN(TP)+" looks at you, letting "+
	"you know that the time for talk is over.", oblist);
    all2act(" "+tmp+how[1]+" as "+PRONOUN(TP)+" looks at", oblist, 
	", letting "+tmp3+" know that the time for talk is over.");
    return 1;
}


public int
mtomorrow(string str)
{
    object *oblist;
    string *how = parse_adverb_with_space(str, "thoughtfully", 0);
    string tmp3, tmp2;

    /* Find if argument is valid */
    oblist = parse_this(how[0], "[at] [the] %i");

    /* Setup failure message */
    notify_fail("Look at [whom] [how] and think of tomorrow's battles?\n");

    if (!strlen(how[0]))
    {
        SOULDESC("looking thoughtful");
        write("You think about what battles tomorrow might bring.\n");
        all(" thinks about what battles tomorrow might bring.");
        return 1;
    }

    if (!sizeof(oblist))
    {
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
	tmp3 = "their";
        tmp2 = "lives";
    }
       else
    {
	tmp3 = POSSESSIVE(oblist[0]);
        tmp2 = "life";
    }

    SOULDESC("looking"+how[1]);
    actor("You look at", oblist, how[1]+" as you think of what battles "+
	"tomorrow might bring.");
    target(" looks at you"+how[1]+" as "+PRONOUN(TP)+" thinks of what "+
	"battles tomorrow might bring.", oblist);
    all2act(" looks at", oblist, how[1]+" as "+PRONOUN(TP)+" thinks of what "+
	"battles tomorrow might bring.");
    return 1;
}


public int
mwipe(string str)
{
    string *how = parse_adverb_with_space(str, ".", 1);
    string location, back_front;

    /* Setup failure message */
    notify_fail("Wipe your [mouth/forehead/neck] [how] with your hand?\n");

    if (!strlen(how[0]) || how[0] == "mouth")
    {
        location = "mouth";
        back_front = " the back of";
    }
    else if (how[0] == "forehead")
    {
        back_front = " the back of";
	location = "forehead";
    }
    else if (how[0] == "neck")
    {
        back_front = "";
        location = "neck";
    }
    else
    {
        return 0;
    }

    write("You wipe your "+location+how[1]+" with"+back_front+
	" your hand.\n");
    all(" wipes "+POSSESSIVE(TP)+" "+location+how[1] + " with"+
	back_front+" "+POSSESSIVE(TP)+" hand.");
    return 1;
}


public int
mwork(string str)
{
    object *oblist;
    string *how = parse_adverb_with_space(str, "in satisfaction", 0);
    string tmp;

    /* Find if argument is valid */
    oblist = parse_this(how[0], "[at] [the] %i");

    /* Setup failure message */
    notify_fail("Rejoice [how] [with whom] after a hard day's work?\n");

    if (!strlen(how[0]))
    {
	SOULDESC("smiling"+how[1]);
        write("You smile"+how[1] + " after a hard day's work.\n");
        all(" smiles"+how[1] + " after a hard day's work.");
        return 1;
    }

    if (!sizeof(oblist))
    {
        return 0;
    }

    if (sizeof(oblist) > 1)
       tmp = "hands";
      else
       tmp = "hand";

    SOULDESC("smiling"+how[1]);
    actor("You grasp the "+tmp+" of", oblist, how[1]+" after a hard day's work.");
    target(" grasps your hand"+how[1]+" after a hard day's work.", oblist);
    all2act(" grasps the "+tmp+" of", oblist, how[1]+" after a hard day's work.");
    return 1;
}
