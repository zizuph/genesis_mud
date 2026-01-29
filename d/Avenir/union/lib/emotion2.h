/* More emotions for the Union (included by emotions.h) */
/* Recoded and cleaned up by Lucius: June 2007.         */

/* usstudy -> incorported mentor "ustudy" code and removed that
 * from the mentor sphere soul. No long restricted to novices.
 * Requires the virtue_desc() function from ability.h, so this
 * file must be included after that one in occ_soul.c
 *
 *    --= Lucius, Nov 2007
 */

/* titles for some emotions   */
#include "titles.h"

public int
pain(string what)
{
    object troom;

    if (!(troom = environment(TP)))
	return 0;

    foreach(object where : FIND_NEIGHBOURS(troom, 2))
    {
	tell_room(where, "@@cry_name:"+ file_name(this_object()) +
	  "@@ out in agony and pain.\n", TP);
    }

    write("You cry out in agony and pain.\n");
    SOULDESC("crying out in anguish");
    return 1;
}

public int
patient(string str)
{
    str = check_adverb_with_space(str, "calmly");

    if (str == NO_ADVERB_WITH_SPACE)
    {
	notify_fail("Fold your hand [how]?\n");
	return 0;
    }

    write("You fold your hands"+ str +" in front of you "+
      "and wait patiently.\n");
    allbb(" folds "+ HIS(TP) +" hands in front of "+ HIM(TP) +
      " and waits"+ str +".");

    return 1;
}

public int
peer(string str)
{
    string *how;
    object *oblist;

    how = parse_adverb_with_space(str, "intently", 0);

    if (!strlen(how[0]))
    {
	write("You peer"+ how[1] +" around.\n");
	allbb(" peers"+ how[1] +" around.");

	SOULDESC("peering"+ how[1]);
	return 1;
    }

    oblist = parse_this(how[0], "[at] [the] %i");

    if (!sizeof(oblist))
    {
	notify_fail("Peer [how] at whom?\n");
	return 0;
    }

    actor("You peer"+ how[1] +" at", oblist);
    all2actbb(" peers"+ how[1] +" at", oblist);
    targetbb(" peers"+ how[1] +" at you.", oblist);

    SOULDESC("peering"+ how[1]);
    return 1;
}

private static string *r_greets = ({
  "Quansu" , "Emait", "Sirli", "Intios",
});

public int
respect(string str)
{
    object who, *oblist;
    string msg, greeting = one_of_list(r_greets);

    if (!strlen(str) || (str == "all"))
    {
	write("You nod your head respectfully to everyone.\n");
	allbb(" nods "+ HIS(TP) +" head respectfully to everyone.\n");

	SOULDESC("looking respectful");
	return 1;
    }

    if (sizeof(oblist = parse_this(str, "[the] %l")) != 1)
	return notify_fail("Respect whom?\n");

    who = oblist[0];

    if (IS_GMASTER(who))
    {
	msg = greeting +", Master of the Union!";

	actor("You bow solemnly before", oblist, " and speak: "+ msg);
	all2act(" bows solemnly before", oblist, " and speaks: "+ msg);
	target(" bows solemnly before you and speaks: "+ msg, oblist);
	return 1;
    }

    if (who->query_wiz_level())
    {
	if (who->query_gender() == G_FEMALE)
	    msg = greeting +", Fair Wizardess!";
	else
	    msg = greeting +", Noble Wizard!";

	actor("You bow respectfully before", oblist, " and speak: "+ msg);
	all2act(" bows respectfully before", oblist, " and speaks: "+ msg);
	target(" bows respectfully before you and speaks: "+ msg, oblist);
	return 1;
    }

    if (!IS_MEMBER(who))
    {
	if (ENEMY(who))
	{
	    write("Enemies of the Union deserve no respect.\n");
	    return 1;
	}

	TP->emote_adjust_union_virtue(US_PRIDE, 4);

	if (FRIEND(who))
	{
	    msg = greeting +", Friend of the Union!";

	    actor("You bow gracefully before", oblist,
	      " and speak: "+ msg);
	    all2act(" bows gracefully before", oblist,
	      " and speaks: "+ msg);
	    target(" bows gracefully before you and speaks: "+
	      msg, oblist);

	    return 1;
	}

	if (wildmatch("/d/Avenir/union/room*", file_name(ENV(TP))))
	{
	    msg = greeting +", and welcome to these great Halls of Shadow.";

	    actor("You bow deeply before", oblist, " and speak: "+ msg);
	    all2act(" bows deeply before", oblist, " and speaks: "+ msg);
	    target(" bows deeply before you and speaks: "+ msg, oblist);

	    return 1;
	}

	if (TP->query_met(who))
	    msg = greeting +", " + who->query_name() + ".";
	else
	    msg = greeting +", " + who->query_race_name() + ".";

	actor("You bow slightly before", oblist, " and speak: "+ msg);
	all2act(" bows slightly before", oblist, " and speaks: "+ msg);
	target(" bows slightly before you and speaks: "+ msg, oblist);

	return 1;
    }

    /* Union members know each other */
    TP->add_introduced(who->query_real_name());
    who->add_introduced(TP->query_real_name());

    if (U_IS_PUNISHED(who, U_PUNISHED_TITLE))
    {
	msg = greeting +", "+ BAD_TITLE +". "+
	    "May you regain Jazur's grace soon.";

	actor("You glare darkly at", oblist, " and speak: "+ msg);
	all2act(" glares darkly at", oblist, " and speaks: "+ msg);
	target(" glares darkly at you and speaks: "+ msg, oblist);

	return 1;
    }

    if (U_IS_PUNISHED(who, U_PUNISHED_DECAY))
    {
	msg = greeting +", "+ BAD_TITLE +". "+
	    "May you regain Jazur's grace soon.";

	actor("You incline your head toward", oblist, " and speak: "+ msg);
	all2act(" nods briefly to", oblist, " and speaks: "+ msg);
	target(" nods briefly to you and speaks: "+ msg, oblist);

	return 1;
    }

    if (U_IS_PUNISHED(who, U_REWARD_TITLE))
    {
	msg = greeting +", "+ GOOD_TITLE +".";

	actor("You bow to", oblist, " and say with genuine "+
	  "admiration: "+ msg);
	all2act(" bows to", oblist, " and speaks with genuine "+
	  "admiration: "+ msg);
	target(" bows to you and speaks with genuine "+
	  "admiration: "+ msg, oblist);

	return 1;
    }

    if (IS_TORNU(who))
    {
	msg = greeting +", "+ GURU_TITLE +".";

	actor("You bow respectfully to", oblist, " and speak: "+ msg);
	all2act(" bows respectfully before", oblist, " and speaks: "+ msg);
	target(" bows respectfully to you and speaks: "+ msg, oblist);

	return 1;
    }

    msg = greeting +", "+ who->query_guild_title_occ() +".";

    actor("You bow briefly before", oblist, " and speak: "+ msg);
    all2act(" bows briefly before", oblist, " and speaks: "+ msg);
    target(" bows briefly before you and speaks: "+ msg, oblist);

    return 1;
}

public int
scorn(string str)
{
    object *oblist, who;

    oblist = parse_live(str, "[the] %o");

    if (!sizeof(oblist))
    {
	notify_fail("Look down on whom?\n");
	return 0;
    }

    who = oblist[0];

    if ((who->query_prop(CONT_I_HEIGHT) > TP->query_prop(CONT_I_HEIGHT)) ||
	who->id("giant") || who->id("dragon") || who->id("troll"))
    {
	TP->emote_adjust_union_virtue(US_PRIDE, -2);

	actor("You try to look down on", oblist, ", even though "+
	  who->query_pronoun() +" is taller than you.");
	all2actbb(" looks foolish trying to look down on", oblist);
	targetbb(" tries to look down on you, even though "+ HE(TP) +
	  " is shorter than you.", oblist);

	return 1;
    }

    actor("You look down on", oblist);
    all2actbb(" looks down on", oblist);
    targetbb(" looks down at you, making you feel insignificant.", oblist);

    TP->emote_adjust_union_virtue(US_PRIDE, 2);
    return 1;
}

private static string *def_ways = ({
  "reticently", "faintly", "gently", "compellingly",
  "darkly", "graciously", "distantly", "vaguely",
  "tautly", "fleetingly", "reservedly",
});

public int
smile(string str)
{
    string *how;
    object *oblist;

    how = parse_adverb_with_space(str, one_of_list(def_ways), 0);

    if (!stringp(how[0]))
    {
	write("You smile"+ how[1] +".\n");
	allbb(" smiles"+ how[1] +".", how[1]);

	SOULDESC("smiling"+ how[1]);
	return 1;
    }

    oblist = parse_this(how[0], "[at] [the] %l");

    if (!sizeof(oblist))
    {
	notify_fail("Smile [how] at whom?\n");
	return 0;
    }

    actor("You smile"+ how[1] +" at", oblist);
    all2actbb(" smiles"+ how[1] +" at", oblist, 0, how[1]);
    targetbb(" smiles"+ how[1] +" at you.", oblist, how[1]);

    SOULDESC("smiling"+ how[1]);
    return 1;
}

public int
spin(string str)
{
    object *oblist, what;

    if (!strlen(str))
    {
	notify_fail("Spin what?\n");
	return 0;
    }

    oblist = all_inventory(TP);

    if (!parse_command(str, oblist, "[my] [the] %o", what))
    {
	notify_fail("Spin what?\n");
	return 0;
    }

    if (what->query_wt() != W_KNIFE)
    {
	notify_fail("You can only do that with a knife or dagger.\n");
	return 0;
    }

    if (random(DEX(TP)) < 15)
    {
	write("You try to spin your "+ what->short(TP) +
	  " on your fingertip, but end up dropping it on the ground.\n");
	allbb(" tries to spin "+ HIS(TP) +" "+ what->short() +" on "+ HIS(TP) +
	  " fingertip, but drops it on the ground.");

	what->move(ENV(TP));
	TP->emote_adjust_union_virtue(US_GRACE, -4);
	return 1;
    }

    write("You spin your "+ what->short(TP) +
      " nimbly on the tip of your finger.\n");
    allbb(" spins "+ HIS(TP) +" "+ what->short() +
      " nimbly on the tip of "+ HIS(TP) +" finger.");

    TP->emote_adjust_union_virtue(US_GRACE, 3);
    return 1;
}

public int
swear(string str)
{
    str = check_adverb_with_space(str, "quietly");

    if (str == NO_ADVERB_WITH_SPACE)
    {
	notify_fail("Swear how?\n");
	return 0;
    }

    write("You swear"+ str +".\n");
    all(" swears"+ str +".");

    SOULDESC("swearing "+str);
    return 1;
}

public int
threaten(string str)
{
    string knife;
    object *oblist, combat;

    if (!strlen(str))
    {
	notify_fail("Threaten who?\n");
	return 0;
    }

    oblist = parse_live(str, "[the] %o");

    if (!sizeof(oblist))
    {
	notify_fail("Threaten who?\n");
	return 0;
    }

    if (oblist[0]->query_stat(SS_DIS) >
	(TP->query_stat(SS_DIS) + random(20)))
    {
	notify_fail("You don't dare.\n");
	return 0;
    }

    if (!strlen(knife = has_knife(TP)->short()))
    {
	actor("You assume a threatening stance before", oblist);
	all2actbb(" assumes a threatening stance before", oblist);
	targetbb(" assumes a threatening stance before you.", oblist);

	SOULDESC("acting in a threatening manner");
	return 1;
    }

    /* A better way to see if the creature has a 'neck', I think... */
    combat = oblist[0]->query_combat_object();
    foreach(int id : combat->query_hitloc_id())
    {
	string loc = combat->query_hitloc(id)[2];

	/* No head or neck... */
	if ((loc != "head") && (loc != "neck"))
	    continue;

	actor("You place the tip of your "+ knife +
	  " against the neck of", oblist);
	all2actbb(" places the tip of "+ HIS(TP) +" "+ knife +
	  " against", oblist, "'s neck.");
	target(" places the tip of "+ HIS(TP) +" "+ knife +
	  " against your neck.", oblist);

	SOULDESC("acting in a threatening manner");
	return 1;
    }

    /* No neck, so we just use the creature name.. */
    actor("You aim your "+ knife +" threatingly towards", oblist);
    all2actbb(" aims "+ HIS(TP) +" "+ knife +" threatingly towards" ,oblist);
    targetbb(" aims "+ HIS(TP) +" "+ knife +" threatingly towards you.", oblist);

    SOULDESC("acting in a threatening manner");
    return 1;
}

public int
triumph(string str)
{
    string *tmp;
    object corpse, *oblist;

    if (!strlen(str))
    {
	write("You stand triumphant and proud.\n");
	allbb(" stands triumphant and proud.");

	SOULDESC("looking triumphant");
	return 1;
    }

    oblist = parse_this(str, "[over] [the] %o");

    if (!sizeof(oblist))
    {
	notify_fail("Stand triumphant over what?\n");
	return 0;
    }

    if (living(oblist[0]))
    {
	actor("But you haven't killed", oblist, " yet!");
	return 1;
    }

    corpse = oblist[0];

    if (!corpse->id("corpse"))
    {
	actor("But,", oblist, " isn't a corpse!");
	return 1;
    }

    tmp = corpse->query_prop(CORPSE_AS_KILLER);

    if (!IN_ARRAY(TP->query_real_name(), tmp))
    {
	foreach(object who : TP->query_team_others())
	{
	    if (!IN_ARRAY(who->query_real_name(), tmp))
		continue;

	    actor("You stand triumphant and proud over", oblist,
	      ", which you helped to kill.");
	    all2actbb(" stands triumphantly over", oblist,
	      ", which "+ HE(TP) +" helped to kill.");

	    SOULDESC("standing triumphantly, eyes ablaze with victory");
	    TP->emote_adjust_union_virtue(US_PRIDE, 3);
	    return 1;
	}

	write("You try to take credit for something you did not kill.\n");
	all2actbb(" stands triumphantly over", oblist,
	  ", trying to take credit for something "+ HE(TP) +" did not kill.");

	TP->emote_adjust_union_virtue(US_PRIDE, -3);
	return 1;
    }

    actor("You stand triumphant and proud over", oblist);
    all2actbb(" stands triumphantly over", oblist,
      ", "+ HIS(TP) +" eyes blazing with victory.");

    SOULDESC("standing triumphantly, eyes ablaze with victory");
    TP->emote_adjust_union_virtue(US_PRIDE, 3);
    return 1;
}

public int
uclean(string str)
{
    object *oblist, what;

    if (!strlen(str))
    {
	notify_fail("Clean what weapon?\n");
	return 0;
    }

    oblist = all_inventory(TP);

    if (!parse_command(str, oblist, "[my] [the] %o", what))
    {
	notify_fail("Clean what weapon?\n");
	return 0;
    }

    if (!what->check_weapon())
    {
	notify_fail("That is not a weapon.\n");
	return 0;
    }

    if (TP->query_exp_combat() == what->query_prop("union_hits"))
    {
	write("Your "+ what->short(TP) +" is already clean.\n");
	return 1;
    }

    write("You take out a cloth and carefully clean your "+
      what->short(TP) +".\n");
    allbb(" takes out a small cloth and carefully cleans "+
      HIS(TP) +" "+ what->short() +".");

    TP->emote_adjust_union_virtue(US_PURITY, 10);
    what->add_prop("union_hits", TP->query_exp_combat());
    return 1;
}

public int
udown(string str)
{
    string wdesc;
    mixed *objs = ({ });

    str = check_adverb_with_space(str, "slightly");

    if (str == NO_ADVERB_WITH_SPACE)
    {
	notify_fail("Lower your weapons [how] as a gesture of peace?\n");
	return 0;
    }

    objs = TP->query_weapon(-1);

    if (sizeof(objs))
	wdesc = COMPOSITE_WORDS(objs->short());
    else
	wdesc = "hands";

    write("You lower your "+ wdesc + str +
      " in a subtle gesture of peace.\n");
    allbb(" lowers "+ HIS(TP) +" "+ wdesc + str +
      " in a subtle gesture of peace.");

    return 1;
}

public int
ufinger(string str)
{
    string *how;
    object *oblist, what;

    how = parse_adverb_with_space(str, "slowly", 0);

    if (!strlen(how[0]))
    {
	notify_fail("Run your fingers [how] along what?\n");
	return 0;
    }

    oblist = all_inventory(TP);

    if (!parse_command(how[0], oblist, "[along] [my] %o", what))
    {
	notify_fail("Run your fingers [how] along what?\n");
	return 0;
    }

    if (!what->id(TOKEN_ID) && !what->id(BAND_ID) &&
	!what->check_weapon())
    {
	notify_fail("You cannot run your fingers along that.\n");
	return 0;
    }

    write("You run your fingers"+ how[1] +" along your "+
	what->short(TP) +".\n");
    allbb(" runs "+ HIS(TP) +" fingers"+ how[1] +" along "+ HIS(TP) +
	" " + what->short() +".");

    TP->emote_adjust_union_virtue(US_GRACE, 2);
    return 1;
}

public int
unamused(string str)
{
    object *oblist;

    if (strlen(str))
    {
	write("You show that you are completely unamused.\n");
	allbb(" looks completely unamused.");

	SOULDESC("looking completely unamused");
	return 1;
    }

    oblist = parse_this(str, "[before] / [at] [the] %l");

    if (!sizeof(oblist))
    {
	notify_fail("Who are you unamused by?\n");
	return 0;
    }

    actor("You are completely unamused by the behaviour of", oblist);
    all2actbb(" is completely unamused by the behaviour of", oblist);
    targetbb(" is completely unamused by your behaviour.", oblist);

    SOULDESC("looking completely unamused");
    return 1;
}

public int
uncloak(string str)
{
    object wep, cloak = one_of_list(TP->query_clothing(A_ROBE));

    if (!cloak || (!cloak->id("cloak") && !cloak->id("cape")))
    {
	notify_fail("You would need to be wearing a "+
	  "cloak or cape to do that.\n");

	return 0;
    }

    str = check_adverb_with_space(str, "gracefully");

    if (str == NO_ADVERB_WITH_SPACE)
    {
	notify_fail("Uncloak yourself how?\n");
	return 0;
    }

    wep = one_of_list(TP->query_weapon(-1));

    if (!objectp(wep))
    {
	write("You"+ str +" throw back your "+ cloak->short(TP) +
	  " and take a defensive stance.\n");
	allbb(str +" throws back "+ HIS(TP) +" "+ cloak->short() +
	  " and takes a defensive stance.");

	SOULDESC("standing defensively");
	return 1;
    }

    write("You"+ str +" throw back your "+ cloak->short() +
      " and hold forth your "+ wep->short(TP) +".\n");
    allbb(str +" throws back "+ HIS(TP) +" "+ cloak->short() +
      " and holds forth "+ HIS(TP) +" "+ wep->short() +".");

    SOULDESC("in a fighting stance");
    return 1;
}

public int
uoath(string str)
{
    int last_char;

    if (!strlen(str) || (str[0..3] != "that"))
    {
	notify_fail("uoath <that> [what]?\n");
	return 0;
    }

    last_char = str[strlen(str) - 1];

    /* Complete the sentence with puncuation, if the */
    /* player did not do so explicitly.              */
    if (last_char > 'A' && last_char < 'z')
	str += ".";

    write("You swear an oath "+ str +"\n");
    all(" swears an oath "+ str);

    return 1;
}

public int
ustudy(string str)
{
    string *how;
    object *oblist;

    how = parse_adverb_with_space(str, "carefully", 0);

    if (!strlen(how[0]))
    {
	notify_fail("Study [how] <who>?\n");
	return 0;
    }

    oblist = parse_this(how[0], "[at] [to] [towards] [the] %l");

    if (!sizeof(oblist))
    {
	notify_fail("Study [how] <who>?\n");
	return 0;
    }
    else if (sizeof(oblist) > 1)
    {
	write("You may only do that to a single target.\n");
	return 1;
    }

    if (IS_MEMBER(oblist[0]))
    {
	actor("You study", oblist, how[1] + ", assessing " +
	  multiple_possessive(oblist) + " virtues.");
	// This is from ability.h
	write(virtue_desc(oblist[0], 0 , TP));
	all2actbb(" studies", oblist, how[1] + ", assessing " +
	  multiple_possessive(oblist) + " virtues.", how[1]);
	targetbb(" studies you" + how[1] + ", assessing your virtues.",
	  oblist, how[1]);
    }
    else
    {
	actor("You"+ how[1] +" study", oblist, " from head to toe, "+
	  "assessing "+ multiple_possessive(oblist) +
	  " strengths and weaknesses.");
	all2actbb(" studies", oblist, how[1] +" from head to toe, "+
	  "assessing "+ multiple_possessive(oblist) +
	  " strengths and weaknesses with a piercing gaze.");
	targetbb(how[1] +" studies you from head to toe, assessing "+
	  "your strengths and weaknesses with a piercing gaze.", oblist);
    }

    return 1;
}

public int
urage(string str)
{
    object wep = one_of_list(TP->query_weapon(-1));

    if (!objectp(wep))
    {
	notify_fail("You hold no weapon to vent your rage on.\n");
	return 0;
    }

    str = check_adverb_with_space(str, "furiously");

    if (str == NO_ADVERB_WITH_SPACE)
    {
	notify_fail("Show your rage how?\n");
	return 0;
    }

    write("You grip your "+ wep->short(TP) + str +
      " as the rage wells up inside you.\n");
    allbb(str +" grips "+ HIS(TP) +" "+ wep->short() + str +" as "+
      HIS(TP) +" "+ TP->query_eyes() +" eyes narrow.");

    SOULDESC("looking furious with rage");
    return 1;
}

public int
uturn(string str)
{
    string *how;
    object *oblist, who;

    how = parse_adverb_with_space(str, "angrily", 0);

    if (!strlen(how[0]))
    {
	notify_fail("Turn [how] towards whom?\n");
	return 0;
    }

    oblist = parse_live(how[0], "[at] [to] [towards] [the] %o");

    if (!sizeof(oblist))
    {
	notify_fail("Turn [how] towards whom?\n");
	return 0;
    }

    who = oblist[0];

    actor("You turn to", oblist,", eyeing "+
      who->query_objective() + how[1] +".");
    all2actbb(" turns toward", oblist, ", a black flame flickering"+
      how[1] +" in "+ HIS(TP) +" eyes.");
    targetbb(" turns to you, a black flame flickering"+ how[1] +
      " in "+ HIS(TP) +" eyes.", oblist);

    if (who->query_humanoid())
    {
	if ((TP->query_stat(SS_DIS) + random(10)) >
	    (who->query_stat(SS_DIS) + random(10)))
	{
	    who->catch_tell("You feel the need to turn away.\n");
	    tell_room(ENV(who), QCTNAME(who) +" turns away, "+
	      HIS(who) +" face pale.\n", who);

	    who->add_prop(LIVE_S_SOULEXTRA, "pale and frightened");
	}
    }

    return 1;
}

public int
wrath(string str)
{
    object *oblist;

    if (!strlen(str))
    {
	write("You show your wrath at the situation.\n");
	allbb(" looks around and "+ HIS(TP) +" face darkens with wrath.");

	SOULDESC("looking wrathful");
	return 1;
    }

    oblist = parse_this(str, "[to] [at] [the] %l");

    if (!sizeof(oblist))
    {
	notify_fail("Show your wrath to whom?\n");
	return 0;
    }

    actor("You show your wrath to", oblist);
    all2actbb("'s face darkens with wrath as "+ HE(TP) +
      " stares at", oblist);
    targetbb("'s face darkens with wrath as "+ HE(TP) +
      " stares at you.", oblist);

    SOULDESC("looking wrathful and terrible");
    return 1;
}
