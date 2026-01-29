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
mcounsel(string str)
{
    object *oblist;
    string *how = parse_adverb_with_space(str, ".", 0);

    /* Find if argument is valid */
    oblist = parse_this(how[0], "[at] [the] %i");

    /* Setup failure message */
    notify_fail("Offer [how] counsel to [whom]?\n");
    if (!strlen(how[0]))
    {

        write("You"+how[1] + " counsel that the world has always been "+
	    "ruled by might.\n");
        all(""+how[1] + " counsels that the world has always been ruled "+
	    "by might.");
        return 1;
    }

    if (!sizeof(oblist))
    {
        return 0;
    }

    actor("You"+how[1]+" counsel", oblist, " that the world has always "+
        "been ruled by the mighty.");
    target(""+how[1]+" counsels you that the world has always been ruled "+
	"by the mighty.", oblist);
    all2act(""+how[1]+" counsels", oblist, " that the world has always "+
	"been ruled by the mighty.");
    return 1;
}


public int
mdeclare(string str)
{
    string *how = parse_adverb_with_space(str, ".", 0);
    string lord = MCREST->query_members_lord(TP->query_name());
    string gender;
    object lord_here, *tmp;

    /* Setup failure message */
    notify_fail("Declare your loyalty to the cause [how]?\n");

    if (strlen(how[0]))
        return 0;

    if (lord == "none")
    {
        notify_fail("You are not a member of a cause.\n");
        return 0;
    }

    gender = capitalize(MCREST->query_lord_gender(lord));
    if (gender != "lord" && gender != "lady")
	gender = "lord";

    if (MCREST->query_lord_status(lord) == MERC_STATUS_ASPIRING)
    {
        if (lord == TP->query_name())
        {
	    write("You"+how[1]+" declare your dedication to establishing "+
		"your cause.\n");
            all(""+how[1]+" declares "+POSSESSIVE(TP)+" dedication to "+
		"establishing "+POSSESSIVE(TP)+" cause.");
             return 1;
        }

        write("You"+how[1]+" declare your dedication to establishing "+
	    "the cause of your "+gender+", "+lord+".\n");
        if (lord_here = (present(lower_case(lord), environment(TP))))
        {
            say(QCTNAME(TP)+how[1]+" declares "+POSSESSIVE(TP)+
		" dedication to establishing the cause of "+POSSESSIVE(TP)+
		" "+gender+", "+lord+".\n", 
		({ lord_here, TP }));
            lord_here->catch_tell(TP->query_The_name(lord_here)+how[1]+
		" declares "+POSSESSIVE(TP)+" dedication to establishing "+
		"your cause.\n");
        } 
       else
        {
            all(QCTNAME(TP)+how[1] + " declares "+POSSESSIVE(TP)+" loyalty to "+
		"establishing the cause of "+POSSESSIVE(TP)+" "+gender+
		", "+lord+".");
        }

        return 1;
    }
    else if (MCREST->query_lord_status(lord) == MERC_STATUS_LORD ||
	MCREST->query_lord_status(lord) == MERC_STATUS_WARLORD)
    {
        if (lord == TP->query_name())
        {
	    write("You"+how[1]+" declare your loyalty to leading the "+
		"cause to prosperity.\n");
            all(""+how[1]+" declares "+POSSESSIVE(TP)+" loyalty to "+
		"leading "+POSSESSIVE(TP)+" cause to prosperity.");
             return 1;
        }

        write("You"+how[1]+" declare your loyalty to the cause of "+
	    "your "+gender+", "+lord+".\n");
        if (lord_here = (present(lower_case(lord), environment(TP))))
        {
            say(QCTNAME(TP)+how[1]+" declares "+POSSESSIVE(TP)+
		" loyalty to the cause of "+POSSESSIVE(TP)+" "+
		gender+", "+lord+".\n", lord_here);
            lord_here->catch_tell(TP->query_The_name(lord_here)+how[1]+
		" declares "+POSSESSIVE(TP)+" loyalty to your cause.\n");
        } 
       else
        {
            all(""+how[1] + " declares "+POSSESSIVE(TP)+" loyalty to "+
		"establishing the cause of "+POSSESSIVE(TP)+" "+gender+
		", "+lord+".\n");
        }

        return 1;
    }	

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


public int
mfarewell(string str)
{
    string lord = MCREST->query_members_lord(TP->query_name());
    string *how, gender, tmp, tmp2, name = "";
    int merc_status;
    object *oblist, lord_here, weapon;
    mixed *tmp_oblist;

    /* Setup failure message */
    notify_fail("Bid [how] <whom/all> farewell [in the name of] [me/lord/lady]"+
        " -or-\n"+
	"Bid [how] <whom/all> farewell [with this text]\n");

    if (strlen(str) && explode(str, " ")[0] == "default")
    {
        str = extract(str, 8);

        if (str == "off")
        {
            TP->remove_prop(MERC_S_DEFAULT_FAREWELL);
            write("You disable your default farewell message.\n");
	    return 1;
        }

        if (strlen(str) > MAX_MESSAGE_SIZE)
        {
            write("The maximum text size cannot be greater than "+
		MAX_MESSAGE_SIZE+" characters.\n");
	    return 1;
        }

        if (member_array("|", explode(str, "")) != -1)
	{
	    write("The text cannot contain the '|' character.\n");
	    return 1;
        }

        setuid(); seteuid(getuid());

        if (!present(MERC_MESSAGE_ID, TP))
            clone_object(MOBJ + "message_object")->move(TP);

        TP->add_prop(MERC_S_DEFAULT_FAREWELL, str);
        write("You set your default farewell message to: "+str+".\n");        
        return 1;
    }

    if (!str)
	return 0;

    /* Temporary fix for human defaulting to the adverb humanely rather
     * than the target human
     */
    if (extract(str, 0, 4) == "human" || extract(str, 0, 5) == "hobbit")
    {
        how = ({ str, " briefly", });
    }
    else
        how = parse_adverb_with_space(str, "briefly", 0);

    if (!strlen(how[0]))
        return 0;

    /* Change everyone to all */
    if (extract(how[0], 0, 7) == "everyone")
	how[0] = "all" + extract(how[0], 8);

    if (!parse_command(how[0], E(TP), "[the] %l %s", 
	tmp_oblist, tmp))
        if (!parse_command(how[0], E(TP),
	    "'all' %s", tmp))
            if (!parse_command(how[0], E(TP), "[the] %l", tmp_oblist))
                return 0;

    /* Remove the weird first element of the tmp_oblist mixed variable */
    if (sizeof(tmp_oblist))
        oblist = NORMAL_ACCESS(tmp_oblist, 0, 0);

    if (!strlen(tmp) && strlen(TP->query_prop(MERC_S_DEFAULT_FAREWELL)))
        tmp = TP->query_prop(MERC_S_DEFAULT_FAREWELL);

    parse_command(tmp, E(TP), "[in] [the] [name] [of] %w", tmp2);

    if (strlen(tmp) && strlen(tmp2) && 
	(tmp2 == "me" || C(tmp2) == lord))
    {
        if (tmp2 == "me" && lord != TP->query_name())
        {
            notify_fail("You are not a mercenary lord, thus you cannot "+
		"bid someone farewell with your own name.\n");
	    return 0;
        }
        else if (C(tmp2) != lord && tmp2 != "me")
        {
            write("You do not follow a lord named "+C(tmp)+", and thus you "+
		"cannot bid someone farewell with that name.\n");
	    return 1;
        }

        gender = MCREST->query_lord_gender(lord);
        if (gender != "lord" && gender != "lady")
	    gender = "lord";

        merc_status = MCREST->query_lord_status(lord);

        name = " in the name of ";

        switch(merc_status)
        {
	    case MERC_STATUS_ASPIRING:
		name += C(lord);
                break;
            case MERC_STATUS_LORD:
		name += C(gender)+" "+C(lord);
		break;
	    case MERC_STATUS_WARLORD:
		name += C(lord)+" the War"+gender;
		break;
	}

    }
    else if (strlen(tmp))
    {
        name = " with the words: "+tmp;
    }
    else
    {
        name = "";
    }

    if (sizeof(TP->query_weapon(-1)))
	weapon = TP->query_weapon(-1)[0];

    if (!sizeof(oblist) || extract(how[0], 0, 2) == "all")
    {
        if (objectp(weapon))
        {
	    write("You raise your "+weapon->short()+" aloft"+how[1]+", "+
		"bidding everyone farewell"+name+".\n");
	    say(QCTNAME(TP)+" raises "+POSSESSIVE(TP)+" "+weapon->short()+
		" aloft"+how[1]+" bidding everyone farewell"+name+".\n");
	    return 1;
        }

        write("You raise your hand"+how[1]+", bidding everyone farewell"+
	    name+".\n");
	say(QCTNAME(TP)+" raises "+POSSESSIVE(TP)+" hand"+how[1]+", bidding "+
	    "everyone farewell"+name+".\n");
        return 1;
    }
    else
    {
        if (objectp(weapon))
        {
	    actor("You raise your "+weapon->short()+" aloft"+how[1]+", bidding",
		oblist, " farewell"+name+".");
	    target(" raises "+POSSESSIVE(TP)+" "+weapon->short()+" aloft"+how[1]+
		", bidding you farewell"+name+".", oblist);
	    all2act(" raises "+POSSESSIVE(TP)+" "+weapon->short()+" aloft"+how[1]+
		", bidding", oblist, " farewell"+name+".");
	    return 1;
        }

	actor("You raise your hand"+how[1]+", bidding",
	    oblist, " farewell"+name+".");
	target(" raises "+POSSESSIVE(TP)+" hand"+how[1]+", bidding "+
	    "you farewell"+name+".", oblist);
	all2act(" raises "+POSSESSIVE(TP)+" hand"+how[1]+", bidding", oblist, 
	    " farewell"+name+".");
        return 1;
    }

    return 0;
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
mglare(string str)
{
    object *oblist, wep = query_weapon(TP);
    string *how = parse_adverb_with_space(str, "threateningly", 1);
    string tmp, tmp2;

    /* Find if argument is valid */
    oblist = parse_this(how[0], "[at] [the] %i");

    /* Setup failure message */
    notify_fail("Glare at [whom] [how]?\n");

    if (wep)
    {
	tmp = "tightening "+POSSESSIVE(TP)+" grip on the "+wep->short();
	tmp2 = "tightening your grip on the "+wep->short();
    }
   else
    {
	tmp = "clenching "+POSSESSIVE(TP)+" fists";
	tmp2 = "clenching your fists";
    }

    if (!strlen(how[0]))
    {
	SOULDESC("glaring around"+how[1]);
        write("You glare around the area, "+tmp2+ how[1] + ".\n");
        all(" glares around the area, "+tmp+how[1] + ".");
        return 1;
    }

    if (!sizeof(oblist))
    {
        return 0;
    }

    SOULDESC("glaring around"+how[1]);
    actor("You glare at", oblist, ", "+tmp2+how[1]+".");
    target(" glares at you, "+tmp+how[1]+".", oblist);
    all2act(" glares at", oblist, ", "+tmp+how[1]+".");
    return 1;
}


public int
mhail(string str)
{
    string lord = MCREST->query_members_lord(TP->query_name());
    string *how, gender, tmp, tmp2, name = "";
    int merc_status;
    object *oblist, lord_here, weapon;
    mixed *tmp_oblist;

    /* Setup failure message */
    notify_fail("Hail [how] <whom/all> [in the name of] [me/lord/lady] -or-\n"+
	"Hail [how] <whom/all> [with this text]\n");

    if (strlen(str) && explode(str, " ")[0] == "default")
    {
        str = extract(str, 8);

        if (str == "off")
        {
            TP->remove_prop(MERC_S_DEFAULT_HAIL);
            write("You disable your default hail message.\n");
	    return 1;
        }

        if (strlen(str) > MAX_MESSAGE_SIZE)
        {
            write("The maximum text size cannot be greater than "+
		MAX_MESSAGE_SIZE+" characters.\n");
	    return 1;
        }

        if (member_array("|", explode(str, "")) != -1)
	{
	    write("The text cannot contain the '|' character.\n");
	    return 1;
        }

        setuid(); seteuid(getuid());

        if (!present(MERC_MESSAGE_ID, TP))
            clone_object(MOBJ + "message_object")->move(TP);

        TP->add_prop(MERC_S_DEFAULT_HAIL, str);
        write("You set your default hail message to: "+str+".\n");        
        return 1;
    }

    if (!str)
	return 0;

    /* Temporary fix for human defaulting to the adverb humanely rather
     * than the target human
     */
    if (extract(str, 0, 4) == "human" || extract(str, 0, 5) == "hobbit")
    {
        how = ({ str, " in greeting", });
    }
    else
        how = parse_adverb_with_space(str, "in greeting", 0);

    if (!strlen(how[0]))
        return 0;

    /* Change everyone to all */
    if (extract(how[0], 0, 7) == "everyone")
	how[0] = "all" + extract(how[0], 8);

    if (!parse_command(how[0], E(TP), "[the] %l %s", 
	tmp_oblist, tmp))
        if (!parse_command(how[0], E(TP),
	    "'all' %s", tmp))
            if (!parse_command(how[0], E(TP), "[the] %l", tmp_oblist))
                return 0;

    /* Remove the weird first element of the tmp_oblist mixed variable */
    if (sizeof(tmp_oblist))
        oblist = NORMAL_ACCESS(tmp_oblist, 0, 0);

    if (!strlen(tmp) && strlen(TP->query_prop(MERC_S_DEFAULT_HAIL)))
        tmp = TP->query_prop(MERC_S_DEFAULT_HAIL);

    parse_command(tmp, E(TP), "[in] [the] [name] [of] %w", tmp2);

    if (strlen(tmp) && strlen(tmp2) && 
	(tmp2 == "me" || C(tmp2) == lord))
    {
        if (tmp2 == "me" && lord != TP->query_name())
        {
            notify_fail("You are not a mercenary lord, thus you cannot "+
		"hail in your own name.\n");
	    return 0;
        }
        else if (C(tmp2) != lord && tmp2 != "me")
        {
            write("You do not follow a lord named "+C(tmp)+", and thus you "+
		"cannot hail someone in that name.\n");
	    return 1;
        }

        gender = MCREST->query_lord_gender(lord);
        if (gender != "lord" && gender != "lady")
	    gender = "lord";

        merc_status = MCREST->query_lord_status(lord);

        name = " Hail in the name of ";

        switch(merc_status)
        {
	    case MERC_STATUS_ASPIRING:
		name += C(lord);
                break;
            case MERC_STATUS_LORD:
		name += C(gender)+" "+C(lord);
		break;
	    case MERC_STATUS_WARLORD:
		name += C(lord)+" the War"+gender;
		break;
	}

    }
    else if (strlen(tmp))
    {
        name = " "+tmp;
    }
    else
    {
        name = " Hail";
    }

    if (sizeof(TP->query_weapon(-1)))
	weapon = TP->query_weapon(-1)[0];

    if (!sizeof(oblist) || extract(how[0], 0, 2) == "all")
    {
        if (objectp(weapon))
        {
	    write("You raise your "+weapon->short()+" aloft"+how[1]+" as you "+
	        "hail everyone, saying:"+
		name+"!\n");
	    say(QCTNAME(TP)+" raises "+POSSESSIVE(TP)+" "+weapon->short()+
		" aloft"+how[1]+" as "+PRONOUN(TP)+" hails everyone"+
		", saying:"+name+"!\n");
	    return 1;
        }

        write("You raise your hand"+how[1]+" as you hail everyone"+
	    ", saying:"+name+"!\n");
	say(QCTNAME(TP)+" raises "+POSSESSIVE(TP)+" hand"+how[1]+" as "+
	    PRONOUN(TP)+" hails everyone, saying:"+name+"!\n");
        return 1;
    }
    else
    {
        if (objectp(weapon))
        {
	    actor("You raise your "+weapon->short()+" aloft"+how[1]+" as you hail",
		oblist, ", saying:"+name+"!");
	    target(" raises "+POSSESSIVE(TP)+" "+weapon->short()+" aloft"+
		how[1]+" as "+ PRONOUN(TP)+" hails you, saying:"+name+"!", oblist);
	    all2act(" raises "+POSSESSIVE(TP)+" "+weapon->short()+" aloft"+
		how[1]+" as "+PRONOUN(TP)+" hails", oblist, ", saying:"+name+"!");
	    return 1;
        }

	actor("You raise your hand"+how[1]+" as you hail",
	    oblist, ", saying:"+name+"!");
	target(" raises "+POSSESSIVE(TP)+" hand"+how[1]+" as "+
	    PRONOUN(TP)+" hails you, saying:"+name+"!", oblist);
	all2act(" raises "+POSSESSIVE(TP)+" hand"+how[1]+" as "+
	    PRONOUN(TP)+" hails", oblist, ", saying:"+name+"!");
        return 1;
    }

    return 0;
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
mkill(string str)
{
    string lord = MCREST->query_members_lord(TP->query_name());
    string *how, gender, tmp, tmp2, name = "";
    int merc_status;
    object *oblist, lord_here, weapon, ob;
    mixed *tmp_oblist;

    /* Setup failure message */
    notify_fail("Kill [how] <whom/all> [in the name of] [me/lord/lady] -or-\n"+
	"Kill [how] <whom/all> [with this text]\n");

    if (strlen(str) && explode(str, " ")[0] == "default")
    {
        str = extract(str, 8);

        if (str == "off")
        {
            TP->remove_prop(MERC_S_DEFAULT_BATTLECRY);
            write("You disable your default battlecry.\n");
	    return 1;
        }

        if (strlen(str) > MAX_MESSAGE_SIZE)
        {
            write("The maximum text size cannot be greater than "+
		MAX_MESSAGE_SIZE+" characters.\n");
	    return 1;
        }

        if (member_array("|", explode(str, "")) != -1)
	{
	    write("The text cannot contain the '|' character.\n");
	    return 1;
        }

        setuid(); seteuid(getuid());

        if (!present(MERC_MESSAGE_ID, TP))
            clone_object(MOBJ + "message_object")->move(TP);

        TP->add_prop(MERC_S_DEFAULT_BATTLECRY, str);
        write("You set your default battlecry to: "+str+".\n");        
        return 1;
    }

    if (!str && !TP->query_attack())
        return 0;
    else if (!str)
        str = OB_NAME(TP->query_attack());

    /* Temporary fix for human defaulting to the adverb humanely rather
     * than the target human
     */
    if (extract(str, 0, 4) == "human" || extract(str, 0, 5) == "hobbit")
    {
        how = ({ str, "", });
    }
    else
        how = parse_adverb_with_space(str, ".", 0);

    if (!strlen(how[0]) && !TP->query_attack())
        return 0;
    else if (!strlen(how[0]))
        how[0] = OB_NAME(TP->query_attack());

    if (!parse_command(how[0], E(TP), "[the] %l %s", 
	tmp_oblist, tmp))
            if (!parse_command(how[0], E(TP), "[the] %l", tmp_oblist))
		    return 0;

    if (!sizeof(tmp_oblist) && TP->query_attack())
        tmp_oblist = ({ 1, TP->query_attack() });

    /* Remove the weird first element of the tmp_oblist mixed variable */
    if (sizeof(tmp_oblist))
        oblist = NORMAL_ACCESS(tmp_oblist, 0, 0);
    
    if (!strlen(tmp) && strlen(TP->query_prop(MERC_S_DEFAULT_BATTLECRY)))
        tmp = TP->query_prop(MERC_S_DEFAULT_BATTLECRY);

    if (strlen(tmp))
        parse_command(tmp, E(TP), "[in] [the] [name] [of] %w", tmp2);

    notify_fail("You cannot attack more than one person at a time.\n");

    if (sizeof(oblist) > 1)
        return 0;

    if (strlen(tmp) && strlen(tmp2) && 
	(tmp2 == "me" || C(tmp2) == lord))
    {
        if (tmp2 == "me" && lord != TP->query_name())
        {
            notify_fail("You are not a mercenary lord, thus you cannot "+
		"shout a battlecry in your own name.\n");
	    return 0;
        }
        else if (C(tmp2) != lord && tmp2 != "me")
        {
            write("You do not follow a lord named "+C(tmp)+", and thus you "+
		"cannot shout a battlecry in that name.\n");
	    return 1;
        }

        gender = MCREST->query_lord_gender(lord);
        if (gender != "lord" && gender != "lady")
	    gender = "lord";

        merc_status = MCREST->query_lord_status(lord);

        name = "Victory to ";

        switch(merc_status)
        {
	    case MERC_STATUS_ASPIRING:
		name += C(lord);
                break;
            case MERC_STATUS_LORD:
		name += C(gender)+" "+C(lord);
		break;
	    case MERC_STATUS_WARLORD:
		name += C(lord)+" the War"+gender;
		break;
	}

    }
    else if (strlen(tmp))
    {
        name = tmp;
    }
    else
    {
        name = "For victory";
    }

    if (sizeof(TP->query_weapon(-1)))
	weapon = TP->query_weapon(-1)[0];

    if (!sizeof(oblist) && !TP->query_attack())
    {
        write("Kill whom?\n");
        return 1;
    }
    else if (oblist[0] == TP->query_attack())
    {
        if (objectp(weapon))
        {
	    write("You raise your "+weapon->short()+" aloft"+how[1]+", shouting: '"+
	        name+"', as you attack "+TP->query_attack()->query_the_name(TP)+
		" with renewed fervor!\n");
	    TP->query_attack()->catch_msg(TP->query_The_name(TP->query_attack())+
		" raises "+POSSESSIVE(TP)+" "+weapon->short()+" aloft"+how[1]+", "+
		"shouting: '"+name+"', as "+PRONOUN(TP)+" attacks you with renewed "+
		"fervor!\n");
	    say(QCTNAME(TP)+" raises "+POSSESSIVE(TP)+" "+weapon->short()+" aloft"+
		how[1]+	", shouting: '"+name+"', as "+PRONOUN(TP)+" attacks "+
		QTNAME(TP->query_attack())+" with renewed fervor!\n", 
		({ TP->query_attack(), TP }));
	    return 1;
        }

	write("You shout: '"+
	    name+"' as you attack "+TP->query_attack()->query_the_name(TP)+
	    " with renewed fervor!\n");
	TP->query_attack()->catch_msg(TP->query_The_name(TP->query_attack())+
	    "shouts: '"+name+"' as "+PRONOUN(TP)+" attacks you with renewed "+
	    "fervor!\n");
	say(QCTNAME(TP)+" shouts: '"+name+"' as "+PRONOUN(TP)+" attacks "+
	    QTNAME(TP->query_attack())+" with renewed fervor!\n", 
	    ({ TP->query_attack(), TP }));
        return 1;
    }
    else
    {

        /* Normal 'kill' command checks here */
        if (!CAN_SEE_IN_ROOM(this_player()))
        {
            notify_fail("You can't see anything here.\n");
            return 0;
        }

        if (this_player()->query_ghost())
        {
            notify_fail("Umm yes, killed. That's what you are.\n");
            return 0;
        }

        ob = oblist[0];
  
        if (!living(ob))
        {
           write(capitalize(LANG_THESHORT(ob)) + " isn't alive!\n");
           return 1;
        }
     
        if (ob->query_ghost())
        {
            write(ob->query_The_name(this_player()) + " is already dead!\n");
            return 1;
        }

        if (ob == this_player())
        {
            write("What? Attack yourself?\n");
            return 1;
        }

        if (this_player()->query_attack() == ob)
        {
            write("Yes, yes.\n");
            return 1;
        }

        if (tmp = environment(this_player())->query_prop(ROOM_M_NO_ATTACK))
        {
            if (stringp(tmp))
                write(tmp);
            else
                write("You sense a divine force preventing your attack.\n");
            return 1;
        }

        if (tmp = ob->query_prop(OBJ_M_NO_ATTACK))
        {
            if (stringp(tmp))
            {
                write(tmp);
            }
            else
            {
                write("You feel a divine force protecting this being, your " +
                    "attack fails.\n");
            }


            return 1;
        }
 
        if (!this_player()->query_npc() &&
            this_player()->query_met(ob) &&
            (this_player()->query_prop(LIVE_O_LAST_KILL) != ob))
        {
            this_player()->add_prop(LIVE_O_LAST_KILL, ob);
            /* Only ask if the person did not use the real name of the target. */
            if (explode(how[0], " ")[0] != ob->query_real_name())
            {
                write("Attack " + ob->query_the_name(this_player()) +
                    "?!? Please confirm by trying again.\n");
                return 1;
            }
        }

        this_player()->reveal_me(1);

        /* Check if we dare! */
        if (!F_DARE_ATTACK(this_player(), ob))
        {
            write("Umm... no. You do not have enough self-discipline to dare!\n");
            say(QCTNAME(this_player()) + " considers attacking " + QTNAME(ob) +
                ", though does not dare to do so.\n", ({ ob, this_player() }) );
            tell_object(ob, this_player()->query_The_name(ob) +
                " looks at you as if ready to attack, though you see fear in " +
                this_player()->query_possessive() + " eyes.\n");
            return 1;
        }

        this_player()->attack_object(ob);
        this_player()->add_prop(LIVE_O_LAST_KILL, ob);

        if (objectp(weapon))
        {
            actor("You raise your "+weapon->short()+" aloft"+how[1]+", "+
		"shouting: '"+name+"', as you rush forward to do battle with",
		oblist, ".");
	    target(" raises "+POSSESSIVE(TP)+" "+weapon->short()+" aloft"+how[1]+
		", shouting: '"+name+"', as "+PRONOUN(TP)+" rushes forward to do "+
		"battle with you.", oblist);
	    all2act(" raises "+POSSESSIVE(TP)+" "+weapon->short()+" aloft"+how[1]+
		", shouting: '"+name+"', as "+PRONOUN(TP)+" rushes forward to do "+
		"battle with", oblist, ".");
	    return 1;
        }

	actor("You shout: '"+name+"' as you rush forward to do battle with",
	    oblist, ".");
	target(" shouts: '"+name+"' as "+PRONOUN(TP)+" rushes forward to do "+
	    "battle with you.", oblist);
	all2act(" shouts: '"+name+"' as "+PRONOUN(TP)+" rushes forward to do "+
	    "battle with ", oblist, ".");
	return 1;
    }

    return 0;
}


public int
mmercy(string str)
{
    string title;
    int setting;

    if (!str)
    {
        setting = TP->query_skill(SS_MERC_MERCY);
        if (setting == 0)
            title = "not merciful";
        else if (setting == 1)
            title = "merciful";
        else
        {
            TP->set_skill(SS_MERC_MERCY, 0);
            title = "not merciful";
        }
        write("You are currently "+title+".\n");
        return 1;
    }


    if (!MERC_MERCY_ABILITY)
    {
	write("Maligant does not permit you to be merciful at this time.\n");
	return 1;
    }

    if (str == "on" || str == "enable" || str == "enabled")
    {
	TP->set_skill(SS_MERC_MERCY, 1);
	write("You will now be merciful and not kill another player.\n");
        say(QCTNAME(TP)+"'s face takes on a merciful expression.\n");
	return 1;
    }

    if (str == "off" || str == "disable" || str == "disabled")
    {
	TP->set_skill(SS_MERC_MERCY, 0);
	write("You are no longer merciful, and can once again kill another "+
	    "player.\n");
        say(QCTNAME(TP)+"'s face takes on a merciless expression.\n");
	return 1;
    }

    NF("What? Use just 'mercy' to check your setting, and 'on' or 'off' "+
       "to change your setting.\n");
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

    if (MEMBER_CLUB(TP))
    {
        tmp = "holster";
        tmp2 = "holstered";
        tmp3 = "club";
    }
   else if (MEMBER_SWORD(TP))
    {
        tmp = "scabbard";
        tmp2 = "sheathed";
        tmp3 = "sword";
    }

    NF("You have no "+tmp+"! Get one immediately!\n");
    if (!(scabbard = present("_merc_guild_item_", TP)))
        return 0;
    
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

    if (scabbard->query_sheathed())
    {
        SOULDESC("looking around"+how[1]+" with narrowed eyes");
        actor("Your eyes narrow"+how[1]+" as you look at", oblist,", your "+
		"hand dropping to the hilt of your "+tmp2+" "+tmp3+".");
        target("'s eyes narrow"+how[1]+" as "+PRONOUN(TP)+" looks at you, "+
		POSSESSIVE(TP)+" hand dropping to the hilt of "+POSSESSIVE(TP)+
		" "+tmp2+" "+tmp3+".", oblist);
        all2act("'s eyes narrow"+how[1]+" as "+PRONOUN(TP)+" looks at",
		oblist, ", "+POSSESSIVE(TP)+" hand dropping to the hilt of "+
		POSSESSIVE(TP)+" "+tmp2+" "+tmp3+".");
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
moptions(string str)
{
    string	mhail_message = "No default message", 
		mfare_message = "No default message",
		mkill_message = "No default message",
		mattack_message = "Disabled",
		mercy_message = "Disabled",
		title_message = "Full introduction",
		defending_message = "You are not defending another",
		order_message = "Disabled",
		gagdog_message = "Disabled",
		tmp = "";

    if (strlen(tmp = TP->query_prop(MERC_S_DEFAULT_BATTLECRY)) && tmp != "none")
        mkill_message = tmp;

    if (strlen(tmp = TP->query_prop(MERC_S_DEFAULT_HAIL)) && tmp != "none")
	mhail_message = tmp;

    if (strlen(tmp = TP->query_prop(MERC_S_DEFAULT_FAREWELL)) && tmp != "none")
	mfare_message = tmp;

    if (TP->query_skill(SS_MERC_AUTOMATTACK))
	mattack_message = "Enabled";

    if (TP->query_skill(SS_MERC_AUTOCOMPLY))
	order_message = "Enabled";

    if (TP->query_skill(SS_MERC_MERCY))
	mercy_message = "Enabled";

    if (TP->query_skill(SS_MERC_TITLE) == 2)
	title_message = "Brief introduction";
    else if (TP->query_skill(SS_MERC_TITLE) == 3)
	title_message = "No introduction";

    if (TP->query_skill(SS_MERC_GAG_DOG) == 1)
	gagdog_message = "Enabled";

    if (objectp(TP->query_defended()))
        defending_message = "You are currently defending "+
	    TP->query_defended()->query_the_name(TP);

    write("Mercenary Guild Options\n"+
          "  Default Battlecry: " + mkill_message + "\n"+
	  "  Default Hail     : " + mhail_message + "\n"+
          "  Default Farewell : " + mfare_message + "\n"+
	  "  Automatic Mattack: " + mattack_message + "\n"+
          "  Automatic Orders : " + order_message + "\n"+
	  "  Defending Other  : " + defending_message + "\n"+
          "  Mercy Status     : " + mercy_message + "\n"+
          "  Title Status     : " + title_message + "\n"+
	  "");
    if (MCREST->query_lord_status(TP->query_name()) >= MERC_STATUS_ASPIRING || TP->query_wiz_level())
        write("  Gag Dog Arrivals : " + gagdog_message + "\n");
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
msecure(string str)
{
    string *how = parse_adverb_with_space(str, "casually", 1);
    string tmp, tmp2, tmp3;
    object scabbard, *wep;

    if (strlen(how[0]))
    {
        NF("Feel secure [how]? No object is needed!\n");
            return 0;
    }

    if (MEMBER_CLUB(TP))
    {
        tmp = "holster";
        tmp2 = "holstered";
        tmp3 = "club";
    }
   else if (MEMBER_SWORD(TP))
    {
        tmp = "scabbard";
        tmp2 = "sheathed";
        tmp3 = "sword";
    }
    else
        tmp3 = "weapon";


    NF("You have no "+tmp+"! Get one immediately!\n");
    if (!(scabbard = present("_merc_guild_item_", TP)))
        return 0;
    
    if (sizeof(TP->query_weapon(-1)))
    {
        wep = TP->query_weapon(-1)[0];
        SOULDESC("looking secure and confident");
        write("You feel secure as your grip tightens on your "+
	    wep->short()+".\n");
        all(" looks more secure as "+POSSESSIVE(TP)+" grip tightens on "+
	    POSSESSIVE(TP)+" "+wep->short()+".\n");
        return 1;
    }

    if (scabbard->query_sheathed())
    {
        SOULDESC("looking secure and confident");
	write("You feel secure as your hand rests"+how[1]+" on the hilt of "+
	    "your "+tmp2+" "+tmp3+".\n");
	all(" looks secure as "+POSSESSIVE(TP)+" hand rests"+how[1]+" on the "+
	    "hilt of "+POSSESSIVE(TP)+" "+tmp2+" "+tmp3+".\n");
	return 1;
    }

    SOULDESC("looking rather panic-striken");
    write("An icy chill shoots through your body as you realize you have no "+
	tmp3+" at the ready.\n");
    all(" looks temporarily panic-stricken.\n");
    return 1;
}


public int
mstray(string str)
{
    string *how = parse_adverb_with_space(str, "meaningfully", 0);
    string tmp, tmp2, tmp3;
    object scabbard;

    if (MEMBER_CLUB(TP))
    {
        tmp = "holster";
        tmp2 = "holstered";
        tmp3 = "club";
    }
   else if (MEMBER_SWORD(TP))
    {
        tmp = "scabbard";
        tmp2 = "sheathed";
        tmp3 = "sword";
    }
   else if (how[0] == "golden scabbard" || !strlen(how[0]))
    {
        NF("You have no scabbard or holster.\n");
        if (!(scabbard = present("_emyn_arnen_scabbard", TP)))
            return 0;
    
        NF("There is nothing sheathed in your golden scabbard!\n");
        if (!sizeof(all_inventory(scabbard)))
            return 0;
 
        SOULDESC("fingering the golden scabbard"+how[1]);
        write("Your hand strays"+how[1]+" to the hilt of your "+
	    "sword sheathed in your golden scabbard.\n");
        all("'s hand strays"+how[1]+" to the hilt of "+POSSESSIVE(TP)+" "+
	    "sword sheathed in "+POSSESSIVE(TP)+" golden scabbard.");
        return 1;
    }
   else
    {
        NF("You have no scabbard or holster.\n");
	return 0;
    }

    if (how[0] == "golden scabbard")
    {
        NF("You have no scabbard or holster.\n");
        if (!(scabbard = present("_emyn_arnen_scabbard", TP)))
            return 0;
    
        NF("There is nothing sheathed in your golden scabbard!\n");
        if (!sizeof(all_inventory(scabbard)))
            return 0;
 
        SOULDESC("fingering the golden scabbard"+how[1]);
        write("Your hand strays"+how[1]+" to the hilt of your "+
	    "sword sheathed in your golden scabbard.\n");
        all("'s hand strays"+how[1]+" to the hilt of "+POSSESSIVE(TP)+" "+
	    "sword sheathed in "+POSSESSIVE(TP)+" golden scabbard.");
        return 1;
    }

    if (strlen(how[0]))
    {
        NF("Your hand strays [how] to [what]? No object is needed!\n");
        if (MEMBER_CLUB(TP) && how[0] != "holster")
            return 0;

        if (MEMBER_SWORD(TP) && how[0] != "scabbard")
            return 0;

    }

    NF("You have no "+tmp+"! Get one immediately!\n");
    if (!(scabbard = present("_merc_guild_item_", TP)))
        return 0;
    
    NF("There is nothing "+tmp2+" in your "+tmp+"!\n");
    if (!scabbard->query_sheathed())
        return 0;

    SOULDESC("fingering the black leather "+
        (tmp3 == "sword" ? "scabbard" : "holster"));
    write("Your hand strays"+how[1]+" to the hilt of your "+tmp2+" "+
	tmp3+".\n");
    all("'s hand strays"+how[1]+" to the hilt of "+POSSESSIVE(TP)+" "+
	tmp2+" "+tmp3+".");
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
mspit(string str)
{
    object *oblist, wep = query_weapon(TP);
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
mswear(string str)
{
    string *how = parse_adverb_with_space(str, "solemnly", 0);
    string lord = MCREST->query_members_lord(TP->query_name());
    string gender;
    object lord_here;

    /* Setup failure message */
    notify_fail("Swear allegiance to your lord [how]?\n");

    if (strlen(how[0]))
        return 0;

    if (lord == "none")
    {
        notify_fail("You are not a member of a cause.\n");
        return 0;
    }

    gender = capitalize(MCREST->query_lord_gender(lord));
    if (gender != "lord" && gender != "lady")
	gender = "lord";

    if (MCREST->query_lord_status(lord))
    {
        if (lord == TP->query_name())
        {
	    write("You"+how[1]+" swear allegiance to yourself. How grand.\n");
            all(""+how[1]+" swears allegiance to "+OBJECTIVE(TP)+"self for "+
		"some reason.\n");
            return 1;
        }

        write("You"+how[1]+" swear allegiance to your "+gender+", "+
	    lord+".\n");
        if (lord_here = (present(lower_case(lord), environment(TP))))
        {
            say(QCTNAME(TP)+how[1]+" swears allegiance to "+POSSESSIVE(TP)+
		" "+gender+", "+lord+".\n", 
		({ lord_here, TP }));
            lord_here->catch_tell(TP->query_The_name(lord_here)+how[1]+
		" swears allegiance to you.\n");
        } 
       else
        {
            all(""+how[1] + " swears allegiance to "+POSSESSIVE(TP)+
		" "+gender+", "+lord+".\n");
        }

        return 1;
    }
    return 0;
}


public int
mtalk(string str)
{
    object *oblist, wep = query_weapon(TP);
    string *how = parse_adverb_with_space(str, "", 1);
    string tmp, tmp2, tmp3;

    /* Find if argument is valid */
    oblist = parse_this(how[0], "[at] [the] %i");

    /* Setup failure message */
    notify_fail("Let [whom] know [how] that the time for talk is over?\n");

    if (wep)
    {
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
mtitle(string str)
{
    string title;
    int setting;

    if (!str)
    {
        setting = TP->query_skill(SS_MERC_TITLE);

        TP->set_skill(SS_MERC_TITLE, 1);
        title = TP->query_guild_title_occ();
        TP->set_skill(SS_MERC_TITLE, setting);   
        
        write("Your title is the "+title+".\n");
        return 1;
    }

    if (!MERC_CHANGE_TITLE_ABILITY)
    {
	write("Maligant does not permit you to hide or change your "+
	    "title at this time.\n");
	return 1;
    }

    if (str == "full" || str == "Full")
    {
	TP->set_skill(SS_MERC_TITLE, 1);
	write("You will introduce yourself fully with the title of '"+
	    TP->query_guild_title_occ()+"'.\n");
	return 1;
    }

    if (str == "brief" || str == "Brief")
    {
	TP->set_skill(SS_MERC_TITLE, 2);
	write("You will introduce yourself simply as 'the Mercenary.'\n");
	return 1;
    }

    if (str == "none" || str == "None")
    {
	TP->set_skill(SS_MERC_TITLE, 3);
	write("You will not introduce yourself as a mercenary at all.\n");
	return 1;
    }

    if (str == "cause" || str == "Cause" && !MCREST->query_crest_lord(TP->query_name()))
    {
	TP->set_skill(SS_MERC_TITLE, 4);
	write("You will introduce yourself fully with the title of '"+
	    TP->query_guild_title_occ()+"'.\n");
	return 1;
    }

    NF("Show which title? Full, brief, cause or none?\n");
    return 0;
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
