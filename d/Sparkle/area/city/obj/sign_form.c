/*
 *  /d/Sparkle/area/city/obj/sign_form.c
 *
 *  This object is given out by Carlsan Fountaine, the Town Crier
 *  as part of the Sign Rating quest in Sparkle.
 *
 *  Using it, players may rate signs in Sparkle to complete the
 *  Quest.
 *
 *  Note: If new signs are added to Sparkle, they can be incorporated
 *        into this quest by adding the room location of the sign to
 *        the global variable SRoom and the name of the establishment
 *        that owns the sign to the global variable Ratings. Then, in
 *        the actual read_sign() function in the room itself, the
 *        following function call would need to be made with the second
 *        argument corresponding to an actual sign name (as it appears
 *        in the Ratings array). e.g:
 *
 *        check_rating_form(this_player(), "post office");
 *
 *  Created March 2011, by Cooper Sherry (Gorboth)
 */

#pragma strict_types

inherit "/std/object";

#include <language.h>
#include <macros.h>
#include <stdproperties.h>
#include "../defs.h"

/* Definitions */
#define     SPATH            ("/d/Sparkle/area/city/rooms/streets/")
#define     SIGN_RATING_PROP ("_sparkle_sign_rating_prop")
#define     RATINGS_FILE     ("sign_ratings")

/* Global Variables */

/* This mapping tells us the room in which a sign can be found. */
public mapping  SRoom   = ([ "church"           : SPATH + "center_f",
                             "bank"             : SPATH + "center_g",
                             "donations office" : SPATH + "market_square",
                             "general store"    : SPATH + "market_square",
                             "library"          : SPATH + "center_f",
                             "adventurer guild" : SPATH + "center_e",
                             "museum"           : SPATH + "center_e",
                             "archives"         : SPATH + "center_b",
                             "enchanter's shop" : SPATH + "center_b",
                             "post office"      : SPATH + "center_a",
                             "inn"              : SPATH + "center_a",
                          ]);

/* This mapping stores the ratings (readability, attractiveness) */
public mapping  Ratings = ([ "church"           : ({ 0, 0 }),
                             "bank"             : ({ 0, 0 }),
                             "donations office" : ({ 0, 0 }),
                             "general store"    : ({ 0, 0 }),
                             "library"          : ({ 0, 0 }),
                             "adventurer guild" : ({ 0, 0 }),
                             "museum"           : ({ 0, 0 }),
                             "archives"         : ({ 0, 0 }),
                             "enchanter's shop" : ({ 0, 0 }),
                             "post office"      : ({ 0, 0 }),
                             "inn"              : ({ 0, 0 }),
                          ]);

public string  *Ratings_Index = m_indexes(Ratings);

public mapping  query_ratings() { return Ratings; }

/* Prototypes */
public void     create_object();
public void     init();
public string   describe();
public string   print_form_line(string sign);
public int      finished_form();
public int      do_rate(string arg);
public void     make_rating(string arg, string sign, int which, object who);
public void     set_sign_rating_prop(object who, string arg);
public void     check_finished_msg(object who);
public void     consider_sign(object who, string sign);
public void     record_ratings();
public string   display_ratings();
public float    check_for_duplicates(float current, mixed *f_arr);
public int      submit_form(string arg);


/*
 * Function name:        create_object
 * Description  :        The constructor
 */
public void
create_object()
{
    set_name("form");
    add_name(RATING_FORM);
    add_name("survey");
    add_adj( ({ "sign", "rating", "survey" }) );

    set_short("sign rating form");
    set_long("@@describe@@");

    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_M_NO_SELL, "That would not be a good idea.\n");
    add_prop(OBJ_M_NO_DROP, "You'd better hang on to that. If you have"
      + " completed the form, you can <submit> it to Carlsan.\n");
    add_prop(OBJ_I_VOLUME, 2);
    add_prop(OBJ_I_WEIGHT, 1);

    add_cmd_item( ({ "form", "rating form", "sign form",
                     "sign rating form" }),
                  ({ "read" }), "@@describe@@");
    
    setuid();
    seteuid(getuid());
} /* create_object */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(do_rate, "rate");
    add_action(submit_form, "submit");
} /* init */


/*
 * Function name:        describe
 * Description  :        show the player the form when they look at it
 *                       with dynamically generated information based on
 *                       the completion level of their quest.
 * Returns      :        string - the result for them to read
 */
public string
describe()
{
    string  form_txt;

    form_txt =
      "  ,------------------------------------------------------------,.\n"
    + "  ---.---------------------------------------------------------  \\\n"
    + "     |                                                            |\n"
    + "     |   Please rate the lettering of the signs of Old Town in    |\n"
    + "     |   Sparkle so we can improve our craft for future custo-    |\n"
    + "     |   mers. We very much appreciate it!                        |\n"
    + "     |                                                            |\n"
    + "     |   Signed, Chadwick Fountaine, Master Engraver              |\n"
    + "     |                                                            |\n"
    + "     | ========================================================== |\n"
    + "     |  Sign              Readability          Attractiveness     |\n"
    + "     | ========================================================== |\n";

    foreach(string this_rating : Ratings_Index)
    {
        form_txt += print_form_line(this_rating);
    }

    form_txt +=
      "     | ========================================================== |\n"
    + "     |                                                            |\n"
    + "     |   To find a sign, <exa map> to see where the building is.  |\n"
    + "     |   When outside the building, <read sign> to read it.       |\n"
    + "     |   Upon reading a sign, you may give it a rating using      |\n"
    + "     |   <rate readability> or <rate attractiveness>.             |\n"
    + "     |                                                            |\n"
    + "     |   When you have completed the form, you may <submit> it    |\n"
    + "     |   to Carlsan for a small reward.                           |\n"
    + "     |                                                            |\n"
    + "  -------------------------------------------------------------. /\n"
    + "  `-------------------------------------------------------------`\n\n";

    set_alarm(0.5, 0.0, &check_finished_msg(this_player()));

    return form_txt;
} /* describe */


/*
 * Function name:        print_form_line
 * Description  :        print out a line for the form based on one of
 *                       the signs that needs rating.
 * Arguments    :        string sign - which sign to check
 * Returns      :        string - the line text to print
 */
public string
print_form_line(string sign)
{
    string  line_txt;
    string *sign_words = explode(sign, " ");
    string *new_sign_words = ({ });
    string  sign_name;
    string  readability     = Ratings[sign][0] + "";
    string  attractiveness  = Ratings[sign][1] + "";
    string  unrated         = "(not yet rated)";

    foreach(string sign_word: sign_words)
    {
        new_sign_words += ({ capitalize(sign_word) });
    }

    sign_name = new_sign_words[0];

    if (sizeof(new_sign_words) > 1)
    {
        sign_name += " " + new_sign_words[1];
    }

    line_txt = "     |  " + sprintf("%-16s", sign_name);

    line_txt += sprintf("%-21s", "  "
             + (Ratings[sign][0] ? "    "
             + sprintf("%2s", readability) : unrated));

    line_txt += sprintf("%-21s", "  "
             + (Ratings[sign][1] ? "    "
             + sprintf("%2s", attractiveness) : unrated)) + "|\n";

    return line_txt;
} /* print_form_line */


/*
 * Function name:        finished_form
 * Description  :        See if the player has completed the rating
 *                       form.
 * Returns      :        int 1 - completed
 *                       int 0 - not yet completed
 */
public int
finished_form()
{
    int    finished = 1;

    foreach(string this_rating : Ratings_Index)
    {
        if (!Ratings[this_rating][0] ||
            !Ratings[this_rating][1])
        {
            finished = 0;
        }
    }

    return finished;
} /* finished_form */


/*
 * Function name:        do_rate
 * Description  :        Allow players to rate a sign if they have just
 *                       read it and are still standing in the correct
 *                       room.
 * Arguments    :        string arg - what the player typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
do_rate(string arg)
{
    string  sign = this_player()->query_prop(SIGN_RATING_PROP);
    string  room = file_name(environment(this_player()));
    string  word;

    notify_fail("You can either <rate readability> or"
     + " <rate attractiveness> with the form.\n");

    if (!strlen(arg))
    {
        return 0;
    }

    if (arg != "readability" &&
        arg != "attractiveness")
    {
        if (parse_command(arg, ({}),
            "'readability' / 'attractiveness' %w", word))
        {
            write("You should simply <rate readability> or"
              + " <rate attractiveness>. You will then be prompted for"
              + " the rating itself.\n");
            return 1;
        }

        return 0;
    }

    if (!sign)
    {
        write("You would need to find and read one of the signs"
          + " first. Even if you had seen it before, working from"
          + " memory isn't likely to provide a very accurate rating.\n");
        return 1;
    }

    if (SRoom[sign] != room)
    {
        write("You would need to be looking at the sign in order to"
          + " give it an accurate rating. Perhaps you should go back"
          + " and stand outside the " + sign + " again before trying"
          + " it. Or, perhaps you are trying to rate a different sign?"
          + " If so, just find and look at the sign you want to rate.\n");
        return 1;
    }

    write("Please rate the " + sign + " for its sign on a scale of 1-10,"
      + " with 10 being the highest level of " + arg + " and 1 being"
      + " the lowest.\n\nEnter your rating (1-10): ");

    input_to(&make_rating( , sign, (arg == "attractiveness"), this_player()));
    return 1;
} /* do_rate */


/*
 * Function name:        make_rating
 * Description  :        Register the actual rating the player has
 *                       made.
 * Arguments    :        string arg   - the rating
 *                       string sign  - the sign the rating is for
 *                       int which    - 0 for readability
 *                                      1 for attractiveness
 *                       object who   - the player in question
 */
public void
make_rating(string arg, string sign, int which, object who)
{
    int     rating = atoi(arg);

    who->catch_msg("\n"); /* for readability */

    if (!rating ||
         rating > 10)
    {
        who->catch_msg("You must choose a rating between 1 and"
          + " 10.\n");
        return;
    }

    tell_room(environment(who), QCTNAME(who) + " makes a note on a form "
      + this_player()->query_pronoun() + " is holding.\n", who);

    if (Ratings[sign][which])
    {
        if (Ratings[sign][which] == rating)
        {
            who->catch_msg("You have already rated the sign on the "
              + sign + " with a " + rating + " for "
              + (which ? "attractiveness" : "readability")
              + " ... no need to belabour the point.\n");
            return;
        }

        who->catch_msg("You change the score for the sign on the "
          + sign + "," + " giving it "
          + LANG_ADDART(which ? "attractiveness" : "readability")
          + " rating of " + rating + " instead.\n");
    }
    else
    {
        who->catch_msg("You give the sign on the " + sign + " a rating of "
          + rating + " for " + (which ? "attractiveness" : "readability")
          + ", and mark your form accordingly.\n");
    }

    Ratings[sign][which] = rating;

    set_alarm(0.5, 0.0, &check_finished_msg(who));

    return;
} /* make_rating */


/*
 * Function name:        set_sign_rating_prop
 * Description  :        Allow an external call to this object to set a
 *                       prop in the player when they read a sign.
 * Arguments    :        object who - the player
 *                       string arg - the value for the prop
 */
public void
set_sign_rating_prop(object who, string arg)
{
    who->add_prop(SIGN_RATING_PROP, arg);
} /* set_sign_rating_prop */


/*
 * Function name:        check_finished_msg
 * Description  :        If the player has finished rating their form,
 *                       we print a special message.
 * Arguments    :        object who - the player
 */
public void
check_finished_msg(object who)
{
    if (finished_form())
    {
        who->catch_msg("\nIt looks as if you have finished rating all of"
          + " the signs. You can now return to Carlsan and <submit"
          + " form>.\n");
    }

    return;
} /* check_finished_msg */


/*
 * Function name:        consider_sign
 * Description  :        Print a message to the player if they are
 *                       reading a sign and working on the quest.
 * Arguments    :        object who  - the player
 *                       string sign - which sign they are considering
 */
public void
consider_sign(object who, string sign)
{
    string  s = "sign hanging in front of the " + sign;
    string  end = " Simply <rate> it now on your form, if you like.\n";

    tell_room(environment(who), QCTNAME(who) + " peers up at the " + s
      + ", considering it carefully.\n", who);

    if (!Ratings[sign][0] &&
        !Ratings[sign][1])
    {
        who->catch_tell("You peer up at the " + s + ", considering it for"
          + " its various qualities of readability and attractiveness."
          + end);
        return;
    }

    if (Ratings[sign][0] &&
        Ratings[sign][1])
    {
        who->catch_tell("You peer up at the " + s + ", considering the"
          + " ratings you have already given it. You could probably"
          + " give new ratings if you felt they should change." + end);
        return;
    }

    if (Ratings[sign][0])
    {
        who->catch_tell("You peer up at the " + s + ", considering it for"
          + " its level of attractiveness." + end);
        return;
    }

    who->catch_tell("You peer up at the " + s + ", considering it for its"
          + " level of readability." + end);
    return;
} /* consider_sign */


/*
 * Function name:        record_ratings
 * Description  :        Take the ratings and have them added to the
 *                       datafile that tracks all that have been recorded
 */
public void
record_ratings()
{
    int    *old_ratings;
    int    *new_ratings;
    int     readability;
    int     attractiveness;
    int     count;
    string  index_name;

    foreach(string which_rating : Ratings_Index)
    {
        index_name = implode(explode(which_rating, " "), "_");
        old_ratings = VENDOR->get_info(RATINGS_FILE, index_name);
        new_ratings = Ratings[which_rating];

        if (!sizeof(old_ratings))
        {
            VENDOR->set_info(RATINGS_FILE, index_name,
                ({ new_ratings[0], new_ratings[1], 1 }) );
        }
        else
        {
            readability    = old_ratings[0] + new_ratings[0];
            attractiveness = old_ratings[1] + new_ratings[1];
            count          = old_ratings[2];
            count++;

            VENDOR->set_info(RATINGS_FILE, index_name,
                ({ readability, attractiveness, count }) );
        }
    }

    return;
} /* record_ratings */


/*
 * Function name:        display_ratings
 * Description  :        Print a display of the signs listed in rank
 *                       order according to Readability, Attractiveness,
 *                       and Combined Score.
 * Returns      :        string - the text to display
 */
public string
display_ratings()
{
    string   display_txt = "";
    string   sign_name;
    string  *sign_words;
    string  *new_sign_words = ({});
    float    readability;
    float    attractiveness;
    float    combined;
    mapping  readability_ratings = ([]);
    mapping  attractiveness_ratings = ([]);
    mapping  combined_ratings = ([]);
    mixed   *readability_order = ({});
    mixed   *attractiveness_order = ({});
    mixed   *combined_order = ({});
    mixed   *readability_rankings = ({});
    mixed   *attractiveness_rankings = ({});
    mixed   *combined_rankings = ({});
    mixed   *this_array;
    string  *rating_indices = ({});
    string   index_name;
    int      participants;
    string   surveys;
    int      i = 0;

    /* First, we populate the various ratings arrays with arrays containing:
     *   0 - which_rating (the name of the sign)
     *   1 - the respective rating that the array should consider
     */
    foreach(string which_rating : Ratings_Index)
    {
        index_name = implode(explode(which_rating, " "), "_");

        if (!participants)
        {
            participants = VENDOR->get_info(RATINGS_FILE, index_name)[2];
        }

        readability    = 
            itof(VENDOR->get_info(RATINGS_FILE, index_name)[0]) /
            itof(VENDOR->get_info(RATINGS_FILE, index_name)[2]);
        attractiveness = 
            itof(VENDOR->get_info(RATINGS_FILE, index_name)[1]) /
            itof(VENDOR->get_info(RATINGS_FILE, index_name)[2]);
        combined       = readability + attractiveness;      

        /* Because we are referencing the mapping by the float value,
         * we have to make sure there are no duplicate indexes.
         */
        if (sizeof(m_indices(readability_ratings)))
        {
            readability    = check_for_duplicates(readability, 
                             m_indices(readability_ratings));
            attractiveness = check_for_duplicates(attractiveness,
                             m_indices(attractiveness_ratings));
            combined       = check_for_duplicates(combined,
                             m_indices(combined_ratings));
        }

        readability_ratings    += ([ readability : which_rating ]);
        attractiveness_ratings += ([ attractiveness : which_rating ]);
        combined_ratings       += ([ combined : which_rating ]);

        /* We create these arrays for sorting purposes */
        readability_order      += ({ readability });
        attractiveness_order   += ({ attractiveness });
        combined_order         += ({ combined });
    } 

    /* First, lets get the arrays in ascending order */
    sort_array(readability_order);
    sort_array(attractiveness_order);
    sort_array(combined_order);

    /* Here, we reverse the order of the sorted arrays to get
     * descending order.
     */
    foreach(string this_rating : Ratings_Index)
    {
        i--;
        readability_rankings += ({ readability_order[i] });
        attractiveness_rankings += ({ attractiveness_order[i] });
        combined_rankings += ({ combined_order[i] });
    }

    /* Now, we'll recycle the *_order variables to create arrays that
     * hold the rank-ordered sign names for each index along with their
     * average score.
     */
    readability_order = ({});
    attractiveness_order = ({});
    combined_order = ({});

    foreach(float this_sign : readability_rankings)
    {
        new_sign_words = ({});
        sign_name  = readability_ratings[this_sign];
        sign_words = explode(sign_name, " ");

        foreach(string sign_word: sign_words)
        {
            new_sign_words += ({ capitalize(sign_word) });
        }

        sign_name = implode(new_sign_words, " ");

        readability_order += ({ ({ sign_name, ftoi(this_sign) }) });
    }

    foreach(float this_sign : attractiveness_rankings)
    {
        new_sign_words = ({});
        sign_name  = attractiveness_ratings[this_sign];
        sign_words = explode(sign_name, " ");

        foreach(string sign_word: sign_words)
        {
            new_sign_words += ({ capitalize(sign_word) });
        }

        sign_name = implode(new_sign_words, " ");

        attractiveness_order += ({ ({  sign_name, ftoi(this_sign) }) });
    }

    foreach(float this_sign : combined_rankings)
    {
        new_sign_words = ({});
        sign_name  = combined_ratings[this_sign];
        sign_words = explode(sign_name, " ");

        foreach(string sign_word: sign_words)
        {
            new_sign_words += ({ capitalize(sign_word) });
        }

        sign_name = implode(new_sign_words, " ");

        combined_order += ({ ({  sign_name, ftoi(this_sign) }) });
    }

    /* Now, we will assemble the printout the rankings */

    /* First the header. Increase screen width to view code properly. */
    display_txt += "\n"
      + " .---------------------------------------------------------------------------.\n"
      + "|                                                                             |\n"
      + "|              CURRENT RESULTS - OPINION POLLING ON CITY SIGNS                |\n"
      + "|                                                                             |\n"
      + "| =========================================================================== |\n"
      + "|     Readability   (avg.)     Attractiveness(avg.)     Overall        (avg.) |\n"
      + "| =========================================================================== |\n";

    /* Then, the individual lines. */
    i = 0;

    foreach(string s : Ratings_Index)
    {
        display_txt += "| "
                     + sprintf("%2d. ", (i + 1))
                     + sprintf("%-17s", readability_order[i][0])
                     + "(" + readability_order[i][1] + ") "
                     + sprintf("%2d. ", (i + 1))
                     + sprintf("%-17s", attractiveness_order[i][0])
                     + "(" + attractiveness_order[i][1] + ") "
                     + sprintf("%2d. ", (i + 1))
                     + sprintf("%-17s", combined_order[i][0])
                     + sprintf("(%2d)", combined_order[i][1])
                     + " |\n";

        i++;
    }

    surveys = sprintf("%-52s", sprintf("%,d", participants)
            + " completed surveys.");

    /* Finally, the footer. Again, increase screen width to view code. */
    display_txt +=
        "| =========================================================================== |\n"
      + "|                                                                             |\n"
      + "|   Thank you to everyone who has participated in this study! At the present  |\n"
      + "|   time we have received " + surveys + "|\n"
      + "|                                                                             |\n"
      + "|   In Gratitude,                                                             |\n"
      + "|   Chadwick Fountaine, Master Engraver                                       |\n"
      + "|                                                                             |\n"
      + " `---------------------------------------------------------------------------'\n\n";

    return display_txt + "\n";
} /* display_ratings */


public void
create_data()
{
    foreach(string this_rating: Ratings_Index)
    {
        Ratings[this_rating] = ({ 10 - random(10), 10 - random(10) });
    }

    record_ratings();
    return;
} /* create_data */


/*
 * Function name:        check_for_duplicates
 * Description  :        If there are any duplicate values for the
 *                       mapping indices, we must devalue the
 *                       following one slightly
 * Arguments    :        float current - the value to check
 *                       mixed f_arr - the array of existing floats
 * Returns      :        float - the value, either modified or
 *                               otherwise
 */
public float
check_for_duplicates(float current, mixed *f_arr)
{
    int    duplicate_found = 1;

    while (duplicate_found)
    {
        foreach(float f : f_arr)
        {
            if (current == f)
            {
                current -= 0.001;
                duplicate_found = 1;
            }
            else
            {
                duplicate_found = 0;
            }
        }
    }

    return current;
} /* check_for_duplicates */


/*
 * Function name:        submit_form
 * Description  :        allow the player to try to submit the form once
 *                       the quest is complete
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
submit_form(string arg)
{
    object  npc;

    if (!strlen(arg))
    {
        notify_fail("What do you wish to submit?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[the] [sign] [rating] [ratings] 'form' [to] [the] [large]"
      + " [sleepy] [man] [human] [carlsan]"))
    {
        notify_fail("Do you wish to submit the form, perhaps?\n");
        return 0;
    }

    if (!finished_form())
    {
        notify_fail("You will first need to complete the form. There are"
          + " still some signs you have not yet finished rating. You can"
          + " <read form> to see which ones are left.\n");
        return 0;
    }

    if (!objectp(npc = present(TOWN_CRIER, environment(this_player()))))
    {
        notify_fail("You'll first need to return to Carlsan.\n");
        return 0;
    }

    write("You hand the completed form to Carlsan.\n");
    tell_room(environment(npc), QCTNAME(this_player()) + " hands a"
      + " piece of paper to " + QTNAME(npc) + ".\n", this_player());

    npc->react_form(this_player());

    record_ratings();
    set_alarm(0.0, 0.0, "remove_object");

    return 1;
} /* submit_form */