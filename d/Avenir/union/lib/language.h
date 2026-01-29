/*
 * Code for the Language of the Union of the
 * Warriors of Shadow.
 *   Lord Cirion, 032696
 *
 * Revisions:
 *   Lucius, Oct 2006:  Cleanup and refactoring.
 *   Lucius, Jun 2016:  Added GMCP support.
 *   Lilith, Feb 2022:  added 'real' Sybarite words. 
 */

#include <std.h>

private static string *W1 = ({
    "a", "o", "t'", "'i", "a'y", "l'", "h'", "'k'", "z'"
});
private static string *W2 = ({
    "ki", "ly", "sh", "al", "re", "sn'", "t'r", "'ak", "ti",
    "tr", "il", "ay", "os", "q'l", "su", "ae", "hl", "eb", 
	"s't", "gl'", "w'a", "lu", "u'd", "t'a", "i'i", "ip"
});
private static string *W3 = ({
    "ayl", "rei", "nmy", "s'lr", "a'kr", "ter",
    "fl'a", "rao", "bre", "ar'l", "tis", "pah",
	"hla", "jin", "cyn", "syb", "dni", "wyr",
	"h'te", "x'tl", "k'fa", "dw'o", "t'hu", 
	"d'xi", "ep'u", "kai", "s'da", "wei"
});
private static string *W4 = ({
    "aril", "sna'y", "ylie", "kran", "fle't", "loor",
    "quai", "laud", "orpi", "ther", "anst", "etio", "yera",
	"m'vat", "dat'r", "svil", "tr'tl", "bl'yv", "yann",
	"ey'th", "jost", "hu'um", "f'nya", "shog", "do'ot",
	"fran", "ar'no", "qaat", "t'fla", "lu'ta", "v'nda",
	"amon", "beya",  "atra", "aren", "arus", "duri", "jure",
	"du'it", "ensi", "fris", "hena", "hlaj", "istu", "k'nna",
	"moyu", "n'var", "sera", "velo", "ve'nu", "t'sla",
	"z'pym", "wyra", "ialr"
});
private static string *W5 = ({
    "flari", "feno't", "amlis", "agnis", "prist",
    "oldia", "rat'tu", "emmig", "tornu", "lecto",
    "tanli", "o'tril", "nessu", "ki'las", "shliy",
    "slist", "trint", "aluni", "pi'ila", "linil",
	"wa'ani", "tjana", "qochi", "do'osa", "verax",
	"co'rin", "aveni", "banti", "gorta", "gra'zo", 
	"gel'ic", "luyal", "nes'na", "rolau", "roras",
    "ry'iak", "s'danz", "suu'na", "t'cael", "temes",
	"verdu", 
});
private static string *W6 = ({
    "quelit", "agrnis", "lyinle", "k'miasl", "nalyia", 
    "win'ana", "pritdi", "fi'arta", "cha'gor", "nilini",
    "bilant", "sam'rit", "ily'tro", "panapa", "aglyna",
    "fahlor", "haveth", "si'irli", "orymil", "syrtis",
	"saba'ym", "tibi'ul", "vohuun", "qoqi'tl", "vulipi",
	"ammali", "alchem", "alieci", "ki'lyle", "lu'fris",
	"lu'arna", "lupra'et", "na'arves", "naliya", "pashat",
	"ul'risa","vulipi", "yerian", "toaqar",
});


/*
 * Function:   replace
 * Arguments:  one word to replace
 */
private string
replace(string str)
{
    string back;
    int size = strlen(str);

    switch(size)
    {
    case 1:  back = one_of_list(W1); break;
    case 2:  back = one_of_list(W2); break;
    case 3:  back = one_of_list(W3); break;
    case 4:  back = one_of_list(W4); break;
    case 5:  back = one_of_list(W5); break;
    default: back = one_of_list(W6); break;
    }

    /* Retain capitializations. */
    if (str == CAP(str))
	back = CAP(back);

    if (size > 0)
    {
	/* Retain ending punctuation. */
	switch(str[size-1])
	{
	case ',': back += ","; break;
	case '.': back += "."; break;
	case '!': back += "!"; break;
	case '?': back += "?"; break;
	}
    }

    return back;
}

/*
 * Function name: should_understand_usay
 * Description  : Various wizards, like the administration, should
 *                always understand special speech. /Mercade.
 * Arguments    : object target - who should understand the language.
 * Returns      : int 1/0 - if true, player will understand.
 */
private int
should_understand_usay(object target)
{
    string name;

    if (IS_MEMBER(target))
	return 1;

    name = target->query_real_name();

    if ((SECURITY->query_wiz_rank(name) >= WIZ_ARCH) ||
	(SECURITY->query_wiz_dom(name) == "Avenir"))
	return 1;

    return 0;
}

private void
usay_to(object who, string how, string gibber, string orig)
{
    string name = TP->query_The_name(who);
    string text = name +" "+ how;

    /* Members automatically understand it */
    if (should_understand_usay(who))
	text += " in High Sybarite: "+ orig;
    else
	text += " in a lilting language: "+ gibber;

    who->catch_tell(text + "\n");
    who->gmcp_comms("usay", name, text);
}

public int
usay(string str)
{
    mixed tmp;
    object *oblist;

    if (!strlen(str))
    {
	notify_fail("Say what in the Union Tongue?\n");
	return 0;
    }

    if (tmp = this_player()->query_prop(LIVE_M_MOUTH_BLOCKED))
    {
	write(stringp(tmp) ? tmp : "You are gagged and cannot speak.\n");
	return 1;
    }

    if (TP->query_skill(SS_LANGUAGE) < 25)
    {
	notify_fail("You do not have enough skill "+
	  "to use the Union tongue.\n");
	return 0;
    }

    tmp = allocate(4);

    if (present(SWAY_ID, TP))
    {
	tmp[0] = TP->actor_race_sound();
	tmp[1] = TP->race_sound();
    }
    else
    {
	tmp[0] = "say";
	tmp[1] = "says";
    }

    if (TP->query_option(OPT_ECHO))
	tmp[3] = "You "+ tmp[0] +" in High Sybarite: "+ str;
    else
	tmp[3] = "Ok.";

    write(tmp[3] + "\n");
    this_player()->gmcp_comms("usay", 0, tmp[3]);

    oblist = filter(all_inventory(ENV(TP)), query_interactive);
    oblist -= ({ TP });

    if (!sizeof(oblist))
	return 1;

    /* Generate gibberish. */
    tmp[2] = implode(map(explode(str, " "), replace), " ");

    /* Tell the people. */
    map(oblist, &usay_to(/* obj */, tmp[1], tmp[2], str));

    return 1;
}

/*
 * Function name: usto_target
 * Description  : Called for each target of the usto command.
 * Arguments    : string how  - how we should sound.
 *                string targ - target description; could be
 *                              "all, including you,",
 *                              "his team, including you,",
 *                              "her team, including you," or "you"
 *                string what - text said.
 *                object who  - target living who hears something.
 */
private void
usto_target(object who, string how, string targ, string what)
{
    string name = TP->query_The_name(who);
    string text = name +" "+ how + " to "+ targ;

    /* Target always understands. */
    if (should_understand_usay(who))
	text += " in High Sybarite: "+ what;
    else
	text += " in a lilting language: "+ what;

    who->catch_tell(text + "\n");
    who->gmcp_comms("usay", name, text);
}

/*
 * Function name: usto_onlooker
 * Description  : Called for each onlooker of the usto command.
 * Arguments    : string how  - how we should sound.
 *                string targ - target description; could be "all"
 *                              "his team", "her team" or object short.
 *                string what - text said.
 *                object who  - target living who hears something.
 */
private void
usto_onlooker(object who, object *oblist, string how, string what)
{
    string targ = FO_COMPOSITE_ALL_LIVE(oblist, who);
    string name = TP->query_The_name(who);
    string text = name +" "+ how;


    // Members & arches automatically understand it and hear it
    if (should_understand_usay(who))
	text += " to "+ targ +" in High Sybarite: "+ what;
    else
	text += " something unintelligible to "+ targ +
	    " in a lilting language.";

    who->catch_tell(text + "\n");
    who->gmcp_comms("usay", name, text);
}

/*
 * Function name: us_to excerpted from /cmd/live/speech "whisper"
 * Description  : Called when somene speaks to someone in the Union Tongue
 * Arguments    : string str - the text to say.
 *                string adverb - the adverb to use.
 * Returns      : int 1/0 - success/failure.
 */
public int
us_to(string str)
{
    mixed tmp;
    string multi;
    object *oblist, *others;

    if (!strlen(str))
    {
	notify_fail("Say to whom/what in the Union Tongue?\n");
	return 0;
    }

    if (tmp = this_player()->query_prop(LIVE_M_MOUTH_BLOCKED))
    {
	write(stringp(tmp) ? tmp : "You are gagged and cannot speak.\n");
	return 1;
    }

    /* Usay to all people. */
    if (wildmatch("all *", str))
    {
	multi = "all";
	tmp = extract(str, 4);
	oblist = FILTER_OTHER_LIVE(all_inventory(ENV(TP)));
    }
    /* Usay to my team. */
    else if (wildmatch("team *", str))
    {
	multi = TP->query_possessive() + " team";
	tmp = extract(str, 5);
	oblist = this_player()->query_team_others() &
	all_inventory(ENV(TP));
    }
    /* Find out who we usay to. */
    else if (!parse_command(str, ENV(TP), "[to] [the] %i %s", oblist, str))
    {
	notify_fail("Say to whom/what in the Union Tongue?\n");
	return 0;
    }
    else
    {
	oblist = NORMAL_ACCESS(oblist, 0, 0) - ({ TP });
    }

    if (!sizeof(oblist))
    {
	notify_fail("Say to whom/what in the Union Tongue?\n");
	return 0;
    }

    str = extract(str, -(strlen(tmp)));
    tmp = allocate(2);

    if (!strlen(str))
    {
	write("Say what in the Union Tongue?\n");
	return 1;
    }

    if (present(SWAY_ID, TP))
    {
	tmp[0] = TP->actor_race_sound();
	tmp[1] = TP->race_sound();
    }
    else
    {
	tmp[0] = "say";
	tmp[1] = "says";
    }

    if (this_player()->query_option(OPT_ECHO))
	actor("You "+ tmp[0] +" to", oblist, " in High Sybarite: " + str, "usay");
    else
	write("Ok.\n");

    // Find out all interactive onlookers as well.
    others = filter(all_inventory(ENV(TP)), query_interactive);
    others -= (oblist + ({ TP }));

    if (!strlen(multi))
	multi = "you";
    else
	multi += ", including you,";

    map(oblist,
      &usto_target(/* obj */, tmp[1], multi, str));

    map(others,
      &usto_onlooker(/* obj */, oblist, tmp[1], str));

    return 1;
}
