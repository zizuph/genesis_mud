public int
uaccept_emote(string arg)
{
    object *oblist, recipient, tp;
    string *how, adverb, tmp;

    // check for union, correct garb, fix capitalization

    tp = this_player();
    how = parse_adverb_with_space(arg, "closely" , 0);
    adverb = how[1];


    if (!stringp(how[0]))
    {
	write("You" + adverb + " examine everyone around for presentability.\n");
	allbb(adverb + " examines everyone around for presentability.", adverb);
	return 1;
    }

    oblist = parse_this(how[0], "[to] [at] [the] %l");

    if (!sizeof(oblist))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    if (sizeof(oblist) > 1)
    {
	notify_fail("You may only do that to a single target.\n");
	return 0;
    }


    recipient = oblist[0];

    actor("You" + adverb + " examine", oblist, ", then straighten "
      + recipient->query_possessive() + " clothes here and there.\nYou proclaim "
      + recipient->query_objective() + " fit for duty.");
    target(adverb + " examines you, then straightens your clothes here and there.\n"
      + capitalize(tp->query_pronoun()) + " proclaims you fit for duty.", oblist, adverb);
    all2act(adverb + " examines", oblist, ", then straightens "
      + recipient->query_possessive() + " clothes here and there.\n"
      + capitalize(tp->query_pronoun()) + " proclaims "
      + recipient->query_objective() + " fit for duty.", adverb);
    return 1;
}

public int
uaclolthayr_emote(string arg)
{
    object *oblist, recipient, tp;
    string *how, adverb, tmp;

    // check for corpse

    tp = this_player();
    how = parse_adverb_with_space(arg, "zealously" , 0);
    adverb = how[1];


    if (!stringp(how[0]))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    oblist = parse_this(how[0], "[to] [at] [the] %o");

    if (!sizeof(oblist))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    recipient = oblist[0];

    if (living(recipient))
    {
	notify_fail("That person is not a corpse (yet).\n");
	return 0;
    }

    if(!(recipient->query_prop(CORPSE_S_RACE)))
    {
	notify_fail("That is not a corpse.\n");
	return 0;
    }

    actor("You" + adverb + " offer", oblist,
      " to Aclolthayr as a dedication to the glory of the Union.");
    all2act(adverb + " offers", oblist, " to Aclolthayr.", adverb);
    return 1;
}

public int
uaddress_emote(string arg)
{
    object *oblist, recipient, tp;
    string *how, adverb, tmp;
    string pos = this_player()->query_possessive();


    // check for weapon

    tp = this_player();
    how = parse_adverb_with_space(arg, "stoically" , 0);
    adverb = how[1];


    if (!stringp(how[0]))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    oblist = parse_this(how[0], "[to] [at] [the] %l");

    if (!sizeof(oblist))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    tmp = u_describe_weapons();
    if(!strlen(tmp))
    {
	notify_fail("You need to be wielding a weapon.\n");
	return 0;
    }

    recipient = oblist[0];

    actor("You" + adverb + " address", oblist, " with your " + tmp + ", secure in power and ready to fight.");
    target(adverb + " addresses you with "
      + pos + " " + tmp + ", secure in power and ready to fight.", oblist, adverb);
    all2act(adverb + " addresses", oblist, " with "
      + pos + " " + tmp + ", secure in power and ready to fight.", adverb);
    return 1;
}

public int
uadmire_emote(string arg)
{
    object *oblist, recipient, tp;
    string *how, adverb, tmp;

    // check for target's weapons

    tp = this_player();
    how = parse_adverb_with_space(arg, "breathlessly" , 0);
    adverb = how[1];


    if (!stringp(how[0]))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    oblist = parse_this(how[0], "[to] [at] [the] %l");

    if (!sizeof(oblist))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    if (sizeof(oblist) > 1)
    {
	notify_fail("You may only do that to a single target.\n");
	return 0;
    }

    recipient = oblist[0];

    tmp = u_describe_weapons(-1, 2, 0, W_ANYH, recipient);
    if(!strlen(tmp))
    {
	notify_fail("That person wields no weapons.\n");
	return 0;
    }

    actor("You" + adverb + " admire", oblist, "'s " + tmp + ".");
    target(adverb + " admires your " + tmp + ".", oblist, adverb);
    all2act(" admires", oblist, "'s " + tmp + adverb + ".", adverb);
    return 1;
}

public int
uadvise_emote(string arg)
{
    object *oblist, recipient, tp;
    string *how, adverb, tmp;
    string pos = this_player()->query_possessive();


    // true

    tp = this_player();
    how = parse_adverb_with_space(arg, "authoritatively" , 0);
    adverb = how[1];

    if (tmp = tp->query_prop(LIVE_M_MOUTH_BLOCKED))
    {
	if(stringp(tmp))
	    notify_fail(tmp + "\n");
	else
	    notify_fail("You cannot seem to use your mouth.\n");
	return 0;
    }


    if (!stringp(how[0]))
    {
	write("You speak" + adverb + ", advising everyone to desist.\n");
	all(" speaks" + adverb + ", advising everyone to desist.", adverb);
	return 1;
    }

    oblist = parse_this(how[0], "[to] [at] [the] %l");

    if (!sizeof(oblist))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }


    recipient = oblist[0];

    actor("You speak" + adverb + ", advising", oblist, " to desist at once or suffer your wrath.");
    targetbb(" speaks" + adverb + ", advising you to desist at once or suffer "
      + pos + " wrath.", oblist, adverb);
    all2actbb(" speaks" + adverb + ", advising", oblist, " to desist at once or suffer "
      + pos + " wrath.", adverb);


    // check if DIS is lower than mine
    if((recipient->query_skill(SS_DIS) < (tp->query_skill(SS_DIS) - random(15))) &&
      recipient->query_humanoid())
	recipient->command("$cringe");

    return 1;
}

public int
ualoof_emote(string arg)
{
    object *oblist, recipient, tp;
    string *how, adverb, tmp;

    // true

    tp = this_player();
    how = parse_adverb_with_space(arg, "quietly" , 0);
    adverb = how[1];


    if (!stringp(how[0]))
    {
	write("You stand" + adverb + " aloof from the others in the area.\n");
	allbb(" stands" + adverb + " aloof from the others in the area.", adverb);
	return 1;
    }

    oblist = parse_this(how[0], "[to] [at] [the] %l");

    if (!sizeof(oblist))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }


    recipient = oblist[0];

    actor("You stand" + adverb + " aloof from", oblist, ".");
    target(" stands" + adverb + " aloof from you.", oblist, adverb);
    all2act(" stands" + adverb + " aloof from", oblist, ".", adverb);
    return 1;
}

public int
uapprove_emote(string arg)
{
    object *oblist;
    string *how, adverb, tmp;
    string pos = this_player()->query_possessive();

    how = parse_adverb_with_space(arg, "approvingly" , 0);
    adverb = how[1];

    if (!stringp(how[0]))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    oblist = parse_live(how[0], "[to] [at] [the] %o");

    if (!sizeof(oblist))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    actor("You look" + adverb + " at", oblist, ", showing "+
      oblist[0]->query_objective() +" your appreciation of service "+
      "unto the protectorate of Sybarus.");
    all2actbb(" looks" + adverb + " at", oblist, ", showing "+
      oblist[0]->query_objective() + " "+ pos +
      " appreciation of service unto the protectorate of Sybarus.", adverb);
    targetbb(" looks" + adverb + " at you, showing you "+ pos +
      " appreciation of service unto the protectorate of Sybarus.",
      oblist, adverb);

    return 1;
}

public int
uassess_emote(string arg)
{
    object *oblist, recipient, tp;
    string *how, adverb, tmp;
    string pos = this_player()->query_possessive();


    // true

    tp = this_player();
    how = parse_adverb_with_space(arg, "slowly" , 0);
    adverb = how[1];


    if (!stringp(how[0]))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    oblist = parse_this(how[0], "[to] [at] [the] %l");

    if (!sizeof(oblist))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    if (sizeof(oblist) > 1)
    {
	notify_fail("You may only do that to a single target.\n");
	return 0;
    }

    recipient = oblist[0];

    actor("You snap your head around and study", oblist, adverb + " from head to toe, assesing every strength and weakness.");
    target(" snaps "
      + pos + " head around and study you" + adverb + " from head to toe, assesing you with a piercing gaze.", oblist, adverb);
    all2act(" snaps "
      + pos + " head around and study", oblist, adverb + " from head to toe, assesing "
      + recipient->query_objective() + " with a piercing gaze.", adverb);

    return 1;
}

public int
uassist_emote(string arg)
{
    object *oblist, recipient, tp;
    string *how, adverb, tmp;

    // join in attack, check for teammates attacking

    tp = this_player();
    how = parse_adverb_with_space(arg, "aggressively" , 0);
    adverb = how[1];

    if (tmp = tp->query_prop(LIVE_M_MOUTH_BLOCKED))
    {
	if(stringp(tmp))
	    notify_fail(tmp + "\n");
	else
	    notify_fail("You cannot seem to use your mouth.\n");
	return 0;
    }


    if (!stringp(how[0]))
    {
	// make sure we can assist
	if(!tp->command("$assist"))
	    return 0;

	write("You" + adverb + " snarl 'Death to the Infidels!' as you join the Nessu Amlis.\n");
	all(adverb + " snarls 'Death to the Infidels!' as "
	  + tp->query_pronoun() + " joins in the attack.", adverb);
	return 1;
    }

    notify_fail(capitalize(query_verb()) + " [how]?\n");
    return 0;
}

public int
uberate_emote(string arg)
{
    object *oblist, recipient, tp;
    string *how, adverb, tmp;

    // true

    tp = this_player();
    how = parse_adverb_with_space(arg, "irritably" , 0);
    adverb = how[1];

    if (tmp = tp->query_prop(LIVE_M_MOUTH_BLOCKED))
    {
	if(stringp(tmp))
	    notify_fail(tmp + "\n");
	else
	    notify_fail("You cannot seem to use your mouth.\n");
	return 0;
    }


    if (!stringp(how[0]))
    {
	write("You berate everyone" + adverb + " for their ignorance.\n");
	all(" berates everyone" + adverb + " for their ignorance.", adverb);
	return 1;
    }

    oblist = parse_this(how[0], "[to] [at] [the] %l");

    if (!sizeof(oblist))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    if (sizeof(oblist) > 1)
    {
	notify_fail("You may only do that to a single target.\n");
	return 0;
    }

    recipient = oblist[0];

    actor("You berate", oblist, adverb + " with a series of verbal assaults upon "
      + recipient->query_possessive() + " ignorance.");
    targetbb(" berates you" + adverb + " with a series of verbal assaults upon your ignorance.", oblist, adverb);
    all2actbb(" berates", oblist, adverb + " with a series of verbal assaults upon "
      + recipient->query_possessive() + " ignorance.", adverb);

    // check if DIS is lower than mine
    if((recipient->query_skill(SS_DIS) < (tp->query_skill(SS_DIS) - random(15))) &&
      recipient->query_humanoid())
	recipient->command("$blush");


    return 1;
}

public int
uboom_emote(string arg)
{
    object *oblist, recipient, tp;
    string *how, adverb, tmp;

    // true

    tp = this_player();
    how = parse_adverb_with_space(arg, "furiously" , 0);
    adverb = how[1];

    if (tmp = tp->query_prop(LIVE_M_MOUTH_BLOCKED))
    {
	if(stringp(tmp))
	    notify_fail(tmp + "\n");
	else
	    notify_fail("You cannot seem to use your mouth.\n");
	return 0;
    }


    if (!stringp(how[0]))
    {
	write("You" + adverb + " decree that all around are Sin'ur and an insult!\n");
	all(adverb + " decrees that all around "
	  + tp->query_objective() + " are Sin'ur.", adverb);
	return 1;
    }

    oblist = parse_this(how[0], "[to] [at] [the] %l");

    if (!sizeof(oblist))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    if (sizeof(oblist) > 1)
    {
	notify_fail("You may only do that to a single target.\n");
	return 0;
    }

    recipient = oblist[0];

    actor("You" + adverb + " decree that", oblist, " is a Sin'ur and an insult!");
    targetbb(adverb + " decrees that you are a Sin'ur.", oblist, adverb);
    all2actbb(adverb + " decrees that", oblist, " is a Sin'ur.", adverb);
    return 1;
}

public int
ubored_emote(string arg)
{
    object *oblist, recipient, tp;
    string *how, adverb, tmp;

    // true

    tp = this_player();
    how = parse_adverb_with_space(arg, "nonchalantly" , 0);
    adverb = how[1];


    if (!stringp(how[0]))
    {
	write("You" + adverb + " perform a slight gesture of boredom, indicating that you know all this already.\n");
	allbb(adverb + " performs a slight gesture of boredom, indicating that "
	  + tp->query_objective() + " knows all this already.", adverb);
	return 1;
    }

    oblist = parse_this(how[0], "[to] [at] [the] %l");

    if (!sizeof(oblist))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }


    recipient = oblist[0];

    actor("You" + adverb + " perform a slight gesture of boredom, indicating that you already know everything", oblist, " is saying.");
    target(adverb + " performs a slight gesture of boredom, indicating that "
      + tp->query_pronoun() + " already knows everything you are saying.", oblist, adverb);
    all2act(adverb + " performs a slight gesture of boredom, indicating that "
      + tp->query_pronoun() + " already knows everything", oblist, " is saying.", adverb);
    return 1;
}

public int
ubow_emote(string arg)
{
    object *oblist, recipient, tp;
    string *how, adverb, tmp;
    string pos = this_player()->query_possessive();


    // true

    tp = this_player();
    how = parse_adverb_with_space(arg, "deeply" , 0);
    adverb = how[1];


    if (!stringp(how[0]))
    {
	write("You bow" + adverb + " with a graceful flourish and steely gestures.\n");
	allbb(" bows" + adverb + " with a graceful flourish and steely gestures.", adverb);
	return 1;
    }

    oblist = parse_this(how[0], "[to] [at] [the] %l");

    if (!sizeof(oblist))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    if (sizeof(oblist) > 1)
    {
	notify_fail("You may only do that to a single target.\n");
	return 0;
    }

    recipient = oblist[0];

    actor("You bow" + adverb + " to", oblist, " with a graceful flourish and steely gestures, never taking your eyes from "
      + recipient->query_objective() + ".");
    target(" bows" + adverb + " to you with a graceful flourish and steely gestures, never taking "
      + pos + " eyes from you.", oblist, adverb);
    all2act(" bows" + adverb + " to", oblist, " with a graceful flourish and steely gestures, never taking "
      + pos + " eyes from "
      + recipient->query_objective() + ".", adverb);
    return 1;
}

public int
ubrighten_emote(string str)
{
    if (strlen(str)) {
	return notify_fail("Just ubrighten is enough.\n");
    } else {
	str = "";
    }

    object *cowl = filter(all_inventory(TP), &->id("cowl"));
    if (sizeof(cowl))
    {
	if (cowl[0]->query_worn())
	    str = " under the " + cowl[0]->short();
    }

    write("Your face brightens visibly" + str +
      " as you manage to make sense of all the "+
      "information you have gained.\n");

    allbb("'s face brightens visibly" + str + " after " +
      this_player()->query_pronoun() + 
      " silently contemplates something.", "visibly");

    return 1;
}

public int
ubrush_emote(string arg)
{
    object *oblist, recipient, tp;
    string *how, adverb, tmp;

    // true

    tp = this_player();
    how = parse_adverb_with_space(arg, "gently" , 0);
    adverb = how[1];


    if (!stringp(how[0]))
    {
	write("You take a moment to brush some barely visible dirt from your clothing.\n");
	allbb(" takes a moment to brush some barely visible dirt from "
	  + tp->query_possessive() + " clothing.", adverb);
	return 1;
    }

    oblist = parse_this(how[0], "[to] [at] [the] %l");

    if (!sizeof(oblist))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    if (sizeof(oblist) > 1)
    {
	notify_fail("You may only do that to a single target.\n");
	return 0;
    }

    recipient = oblist[0];

    actor("You take a moment to brush some barely visible dirt from", oblist, "'s clothing.");
    target(" takes a moment to brush some barely visible dirt from your clothing.", oblist, adverb);
    all2act(" takes a moment to brush some barely visible dirt from", oblist, "'s clothing.", adverb);
    return 1;
}

public int
ucall_emote(string arg)
{
    object *oblist, recipient, tp;
    string *how, adverb, tmp;

    // true

    tp = this_player();
    how = parse_adverb_with_space(arg, "expectantly" , 0);
    adverb = how[1];

    if (tmp = tp->query_prop(LIVE_M_MOUTH_BLOCKED))
    {
	if(stringp(tmp))
	    notify_fail(tmp + "\n");
	else
	    notify_fail("You cannot seem to use your mouth.\n");
	return 0;
    }


    if (!stringp(how[0]))
    {
	write("You call" + adverb + " for someone to answer the question.\n");
	allbb(" calls" + adverb + " for someone to answer the question.", adverb);
	return 1;
    }

    oblist = parse_this(how[0], "[to] [at] [the] %l");

    if (!sizeof(oblist))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    if (sizeof(oblist) > 1)
    {
	notify_fail("You may only do that to a single target.\n");
	return 0;
    }

    recipient = oblist[0];

    actor("You call" + adverb + " on", oblist, " to answer the next question.");
    target(" calls" + adverb + " on you to answer the next question.", oblist, adverb);
    all2act(" calls" + adverb + " on", oblist, " to answer the next question.", adverb);
    return 1;
}

public int
ucare_emote(string arg)
{
    object *oblist, recipient, tp;
    string *how, adverb, tmp;
    string pos = this_player()->query_possessive();


    // Check for weapon

    tp = this_player();
    how = parse_adverb_with_space(arg, "carefully" , 0);
    adverb = how[1];


    if (!stringp(how[0]))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    oblist = parse_this(how[0], "[to] [at] [the] %i");

    if (!sizeof(oblist))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }


    recipient = oblist[0];

    actor("You inspect", oblist, adverb + ", a look of concern on your face.");
    target(" inspects you" + adverb + ", a look of concern on "
      + pos + " face.", oblist, adverb);
    all2act(" inspects", oblist, adverb + ", a look of concern on "
      + pos + " face.", adverb);
    return 1;
}

public int
ucaress_emote(string arg)
{
    object *oblist, recipient, tp;
    string *how, adverb, tmp;
    string pos = this_player()->query_possessive();


    // check for weapon

    tp = this_player();
    how = parse_adverb_with_space(arg, "softly" , 0);
    adverb = how[1];


    if (!stringp(how[0]))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    oblist = parse_this(how[0], "[to] [at] [the] %i");

    if (!sizeof(oblist))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    if (sizeof(oblist) > 1)
    {
	notify_fail("You may only do that to a single target.\n");
	return 0;
    }

    recipient = oblist[0];

    if (living(recipient))
    {
	notify_fail("You cannot do that to a living being.\n");
	return 0;
    }

    if(!(recipient->check_weapon()))
    {
	notify_fail("That is not a weapon.\n");
	return 0;
    }

    actor("You" + adverb + " caress", oblist, ", sensing the powers hidden within.");
    target(adverb + " caresses you, a mysterious gleam appearing in "
      + pos + " black eyes.", oblist, adverb);
    all2act(adverb + " caresses", oblist, ", a mysterious gleam appearing in "
      + pos + " black eyes.", adverb);
    return 1;
}

public int
ucasesort_emote(string arg)
{
    object *oblist, recipient, tp;
    string *how, adverb, tmp;

    // check for case around

    tp = this_player();
    how = parse_adverb_with_space(arg, "concertedly" , 0);
    adverb = how[1];


    if (!stringp(how[0]))
    {
	if(file_name(ENV(tp)) != (ROOM + "arsenal"))
	{
	    notify_fail("You can only do that in the arsenal.\n");
	    return 0;
	}

	write("You" + adverb + " examine the case, and start to sort out the dirty and battle scarred items.\n");
	all(adverb + " examines the case, and starts to sort out the dirty and battle scarred items.", adverb);
	return 1;
    }

    notify_fail(capitalize(query_verb()) + " [how]?\n");
    return 0;
}

public int
uchastise_emote(string arg)
{
    object *oblist, recipient, tp;
    string *how, adverb, tmp;

    // true

    tp = this_player();
    how = parse_adverb_with_space(arg, "disapprovingly" , 0);
    adverb = how[1];

    if (tmp = tp->query_prop(LIVE_M_MOUTH_BLOCKED))
    {
	if(stringp(tmp))
	    notify_fail(tmp + "\n");
	else
	    notify_fail("You cannot seem to use your mouth.\n");
	return 0;
    }


    if (!stringp(how[0]))
    {
	write("You chastise everyone present" + adverb + " for their misbehaviour.\n");
	all(" chastises everyone present" + adverb + " for their misbehaviour.", adverb);
	return 1;
    }

    oblist = parse_this(how[0], "[to] [at] [the] %l");

    if (!sizeof(oblist))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    if (sizeof(oblist) > 1)
    {
	notify_fail("You may only do that to a single target.\n");
	return 0;
    }

    recipient = oblist[0];

    actor("You chastise", oblist, adverb + " for "
      + recipient->query_possessive() + " misbehaviour.");
    targetbb(" chastises you" + adverb + " for your misbehaviour.", oblist, adverb);
    all2actbb(" chastises", oblist, adverb + " for "
      + recipient->query_possessive() + " misbehaviour.", adverb);

    return 1;
}

public int
ucheer_emote(string arg)
{
    object *oblist, recipient, tp;
    string *how, adverb, tmp;

    // true

    tp = this_player();
    how = parse_adverb_with_space(arg, "heartily" , 0);
    adverb = how[1];

    if (tmp = tp->query_prop(LIVE_M_MOUTH_BLOCKED))
    {
	if(stringp(tmp))
	    notify_fail(tmp + "\n");
	else
	    notify_fail("You cannot seem to use your mouth.\n");
	return 0;
    }


    if (!stringp(how[0]))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    oblist = parse_this(how[0], "[to] [at] [the] %l");

    if (!sizeof(oblist))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    if (sizeof(oblist) > 1)
    {
	notify_fail("You may only do that to a single target.\n");
	return 0;
    }

    recipient = oblist[0];

    actor("You" + adverb + " applaud the brilliance shown by", oblist, ".");
    targetbb(adverb + " applauds the brilliance shown by you.", oblist, adverb);
    all2actbb(adverb + " applauds the brilliance shown by", oblist, ".", adverb);
    return 1;
}

public int
uchoose_emote(string arg)
{
    object *oblist, recipient, tp;
    string *how, adverb, tmp;

    // true

    tp = this_player();
    how = parse_adverb_with_space(arg, "carefully" , 0);
    adverb = how[1];

    if (tmp = tp->query_prop(LIVE_M_MOUTH_BLOCKED))
    {
	if(stringp(tmp))
	    notify_fail(tmp + "\n");
	else
	    notify_fail("You cannot seem to use your mouth.\n");
	return 0;
    }


    if (!stringp(how[0]))
    {
	write("You decide to choose your words very" + adverb + " before responding.\n");
	all(" appears to choose "
	  + tp->query_possessive() + " words very" + adverb + " before responding.", adverb);
	return 1;
    }

    notify_fail(capitalize(query_verb()) + " [how]?\n");
    return 0;
}

public int
ucompell_emote(string arg)
{
    object *oblist, recipient, tp;
    string *how, adverb, tmp;
    string pos = this_player()->query_possessive();


    // true

    tp = this_player();
    how = parse_adverb_with_space(arg, "compellingly" , 0);
    adverb = how[1];


    if (!stringp(how[0]))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    oblist = parse_this(how[0], "[to] [at] [the] %l");

    if (!sizeof(oblist))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    if (sizeof(oblist) > 1)
    {
	notify_fail("You may only do that to a single target.\n");
	return 0;
    }

    recipient = oblist[0];

    actor("You" + adverb + " force", oblist, " to meet your gaze so "
      + recipient->query_pronoun() + " understands how serious you are.");
    target(adverb + " forces you to meet "
      + pos + " gaze. Dark flames flickering in "
      + pos + " eyes indicate that "
      + tp->query_pronoun() + " is serious.", oblist, adverb);
    all2act(" meets", oblist, "'s eyes" + adverb + ".", adverb);
    return 1;
}

public int
ucommit_emote(string arg)
{
    object *oblist, recipient, tp;
    string *how, adverb, tmp;
    string pos = this_player()->query_possessive();


    // true

    tp = this_player();
    how = parse_adverb_with_space(arg, "carefully" , 0);
    adverb = how[1];


    if (!stringp(how[0]))
    {
	write("You look" + adverb + " around at your surroundings, committing them to your memory forever.\n");
	allbb(" looks" + adverb + " around at "
	  + pos + " surroundings, committing them to "
	  + pos + " memory forever.", adverb);
	return 1;
    }

    oblist = parse_this(how[0], "[to] [at] [the] %i");

    if (!sizeof(oblist))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    if (sizeof(oblist) > 1)
    {
	notify_fail("You may only do that to a single target.\n");
	return 0;
    }

    recipient = oblist[0];

    actor("You look" + adverb + " at", oblist, ", committing "
      + recipient->query_possessive() + " features to your memory forever.");
    target(" looks" + adverb + " at you, committing your features to "
      + pos + " memory forever.", oblist, adverb);
    all2act(" looks" + adverb + " at", oblist, ", committing "
      + recipient->query_possessive() + " features to "
      + pos + " memory forever.", adverb);
    return 1;
}

public int
uconfident_emote(string arg)
{
    object *oblist, recipient, tp;
    string *how, adverb, tmp;

    // check for sword

    tp = this_player();
    how = parse_adverb_with_space(arg, "slightly" , 0);
    adverb = how[1];

    tmp = u_describe_weapons(W_SWORD);
    if(!strlen(tmp))
    {
	notify_fail("You need to be wielding a sword.\n");
	return 0;
    }

    if (!stringp(how[0]))
    {
	write("You let the tip of your " + tmp
	  + " rest against the ground and lean" + adverb
	  + " against its pommel while glancing about, confident "
	  + "that you will prevail.\n");
	allbb(" lets the tip of "+ tp->query_possessive() +" "
	  + tmp + " rest against the "
	  + "ground and leans" + adverb + " against its pommel with "
	  + "a confident look on "
	  + tp->query_possessive() + " face.", adverb);
	return 1;
    }

    oblist = parse_this(how[0], "[to] [at] [the] %i");

    if (!sizeof(oblist))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }


    recipient = oblist[0];

    actor("You let the tip of your " + tmp + " rest against the "
      + "ground and lean" + adverb + " against its pommel while "
      + "glancing about, confident that you will prevail "
      + "against", oblist, ".");
    target(" lets the tip of " + tp->query_possessive() + " "
      + tmp + " rest against the "
      + "ground and leans" + adverb + " against its pommel with "
      + "a confident stare at you.", oblist, adverb);
    all2act(" lets the tip of " + tp->query_possessive() + " "
      + tmp + " rest against the "
      + "ground and leans" + adverb + " against its pommel with "
      + "a confident stare at", oblist, ".", adverb);
    return 1;
}

public int
ucongrat_emote(string arg)
{
    object *oblist, recipient, tp;
    string *how, adverb, tmp;

    // true

    tp = this_player();
    how = parse_adverb_with_space(arg, "cheerfully" , 0);
    adverb = how[1];

    if (tmp = tp->query_prop(LIVE_M_MOUTH_BLOCKED))
    {
	if(stringp(tmp))
	    notify_fail(tmp + "\n");
	else
	    notify_fail("You cannot seem to use your mouth.\n");
	return 0;
    }


    if (!stringp(how[0]))
    {
	write("You" + adverb + " congratulate everyone with the word 'Gratios'.\n");
	all(adverb + " congratulates everyone with the word 'Gratios'.", adverb);
	return 1;
    }

    oblist = parse_this(how[0], "[to] [at] [the] %l");

    if (!sizeof(oblist))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }


    recipient = oblist[0];

    actor("You" + adverb + " congratulate", oblist, " with the word 'Gratios'.");
    targetbb(adverb + " congratulates you with the word 'Gratios'.", oblist, adverb);
    all2actbb(adverb + " congratulates", oblist, " with the word 'Gratios'.", adverb);
    return 1;
}

public int
uconsider_emote(string arg)
{
    object *oblist, recipient, tp;
    string *how, adverb, tmp;

    // make target shiver, DIS

    tp = this_player();
    how = parse_adverb_with_space(arg, "solemnly" , 0);
    adverb = how[1];


    if (!stringp(how[0]))
    {
	write("You" + adverb + " consider this weighty subject.\n");
	allbb(adverb + " considers something of great weight.", adverb);
	return 1;
    }

    oblist = parse_this(how[0], "[to] [at] [the] %l");

    if (!sizeof(oblist))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }


    recipient = oblist[0];

    actor("You" + adverb + " consider a suitable course of action regarding", oblist, ".");
    target(" stares" + adverb + " at you and seems to be grimly considering something.", oblist, adverb);
    all2act(" stares" + adverb + " at", oblist, " and seems to be grimly considering something.", adverb);
    return 1;
}

public int
ucontempt_emote(string arg)
{
    object *oblist, recipient, tp;
    string *how, adverb, tmp;

    // true

    tp = this_player();
    how = parse_adverb_with_space(arg, "fluently", 0);
    adverb = how[1];

    if (tmp = tp->query_prop(LIVE_M_MOUTH_BLOCKED))
    {
	if(stringp(tmp))
	    notify_fail(tmp + "\n");
	else
	    notify_fail("You cannot seem to use your mouth.\n");
	return 0;
    }


    if (!stringp(how[0]))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    oblist = parse_this(how[0], "[to] [at] [the] %l");

    if (!sizeof(oblist))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    if (sizeof(oblist) > 1)
    {
	notify_fail("You may only do that to a single target.\n");
	return 0;
    }

    recipient = oblist[0];

    actor("You sneer contemptously at", oblist, " while cursing "
      + recipient->query_objective() + adverb + " in the name of "
      + "Jazur.");
    targetbb(" sneers contemptously at you while cursing you"
      + adverb + " in the name of Jazur.", oblist, adverb);
    all2actbb(" sneers contemptously at", oblist, " while cursing "
      + recipient->query_objective() + adverb + " in the name of "
      + "Jazur.", adverb);
    return 1;
}

public int
ucorpse_emote(string arg)
{
    object *oblist, recipient, tp;
    string *how, adverb, tmp;

    // check for corpse

    tp = this_player();
    how = parse_adverb_with_space(arg, "disappointedly" , 0);
    adverb = how[1];

    if (tmp = tp->query_prop(LIVE_M_MOUTH_BLOCKED))
    {
	if(stringp(tmp))
	    notify_fail(tmp + "\n");
	else
	    notify_fail("You cannot seem to use your mouth.\n");
	return 0;
    }


    if (!stringp(how[0]))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    oblist = parse_this(how[0], "[to] [at] [the] %i");

    if (!sizeof(oblist))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    if (sizeof(oblist) > 1)
    {
	notify_fail("You may only do that to a single target.\n");
	return 0;
    }

    recipient = oblist[0];

    if (living(recipient))
    {
	notify_fail("You cannot do that to a living being.\n");
	return 0;
    }

    if(!(recipient->query_prop(CORPSE_S_RACE)))
    {
	notify_fail("That is not a corpse.\n");
	return 0;
    }

    actor("You kick", oblist, adverb + ", contemplating the information "
      + "that was lost by this unfortunate death.");
    target(" kicks you" + adverb + ", contemplating the information that "
      + "was lost by this unfortunate death.", oblist, adverb);
    all2act(" kicks", oblist, adverb + ", obviously engraged with "
      + "its premature death.", adverb);
    return 1;
}

public int
ucount_emote(string arg)
{
    object *oblist, recipient, tp;
    string *how, adverb, tmp;

    // true

    tp = this_player();
    how = parse_adverb_with_space(arg, "thoughtfully" , 0);
    adverb = how[1];


    if (!stringp(how[0]))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    oblist = parse_this(how[0], "[to] [at] [the] %l");

    if (!sizeof(oblist))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    if (sizeof(oblist) > 1)
    {
	notify_fail("You may only do that to a single target.\n");
	return 0;
    }

    recipient = oblist[0];

    actor("You" + adverb + " stare at", oblist, " and count in your mind how many daggers it will take for the kill.");
    target(" stares at you and seems to calculate something.\nA disconcerting smile spreads across "
      + tp->query_possessive() + " face.", oblist, adverb);
    all2act(" stares at", oblist, " and seems to calculate something.\nA disconcerting smile spreads across "
      + tp->query_possessive() + " face.", adverb);
    return 1;
}

public int
ucrime_emote(string arg)
{
    object *oblist, recipient, tp;
    string *how, adverb, tmp;
    string *killer;
    mixed weapons;

    // true

    tp = this_player();
    how = parse_adverb_with_space(arg, "carefully" , 0);
    adverb = how[1];


    if (!stringp(how[0]))
    {
	write("You look" + adverb + " around for evidence of the crime that was perpetrated here.\n");
	allbb(" looks" + adverb + " around for evidence of the crime that was perpetrated here.", adverb);
	return 1;
    }

    oblist = parse_this(how[0], "[to] [at] [the] %i");

    if (!sizeof(oblist))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    if (sizeof(oblist) > 1)
    {
	notify_fail("You may only do that to a single target.\n");
	return 0;
    }

    recipient = oblist[0];

    if(living(recipient))
    {
	actor("You look" + adverb + " at", oblist, " for signs of guilt.");
	target(" looks" + adverb + " at you for signs of guilt.", oblist, adverb);
	all2act(" looks" + adverb + " at", oblist, " for signs of guilt.", adverb);
    }
    else
    {
	actor("You look" + adverb + " at", oblist, " for evidence of the crime.");
	all2act(" looks" + adverb + " at", oblist, " for evidence of the crime.", adverb);

	if(killer = recipient->query_prop(CORPSE_AS_KILLER))
	{
	    // If the player is in the game, and is wielding weapons,
	    // get an array of weapon types they are carrying.
	    // Of course, the killer may have been wielding other
	    // weapons when they killed the corpse, but this is as
	    // good as we can do. 
	    weapons = find_player(killer[0])->query_weapon(-1)->weapon_type();
	    if(sizeof(weapons) > 0)
		write("It looks like it was killed with "
		  + LANG_ADDART(COMPOSITE_WORDS(weapons)) + ".\n");
	    else
		write("You cannot determine what weapons were used "
		  + "to kill the corpse.\n");
	}

    }

    return 1;
}

public int
ucry_emote(string arg)
{
    object *oblist, recipient, tp;
    string *how, adverb, tmp;

    // true

    tp = this_player();
    how = parse_adverb_with_space(arg, "loudly" , 0);
    adverb = how[1];

    if (tmp = tp->query_prop(LIVE_M_MOUTH_BLOCKED))
    {
	if(stringp(tmp))
	    notify_fail(tmp + "\n");
	else
	    notify_fail("You cannot seem to use your mouth.\n");
	return 0;
    }


    if (!stringp(how[0]))
    {
	write("You cry out" + adverb + " in intense pain.\n");
	all(" cries out" + adverb + " in intense pain.", adverb);
	return 1;
    }

    oblist = parse_this(how[0], "[to] [at] [the] %l");

    if (!sizeof(oblist))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }


    recipient = oblist[0];

    actor("You cry out" + adverb + " to", oblist, " for aid.");
    targetbb(" cries out" + adverb + " to you for aid.", oblist, adverb);
    all2actbb(" cries out" + adverb + " to", oblist, " for aid.", adverb);
    return 1;
}

public int
ucurl_emote(string arg)
{
    object *oblist, recipient, tp;
    string *how, adverb, tmp;
    string pos = this_player()->query_possessive();


    // true

    tp = this_player();
    how = parse_adverb_with_space(arg, "disdainfully" , 0);
    adverb = how[1];


    if (!stringp(how[0]))
    {
	write("You curl your upper lip" + adverb + ".\n");
	allbb(" curls "
	  + pos + " upper lip" + adverb + ".", adverb);
	return 1;
    }

    oblist = parse_this(how[0], "[to] [at] [the] %i");

    if (!sizeof(oblist))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }


    recipient = oblist[0];

    actor("You curl your upper lip" + adverb + " at", oblist, ".");
    target(" curls "
      + pos + " upper lip" + adverb + " at you.", oblist, adverb);
    all2act(" curls "
      + pos + " upper lip" + adverb + " at", oblist, ".", adverb);
    return 1;
}

public int
ucurtsey_emote(string arg)
{
    object *oblist, recipient, tp;
    string *how, adverb, tmp;

    // true

    tp = this_player();
    how = parse_adverb_with_space(arg, "fluidly" , 0);
    adverb = how[1];


    if (!stringp(how[0]))
    {
	write("You curtsey" + adverb + " with grace and dignity.\n");
	allbb(" curtseys" + adverb + " with grace and dignity.", adverb);
	return 1;
    }

    oblist = parse_this(how[0], "[to] [at] [the] %l");

    if (!sizeof(oblist))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }


    recipient = oblist[0];

    actor("You curtsey" + adverb + " before", oblist, " with grace and dignity.");
    target(" curtseys" + adverb + " before you with grace and dignity.", oblist, adverb);
    all2act(" curtseys" + adverb + " before", oblist, " with grace and dignity.", adverb);
    return 1;
}

public int
udeclare_emote(string arg)
{
    object *oblist, recipient, tp;
    string *how, adverb, tmp;

    // check for weapon, slam fist is there is none

    tp = this_player();
    how = parse_adverb_with_space(arg, "fiercely" , 0);
    adverb = how[1];

    if (tmp = tp->query_prop(LIVE_M_MOUTH_BLOCKED))
    {
	if(stringp(tmp))
	    notify_fail(tmp + "\n");
	else
	    notify_fail("You cannot seem to use your mouth.\n");
	return 0;
    }

    tmp = u_describe_weapons(-1, 1);
    if(!strlen(tmp))
    {
	notify_fail("You need to be wielding a weapon.\n");
	return 0;
    }

    if (!stringp(how[0]))
    {
	write("You wrap your hand around your " + tmp + " while" + adverb
	  + " declaring: I am prepared to die for Jazur and Sybarus!\n");
	all(" wraps "
	  + tp->query_possessive() + " hand around "
	  + tp->query_possessive() + " " + tmp + " while" + adverb
	  + " declaring: I am prepared to die for Jazur and Sybarus!", adverb);
	return 1;
    }

    notify_fail(capitalize(query_verb()) + " [how]?\n");
    return 0;
}

public int
udefend_emote(string arg)
{
    object *oblist, recipient, tp;
    string *how, adverb, tmp;

    // true

    tp = this_player();
    how = parse_adverb_with_space(arg, "nobly" , 0);
    adverb = how[1];


    if (!stringp(how[0]))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    oblist = parse_this(how[0], "[to] [at] [the] %i");

    if (!sizeof(oblist))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    if (sizeof(oblist) > 1)
    {
	notify_fail("You may only do that to a single target.\n");
	return 0;
    }

    recipient = oblist[0];

    actor("You stand before", oblist, ", intent on preventing harm from coming to "
      + recipient->query_objective() + ".");
    target(" stands before you, intent on preventing harm from coming to you.", oblist, adverb);
    all2act(" stands before", oblist, ", intent on preventing harm from coming to "
      + recipient->query_objective() + ".", adverb);
    return 1;
}

public int
udefer_emote(string arg)
{
    object *oblist, recipient, tp;
    string *how, adverb, tmp;

    // true

    tp = this_player();
    how = parse_adverb_with_space(arg, "humbly" , 0);
    adverb = how[1];

    if (tmp = tp->query_prop(LIVE_M_MOUTH_BLOCKED))
    {
	if(stringp(tmp))
	    notify_fail(tmp + "\n");
	else
	    notify_fail("You cannot seem to use your mouth.\n");
	return 0;
    }


    if (!stringp(how[0]))
    {
	write("You" + adverb + " defer.\n");
	allbb(adverb + " defers.", adverb);
	return 1;
    }

    oblist = parse_this(how[0], "[to] [at] [the] %l");

    if (!sizeof(oblist))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }


    recipient = oblist[0];

    actor("You" + adverb + " defer to", oblist, ".");
    target(adverb + " defers to you.", oblist, adverb);
    all2act(adverb + " defers to", oblist, ".", adverb);
    return 1;
}

public int
udisapprove_emote(string arg)
{
    object *oblist, recipient, tp;
    string *how, adverb, tmp;

    // true

    tp = this_player();
    how = parse_adverb_with_space(arg, "coldly" , 0);
    adverb = how[1];


    if (!stringp(how[0]))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    oblist = parse_this(how[0], "[to] [at] [the] %l");

    if (!sizeof(oblist))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    if (sizeof(oblist) > 1)
    {
	notify_fail("You may only do that to a single target.\n");
	return 0;
    }

    recipient = oblist[0];

    actor("You look" + adverb + " at", oblist, ", your mouth set in thin, "+
      "disapproving lines.");
    all2act(" looks" + adverb + " at", oblist, ", " 
      + tp->query_possessive() + " mouth set in thin, "+
      "disapproving lines.", adverb);
    target(" looks" + adverb + " at you, "+ tp->query_possessive() + 
      " mouth set in thin, disapproving lines.", oblist, adverb);
    return 1;
}

public int
udisbelief_emote(string arg)
{
    object *oblist, recipient, tp;
    string *how, adverb, tmp;
    string pos = this_player()->query_possessive();


    // true

    tp = this_player();
    how = parse_adverb_with_space(arg, "dramatically" , 0);
    adverb = how[1];


    if (!stringp(how[0]))
    {
	write("You" + adverb + " slap your hand over your eyes and "+
	  "forehead in complete disbelief.\n");
	allbb(adverb + " slaps "
	  + pos + " hand over "
	  + pos + " eyes and forehead in complete disbelief.", adverb);
	return 1;
    }

    notify_fail(capitalize(query_verb()) + " [how]?\n");
    return 0;
}

public int
udiscern_emote(string arg)
{
    object *oblist, recipient, tp;
    string *how, adverb, tmp;

    // true

    tp = this_player();
    how = parse_adverb_with_space(arg, "astutely" , 0);
    adverb = how[1];

    if (!stringp(how[0]))
    {
	write("You" + adverb + " attempt to discern the deeper meanings implied here.\n");
	allbb(adverb + " discerns the deeper meanings implied here.", adverb);
	return 1;
    }

    oblist = parse_this(how[0], "[to] [at] [the] %l");

    if (!sizeof(oblist))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    recipient = oblist[0];

    actor("You" + adverb + " discern the deeper meanings implied by", oblist, ".");
    target(adverb + " discerns the deeper meanings implied by you.", oblist, adverb);
    all2act(adverb + " discerns the deeper meanings implied by", oblist, ".", adverb);
    return 1;
}

public int
udisdain_emote(string arg)
{
    object *oblist, recipient, tp;
    string *how, adverb, tmp;

    // true

    tp = this_player();
    how = parse_adverb_with_space(arg, "pointedly" , 0);
    adverb = how[1];

    if (!stringp(how[0]))
    {
	write("You look"+ adverb +" around you with an expression of "+
	  "utter disdain upon your face.\n");
	allbb(" looks"+ adverb +" around with an expression of utter "+
	  "disdain upon "+ tp->query_possessive() +" face.", adverb);
	return 1;
    }

    oblist = parse_this(how[0], "[to] [at] [the] %l");

    if (!sizeof(oblist))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    recipient = oblist[0];
    actor("You look" + adverb + " at", oblist, ", an expression of "+
      "utter disdain upon your face.");
    target(" looks" + adverb + " at you, an expression of "+
      "utter disdain upon "+ tp->query_possessive() +" face.", 
      oblist, adverb);
    all2act(adverb + " looks at", oblist, ", an "+
      "expression of utter disdain upon "+ tp->query_possessive() +
      " face.", adverb);
    return 1;
}

