
/*
*   sol_emotes1.h
*
*   This file contains the emotes/feelings
*   of the Solamnic Knights
*
*   kA - kO
*
*   Grace, July 1994
*   new emotes added Nov 1995 by Grace
*
*/
/********************* kaccept *************************************/
int
kaccept(string str)
{
    object *oblist;
    oblist = parse_this(str, "[the] %l");

    if (!sizeof(oblist))
    {
	NF("Accept who?\n");
	return 0;
    }

    actor("You humbly accept the offer that", oblist, " has made.");
    target(" humbly accepts your offer.", oblist);
    all2act(" humbly accepts the offer", oblist, " has made.");   
    return 1;
}

/************************ kamused ***********************************/

int
kamused(string str)
{
    if (strlen(str))
    {
	NF("Kamuse what?!");
	return 0;
    }

    write("You are NOT amused!\n");
    all(" is NOT amused!");
    return 1;
}

/********************* kassist *************************************/
int
kassist(string str)
{
    object *oblist;

    NF("Assist who?\n");
    if (!str)
    {
	write("You gallantly offer your assistance.\n");
	all(" gallantly offers " + TP->query_possessive() +
	  " assistance.");
	return 1;
    }
    if (str == lower_case(TP->query_name()))
    {
	write("You gallantly assist yourself, what a self-sufficient " +
	  "person you are!\n");
	return 1;
    }
    oblist = parse_this(str, "[the] %l");
    if (!sizeof(oblist))
	return 0;

    actor("You gallantly offer", oblist, " your assistance.");
    target(" gallantly offers you " + TP->query_possessive() +
      " assistance.", oblist);
    all2act(" gallantly offers " + TP->query_possessive() +
      " assistance to", oblist, ".");
    return 1;
}


/********************* battlecry ********************************************/
int
battlecry(string str)
{
    NF("Battlecry What?\n");

    if (TP->query_prop(KNIGHT_I_DEVOTION) < TP->query_age() + 1000)
	TP->add_prop(KNIGHT_I_DEVOTION, TP->query_age() + 1000);

    if (!str)
    {
	write("You give a heroic battlecry as you prepare to destroy your enemies!\n");
	SAY(" gives a heroic battlecry and prepares to kill " + POSSESSIVE(TP) + " enemies!");
	return 1;
    }
    if (str == "death")
    {
	write("You scream a battlecry of death to all your enemies!\n");
	SAY(" screams a battlecry declaring death to all " + POSSESSIVE(TP) + " enemies!");
	return 1;
    }
    return 0;
}

/********************** kbow ******************************************/
/* Modified by Morrigan, 10/6/96, to only allow full Knights to bow   */
int
kbow(string str)
{
    object *oblist;
    string his_her;

    if (TP->query_knight_level() == 2 && !str)
    {
	write("Straightening your back with pride, you bow formally.\n");
	say("Straightening "+POSSESSIVE(TP)+" back with pride, "+QTNAME(TP)+
	  " bows formally.\n");
	return 1;
    }

    NF("Bow to whom?\n");

    if (!str)
    {
	write("You bow with the old-fashioned courtesy of a Solamnic Knight.\n");
	all(" bows with the old-fashioned courtesy of a Solamnic Knight.");
	return 1;
    }

    oblist = parse_this(str, "[to] / [before] [the] %l");
    if (!sizeof(oblist))
	return 0;

    if (TP->query_knight_level() == 2)
    {
	if (sizeof(oblist) == 1 && oblist[0]->query_knight_level() > 2)
	{
	    his_her = oblist[0]->query_possessive();
	    actor("Straightening your back with pride, you bow to",
	      oblist, " with the respect befitting a Knight of "+
	      his_her+" station.");
	    target(" straightens "+POSSESSIVE(TP)+" back with pride "+
	      "and bows to you with the respect befitting a Knight "+
	      "of your station.", oblist);
	    all2act(" straightens "+POSSESSIVE(TP)+" back with pride "+
	      "and bows to", oblist, " with the respect befitting a "+
	      "Knight of "+his_her+" station.");
	    return 1;
	}

	actor("Straightening your back with pride, you bow formally before",
	  oblist, ".");
	target(" straightens "+POSSESSIVE(TP)+" back with pride and bows "+
	  "formally before you.", oblist);
	all2act(" straightens "+POSSESSIVE(TP)+" back with pride and bows "+
	  "formally before", oblist, ".");
	return 1;
    }

    actor("You bow to", oblist, " with the old-fashioned courtesy" +
      " of a Solamnic Knight.");
    target(" bows to you with the old-fashioned courtesy" +
      " of a Solamnic Knight.", oblist);
    all2act(" bows to", oblist, " with the old-fashioned courtesy" +
      " of a Solamnic Knight.");
    return 1;
}

/************************ kbrook ***********************************/
int
kbrook(string str)
{
    object *oblist;


    if (!str)
    {
	write("You will brook no further argument.\n");
	all(" will brook no further argument!");
	return 1;
    }

    oblist = parse_this(str, "[from] [the] %l");
    if (!sizeof(oblist))
    {
	NF("You will brook no argument from whom?");
	return 0;
    }

    target(" will brook no further argument from you!",oblist);
    actor("You will brook no further argument from", oblist, "!");
    all2act(" will brook no further argument from", oblist, "!");
    return 1;
}

/************************* kbrush ******************************/
int kbrush(string str)
{
    object *armours = TP->query_armour(-1), armour, cloak;
    int i;
    string *pre, ob;

    if (present("_knight_cloak", TP))
	cloak = present("_knight_cloak", TP);

    if (cloak && str == "cape" || str == "c")
	ob = cloak->short();
    else
	ob = "tunic";

    if (sizeof(armours))
	for (i = 0; i < sizeof(armours); i++)
	{
	    if (armours[i]->query_at() == A_HANDS ||
	      armours[i]->query_at() == A_R_HAND ||
	      armours[i]->query_at() == A_L_HAND)
		armour = armours[i];
	}

    if (armour)
	pre = ({ "Removing your "+armour->short()+" briefly, you ",
	  "Removing "+POSSESSIVE(TP)+" "+armour->short()+
	  " briefly, "+QTNAME(TP)+" " });
    else
	pre = ({ "You ", QCTNAME(TP)+" " });

    write(pre[0]+"brush the dust away that has gathered on your "+
      ob+".\n");
    say(pre[1]+"brushes away the dust that has gathered on "+
      POSSESSIVE(TP)+" "+ob+".\n");
    return 1;
}

/*********************** kbye ***************************************/
int
kbye(string str)
{
    object *oblist;

    if (TP->query_prop(KNIGHT_I_DEVOTION) < TP->query_age() + 1000)
	TP->add_prop(KNIGHT_I_DEVOTION, TP->query_age() + 1000);   

    if (!strlen(str))
    {
	write("You say: May the roads you walk be sunny and straight, "+
	  "and may Paladine's smile be warm upon your face.\n");
	all(" says: May the roads you walk be sunny and straight, and "+
	  "may Paladine's smile be warm upon your face.");
	return 1;
    }

    oblist = parse_this(str, "[to] [the] %l");
    oblist -= ({ this_player });

    if (!sizeof(oblist))
    {
	notify_fail("Say goodbye to who?\n");
	return 0;
    }

    actor("You say to", oblist, ": May the roads you walk be sunny and "+
      "straight, and may Paladine's smile be warm upon your face.");
    target(" says to you: May the roads you walk be sunny and straight, "+
      "and may Paladine's smile be warm upon your face.", oblist);
    all2act(" says to", oblist, ": May the roads you walk be sunny and "+
      "straight, and may Paladine's smile be warm upon your face.");
    return 1;
}

/********************* kchant *****************************************
*** The Death Chant, or Prayer to Huma, said over a fallen comrade ***
*/

int
kchant(string str)
{
    if (strlen(str))
    {
	notify_fail("Kchant what?\n");
	return 0;
    }

    if (TP->query_prop(KNIGHT_I_DEVOTION) < TP->query_age() + 1000)
	TP->add_prop(KNIGHT_I_DEVOTION, TP->query_age() + 1000);

    write("You raise your voice, mournfully chanting the Prayer to Huma:\n" +
      "       Return this man to Huma's breast\n" +
      "       Beyond the wild impartial skies.\n" +
      "       Grant to him a warriors rest,\n" +
      "       And set the last spark of his eyes\n" +
      "       Free from the smothering clouds of war.\n" +
      "       Upon the torches of the stars\n" +
      "       Let the last surge of his breath\n" +
      "       Take refuge on the cradling air\n" +
      "       Above the dreams of ravens where\n" +
      "       Only the hawk remembers death.\n" +
      "       Then let his shade to Huma rise\n" +
      "       Beyond the wild, impartial skies.\n");

    all(" raises " + TP->query_possessive() + " voice, mournfully" +
      " chanting the Prayer to Huma:\n" +
      "       Return this man to Huma's breast\n" +
      "       Beyond the wild impartial skies.\n" +
      "       Grant to him a warriors rest,\n" +
      "       And set the last spark of his eyes\n" +
      "       Free from the smothering clouds of war.\n" +
      "       Upon the torches of the stars\n" +
      "       Let the last surge of his breath\n" +
      "       Take refuge on the cradling air\n" +
      "       Above the dreams of ravens where\n" +
      "       Only the hawk remembers death.\n" +
      "       Then let his shade to Huma rise\n" +
      "       Beyond the wild, impartial skies.");
    return 1;
}

/*********************** kchaste ***************************************/
int
kchaste(string str)
{
    object *oblist;
    if (!strlen(str))
    {
	notify_fail("Give whom a chaste kiss?\n");
	return 0;
    }

    oblist = parse_this(str, "[to] [the] %l");
    if (!sizeof(oblist))
	return 0;

    actor("You give", oblist, " a chaste kiss, one on each cheek.");
    target(" gives you a chaste kiss, one on each cheek.", oblist);
    all2act(" gives", oblist, " a chaste kiss, one on each cheek.");
    return 1;
}


/********************** kclasp *****************************************/

int
kclasp(string str)
{
    object *oblist;

    NF("kclasp whom?\n");

    if (!str)
    {
	write("You stretch your hand out. No one takes it. You put your" +
	  " hand in your pocket, embarrassed.\n");
	all(" stuffs " + TP->query_possessive() + " hands in " +
	  TP->query_possessive() + " pockets, looking mildly embarrassed.");
	return 1;
    }

    oblist = parse_this(str, "[of] [the] %l");
    if (!sizeof(oblist))
	return 0;

    actor("You clasp the hand of", oblist, " in welcome.");
    target(" clasps your hand in warm welcome.", oblist);
    all2act(" clasps the hand of", oblist, " in warm welcome.");
    return 1;
}


/********************* kcount ******************************************/
/****** Thanks to Mayhem for showing me how to code what I wanted ******/

int
kcount()
{
    write("You inhale deeply in frustration.\n");
    all(" inhales deeply.");
    set_alarm(2.0,0.0,"begin_count");
    return 1;
}

begin_count()
{
    write("You begin counting to 10:\n" + "   1... 2... 3... 4...\n");
    all(" slowly counts to ten.");
    set_alarm(3.0,0.0,"turn_red");
    return 1;
}

turn_red()
{
    write("...5... 6... 7...\n" + "You can feel you face grow hot.\n");
    all(" begins to turn red in the face.");
    set_alarm(3.0,0.0,"do_exhale");
    return 1;
}

do_exhale()
{
    write("...8... 9... 10\nYou exhale deeply.\n");
    all(" exhales slowly.");
    set_alarm(2.0,0.0,"do_grace");
    return 1;
}

do_grace()
{
    write("Paladine's grace flows through you, washing away your anger.\n" +
      "You feel much more relaxed.\n");
    all(" looks much more relaxed.");
    return 1;
}


/********************* kcrfaith  ********************************************/
/* Added 10/6/96 by Morrigan, created by Teth.                              */
int
kcrfaith(string str)
{
    if (TP->query_knight_level() != 3)
    {
	write("You are not a Knight of the Crown.\n");
	return 1;
    }

    write("You declare your faith that the Knighthood will rise in power "+
      "again, like a phoenix reborn.\n");
    all(" declares "+TP->query_possessive()+" faith that the Knighthood "+
      "will rise in power again, like a phoenix reborn.");
    return 1;
}


/********************* kcrstand **************************************/
/* Suggested by Teth, added by Morrigan. 10/6/96                     */
int
kcrstand(string str)
{
    object *oblist;
    oblist = parse_this(str, "[the] %l");

    if (TP->query_knight_level() != 3)
    {
	write("You are not a Knight of the Crown.\n");
	return 1;
    }

    if (!sizeof(oblist))
    {
	NF("Stand by whom?\n");
	return 0;
    }

    actor("You state your decision to stand by", oblist, "'s "+
      "side, no matter what occurs.");
    target(" states "+POSSESSIVE(TP)+" decision to stand by your side, no matter "+
      "what occurs.", oblist);
    all2act(" states "+TP->query_possessive()+" decision to stand by",
      oblist, "'s side, no matter what occurs.");
    return 1;

}


/********************* kcry******************************************/
int
kcry(string str)
{
    object *oblist;

    if (!strlen(str))
    {
	write("You cry:   By the Measure, now and always, let " +
	  "swords fall as swords will fall!\n");
	all(" cries:   By the Measure, now and always, let " +
	  "swords fall as swords will fall!");
	return 1;
    }

    oblist = parse_this(str, "[at] [to] %l");

    if (!sizeof(oblist))
    {
	NF("Cry to whom?\n");
	return 0;
    }

    actor("You cry out to", oblist, ":   By the Measure, now and " +
      "always, let swords fall as swords will fall!");
    target(" cries out to you:    By the Measure, now and " +
      "always, let swords fall as swords will fall!", oblist);
    all2act(" cries out to", oblist, ":   By the Measure, now and " +
      "always, let swords fall as swords will fall!");
    return 1;
}


/************************* kdeclare **********************************/
int
kdeclare(string str)
{
    if (strlen(str))
    {
	notify_fail("Declare what? Try it without a string.\n");
	return 0;
    }

    if (TP->query_prop(KNIGHT_I_DEVOTION) < TP->query_age() + 1000)
	TP->add_prop(KNIGHT_I_DEVOTION, TP->query_age() + 1000);

    write("You fiercely declare: Est Sularus Oth Mithas!\n" +
      "                      My Honour is my Life!\n");
    all(" fiercely declares: Est Sularus Oth Mithas!\n" +
      "                               My Honour is my Life!");
    return 1;
}

/********************* kdeem ****************************************/

int
kdeem(string str)
{
    object *oblist;
    oblist = parse_this(str, "[the] %l");

    if (!sizeof(oblist))
    {
	NF("Kdeem whom?\n");
	return 0;
    }

    actor("You deem", oblist, " to be a worthy comrade-in-arms.");
    target(" deems you to be a worthy comrade-in-arms.", oblist);
    all2act(" deems", oblist, " to be a worthy comrade-in-arms.");
    return 1;

}


/********************* kdie****************************************/
/*
int
kdie(string str)
{
   string pos = POSSESSIVE(TP);
   write("With a last glance at your wounds you pull yourself together " +
      "and prepare for Paladine's embrace in your last glorious battle!\n");
   all(" looks down at " + pos + " many wounds and grits " + pos +
      " teeth. With a final cry to Paladine " + PRONOUN(TP) +
      " prepares to end " + pos + " life in one last glorious battle!");
   return 1;
}
*/

/********************* kduel1****************************************/
int
kduel1(string str)
{
    object *oblist;

    if (!str)
    {
	NF("Challenge who?\n");
	return 0;
    }

    oblist = parse_this(str, "[the] %l");
    if (!sizeof(oblist))
	return 0;

    actor("You challenge", oblist, " to a duel!\n");
    target(" challenges you to a duel!", oblist);
    all2act(" challenges", oblist," to a duel!");
    return 1;
}


/********************* kduel2 **********************************/
/* Modified 10/6/96 by Morrigan to take into account whether or*/
/* not the Knight is wielding a weapon.                        */
int
kduel2(string str)
{
    object *oblist;
    object *wielded_weapons;
    object weapon;
    int i;

    wielded_weapons = TP->query_weapon(-1);

    if (sizeof(wielded_weapons)) {

	for (i = 0; i < sizeof(wielded_weapons); i++) {
	    weapon = wielded_weapons[i];

	}
    }

    oblist = parse_this(str, "[the] %l");

    if(!sizeof(oblist)) {
	notify_fail("Challenge whom?\n");
	return 0;
    }

    if (!weapon)
    {
	write("You cannot brandish your weapon at someone if you "+
	  "are not wielding one!\n");
	return 1;
    }

    target(" brandishes " + TP->query_possessive() + " "+ weapon->short()+
      " at you and shouts: By Paladine I challenge you!", oblist);
    actor("You brandish your "+weapon->short()+" at", oblist, " shouting:" +
      "   By Paladine I challenge you!");
    all2act(" brandishes " + TP->query_possessive() +" "+weapon->short()+
      " at", oblist," and shouts: By Paladine I challenge you!");
    return 1;
}


/****** Gotta give Aridor a 'hand' for his help with this one ******/
int
khand(string str)
{
    object *oblist, *oblf = ({ }), *oblm = ({ });
    int i;

    oblist = parse_this(str, "[the] %l [on] [the] [hand]");

    if (!oblist || !sizeof(oblist))
    {
	notify_fail("Kiss whom on the hand?\n");
	return 0;
    }

    for (i = 0; i < sizeof(oblist); i++)
    {
	if (oblist[i]->query_gender() == 1)
	    oblf += ({ oblist[i] });
	else
	    oblm += ({ oblist[i] });
    }
    if (oblf && sizeof(oblf))
    {
	actor("You go down on one knee before", oblf, " and " +
	  "take her hand in yours, kissing it tenderly.");
	target(" goes down on one knee before you and takes your " +
	  "hand, kissing it tenderly.", oblf);
	all2act(" goes down on one knee before", oblf," and " +
	  "takes her hand, kissing it tenderly.");
    }
    if (oblm && sizeof(oblm))
    {
	actor("You take the hand of", oblm, " and " +
	  "press it against your cheek, " +
	  "peering soulfully up at him.");
	target(" takes your hand and presses it against "
	  + TP->query_possessive() + " cheek, peering " +
	  "soulfully up at you.", oblm);
	all2act(" takes the hand of", oblm," and presses it " +
	  "against " + TP->query_possessive() + " cheek, " +
	  "peering soulfully up at him.");
    }
    return 1;
} 


/********************* honour ***********************************************/
int
honour(string str)
{
    object *ob, *obsup = ({ }), *obinf = ({ });
    int i, own_level;

    NF("A Knight of the Black Rose has no honour.\n");
    if ((own_level = TP->query_knight_level()) == L_BROSE)
	return 0;

    NF("Honour who?\n");
    ob = parse_this(str, "[the] %l");
    if (!ob || !sizeof(ob))
	return 0;

    for (i = 0; i < sizeof(ob); i++)
    {
	if ((ob[i]->query_wiz_level() ||
	    ob[i]->query_knight_level() == 11 ||
	    ob[i]->query_knight_level() > own_level ||
	    ob[i]->query_knight_sublevel() >= TP->query_knight_sublevel()) &&
	  !TP->query_wiz_level())
	    obsup += ({ ob[i] });
	else
	    obinf += ({ ob[i] });
    }

    if (obsup && sizeof(obsup))
    {
	actor("You bow deeply in front of", obsup, ".");
	target(" bows deeply in front of you.", obsup);
	all2act(" bows deeply in front of", obsup, ".");
    }

    if (obinf && sizeof(obinf))
    {
	actor("You give", obinf, " your blessings.");
	target(" gives you " + POSSESSIVE(TP) + " blessings.", obinf);
	all2act(" gives", obinf, " " + POSSESSIVE(TP) + " blessings.");
    }

    return 1;
}            

/********************* klaugh ***************************************/
int
klaugh(string str)
{
    object *oblist;


    if (!strlen(str))
    {
	write("You burst into hearty, infectious laughter.\n");
	all(" bursts into hearty, infectious laughter.");
	return 1;
    }

    oblist = parse_this(str, "[at] [the] %l");

    if (!sizeof(oblist))
    {
	notify_fail("Klaugh at whom?\n");
	return 0;
    }

    actor("You burst into hearty, infectious laughter at", oblist, ".");
    target(" bursts into hearty, infectious laughter at you.", oblist);
    all2act(" bursts into hearty, infectious laughter at", oblist, ".");
    return 1;
}


/******************** kmagic ****************************************/
/* Added 10/6/96 by Morrigan.                                       */
int
kmagic(string str)
{
    object *oblist;

    if (!strlen(str))
    {
	write("You scowl at the thought of magic, and how it has "+
	  "corrupted Krynn.\n");
	all(" scowls at the thought of magic.");
	return 1;
    }

    oblist = parse_this(str, "[at] [the] %l");

    if (!sizeof(oblist))
    {
	notify_fail("Scowl at whom?\n");
	return 0;
    }

    if (sizeof(oblist) == 1)
	str = (string)oblist[0]->query_objective();
    else
	str = "them";

    actor("You scowl at", oblist, " as you think of how magic has "+
      "corrupted "+str+".");
    target(" scowls at you, obviously thinking about corrupting " +
      "magic.", oblist);
    all2act(" scowls at", oblist, ", obviously thinking about " +
      "corrupting magic.");
    return 1;
}


/*********************** knees ***************************************/
int
knees(string str)
{
    object *oblist;

    oblist = parse_this(str, "[before] [the] %l");
    oblist -= ({ this_player });

    if ((!strlen(str)) || (!sizeof(oblist)))
    {
	notify_fail("Get on your knees before who?\n");
	return 0;
    }

    if (sizeof(oblist) == 1)
	str = (string)oblist[0]->query_objective();
    else
	str = "them";

    actor("You kneel before", oblist, ", asking "+str+" to bless you.");
    targetbb(" kneels before you, asking for your blessing.", oblist);
    all2actbb(" kneels before", oblist, ", asking "+str+" to bless "+
      TP->query_objective()+".");
    return 1;
}


/********************** knod ************************************/
/* Added 10/6/96 by Morrigan, suggested by Kayen.               */
int
knod(string str)
{
    object *oblist;

    if (!strlen(str))
    {
	write("You give a stern and confident nod, notifying "+
	  "everyone that it's time to press forward.\n");
	all(" gives a stern and confident nod, notifying every"+
	  "one that it's time to press forward.");
	return 1;
    }

    oblist = parse_this(str, "[at] [the] %l");

    if (!sizeof(oblist))
    {
	notify_fail("Knod at whom?\n");
	return 0;
    }

    if (sizeof(oblist) == 1)
	str = (string)oblist[0]->query_objective();
    else
	str = "them";

    actor("You give", oblist, " a stern and confident nod, "+
      "notifying "+str+" that it's time to press forward.");
    target(" gives you a stern and confident nod, notifying you "+
      "that it's time to press forward.", oblist);
    all2act(" gives", oblist, " a stern and confident nod, notifying "+
      str+" that it's time to press forward.");
    return 1;
}


/************************ knose *************************************/
int
knose(string str)
{
    object *oblist;

    if (!strlen(str))
    {
	if (TP->query_gender() == 1)
	{
	    write("You wrinkle your nose in distaste!\n");
	    all(" wrinkles her pretty little nose in distaste.");
	}
	else
	{
	    write("You wrinkle your nose in distaste!\n");
	    all(" wrinkles his nose in distaste.");
	}
	return 1;
    }

    oblist = parse_this(str, "[at] [the] %l");

    if (!sizeof(oblist))
    {
	notify_fail("Wrinkle your nose at whom?\n");
	return 0;
    }
    if (TP->query_gender() == 1)
    {
	target(" wrinkles her pretty little nose at you in " +
	  "distaste.", oblist);
	actor("You wrinkle your nose in distaste at", oblist, ".");
	all2act(" wrinkles her pretty little nose" +
	  " at", oblist, " in distaste.");
    }
    else
    {
	target(" wrinkles his nose at you in distaste.", oblist);
	actor("You wrinkle your nose in distaste at", oblist, ".");
	all2act(" wrinkles his nose at", oblist, " in distaste.");
    }
    return 1;
}

/********************* nsmile ***********************************************/
int
nsmile()
{
    write("You smile just like Nick.\n");
    allbb(" smiles just like if Nick had taught " + OBJECTIVE(TP) + ".");
    return 1;
}

