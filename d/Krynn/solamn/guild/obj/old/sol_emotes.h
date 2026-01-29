
/*
 *   sol_emotes.h
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

int
kbow(string str)
{
    object *oblist;
    
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
    write("You begin counting to 10:\n" + "   1... 2... 3...\n");
    all(" slowly counts to ten.");
    set_alarm(3.0,0.0,"turn_red");
    return 1;
}

turn_red()
{
    write("...6... 7... 8...\n" + "You can feel you face grow hot.\n");
    all(" begins to turn red in the face.");
    set_alarm(3.0,0.0,"do_exhale");
    return 1;
}

do_exhale()
{
    write("...9... 10\nYou exhale deeply.\n");
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
int
kduel2(string str)
{
    object *oblist;
    
    NF("Challenge who?\n");
    if (!str)
      {
	  write("You brandish your sword, shouting:" +
		"    By Paladine I challenge you!\n");
	  all(" brandishes " + TP->query_possessive() +
	      " sword, shouting: By Paladine I challenge you!");
	  return 1;
      }
    
    oblist = parse_this(str, "[the] %l");
    if (!sizeof(oblist))
      return 0;
    
    target(" brandishes " + TP->query_possessive() + " sword at you" +
	   " and shouts: By Paladine I challenge you!", oblist);
    actor("You brandish your sword at", oblist, " shouting:" +
	  "   By Paladine I challenge you!");
    all2act(" brandishes " + TP->query_possessive() +
	    " sword at", oblist," and shouts: By Paladine I" +
	    " challenge you!");
    return 1;
}

/********************* flex *************************************************/

int
flex(string str)
{
    write("You flex your muscles, it makes you look very intimidating!\n");
    allbb(" flexes " + POSSESSIVE(TP) + " muscles in a very intimidating " +
	  "manner!");
    return 1;
}


/*********************** kgrin ***************************************/
int
kgrin(string str)
{
    object *oblist;
   
    if (!strlen(str))
    {
        write("You grin in a lopsided, cynical way.\n");
        all(" grins in a lopsided, cynical way.");
	return 1;
    }
    
    oblist = parse_this(str, "[at] [the] %l");
    oblist -= ({ this_player });

    if (!sizeof(oblist))
      {
	  notify_fail("Kgrin at who??\n");
	  return 0;
      }
    
    actor("You grin at", oblist, " in a lopsided, cynical way.");
    targetbb(" grins at you in a lopsided, cynical way.", oblist);
    all2actbb(" grins at", oblist, " in a lopsided, cynical way.");
    return 1;
}




/********************* khand ***************************************/
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


/********************** kmourn **********************************/

int
kmourn(string str)
{
    if (strlen(str))
      {
	  notify_fail("Kmourn what? Try it without adding a name.\n");
	  return 0;
      }
    
    write("You intone: We do not mourn the loss of those who die " +
	  "fulfilling their destinies.\n");
    all(" intones: We do not mourn the loss of those who die fulfilling" +
        " their destinies.");
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

