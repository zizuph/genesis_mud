/**********************************************************************
 * - soul.c                                                         - *
 * - Clans, celtic race guild soul                                  - *
 * - Recoded by Damaris 2/2002                                      - *
 * - Updated by Zhar 4/2015                                         - *
 **********************************************************************/
#pragma no_clone
#pragma no_inherit
#pragma strict_types

#include "guild.h"
inherit "/cmd/std/command_driver"; 
inherit "/d/Khalakhor/guilds/tempt/commands";

#include "guild.h"
#include <adverbs.h>
#include <composite.h>
#include <cmdparse.h>
#include <macros.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <ss_types.h>
#include <tasks.h>
#include <options.h>

#define SUBLOC_SOULEXTRADESC ("_soul_cmd_extra")
#define SOULDESC(x)          (this_player()->add_prop(LIVE_S_SOULEXTRA, (x)))
#define LANGUAGE_ALL_RSAY    (55) /* When will you understand all csay     */
#define LANGUAGE_MIN_RSAY    (15) /* Below this you understand no csay     */

varargs int say_text(string str, string adverb = "");
public int say_to(string str, function format);

public int query_cmd_soul()
{
    return 1;
}

public string get_soul_id()
{
    return "clans";
}

public mapping
query_cmdlist()
{
    return ([
        "cl"         : "cl",
        "claccept"   : "claccept",
        "clbow"      : "clbow",
        "clcurtsey"  : "clcurtsey",
        "cldecline"  : "cldecline",
        "clfrown"    : "clfrown",
        "clgiggle"   : "clgiggle",
        "clgreet"    : "clgreet",
        "clgrin"     : "clgrin",
        "clhelp"     : "clhelp",
        "clhome"     : "clhome",
        "cllaugh"    : "cllaugh",
        "cllist"     : "clwho",
        "cllook"     : "cllook",
        "clnod"      : "clnod",
        "clsay"      : "clsay",
        "clsmile"    : "clsmile",
        "clstand"    : "clstand",
        "cltear"     : "cltear",
        "clwarcry"   : "clwarcry",
        "clwho"      : "clwho",
    ]);
}

public void
using_soul(object live)
{
    if (!objectp(live))
        return;

    live->add_subloc(GUILD_SUBLOC, this_object());
}

public string
show_subloc(string subloc, object on, object who)
{
    string str, clan, color;

    if (subloc != GUILD_SUBLOC)
        return "";

    if (on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "";

    if (clan = SERVER->query_clan(on->query_real_name()))
    {
        color =  COMPOSITE_WORDS(CLANS[clan][CLAN_CLRS]);
    }

    if (on != who)
    {
        str = capitalize(on->query_pronoun())
            + " seems to be a human from Khalakhor.\n";

        if (color)
        {
            str += capitalize(on->query_pronoun())
                + " wears the "
                + color
                + " colours "
                + (IS_MEMBER(who) ? "from " + clan : "of a Celtic Clan")
                + ".\n";
        }
    }
    else
    {
        str = "You have the distinct features of a Khalakhor human.\n";

        if (color)
        {
            str += "You are wearing the "
                + color
                + " colours from "
                + clan
                + ".\n";
        }
    }

    return str;
}

/**********************************************************************
 * - Emotions begin here. When adding and updating please list them - *
 * - Alphabetically.                                                - *
 **********************************************************************/
 
int
cl(string str)
{
    string *words;

    if (!strlen(str))
    {
        notify_fail("Perform which Clan command? "
            + "Syntax: cl <command> [<arguments>]\n");

        return 0;
    }

    words = explode(str, " ");

    if (!stringp(cmdlist[words[0]]))
    {
        notify_fail("The command "
            + words[0]
            + " is not a known Clan command.\n");

        return 0;
    }

    str = ((sizeof(words) > 1) ? implode(words[1..], " ") : "");

    return call_other(this_object(), cmdlist[words[0]], str);
}

int
claccept(string str)
{
    object *oblist;

    oblist = parse_this(str, "[the] %l");

    if (!sizeof(oblist))
    {
        if (strlen(parse_msg))
        {
            write(parse_msg);

            return 1;
        }

        notify_fail("Accept whom?\n");
        
        return 0;
    }

    actor("You embrace", oblist, " in a sign of acceptance.");
    all2act(" embraces", oblist, " in a sign of acceptance.");
    target(" embraces you in a sign of acceptance.", oblist, "");

    return 1;
}

int
clbow(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, "slightly", 0);

    if (!stringp(how[0]))
    {
        write("You bow"
            + how[1]
            + ", displaying a hint of celtic heritage.\n");
        allbb(" bows"
            + how[1]
            + ", displaying a hint of celtic heritage.",
            how[1], ACTION_VISUAL | ACTION_MACTIVITY);

        return 1;
    }

    oblist = parse_this(how[0], "[to] / [before] [the] %i",
        ACTION_PROXIMATE | ACTION_VISUAL | ACTION_MACTIVITY);
        
    if (!sizeof(oblist))
    {
        if (strlen(parse_msg))
        {
            write(parse_msg);

            return 1;
        }

        notify_fail("Clbow [how] to whom/what?\n");

        return 0;
    }

    actor("You"
        + how[1]
        + " bow to", oblist, ", displaying a hint of celtic heritage.");
    all2actbb(""
        + how[1]
        + " bows to", oblist, ", displaying a hint of celtic heritage.",
        how[1], ACTION_PROXIMATE | ACTION_VISUAL | ACTION_MACTIVITY);
    targetbb(""
        + how[1]
        + " bows before you, displaying a hint of celtic heritage.", oblist,
        how[1], ACTION_PROXIMATE | ACTION_VISUAL | ACTION_MACTIVITY);

    return 1;
}

int
clcurtsey(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, "slightly", 0);

    if (!stringp(how[0]))
    {
        write("You curtsey"
            + how[1]
            + ", displaying a hint of celtic heritage.\n");
        allbb(" curtseys"
            + how[1]
            + ", displaying a hint of celtic heritage.", how[1],
            ACTION_VISUAL | ACTION_MACTIVITY);
 
        return 1;
    }

    oblist = parse_this(how[0], "[to] / [before] [the] %i",
        ACTION_PROXIMATE | ACTION_VISUAL | ACTION_MACTIVITY);

    if (!sizeof(oblist))
    {
        if (strlen(parse_msg))
        {
            write(parse_msg);

            return 1;
        }

        notify_fail("Clcurtsey [how] to whom/what?\n");

        return 0;
    }

    actor("You"
        + how[1]
        + " curtsey to", oblist,", displaying a hint of celtic heritage.");
    all2actbb(""
        + how[1]
        + " curtseys to", oblist, ", displaying a hint of celtic heritage.",
        how[1], ACTION_PROXIMATE | ACTION_VISUAL | ACTION_MACTIVITY);
    targetbb(""
        + how[1]
        + " curtseys before you, displaying a hint of celtic heritage.",
        oblist, how[1], ACTION_PROXIMATE | ACTION_VISUAL | ACTION_MACTIVITY);

        return 1;
}

int
cldecline(string str)
{
    object *oblist;

    oblist = parse_this(str, "[the] %l");

    if (!sizeof(oblist))
    {
        if (strlen(parse_msg))
        {
            write(parse_msg);

            return 1;
        }

        notify_fail("Cldecline whom?\n");

        return 0;
    }

    actor("You decline", oblist, " offer with a slight gesture.", 1);
    all2act(" declines", oblist, " offer with a slight gesture.", 0, 0, 1);
    target(" declines your offer with a slight gesture.", oblist, "",
        ACTION_INGRATIATORY);

    return 1;
}

int
clfrown(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, "in deep displeasure", 0);

    if (!stringp(how[0]))
    {
        SOULDESC("frowning" + how[1]);
        write("Your stern features frown"
            + how[1]
            + ".\n");
        allbb(" stern features frown"
            + how[1]
            + ".",
            how[1], 0, 1);

        return 1;
    }

    oblist = parse_this(how[0], "[at] [the] %i");

    if (!sizeof(oblist))
    {
        notify_fail("Frown [how] at whom/what?\n");

        return 0;
    }

    SOULDESC("frowning" + how[1]);
    actor("Your stern features frown"
        + how[1]
        + " at", oblist);
    all2actbb(" stern features frown"
        + how[1]
        + " at", oblist, 0, how[1], 0, 0, 1);
    targetbb(" stern features frown"
        + how[1]
        + " at you.", oblist, how[1], 0, 1);

    return 1;
}

int
clgiggle(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, "slightly", 0);

    if (!stringp(how[0]))
    {
        SOULDESC("giggling" + how[1]);
        write("You giggle"
            + how[1]
            + " with a glint of amusement dancing in your eyes.\n");
        allbb(" giggles"
            + how[1]
            + " with a glint of amusement dancing in "
            + HIS(TP)
            + " eyes.",
            how[1]);

        return 1;
    }

    oblist = parse_this(how[0], "[at] [the] %i");

    if (!sizeof(oblist))
    {
        notify_fail("Clgiggle [how] at whom/what?\n");

        return 0;
    }

    SOULDESC("giggling" + how[1]);
    actor("You giggle"
        + how[1]
        + " with a glint of amusement dancing in your eyes at",
        oblist);
    all2actbb(" giggles"
        + how[1]
        + " with a glint of amusement dancing in "
        + HIS(TP)
        + " eyes at",
        oblist, 0, how[1]);
    targetbb(" giggles"
        + how[1]
        + " with a glint of amusement dancing in "
        + HIS(TP)
        + " eyes at you.",
        oblist, how[1]);

    return 1;
}

int
clgreet(string str)
{
    object *oblist;

    oblist = parse_this(str, "[the] %l");

    if (!sizeof(oblist))
    {
        if (strlen(parse_msg))
        {
            write(parse_msg);

            return 1;
        }

        notify_fail("Clgreet whom?\n");

        return 0;
    }

    actor("You grasp", oblist, " by the forearms in a sign of greetings.");
    all2act(" grasps", oblist, " by the forearms in a sign of greetings.");
    target(" grasps you by the forearms in a sign of greetings.",
        oblist, "");

    return 1;
}

int
clgrin(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, "slightly", 0);

    if (!stringp(how[0]))
    {
        write("You grin"
            + how[1]
            + ", a strange glint in "
            + HIS(TP)
            + " eye.\n");
        allbb(" grins"
            + how[1]
            + ", a strange glint in "
            + HIS(TP)
            + " eye.\n",
            how[1], ACTION_VISUAL | ACTION_MACTIVITY);

        return 1;
    }

    oblist = parse_this(how[0], "[to] / [before] [the] %i",
        ACTION_PROXIMATE | ACTION_VISUAL | ACTION_MACTIVITY);

    if (!sizeof(oblist))
    {
        if (strlen(parse_msg))
        {
            write(parse_msg);

            return 1;
        }

        notify_fail("Clgrin [how] to whom/what?\n");

        return 0;
    }

    actor("Your grin"
        + how[1]
        + " to", oblist,", a strange glint in your eyes.");
    all2actbb(" grins"
        + how[1]
        + "  before",
        oblist,
        ", a strange glint in "
         + HIS(TP)
         + " eye.\n",
        how[1], ACTION_PROXIMATE | ACTION_VISUAL | ACTION_MACTIVITY);
    targetbb(" grins"
        + how[1]
        + " at you"
        + ", a strange glint in "
        + HIS(TP)
        + " eye.\n",
        oblist, how[1], ACTION_PROXIMATE | ACTION_VISUAL | ACTION_MACTIVITY);

    return 1;
}

public int
clhelp(string str)
{
    string filename, subject, text;

    if (!str)
    {
        subject = "index";
    }
    else if (sscanf(str, "%s", subject) != 1)
    {
        notify_fail("There is no help section for that subject.\n");

        return 0;
    }

    filename = HELP + subject;

    if (file_size(filename) > 0)
    {
        setuid();
        seteuid(getuid());

        text = read_file(filename);

        this_player()->more(text);

        return 1;
    }

    notify_fail("There is no help section for that subject.\n");

    return 0;
}

int
clhome()
{
    write("You gaze off into the distance as you recall your home.\n");
    allbb(" gazes off into the distance.");

    return 1;
}

int
cllaugh(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, "slightly", 0);

    if (!stringp(how[0]))
    {
        SOULDESC("laughing" + how[1]);
        write("You laugh"
            + how[1]
            + " with an unstable glint in your eye.\n");
        allbb(" laughs"
            + how[1]
            + " with an unstable glint in "
            + HIS(TP)
            + " eye.",
            how[1]);

        return 1;
    }

    oblist = parse_this(how[0], "[at] [the] %i");

    if (!sizeof(oblist))
    {
        notify_fail("Laugh [how] at whom/what?\n");

        return 0;
    }

    SOULDESC("laughing" + how[1]);
    actor("You laugh"
        + how[1]
        + " with an unstable glint in your eye at", oblist);
    all2actbb(" laughs"
        + how[1]
        + " with an unstable glint in "
        + HIS(TP)
        + " eye at",
        oblist, 0, how[1]);
    targetbb(" laughs"
        + how[1]
        + " with an unstable glint in "
        + HIS(TP)
        + " eye at you.",
        oblist, how[1]);

    return 1;
}

int
cllook(string str)
{
    object *oblist;

    if (!stringp(str))
    {
        write("You look towards the distance with unrest.\n");
        allbb(" looks towards the distance with concern etched in "
            + HIS(TP)
            + " stern features.");

        return 1;
    }

    oblist = parse_this(str, "[at] [the] %i");

    if (!sizeof(oblist))
    {
        notify_fail("Look at whom/what?\n");

        return 0;
    }

    actor("You look at", oblist, " with concern.");
    targetbb(" looks at you with concern etched in "
        + HIS(TP)
        + " stern features.",
        oblist);
    all2actbb(" looks at", oblist, " with concern etched in "
        + HIS(TP)
        + " stern features.");

    return 1;
}

int
clnod(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, "thoughtfully", 0);

    if (!stringp(how[0]))
    {
        write("You pause briefly and then nod"
            + how[1]
            + ".\n");
        allbb(" pauses briefly and then nods"
            + how[1]
            + ".",
            how[1]);
        SOULDESC("nodding" + how[1]);

        return 1;
    }

    oblist = parse_this(how[0], "[at] [the] %i");

    if (!sizeof(oblist))
    {
        notify_fail("Nod [how] at whom/what?\n");

        return 0;
    }

    SOULDESC("nodding" + how[1]);
    actor("You pause briefly and then nod"
        + how[1]
        + " at",
        oblist);
    all2actbb(" pauses briefly and then nods"
        + how[1]
        + " at",
        oblist, 0, how[1]);
    targetbb(" pauses briefly and then nods"
        + how[1]
        + " at you.",
        oblist, how[1]);

    return 1;
}

int
clsmile(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, "slightly", 0);

    if (!stringp(how[0]))
    {
        write("You smile"
            + how[1]
            + ", a mysterious glint in your eye.\n");
        allbb(" smiles"
            + how[1]
            + ", a mysterious glint in "
            + HIS(TP)
            + " eye.",
            how[1], ACTION_VISUAL | ACTION_MACTIVITY);

        return 1;
    }

    oblist = parse_this(how[0], "[to] / [before] [the] %i",
        ACTION_PROXIMATE | ACTION_VISUAL | ACTION_MACTIVITY);
 
    if (!sizeof(oblist))
    {
        if (strlen(parse_msg))
        {
            write(parse_msg);

            return 1;
        }

        notify_fail("Clsmile [how] to whom/what?\n");

        return 0;
    }

    actor("You smile"
        + how[1]
        + " to", oblist, ", a mysterious glint in your eye.");
    all2actbb(" smiles"
        + how[1]
        + " to", oblist, ", a mysterious glint in "
        + HIS(TP)
        + " eye.",
        how[1], ACTION_PROXIMATE | ACTION_VISUAL | ACTION_MACTIVITY);
    targetbb(" smiles"
        + how[1]
        + " before you, a mysterious glint in "
        + HIS(TP)
        + " eye.",
        oblist, how[1], ACTION_PROXIMATE | ACTION_VISUAL | ACTION_MACTIVITY);

    return 1;
}

int
clstand()
{
    write("You stand your ground.\n");
    allbb(" stands "
        + HIS(TP)
        + " ground.");

    return 1;
}

int
cltear(string str)
{
    str = check_adverb_with_space(str, "silently");

    if (str == NO_ADVERB_WITH_SPACE)
    {
        notify_fail("Cry how?\n");

        return 0;
    }

    SOULDESC("crying" + str);
    write("A single tear"
        + str
        + " rolls down your cheek.\n");
    allbb(" looks up and a single tear"
        + str
        + " rolls down "
        + HIS(TP)
        + " cheek.",
        str, ACTION_MACTIVITY | ACTION_VISUAL);

    return 1;
}

int
clwarcry(string str)
{
    object *oblist;

    if (!stringp(str))
    {
        write("You shout the ancient war cry: 'Faugh a Ballagh!'\n");
        allbb(" shouts an ancient war cry: 'Faugh a Ballagh!'");

        return 1;
    }

    oblist = parse_this(str, "[at] [the] %i");

    if (!sizeof(oblist))
    {
        notify_fail("clwarcry at whom/what?\n");

        return 0;
    }

    actor("You shout the ancient war cry at", oblist, ": 'Faugh a Ballagh!'");
    targetbb(" shouts an ancient war cry at you: 'Faugh a Ballagh!'", oblist);
    all2actbb(" shouts an ancient war cry at", oblist, ": 'Faugh a Ballagh!'");

    return 1;
}

mixed
get_title(object who)
{
    if (!who->query_guild_member(GUILD_NAME))
    {
        return 0;
    }

    if (wildmatch("*jr", who->query_real_name()))
    {
        return 0;
    }

    if (who->query_wiz_level())
    {
        if (SECURITY->query_guild_is_master("Clans of Khalakhor", 
                                            who->query_real_name()))
        {
            return who->query_name();
        }

        return 0;
    }

    return who->query_name() + " " + who->query_guild_title_race();
}

int
clwho(string str)
{
    string *titles;

    titles = map(users() - ({ this_player() }), get_title) - ({ 0 });

    write("You touch the ground and listen close to what it says.\n\n");

    write("You raise up knowing "
        + (sizeof(titles) ? LANG_WNUM(sizeof(titles)) : "no")
        + " other clan member"
        + ((sizeof(titles) == 1) ? " is" : "s are")
        + " nearby.\n");

    map(titles, write @ &sprintf("- %-=70s\n", ));

    write("\n");

    return 1;
}

/**************************************************************************
 * clsay - say something in your racial tongue.
 */
string
race_text(string race, string text)
{
    string *words, to_print;
    int sentence_index, sentence_size;

    object player = previous_object(-1);
    int skill = player->query_skill(SS_LANGUAGE);

    /* Wizards, players of the same race and people with a generally
     * high education in languages will understand the racial speech.
     */
    if (player->query_wiz_level()
        || race == player->query_race_name()
        || skill >= LANGUAGE_ALL_RSAY)
    {
        return text;
    }

    /* Other players will only hear a part of the text. */
    skill -= LANGUAGE_MIN_RSAY;
    to_print = "";
    words = explode(text, " ");
    sentence_index = -1;
    sentence_size = sizeof(words);

    while(++sentence_index < sentence_size)
    {
        if (strlen(to_print))
            to_print += " ";

        if (skill > 0
            && random(LANGUAGE_ALL_RSAY - LANGUAGE_MIN_RSAY) <= skill)
        {
            to_print += words[sentence_index];
        }
        else
        {
            to_print += extract("....................", 1,
                strlen(words[sentence_index]));
        }
    }

    return to_print;
}

void
print_clsay(object *oblist, string say_string)
{
    string qcomp, output;

    qcomp = COMPOSITE_ALL_LIVE(oblist);

    if (this_player()->query_option(OPT_ECHO))
    {
        write("You speak in Gaelic to " + qcomp + ": " + say_string + "\n");
    }
    else
    {
        write("Ok.\n");
    }

    /* How much of this text is seen depends on the language skill */
    output = "@@race_text:"
        + file_name(this_object())
        + "|"
        + this_player()->query_race_name()
        + "|"
        + say_string
        + "@@";

    say(QCTNAME(this_player())
        + " speaks in Gaelic to "
        + QCOMPLIVE
        + ": "
        + output
        + "\n", (oblist + ({ this_player() }) ));

    oblist->catch_msg(QCTNAME(this_player())
        + " speaks in Gaelic to you: "
        + output
        + "\n");
}

int
clsay(string str)
{
    int index;
    int skill;
    int size;
    int sentence_size;
    int sentence_index;
    mixed tmp;
    string to_print;
    string *words;
    object *oblist;

    string  race = this_player()->query_race_name();
    string  pos = this_player()->query_possessive();

    if (!objectp(environment(this_player())))
        return 0;

    if (!stringp(str))
    {
        notify_fail("Say what in your Gaelic language?\n");

        return 0;
    }

    if (tmp = this_player()->query_prop(LIVE_M_MOUTH_BLOCKED))
    {
        write(stringp(tmp) ? tmp : "You are gagged and cannot speak.\n");

        return 1;
    }

    if (wildmatch("to *", str)
        && say_to(extract(str, 3), &print_clsay()))
    {
        return 1;
    }

    if (this_player()->query_option(OPT_ECHO))
    {
        write("You speak in Gaelic: " + str + "\n");
    }
    else
    {
        write("Ok.\n");
    }

    say(QCTNAME(this_player())
        + " speaks in Gaelic: "
        + "@@race_text:"
        + file_name(this_object())
        + "|"
        + this_player()->query_race_name()
        + "|"
        + str
        + "@@\n");

    return 1;
}


void
print_say(string adverb, object *oblist, string say_string)
{
    string qcomp, r_sound;

    qcomp = COMPOSITE_ALL_LIVE(oblist);

    if (this_player()->query_option(OPT_ECHO))
    {
        write("You" + adverb + " " + this_player()->actor_race_sound() +
            " to " + qcomp + ": " + say_string + "\n");
    }
    else
    {
        write("Ok.\n");
    }

    r_sound = (" @@race_sound:" + file_name(this_player()) + "@@ to ");
    say(QCTNAME(this_player()) + adverb + r_sound + QCOMPLIVE + ": " +
        say_string + "\n", (oblist + ({ this_player() }) ));
    oblist->catch_msg(QCTNAME(this_player()) + adverb + r_sound + "you: " +
        say_string + "\n");
}

/*
 * Function name: say_to
 * Description  : This function is called whenever the player starts his
 *                say-string with 'to'. This usually indicates that the
 *                player wants to say something to some people in particular.
 *                All others will still hear it though.
 * Arguments    : string str - the text to say (not including 'to').
 *                string adverb - the adverb to use.
 * Returns      : int 1/0 - success/failure.
 */
public int
say_to(string str, function format)
{
    object *oblist;
    string r_sound;
    string qcomp;
    string say_string;

    /* We must parse the lower case of the string 'str' since parse_command
     * does not find capitalized player names, so it would not trigger on
     * "say to Mercade Greetings!" However, since we want to keep the
     * capitals in the said text, we store the original text in the variable
     * 'say_string' and use that later.
     */
    say_string = str;

    /* Whisper to all people. */
    if (wildmatch("all *", str))
    {
        str = extract(str, 4);
        oblist = FILTER_OTHER_LIVE(all_inventory(environment(this_player())));
    }
    /* Whisper to my team. */
    else if (wildmatch("team *", str))
    {
        str = extract(str, 5);
        oblist = this_player()->query_team_others()
            & all_inventory(environment(this_player()));
    }
    /* Find out who we talk to. */
    else if (!parse_command(lower_case(str),
                            environment(this_player()),
                            "[to] [the] %i %s", oblist, str))
    {
        notify_fail("Say [how] what to whom/what?\n");

       return 0;
    }
    else
    {
        oblist = NORMAL_ACCESS(oblist, 0, 0) - ({ this_player() });
    }

    if (!sizeof(oblist)
        || !strlen(str))
    {
        return 0;
    }

    say_string = extract(say_string, -(strlen(str)));
    this_player()->set_say_string(say_string);
    
    format(oblist, say_string);
    
    return 1;
}

/* **************************************************************************
 * say_text - say something to another player.
 *
 * This function is not called say() because of the simul-efun by that name.
 */
varargs int
say_text(string str, string adverb = "")
{
    mixed tmp;

    if (!strlen(str))
    {
        notify_fail("What do you wish to say?\n");

        return 0;
    }

    if (tmp = this_player()->query_prop(LIVE_M_MOUTH_BLOCKED))
    {
        write(stringp(tmp) ? tmp : "You are gagged and cannot speak.\n");

        return 1;
    }

    /* We do not want people to add too many spaces and use the say command
     * as a way to generate emotions themselves. However, we do not want to
     * waste this on wizards and we also test whether people haven't used
     * too many spaces. You cannot make an emotion with only a few. This
     * wildmatch is 40% faster than the explode/implode stuff, so as long
     * as people don't use 8 spaces more than 40% of the time, this check
     * pays itself back.
     */
    if (!this_player()->query_wiz_level()
        && wildmatch("*       *", str))
    {
        str = implode((explode(str, " ") - ({ "" }) ), " ");
    }

    /* This is a test for the command 'say to'. If it fails, we just default
     * to the normal say.
     */
    if (wildmatch("to *", str)
        && say_to(extract(str, 3), &print_say(adverb)))
    {
        return 1;
    }

    this_player()->set_say_string(str);

    if (this_player()->query_option(OPT_ECHO))
    {
        write("You"
            + adverb
            + " "
            + this_player()->actor_race_sound()
            + ": "
            + str
            + "\n");
    }
    else
    {
        write("Ok.\n");
    }

    say(QCTNAME(this_player())
        + adverb
        + " @@race_sound:"
        + file_name(this_player())
        + "@@: "
        + str
        + "\n");

    return 1;
}
