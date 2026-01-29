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
public int      sort_ratings(mixed *rating_a, mixed *rating_b);


/*
 * Function name:        create_object
 * Description  :        The constructor
 */
public void
create_object()
{
    set_name("form");
    add_name(RATING_FORM);
    add_adj( ({ "sign", "rating" }) );

    set_short("sign rating form");
    set_long("@@describe@@");

    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_M_NO_SELL, "That would not be a good idea.\n");
    add_prop(OBJ_M_NO_DROP, "You'd better hang on to that.\n");
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
 * Function name:        check_finished
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
          + " the signs. You can now return to Carlsan and <claim"
          + " reward>.\n");
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
        old_ratings = VENDOR->get_info("sign_ratings", index_name);
        new_ratings = Ratings[which_rating];

        if (!sizeof(old_ratings))
        {
            VENDOR->set_info("sign_ratings", index_name,
                ({ new_ratings[0], new_ratings[1], 1 }) );
        }
        else
        {
            readability    = old_ratings[0] + new_ratings[0];
            attractiveness = old_ratings[1] + new_ratings[1];
            count          = old_ratings[2];
            count++;

            VENDOR->set_info("sign_ratings", index_name,
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
    float    readability;
    float    attractiveness;
    float    combined;
    //mapping  readability_rankings = ([]);
    //mapping  attractiveness_rankings = ([]);
    //mapping  combined_rankings = ([]);
    //string  *rating_indices = ({});
    string   index_name;
    int *    rating = ({});
    mixed *  ratings = ({});

    foreach(string which_rating : Ratings_Index)
    {
        index_name = implode(explode(which_rating, " "), "_");

        rating = VENDOR->get_info("sign_ratings", index_name);
        if (!sizeof(rating))
            continue;
        dump_array(rating);
        readability    = itof(rating[0]) / itof(rating[2]);
        attractiveness = itof(rating[1]) / itof(rating[2]);
        combined       = readability + attractiveness;
        
        ratings += ({ ({ which_rating, readability, attractiveness,
            combined }) });
    }
    ratings = sort_array(ratings, sort_ratings);

    dump_array(ratings);

    return "";
} /* display_rankings */


/*
 * Function name:        sort_ratings
 * Description  :        Sorts ratings by score
 * Arguments    :        mixed * - the two ratings to compare
 * Returns      :        int - result of comparison
 */
public string
sort_ratings(mixed *rating_a, mixed *rating_b)
{
    return rating_b[3] - rating_a[3];
} /* sort_ratings */