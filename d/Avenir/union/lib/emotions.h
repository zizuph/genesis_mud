/*
 * Emotions for the Union of the Warriors of
 * Shadow.
 *  Cirion 032596
 *
 * Recoded and cleaned up by Lucius: June 2007.
 */
#include <adverbs.h>
#include <cmdparse.h>

/* ****** Definitions ****** */
#define SOULDESC(x)  TP->add_prop(LIVE_S_SOULEXTRA, x)

/******* Pain & Joy Functions ***** */
public string
cry_name(void)
{
    object pobj;
    string myrace;
    mapping race_str = ([
       "gnome":"gnomish",
         "elf":"elvish",
       "dwarf":"dwarvish",
       "human":"human's",
      "hobbit":"squeaky",
      "goblin":"goblin's"
    ]);

    myrace = TP->query_race();
    if (race_str[myrace])
	myrace = race_str[myrace];

    /* Reciever of message */
    pobj = previous_object();
    if (file_name(pobj) == "/secure/vbfc_object")
	pobj = previous_object(-1);

    if (pobj->query_met(TP))
    {
	if (environment(pobj) == environment(TP))
	    return TP->query_name() +" cries";
	else
	    return "You hear "+ TP->query_name() +" crying";
    }
    else
    {
	string str;

	if (environment(pobj) == environment(TP))
	    str = TP->query_nonmet_name() +" cries";
	else
	    str = TP->query_gender_string() +" "+
		myrace +" voice cries";

	return capitalize(LANG_ADDART(str));
    }
}

private string
multiple_possessive(object *obs)
{
    if (sizeof(obs) > 1)
	return "their";
    else
	return obs[0]->query_possessive();
}

/************EMOTIONS*********** */
public int
angry(string str)
{
    object *oblist;

    if (!strlen(str))
    {
	write("Your eyes burn with the dark fire as you show your anger.\n");
	allbb("'s eyes seem to burn with a fearsome dark fire.");

	TP->emote_adjust_union_virtue(US_PRIDE, 2);
	SOULDESC("looking very angry");
	return 1;
    }

    oblist = parse_this(str, "[before] / [at] / [to] [the] %l");
    if (!sizeof(oblist))
    {
	notify_fail("Show your anger to whom?\n");
	return 0;
    }

    actor("You turn towards", oblist, ", showing your anger.");
    all2actbb(" turns towards", oblist,", "+ HIS(TP) +
      " black eyes burning with a fearsome dark flame.");
    targetbb(" turns towards you, "+ HIS(TP) +" black eyes aglow "+
      "with a fearsome dark flame.", oblist);

    SOULDESC("looking very angry");
    TP->emote_adjust_union_virtue(US_PRIDE, 3);
    return 1;
}

public int
blink(string str)
{
    if (strlen(str))
    {
	notify_fail("Blink what?\n");
	return 0;
    }

    write("You blink.\n");
    allbb(" blinks.");
    SOULDESC("blinking");
    return 1;
}

public int
brood(string str)
{
    str = check_adverb_with_space(str, "deeply");

    if (str == NO_ADVERB_WITH_SPACE)
    {
	notify_fail("Brood how?\n");
	return 0;
    }

    write("You brood"+ str +" over the matter at hand.\n");
    allbb(" broods"+ str +" over some matter.");

    SOULDESC("brooding");
    TP->emote_adjust_union_virtue(US_DIGNITY, 2);
    return 1;
}

public int
calm(string str)
{
    if (strlen(str))
    {
	notify_fail("How do you want to be calm?\n");
	return 0;
    }

    int panic = (TP->query_stat(SS_DIS) * 3);
    panic = min((TP->query_panic() * 100) / panic, 100);

    if (panic < 50)
    {
	write("You remain calm despite the peril ahead.\n");
	allbb(" remains calm.");

	SOULDESC("looking calm and collected");
	TP->emote_adjust_union_virtue(US_DIGNITY, 3);
	return 1;
    }

    write("You try to keep your calm, but fail completely.\n");
    allbb(" tries to keep "+ HIS(TP) +" calm, but fails.");

    SOULDESC("looking extremely scared and panicky");
    TP->emote_adjust_union_virtue(US_PRIDE, -3);
    return 1;
}

public int
clash(string str)
{
    string ret;
    mixed *objs = TP->query_weapon(-1);

    if (sizeof(objs) < 2)
    {
	notify_fail("You would need to be wielding two weapons "+
	  "to do that.\n");
	return 0;
    }

    if (TP->query_stat(SS_STR) > 100)
	ret = ".\nSparks fly everywhere";
    else
	ret = "";

    write("You clash "+ LANG_THESHORT(objs[0]) +" against "+
      LANG_THESHORT(objs[1]) +", making a loud noise"+ ret +".\n");
    all(" clashes "+ HIS(TP) +" "+ objs[0]->short() +" against "+
	HIS(TP) +" "+ objs[1]->short() +", making a loud noise"+ ret +".");

    return 1;
}

public int
cross(string str)
{
    string ret;
    mixed *objs = TP->query_weapon(-1);

    if (sizeof(objs) < 2)
    {
	notify_fail("You would need to be wielding two weapons "+
	  "to do that.\n");
	return 0;
    }

    write("You hold "+ LANG_THESHORT(objs[0]) +" across "+
      LANG_THESHORT(objs[1]) +" in a cross before you.\n");
    allbb(" holds "+ HIS(TP) +" "+objs[0]->short() +" across "+ HIS(TP) +
      " "+objs[1]->short() +" before "+ HIM(TP) +", making a cross.");

    TP->emote_adjust_union_virtue(US_GRACE, 2);
    return 1;
}

public int
curse(string str)
{
    string *how;
    object *oblist;

    how = parse_adverb_with_space(str, "furiously", 0);

    if (!strlen(how[0]))
    {
	write("You curse"+ how[1] +" in the name of Plalgus.\n");
	all(" curses"+ how[1] +" in the name of Plalgus.");

	SOULDESC("cursing angrily");
	return 1;
    }

    oblist = parse_this(how[0], "[at] [the] %l");

    if (!sizeof(oblist))
    {
	notify_fail("Curse [how] at whom?\n");
	return 0;
    }

    actor("You curse"+ how[1] +" at", oblist);
    all2act(" curses"+ how[1] +" at", oblist);
    target(" curses"+ how[1] +" at you.", oblist);

    SOULDESC("cursing angrily");
    return 1;
}

public int
dance(string str)
{
    object *oblist;

    if (!strlen(str))
    {
	write("You dance with a sinuous, weaving motion.\n");
	all(" seems to dance with a strange, weaving motion.");

	SOULDESC("swaying back and forth slowly");
	TP->emote_adjust_union_virtue(US_GRACE, 2);
	return 1;
    }

    oblist = parse_this(str, "[with] / [before] [the] %l");

    if (!sizeof(oblist))
    {
	notify_fail("Dance with whom?\n");
	return 0;
    }

    actor("You dance before", oblist, " with a sinuous, weaving motion.");
    all2act(" dances before", oblist, " with a sinuous, weaving motion.");
    target(" dances before you with a strange, weaving motion.", oblist);

    SOULDESC("swaying back and forth slowly");
    TP->emote_adjust_union_virtue(US_GRACE, 2);
    return 1;
}

public int
dignity(string str)
{
    object *oblist;

    if (!strlen(str))
    {
	write("You stand to your full height, dignified and proud.\n");
	allbb(" stands to "+HIS(TP)+" full height, dignified and proud.");

	SOULDESC("standing dignified and proud");
	TP->emote_adjust_union_virtue(US_DIGNITY, 2);
	return 1;
    }

    oblist = parse_this(str, "[before] [the] %l");
    if (!sizeof(oblist))
    {
	notify_fail("Stand dignified before whom?\n");
	return 0;
    }

    actor("You stand dignified before", oblist);
    all2actbb(" stands to "+ HIS(TP) +" full height before",
      oblist, ", dignified and proud.");
    targetbb(" stands to "+ HIS(TP) +" full height before you, "+
      "dignified and proud.", oblist);

    SOULDESC("standing dignified and proud");
    TP->emote_adjust_union_virtue(US_DIGNITY, 5);
    return 1;
}

public int
ectios(string str)
{
    object *oblist;

    if (!strlen(str))
    {
	write("You touch two fingers to your lips in farewell "+
	  "and whisper \"Ectios\".\n");
	allbb(" brushes two fingers to "+ HIS(TP) +" lips briefly "+
	  "in a salute of farewell and whispers \"Ectios\".\n"+
	  CAP(HIS(TP)) +" eyes flicker momentarily with a lonely flame.");

	return 1;
    }

    oblist = parse_this(str, "[to] [the] %l");
    if (!sizeof(oblist))
    {
	notify_fail("Bid farewell to whom?\n");
	return 0;
    }

    actor("You touch two fingers to your lips in farewell "+
      "and whisper \"Ectios\" to",oblist,".");
    all2actbb(" turns towards", oblist," and whispers something "+
      "softly.\n"+ CAP(HIS(TP)) +" eyes flicker momentarily with "+
      "a lonely flame.");
    targetbb(" turns towards you and brushes two fingers to "+ HIS(TP) +
      " lips briefly in a salute of farewell, "+
      "whispering \"Ectios\".", oblist);

    oblist->union_hook_got_ectios(TP);
    return 1;
}

public int
gaze(string str)
{
    string *how;
    object *oblist;

    how = parse_adverb_with_space(str, "menacingly", 0);
    oblist = parse_this(how[0], "[at] [the] %l");

    if (!sizeof(oblist))
    {
	write("You gaze"+ how[1] +" about, your eyes aglow "+
	  "with dark flames.\n");
	allbb(" gazes"+ how[1] +" about, "+ HIS(TP) +
	  " eyes aglow with a dark flame.");

	SOULDESC("gazing"+ how[1]);
	return 1;
    }

    actor("You gaze"+ how[1] +" at", oblist,", your eyes "+
      "aglow with dark flames.");
    all2actbb(" gazes"+ how[1] +" at", oblist,", "+ HIS(TP) +
      " eyes aglow with a dark flame.");
    targetbb(" gazes"+ how[1] +" at you, a dark fire burning in "+
      HIS(TP) +" eyes.", oblist);

    SOULDESC("gazing"+ how[1]);
    return 1;
}

public int
glare(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, "fiercefully", 0);

    if (!strlen(how[0]))
    {
	write("You glare"+ how[1] +".\n");
	allbb(" glares"+ how[1] +".");
	SOULDESC("glaring"+ how[1]);
	return 1;
    }

    oblist = parse_this(how[0], "[at] [the] %l");

    if (!sizeof(oblist))
    {
	notify_fail("Glare [how] at whom?\n");
	return 0;
    }

    SOULDESC("glaring"+ how[1]);
    targetbb(" glares"+ how[1] +" at you.", oblist);
    actor("You glare"+ how[1] +" at", oblist);
    all2actbb(" glares"+ how[1] +" at", oblist);
    return 1;
}

public int
greet(string str)
{
    object *oblist = parse_this(str, "[the] %l");

    if (!sizeof(oblist))
    {
	notify_fail("Greet whom?\n");
	return 0;
    }

    actor("You greet", oblist," with a slight nod of your head.");
    all2actbb(" greets", oblist ," with a slight nod of "+ HIS(TP) +" head.");
    targetbb(" greets you with a slight nod of "+ HIS(TP) +" head.", oblist);

    return 1;
}

private static string *ind_dir = ({
  "up", "down", "north", "south", "west", "east",
  "northwest", "southwest", "northeast", "southeast",
  "in", "out",
});

public int
indicate(string str)
{
    object *oblist, knife;

    if (!(knife = has_knife(TP)))
    {
	notify_fail("You would need to be holding a knife to do that.\n");
	return 0;
    }

    if (!strlen(str))
    {
	write("You wave your "+ knife->short() +
	  " in a general direction.\n");
	allbb(" waves "+ HIS(TP) +" "+ knife->short() +
	  " in a general direction.");
	return 1;
    }

    str = lower_case(str);
    if (member_array(str, ind_dir) >= 0)
    {
	write("You indicate "+ str +" with your "+
	  knife->short() +".\n");
	allbb(" indicates "+ str +" with "+ HIS(TP) +" "+
	  knife->short() +".");
	return 1;
    }

    if ((str == TP->query_real_name()) ||
	(str == "me") || (str == "myself"))
    {
	write("You point your "+ knife->short() +" at yourself.\n");
	allbb(" points "+ HIS(TP) +" "+ knife->short() +
	  " at "+ HIM(TP) +"self.");
	return 1;
    }

    oblist = parse_this(str, "[the] %i");

    if (!sizeof(oblist))
    {
	if (environment(TP)->item_id(str))
	{
	    write("You indicate the "+ str +" with your "+
	      knife->short()+".\n");
	    allbb(" indicates "+ LANG_ADDART(str) +" with "+
	      HIS(TP) +" "+ knife->short() +".");
	    return 1;
	}

	notify_fail("Where or what do you want to indicate with your "+
	  knife->short() +"?\n");
	return 0;
    }

    actor("You point at", oblist ," with your "+
      knife->short() +".");
    all2actbb(" points at", oblist ," with "+ HIS(TP) +" "+
      knife->short() +".");
    targetbb(" points at you with "+ HIS(TP) +" "+
      knife->short() +".", oblist);

    return 1;
}

public int
interrupt(string str)
{
    object *oblist;

    if (!strlen(str))
    {
	write("You raise your hand, signifying that you would like "+
	  "to speak.\n");
	allbb(" raises "+ HIS(TP) +" hand, signifying that "+ HE(TP) +
	  " would like to say something.");

	SOULDESC("trying to say something");
	return 1;
    }

    oblist = parse_this(str, "[the] %l");

    if (!sizeof(oblist))
    {
	notify_fail("Interrupt whom?\n");
	return 0;
    }

    actor("You interrupt", oblist, ", indicating that you want to speak.");
    all2actbb(" interrupts", oblist, ", indicating that "+
      HE(TP) +"wants to speak.");
    targetbb(" interrupts you, trying to say something.", oblist);

    SOULDESC("trying to say something");
    return 1;
}

public int
joy(string str)
{
    object *oblist, troom;

    if (!(troom = environment(TP)))
	return 0;

    foreach(object where : FIND_NEIGHBOURS(troom, 2))
    {
	tell_room(where, "@@cry_name:"+ file_name(this_object()) +
	  "@@ out loud and joyous.\n", TP);
    }

    if (!strlen(str))
    {
	write("You cry out in a loud, joyous voice.\n");
	SOULDESC("looking euphoric");
	TP->emote_adjust_union_virtue(US_DIGNITY, 2);
	return 1;
    }

    oblist = parse_this(str, "[the] %l");

    if (!sizeof(oblist))
    {
	notify_fail("Who are you so joyful to see?\n");
	return 0;
    }

    actor("You cry out in a loud, joyous voice, suffused "+
      "with pleasure by", oblist, "'s presence.");
    all2actbb(" cries out loud and joyous, apparently "+
      "pleased by", oblist, "'s presence.");
    targetbb(" cries out loud and joyous, suffused with "+
      "pleasure by your presence.", oblist);

    SOULDESC("looking euphoric");
    TP->emote_adjust_union_virtue(US_DIGNITY, 2);
    return 1;
}

public int
laugh(string str)
{
    string *how;
    object *oblist;

    how = parse_adverb_with_space(str, "silently", 0);

    if (!strlen(how[0]))
    {
	write("You laugh"+ how[1] +".\n");
	all(" laughs"+ how[1] +".");

	SOULDESC("laughing"+ how[1]);
	return 1;
    }

    oblist = parse_this(how[0], "[at] [the] %l");

    if (!sizeof(oblist))
    {
	notify_fail("Laugh how [at whom]?\n");
	return 0;
    }

    actor("You laugh"+ how[1] +" at", oblist, ".");
    all2act(" laughs"+ how[1] +" at", oblist);
    target(" laughs"+ how[1] +" at you.", oblist);

    SOULDESC("laughing"+ how[1]);
    return 1;
}

public int
mourn(string str)
{
    object *oblist, who;

    if (!strlen(str))
    {
	write("You show your grief.\n");
	allbb(" mourns sadly.");

	SOULDESC("grieving");
	return 1;
    }

    oblist = parse_this(str, "[over] / [for] [the] / [a] %o");

    if (!sizeof(oblist))
    {
	notify_fail("Mourn over what?\n");
	return 0;
    }

    if (living(oblist[0]))
    {
	actor("But", oblist, " is not yet dead.");
	return 1;
    }

    if (!oblist[0]->id("corpse"))
    {
	notify_fail("That would be silly.\n");
	return 0;
    }

    actor("You mourn over ", oblist);
    all2actbb(" mourns over ", oblist);

    SOULDESC("grieving");

    who = find_player(oblist[0]->query_real_name());

    if (!who || !who->query_ghost())
	return 1;

    write("You feel comforted slightly.\n");
    who->catch_tell("A sense of grief falls upon you, and enshrouds "+
      "you like a veil.\nYou feel the presence of "+
      TP->query_the_name(who) +".\n");

    TP->emote_adjust_union_virtue(US_DIGNITY, 10);
    return 1;
}

public int
murmur(string str)
{
    object *oblist;

    if (!strlen(str))
    {
	write("You murmur something under your breath.\n");
	all(" murmurs something incomprehensible.");

	SOULDESC("murmuring about something");
	return 1;
    }

    if ((strlen(str) > 60) && !TP->query_wiz_level())
    {
	write("You don't have enough breath to murmur that much.\n");
	allbb(" murmurs something incomprehensible.");
	SOULDESC("murmuring about something");
	return 1;
    }

    write("You murmur something about "+ str +"\n");
    all(" murmurs something about "+ str);

    SOULDESC("murmuring something");
    return 1;
}

#include "emotion2.h"
