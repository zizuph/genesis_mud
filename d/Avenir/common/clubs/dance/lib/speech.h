/**********************************************************************
 * - speech.h                                                       - *
 * - Dancers breathy speak. Updated to be able to use targets.      - *
 * - Based on mudlib speech.c                                       - *
 * - Created by Damaris@Genesis 03/2006                             - *
 **********************************************************************/

/*
 * Prototype.
 */
varargs int say_text(string str, string sayadv = "");
public int say_to(string str, function format);

string
dsay_adverb()
{
    string *words = ({ "seductively", "softly", "charmingly", "huskily", 
           "provocatively", "bewitchingly", "persuasively", "sweetly", 
           "suggestively", "casually", "languidly", "thrillingly", 
           "tenderly", "amorously", "delectably", "delightfully" });
    return words[random(sizeof(words))];
}
    
string
dance_text(string text)
{
    object player = previous_object(-1);
    string *words, to_print;
    int sentence_index, sentence_size;

    to_print = "";

    words = explode(text, " ");
    sentence_index = -1;
    sentence_size = sizeof(words);
    
    while(++sentence_index < sentence_size)
    {
        if (strlen(to_print))
            to_print += " ";
        
    }
    
    return to_print;
}

void
print_dspeak(object *oblist, string say_string)
{
    string qcomp, sayadv;

    qcomp = COMPOSITE_ALL_LIVE(oblist);
    sayadv = dsay_adverb();
    if (this_player()->query_option(OPT_ECHO))
    {
        write("You "+ sayadv +" breath to " + qcomp + ": " + say_string + "\n");
    }
    else
    {
        write("Ok.\n");
    }

  
    say(QCTNAME(this_player()) + " "+ sayadv +" breathes to " + QCOMPLIVE + ": " +
        say_string + "\n", (oblist + ({ this_player() }) ));
    oblist->catch_msg(QCTNAME(this_player()) + " "+ sayadv +" breathes to you: " + say_string + "\n");
}

int
dspeak(string str)
{
    int     index;
    int     size;
    mixed   tmp;
    object *oblist;
    string  pos = this_player()->query_possessive();
    string  *words;
    int     sentence_size;
    int     sentence_index;
    string  to_print;
    string  sayadv;
    sayadv = dsay_adverb();
    
    if (!objectp(environment(this_player())))
    {
        return 0;
    }

    if (!stringp(str))
    {
        notify_fail("Say what in the breathy speech of the Dancers?\n");
        return 0;
    }
    
    if (tmp = this_player()->query_prop(LIVE_M_MOUTH_BLOCKED))
    {
        write(stringp(tmp) ? tmp : "You are gagged and cannot speak.\n");
        return 1;
    }

    if (wildmatch("to *", str))
    {
        if (say_to(extract(str, 3), &print_dspeak()))
        {
            return 1;
        }
    }

    if (this_player()->query_option(OPT_ECHO))
        write("You "+ sayadv +" breathe: " + str + "\n");
    else
        write("Ok.\n");

    say(QCTNAME(this_player()) + " "+ sayadv +" breathes: " + str + "\n");
    
    return 1;
}


void
print_say(string sayadv, object *oblist, string say_string)
{
    string qcomp;

    qcomp = COMPOSITE_ALL_LIVE(oblist);
    sayadv = dsay_adverb();
    if (this_player()->query_option(OPT_ECHO))
    {
        write("You" + sayadv + " breathe to " + qcomp + ": " + say_string + "\n");
    }
    else
    {
        write("Ok.\n");
    }

    say(QCTNAME(this_player()) + sayadv + " breathes: " +
        say_string + "\n", (oblist + ({ this_player() }) ));
    oblist->catch_msg(QCTNAME(this_player()) + sayadv + "breathes you: " +
        say_string + "\n");
}

/*
 * Function name: say_to
 * Description  : This function is called whenever the player starts his
 *                say-string with 'to'. This usually indicates that the
 *                player wants to say something to some people in particular.
 *                All others will still hear it though.
 * Arguments    : string str - the text to say (not including 'to').
 *                string sayadv - the sayadv to use.
 * Returns      : int 1/0 - success/failure.
 */
public int
say_to(string str, function format)
{
    object *oblist;
    string qcomp;
    string say_string;

    /* We must parse the lower case of the string 'str' since parse_command
     * does not find capitalized player names, so it would not trigger on
     * "say to Mercade Greetings!" However, since we want to keep the
     * capitals in the said text, we store the original text in the variable
     * 'say_string' and use that later.
     */
    say_string = str;

    /* Speak to all people. */
    if (wildmatch("all *", str))
    {
        str = extract(str, 4);
        oblist = FILTER_OTHER_LIVE(all_inventory(environment(this_player())));
    }
    /* Speak to my team. */
    else if (wildmatch("team *", str))
    {
        str = extract(str, 5);
        oblist = this_player()->query_team_others() &
            all_inventory(environment(this_player()));
    }
    /* Find out who we talk to. */
    else if (!parse_command(lower_case(str), environment(this_player()),
        "[to] [the] %i %s", oblist, str))
    {
        notify_fail("Say what in the breathy speech of the Dancers?\n");
        return 0;
    }
    else
    {
        oblist = NORMAL_ACCESS(oblist, 0, 0) - ({ this_player() });
    }

    if (!sizeof(oblist) ||
        !strlen(str))
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
say_text(string str, string sayadv = "")
{
    mixed tmp;
    sayadv = dsay_adverb();
    if (!strlen(str))
    {
        notify_fail("Say what in the breathy speech of the Dancers?\n");
        return 0;
    }

    if (tmp = this_player()->query_prop(LIVE_M_MOUTH_BLOCKED))
    {
        write(stringp(tmp) ? tmp : "You are gagged and cannot speak.\n");
        return 1;
    }

    if (!this_player()->query_wiz_level() &&
        wildmatch("*       *", str))
    {
        str = implode((explode(str, " ") - ({ "" }) ), " ");
    }

    if (wildmatch("to *", str))
    {
        if (say_to(extract(str, 3), &print_say(sayadv)))
        {
            return 1;
        }
    }

    this_player()->set_say_string(str);
    if (this_player()->query_option(OPT_ECHO))
    {
        write("You" + sayadv + " breathe: " + str + "\n");
    }
    else
    {
        write("Ok.\n");
    }

    say(QCTNAME(this_player()) + sayadv + " breathes: " + str + "\n");
    return 1;
}
