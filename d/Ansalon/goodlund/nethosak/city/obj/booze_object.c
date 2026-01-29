/*
 * - slurred_speech.c
 *
 *   This tool will take normal speech, and turn it into a
 *   drunken slur.
 *
 *   Read the header for the 'do_slur()' function for more info.
 *
 * Original Coder: Satyrane 12/1995
 * Revised by    : Lucius   02/2000
 */
#pragma strict_types

inherit "/std/object";
inherit "/lib/commands";

#include <adverbs.h>
#include <files.h>
#include <state_desc.h>
#include <stdproperties.h>

#define DEFAULT_TIME    120  /* In seconds (2 minutes) */

private static int time, alarm;

public void
create_object()
{
    set_name("slurred_speech");
    set_long("This is an object to slur a persons speech.\n");
    set_no_show();
}

public void
remove_object()
{
    if (alarm)
        remove_alarm(alarm);

    ::remove_object();
}

/*
 * Function name: stop_slurring
 * Description  : This function will stop slurring and remove this object.
 */
public void
stop_slurring()
{
    alarm = 0;
    remove_object();
}

/*
 * Function name: start_slurring
 * Description  : Set the alarm to begin slurring a person speech.
 *
 * Notes        : If this is called, and set_drunk_time() not set,
 *                a default length will be used as defined at the
 *                top of this file.
 *
 *                Additional calls to this will only increase
 *                the amount of time the alarm is active.
 *                The time value gets sets to 0, and the default
 *                value used for additional calls, unless you reset
 *                the drunk_time.  Use this to extend the length of
 *                drunkennes rather then clone a new object for 
 *                each sip from a single source.
 */
public void
start_slurring()
{
    if (alarm)
        remove_alarm(alarm);

    if (!time)
        time = DEFAULT_TIME;

    alarm = set_alarm(itof(time), 0.0, &stop_slurring());
    time  = 0;
}

/*
 * Function name: set_drunk_time
 * Description  : How long should the possessor of this item
 *                have slurred speech for.  (in seconds)
 * Arguments    : int - The length in seconds. If < 1, immediately destruct.
 */
public void
set_drunk_time(int i)
{
    if (time < 1)
        stop_slurring();

    time = i;
} 

/*
 * Function name: intoxicated
 * Description  : See if the player is 'obliviated'.
 *                From the 'vitals intox' command.
 * Returns      : int - 1, Yes - 0, No.
 */
private int
intoxicated()
{
    int value1, value2;
    string intox;

    value1 = environment()->query_prop(LIVE_I_MAX_INTOX);
    value2 = environment()->query_intoxicated();
    value1 = (120 * value2 / ((value1 != 0) ? value1 : value2));
    intox  = CMD_LIVE_STATE->get_proc_text(value1, SD_INTOX, 0);
    return wildmatch("*obliv*", intox);
}

/*
 * Function name: do_slur
 * Description  : Convert normal text to slurred speech.
 * Arguments    : string - What the player is attempting to say.
 * Returns      : int - 1, we slurred the speech.
 *                      0, let them speek normally.
 *
 * Notes        : If you set the drunk time, set_drunk_time(int i),
 *                and call 'start_slurring()' in this object, slurring
 *                will be active until the alarm expires, whereupon this
 *                object will be deleted.  Otherwise, it checks to see if
 *                a person is in an 'obliviated' state before their speech
 *                becomes slurred.  If you don't use the alarm method,
 *                you must handle the destruction of this object on your own.
 */
public int
do_slur(string str) 
{
    int i = -1, j = 0, changed;
    string *estr, *how, verb, sayto;

    if (!str || str == "")
        return 0;

    if (!living(environment()))
        return 0;

    if (!alarm && !intoxicated())
        return 0;

    verb = query_verb();

    if ((verb == "asay") || (verb == "a'"))
    {
        how = parse_adverb_with_space(str, NO_DEFAULT_ADVERB, 0);
        if (strlen(how[0]) && how[1] != NO_DEFAULT_ADVERB_WITH_SPACE)
            str = how[0];
        else
            how[1] = NO_ADVERB;
    }

    estr = explode(str, " ") - ({ "" });

    if (estr[0] == "to")
    {
        sayto = implode(estr[0..1], " ");
        estr -= estr[0..1];
    }

    str = implode(estr, " ");
    j   = sizeof(estr = explode(str, ""));

    while( ++i < j)
    {
        if (random(2))
            continue;

        if (estr[i] != lower_case(estr[i]))
        {
            changed = 1;
            estr[i] = lower_case(estr[i]);
        }

        switch (estr[i])
        {
        case "a":
            estr[i] = ({"ah", "a", "eh"})[random(3)];
            break;

        case "b":
            estr[i] = ({"b", "bh"})[random(2)];
            break;

        case "d":
            estr[i] = ({"d", "dh"})[random(2)];
            break;

        case "e":
            estr[i] = ({"e", "ae"})[random(2)];
            break;

        case "f":
            estr[i] = ({"f", "ph", "phf"})[random(3)];
            break;

        case "h":
            estr[i] = ({"h", "hh", " *hic* "})[random(3)];
            break;

        case "j":
            estr[i] = ({"j", "g", "zh", "jh"})[random(4)];
            break;

        case "k":
            estr[i] = ({"k", "ck", "kh"})[random(3)];
            break;

        case "l":
            estr[i] = ({"l", "ll", "el"})[random(3)];
            break;

        case "o":
            estr[i] = ({"o", "oh"})[random(2)];
            break;

        case "p":
            estr[i] = ({"p", "ph", "pf"})[random(3)];
            break;

        case "r":
            estr[i] = ({"r", "re", "rr"})[random(3)];
            break;

        case "s":
            estr[i] = ({"s", "sh", "csh", "ss"})[random(4)];
            break;

        case "t":
            estr[i] = ({"t", "d", "dh"})[random(3)];
            break;

        case "u":
            estr[i] = ({"u", "uh"})[random(2)];
            break;

        case "w":
            estr[i] = ({"w", "wh"})[random(2)];
            break;

        case "z":
            estr[i] = ({"z", "zsh", "tsch", "zz", "ts"})[random(5)];
            break;
        }

        if (changed)
        {
            changed = 0;
            estr[i] = capitalize(estr[i]);
        }
    }

    if (sayto)
        str = sayto + " ";
    else
        str = "";

    str += implode(estr, "");

    CMD_LIVE_SPEECH->say_text(str, " drunkenly");
    return 1;
}

public void
init()
{
    ::init();

    if (environment() != this_player())
        return;

    add_action( do_slur, "a'", 2 );
    add_action( do_slur, "asay"  );
    add_action( do_slur, "'", 2  );
    add_action( do_slur, "say"   );
}

