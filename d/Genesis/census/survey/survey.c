/*
 *  /d/Sparkle/area/tutorial/object/survey.c
 *
 *  This object performs the survey for new players who find their
 *  way to Genesis, to provide data for future analysis.
 *
 *  Created March 2011, by Cooper Sherry (Gorboth)
 *    - Thanks go to Tialin, Benner, and Hektor for development of the
 *      survey questions.
 */

#pragma strict_types

inherit "/std/object";

#include <language.h>
#include <macros.h>
#include <money.h>
#include <stdproperties.h>
#include <time.h>
#include "defs.h"

/* Definitions */
#define     SURVEY_PROP    ("_tutorial_survey_prop")
#define     TELL_G(x)      (find_living("gorboth")->catch_msg("DEBUG: "+x+"\n"))
#define     SURVEY_FILE(n) (extract((n), 0, 0) + "/" + (n))

/* Global Variables */
public string   File_Text;
public int      Survey_Position = 0;
public int      Current_Question = 0;
public int      Current_Range = 0;
public int      Stop_Survey = 0;
public mixed    Friend = 0;
public mixed    Banner = 0;
public mixed    Other_Way = 0;
public mixed    Other_Poster = 0;
public int      Revising = 0;
public mapping  Countries =   ([ "ar" : "argentina",
                                 "at" : "austria",
                                 "au" : "australia",
                                 "be" : "belgium",
                                 "bo" : "bolivia",
                                 "br" : "brazil",
                                 "ca" : "canada",
                                 "ch" : "switzerland",
                                 "cl" : "chile",
                                 "cn" : "china",
                                 "co" : "columbia",
                                 "cr" : "costa rica",
                                 "cu" : "cuba",
                                 "cz" : "czech republic",
                                 "de" : "germany",
                                 "dk" : "denmark",
                                 "ec" : "ecuador",
                                 "eg" : "egypt",
                                 "es" : "spain",
                                 "fi" : "finland",
                                 "fr" : "france",
                                 "gb" : "great britain",
                                 "gr" : "greece",
                                 "hk" : "hong kong",
                                 "hr" : "croatia",
                                 "hu" : "hungary",
                                 "id" : "indonesia",
                                 "ie" : "ireland",
                                 "il" : "israel",
                                 "in" : "india",
                                 "iq" : "iraq",
                                 "ir" : "iran",
                                 "is" : "iceland",
                                 "it" : "italy",
                                 "jp" : "japan",
                                 "kr" : "korea, south",
                                 "lv" : "latvia",
                                 "lu" : "luxembourg",
                                 "my" : "malaysia",
                                 "mc" : "monaco",
                                 "mx" : "mexico",
                                 "nl" : "netherlands",
                                 "no" : "norway",
                                 "nz" : "new zealand",
                                 "pe" : "peru",
                                 "ph" : "philippines",
                                 "pk" : "pakistan",
                                 "pl" : "poland",
                                 "pr" : "puerto rico",
                                 "pt" : "portugal",
                                 "ro" : "romania",
                                 "ru" : "russia",
                                 "se" : "sweden",
                                 "sg" : "singapore",
                                 "sk" : "slovak republic",
                                 "tr" : "turkey",
                                 "tw" : "taiwan",
                                 "ua" : "ukraine",
                                 "us" : "united states",
                                 "uy" : "uruguay",
                                 "ve" : "venezuela",
                                 "vn" : "vietnam",
                                 "yu" : "yugoslavia",
                                 "za" : "south africa",
                                 "xx" : "other than on list", ]);
public string  *Questions = ({
                    "How old are you?",
                    "What is your gender?",
                    "In which city do you live?",
                    "In which country do you live?",
                    "Are you new to Genesis?",
                    "How long has it been since your last visit?",
                    "Where did you hear about Genesis?",
                    "Where did you see the poster?",
                    "How would you rate the poster's appearance?",
                          });
public string  *Review = ({
                    "[1] Age:               ",
                    "[2] Gender:            ",
                    "[3] City:              ",
                    "[4] Country:           ",
                    "[5] New Player:        ",
                    "[6] Last visit:        ",
                    "[7] Found Genesis via: ",
                    "[8] Poster location:   ",
                    "[9] Poster appearance: ",
                         });
public mixed   *Choices_Made = allocate(sizeof(Questions));
public mixed   *Answers = ({ ({
                    "[1] Under 18",
                    "[2] 18-24",
                    "[3] 25-34",
                    "[4] 35-44",
                    "[5] 45-54",
                    "[6] 55-64",
                    "[7] 65+",
                             }),
                             ({
                    "[1] Male",
                    "[2] Female",
                             }),
                             ({}),
                             ({}),
                             ({
                    "[1] Yes",
                    "[2] No",
                             }),
                             ({
                    "[1] Within 1 week",
                    "[2] Within 1 month",
                    "[3] Within 3 months",
                    "[4] Within a year",
                    "[5] Longer",
                             }),
                             ({
                    "[1] A friend",
                    "[2] A colleague",
                    "[3] Poster",
                    "[4] Mud listing pages",
                    "[5] Web Banner Advertisement",
                    "[6] Other",
                             }),
                             ({
                    "[1] Library", 
                    "[2] College/University",
                    "[3] School",
                    "[4] Bar",
                    "[5] Store",
                    "[6] Bus Stop",
                    "[7] Other",
                             }),
                             ({
                    "[1] Very poor",
                    "[2] Poor",
                    "[3] Mediocre",
                    "[4] Good",
                    "[5] Very good",
                             }), });

/* Prototypes */
public void     create_object();
public void     init();
public void     do_survey(object who); 
public void     survey_answer(string arg, object who);
public void     check_finished(object who);
public void     extra_answer(string arg, object who, string topic); 
public void     review_answers(string arg, object who);
public void     record_answers(object who);
public void     init_extras();
public void     log_survey(string dfile, string dindex, string dpath = LOG_DIR);
public string   merge_words(string arg);
public int      illegal_text(string arg);


/*
 * Function name:        create_object
 * Description  :        The constructor
 */
public void
create_object()
{
    set_name("survey");

    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_M_NO_SELL, "That would not be a good idea.\n");
    add_prop(OBJ_M_NO_GIVE, 1);
    add_prop(OBJ_I_VOLUME, 1);
    add_prop(OBJ_I_WEIGHT, 1);

    set_long("This item cannot be seen.\n");
    
    add_prop(OBJ_I_NO_DROP, "This item cannot be dropped.\n");

    setuid();
    seteuid(getuid());

    Answers[3] = ({ read_file(SURVEY_DIR + "country_list.txt") });
} /* create_object */


/*
 * Function name:        init
 * Description  :        start up the survey
 */
public void
init()
{
    object  who = environment(this_object());

    ::init();

    if (interactive(who))
    {
        if (read_file(LOG_DIR + SURVEY_FILE(who->query_real_name())))
        {
            who->catch_tell("You've already completed the survey, and"
              + " thanks again!\n");

            remove_object();
            return;
        }

        set_alarm(2.0, 0.0, &do_survey(who));
    }
} /* enter_env */


/*
 * Function name:        do_survey
 * Description  :        perform a survey question
 * Arguments    :        object who - the user taking the survey
 */
public void
do_survey(object who)
{
    string  question = Questions[Current_Question];
    string *choices = Answers[Current_Question];
    int     choice_num = sizeof(choices);
    string  paren_txt;
    string  divider = "----------------------------------------------"
                    + "---------------------------------\n";

    if (!Current_Question)
    {
        who->catch_tell("\n"
+ "          .-------------------------------------------------------.\n"
+ "         |  Thank you for participating in the New Player Survey!  |\n"
+ "         |                                                         |\n"
+ "         |    Answering the following questions typically takes    |\n"
+ "         |        less than one minute. So, let's begin ...        |\n"
+ "          `-------------------------------------------------------'\n\n");
    }
    else if (!Revising && !Stop_Survey)
    {
        who->catch_tell("\n   -***- Survey Progress: Question "
          + (Current_Question + 1) + " out of " + sizeof(Questions)
          + " -***-\n\n");
    }

    who->catch_tell(divider + question + "\n" + divider + "\n");

    foreach(string choice: choices)
    {
        who->catch_tell("\t" + choice + "\n");
    }

    paren_txt = " (1 - " + choice_num + "): ";

    if (Current_Question == 3)
    {
        paren_txt = " (use 2-digit code): ";
    }

    if (sizeof(choices))
    {
        who->catch_tell("\n");
    }

    who->catch_tell("Please type your answer"
      + ((choice_num) ? paren_txt : ": "));

    input_to(&survey_answer( , who));
    return;
} /* do_survey */


/*
 * Function name:        survey_answer
 * Description  :        check the answer the player gave to a survey
 *                       question and take appropriate action.
 * Arguments    :        string arg - the survey answer they typed
 *                       object who - the survey taker
 */
public void
survey_answer(string arg, object who)
{
    string  question = Questions[Current_Question];
    string *choices = Answers[Current_Question];
    int     choice_num = sizeof(choices);
    int     num_answer = atoi(arg);
    int     skip = 0;

    arg = lower_case(arg);

    if (arg == "quit" || arg == "q" || arg == "~q")
    {
        who->catch_tell("\n\nQuitting out ... maybe another time.\n");
        who->remove_prop(SURVEY_PROP);
        remove_object();
        return;
    }

    if (illegal_text(arg))
    {
        who->catch_tell("Answers cannot include commas.\nPlease re-type"
          + " your answer: ");
        input_to(&survey_answer( , who));
        return;
    }


    if (!choice_num)
    {
        if (!strlen(arg))
        {
            who->catch_tell("Please type your answer: ");
            input_to(&survey_answer( , who));
            return;
        }

        Choices_Made[Current_Question] = arg;
    }
    else if (Current_Question == 3)
    {
        if (strlen(arg) != 2)
        {
            who->catch_tell("Please use the 2-digit abbreviation"
              + " (from above list): ");
            input_to(&survey_answer( , who));
            return;
        }

        if (!IN_ARRAY(arg, m_indexes(Countries)))
        {
            who->catch_tell("Please select from the above list (2-digit"
              + " abbreviation): ");
            input_to(&survey_answer( , who));
            return;
        }

        Choices_Made[Current_Question] = arg;
    }
    else
    {
        if (!num_answer ||
             num_answer > choice_num)
        {
            who->catch_tell("Please answer with 1 - " + choice_num
                + ": ");
            input_to(&survey_answer( , who));
            return;
        }

        Choices_Made[Current_Question] = num_answer;

        switch (Current_Question)
        {
            case 4:
                Stop_Survey = 0;
                Survey_Position = Current_Question;

                if (num_answer == 1)
                {
                    skip = 1;
                }
                break;
            case 5:
                Stop_Survey = 1;
                Choices_Made[6] = 0;
                Choices_Made[7] = 0;
                Choices_Made[8] = 0;
                break;
            case 6:
                Choices_Made[5] = 0;

                switch (num_answer)
                {
                    case 3:
                        Survey_Position == Current_Question;
                        break;
                    default:
                        Choices_Made[7] = 0;
                        Choices_Made[8] = 0;
                        break;
                }
                switch (num_answer)
                {
                    case 1:
                    case 2:
                        who->catch_tell("The name of their Genesis"
                          + " character? (blank if unknown): ");
                        input_to(&extra_answer( , who, "recruiter"));
                        return;
                        break;
                    case 3:
                        init_extras();
                        Stop_Survey = 0;
                        Survey_Position = Current_Question;
                        break;
                    case 4:
                        Stop_Survey = 1;
                        init_extras();
                        break;
                    case 5:
                        who->catch_tell("Webpage where you saw the"
                          + " advertisement? (blank if unknown): ");
                        input_to(&extra_answer( , who, "banner"));
                        return;
                        break;
                    case 6:
                        who->catch_tell("Brief description of this"
                          + " other way you found us: ");
                        input_to(&extra_answer( , who, "other_way"));
                        return;
                        break;
                    default:
                        break;
                }
                break;
            case 7:
                switch (num_answer)
                {
                    case 7:
                        who->catch_tell("Where was the poster"
                          + " located? (leave blank if"
                          + " unsure): ");
                        input_to(&extra_answer( , who, "other_poster"));
                        return;
                        break;
                    default:
                        break;
                }

                if (!Choices_Made[8])
                {
                    Stop_Survey = 0;
                    Current_Question = 7;
                    Survey_Position = 7;
                }
                break;
            default:
                break;
        }
    }

    check_finished(who);

    if (Stop_Survey)
    {
        return;
    }

    Current_Question += skip;
    Survey_Position += skip;

    Current_Question++;
    Survey_Position++;

    do_survey(who);
} /* survey_answer */


/*
 * Function name:        check_finished
 * Description  :        see if the user has completed the survey,
 *                       and allow them to review/change their answers.
 * Arguments    :        who - the user
 */
public void
check_finished(object who)
{
    int     i = 0;
    string  found;
    string  poster;
    string *words;
    string *new_words = ({});
    string  word;

    if (Friend)
    {
        found = Friend;
    }

    if (Banner)
    {
        found = Banner;
    }

    if (Other_Way)
    {
        found = Other_Way;
    }

    if (Other_Poster)
    {
        poster = Other_Poster;
    }

    if (Survey_Position >= (sizeof(Questions) - 1) || Stop_Survey)
    {
        who->catch_tell("\nPlease review your answers.\n\n");

        File_Text = "";

        foreach(mixed this_choice: Choices_Made)
        {
            switch (i)
            {
                case 2:
                    who->catch_tell("\t" + Review[i]
                      + capitalize(this_choice) + "\n");
                    File_Text += "\t" + Review[i]
                      + capitalize(this_choice) + "\n";
                    break;
                case 3:
                    words = explode(Countries[this_choice], " ");

                    foreach(string this_word: words)
                    {
                        new_words += ({ capitalize(this_word) });
                    }

                    word = implode(new_words, " ");

                    who->catch_tell("\t" + Review[i] + word + "\n");
                    File_Text += "\t" + Review[i] + word + "\n";
                    break;
                default:
                    if (!this_choice)
                    {
                        who->catch_tell("\t[" + (i+1) + "]"
                          + " (category n/a)     ---\n");
                        File_Text += "\t[" + (i+1) + "]"
                          + " (category n/a)     ---\n";
                    }
                    else
                    {
                        this_choice--;

                        if (i == 7)
                        {
                            who->catch_tell("\t" + Review[i]
                                + Answers[i][this_choice][4..]
                                + ((poster) ? " (" + poster + ")" : "")
                                + "\n");
                            File_Text += "\t" + Review[i]
                                + Answers[i][this_choice][4..]
                                + ((poster) ? " (" + poster + ")" : "")
                                + "\n";
                        }
                        else
                        {
                            who->catch_tell("\t" + Review[i]
                                + Answers[i][this_choice][4..]
                                + ((found && i == 6) ? " (" + found + ")" : "")
                                + "\n");
                            File_Text += "\t" + Review[i]
                                + Answers[i][this_choice][4..]
                                + ((found && i == 6) ? " (" + found + ")" : "")
                                + "\n";
                        }
                    }
                    break;
            }

            i++;
        }

        who->catch_tell("\nEnter number to change or type \"done\" if"
          + " all are correct: ");
        input_to(&review_answers( , who));

        Stop_Survey = 1;

        return;
    }
} /* check_finished */


/*
 * Function name:        extra_answer
 * Description  :        get some extra info on things, as needed
 * Arguments    :        string arg - what was typed
 *                       object who - the user
 *                       string topic - the topic of info
 */
public void
extra_answer(string arg, object who, string topic)
{
    init_extras();

    if (arg == "quit" || arg == "q" || arg == "~q")
    {
        who->catch_tell("\n\nQuitting out ... maybe another time.\n");
        who->remove_prop(SURVEY_PROP);
        remove_object();
        return;
    }

    if (illegal_text(arg))
    {
        who->catch_tell("Answers cannot include commas.\nPlease re-type"
          + " your answer: ");
        input_to(&extra_answer( , who, topic));
        return;
    }

    if (!strlen(arg))
    {
        if (topic == "other_way")
        {
            who->catch_tell("Please type your answer: ");
            input_to(&extra_answer( , who, topic));
            return;
        }
        else if (topic == "recruiter")
        {
            Friend = "unknown";
            Stop_Survey = 1;
        }
        else if (topic == "other_poster")
        {
            Other_Poster = "unknown";

            Current_Question++;
            Survey_Position++;

            do_survey(who);

            return;
        }
        else
        {
            Banner = "unknown";
            Stop_Survey = 1;
        }
    }
    else
    {
        switch (topic)
        {
            case "recruiter":
                Friend = lower_case(arg);
                Stop_Survey = 1;
                break;
            case "banner":
                Banner = lower_case(arg);
                Stop_Survey = 1;
                break;
            case "other_poster":
                Other_Poster = lower_case(arg);

                Current_Question++;
                Survey_Position++;

                do_survey(who);

                return;

                break;
            default:
                Other_Way = lower_case(arg);
                Stop_Survey = 1;
                break;
        }
    }

    if (Current_Question > 7)
    {
        Stop_Survey = 1;
    }

    check_finished(who);
} /* extra_answer */


/*
 * Function name:        review_answers
 * Description  :        allow the player to change answers as needed
 * Arguments    :        string arg - what the player typed
 *                       object who - the player
 */
public void
review_answers(string arg, object who)
{
    int     num_answer = atoi(arg);
    int     which_answer = num_answer - 1;
    object  reward;

    if (!strlen(arg))
    {
        who->catch_tell("\nEnter number to change or type \"done\" if"
          + " all are correct: ");
        input_to(&review_answers( , who));
        return;
    }

    if (lower_case(arg) == "done" || lower_case(arg) == "quit")
    {
        who->catch_tell("\nThis completes the survey. Thank you for your"
          + " time!\n");

        reward = MONEY_MAKE(10, "gold");
        reward->move(who);

        who->catch_tell("You receive 10 gold coins.\n");

        record_answers(who);
        remove_object();
        return;
    }

    if (!num_answer ||
         num_answer > 9)
    {
        who->catch_tell("Please answer with 1 - 9 (or \"done\"): ");
        input_to(&review_answers( , who));
        return;
    }

    switch (num_answer)
    {
        case 3:
            Survey_Position = which_answer;
            break;
        case 6:
            if (Choices_Made[4] == 1)
            {
                who->catch_tell("---This category only applies to returning"
                  + " players.\nEnter number to"
                  + " change or type \"done\" if all are"
                  + " correct: ");
                input_to(&review_answers( , who));
                return;
            }
            break;
        case 7:
            if (Choices_Made[4] == 2)
            {
                who->catch_tell("---This category only applies to new"
                  + " players.\nEnter number to"
                  + " change or type \"done\" if all are"
                  + " correct: ");
                input_to(&review_answers( , who));
                return;
            }
            break;
        case 8..9:
            if (Choices_Made[6] != 3)
            {
                who->catch_tell("---This category only applies to"
                  + " poster-based character creation.\n"
                  + "Enter number to"
                  + " change or type \"done\" if all are"
                  + " correct: ");
                input_to(&review_answers( , who));
                return;
            }
            break;
        default:
            break;
    }

    Current_Question = which_answer;

    if (Current_Question == 6)
    {
        Stop_Survey = 0;
    }

    do_survey(who);

    return;
} /* review_answers */


/*
 * Function name:        record_answers
 * Description  :        log the data
 * Arguments    :        object who - the player
 */
public void
record_answers(object who)
{
    string  final_info = "XXX";
    string  extra = "";
    string  poster = "unknown";
    mixed   last_login = 0;
    mixed   method = 0;
    mixed   poster_location = 0;
    mixed   poster_rating = 0;
    string  dindex;
    string *words;
    string *new_words = ({});
    string  word;
    string *referrals = ({});
    string *old_referrals;

    if (Choices_Made[7] == 7)
    {
        if (Other_Poster)
        {
            poster = Other_Poster;
        }
    }
    else
    {
        poster = Answers[7][Choices_Made[7]-1][4..];
    }

    if (Choices_Made[4] == 2)
    {
        final_info = Answers[5][Choices_Made[5]-1][4..];
    }
    else
    {
        switch(Choices_Made[6])
        {
            case 1:
                final_info = "friend(" + capitalize(Friend) + ")";
                break;
            case 2: 
                final_info = "coll--(" + capitalize(Friend) + ")";
                break;
            case 3:
                final_info = "poster("
                           + poster + ") "
                           + Answers[8][Choices_Made[8]-1][4..];
                break;
            case 4:
                final_info = "mud-list";
                break;
            case 5:
                final_info = "banner(" + Banner + ")";
                break;
            case 6:
                final_info = "other-(" + Other_Way + ")";
                break;
            default:
                break;
        }
    }

    /* First, lets do a general log of all the info, easily readable by
     * human eyes.
     */
    write_file(LOG_DIR + "completed",
        TIME2FORMAT(time(), "mm/dd/yyyy")
      + sprintf(" %-12s", capitalize(who->query_real_name()))
      + sprintf("%-9s", Answers[0][Choices_Made[0]-1][4..])
      + ((Choices_Made[1] == 1) ? "M " : "F ")
      + sprintf("%11s, %-2s ", capitalize(Choices_Made[2]),
                               upper_case(Choices_Made[3]))
      + ((Choices_Made[4] == 1) ? "NEW " : "old ")
      + final_info + "\n");

    if (Choices_Made[4] == 2)
    {
        last_login = Answers[5][Choices_Made[5]-1];
    }
    else
    {
        switch(Choices_Made[6])
        {
            case 1:
                method = "friend";
                break;
            case 2: 
                method = "colleague";
                break;
            case 3:
                method = "poster";
                poster_location = poster;
                poster_rating = Answers[8][Choices_Made[8]-1][4..];
                break;
            case 4:
                method = "mud-list";
                break;
            case 5:
                method = "banner";
                break;
            case 6:
                method = "other";
                break;
            default:
                break;
        }
    }

    /* Lets make another entry of this to a special file just for the
     * player.
     */
    write_file(LOG_DIR + SURVEY_FILE(who->query_real_name()), File_Text);

    /* Okay, now lets use the same data, but log it for importing into
     * a spreadsheet application such as Excel.
     */
    if (!strlen(read_file(LOG_DIR + "survey_spreadsheet")))
    {
        write_file(LOG_DIR + "survey_spreadsheet",
            "Year,"
          + "Month,"
          + "Day,"
          + "Name,"
          + "Age,"
          + "Gender,"
          + "City,"
          + "Country,"
          + "Heritage,");
        write_file(LOG_DIR + "survey_spreadsheet",
            "Found-Via,"
          + "Friend,"
          + "Colleague,"
          + "Poster,"
          + "Poster-Rating,"
          + "Mud-Pages,"
          + "Banner-Loc,"
          + "Other-Method,"
          + "Last-Login"
          + "\n");
    }

    write_file(LOG_DIR + "survey_spreadsheet",
    TIME2FORMAT(time(), "yyyy,mm,dd")              + "," /* Yr,Mo,Day  */
  + capitalize(who->query_real_name())             + "," /* Name       */
  + Answers[0][Choices_Made[0]-1][4..]             + "," /* Age        */
  + ((Choices_Made[1] == 1) ? "M" : "F")           + "," /* Gender     */
  + capitalize(Choices_Made[2])                    + "," /* City       */
  + upper_case(Choices_Made[3])                    + "," /* Country    */
  + ((Choices_Made[4] == 1) ? "NEW" : "old")       + "," /* Heritage   */
     );
    write_file(LOG_DIR + "survey_spreadsheet",
    ((method) ? method : "")                       + "," /* Found-Via  */
  + ((Choices_Made[6] == 1) ? Friend : "")         + "," /* Friend     */
  + ((Choices_Made[6] == 2) ? Friend : "")         + "," /* Colleague  */
  + ((Choices_Made[6] == 3) ? poster_location : "")+ "," /* Poster     */
  + ((Choices_Made[8]) ? Choices_Made[8] : "")     + "," /* Poster-Rtg */
  + ((Choices_Made[6] == 4) ? "Yes" : "")          + "," /* Mud-Pages  */
  + ((Choices_Made[6] == 5) ? Banner : "")         + "," /* Banner-Loc */
  + ((Choices_Made[6] == 6) ? Other_Way : "")      + "," /* Other-Meth */
  + ((Choices_Made[5]) ? 
        Answers[5][Choices_Made[5]-1][4..] : "")           /* Last-Login */
  + "\n");

    /* Now lets perform some useful data ticks for quick checking */

    /* Where they came from */
    dindex = upper_case(Choices_Made[3]) + "_"
           + merge_words(capitalize(Choices_Made[2]));
    log_survey("residence", dindex);

    /* How they found us */
    if (method)
    {
        log_survey("method", method);
    }

    /* Who referred them */
    if (Friend)
    {
        old_referrals = SURVEY_MASTER->get_info(
            "referrals", merge_words(Friend));

        referrals = ((sizeof(old_referrals)) ? old_referrals : ({}) );

        referrals += ({ who->query_real_name() });

        SURVEY_MASTER->set_info("referrals", merge_words(Friend), referrals);   
    }

    /* Where they saw the poster */
    if (poster_location)
    {
        log_survey("poster_loc", merge_words(poster_location));
    }

    /* What they thought of the poster */
    if (Choices_Made[8])
    {
        log_survey("poster_rtg", 
            merge_words(Answers[8][Choices_Made[8]-1][4..]));
    }

    
} /* record_answers */


/*
 * Function name:        init_extras
 * Description  :        initialize the extra var values
 */
public void
init_extras()
{
    Friend = 0;
    Other_Way = 0;
    Other_Poster = 0;
    Banner = 0;
} /* init_extras */


/*
 * Function name:        log_survey
 * Description  :        do some incremental logging of survey info into
 *                       appropriate data files.
 * Arguments    :        string dfile  - the name of the datafile
 *                       string dindex - the name of the index point
 *                       string dpath  - the datafile path
 */
public void
log_survey(string dfile, string dindex, string dpath = LOG_DIR)
{
    string *explode_dindex = explode(dindex, " ");
    int     instances;

    if (sizeof(explode_dindex) > 1)
    {
        dindex = implode(explode_dindex, "_");
    }

    instances  = SURVEY_MASTER->get_info(dfile, dindex);
    instances ++;

    SURVEY_MASTER->set_info(dfile, dindex, instances);
} /* log_survey */


/*
 * Function name:        merge_words
 * Description  :        for some logging, we'll want to remove spaces
 *                       from strings.
 * Arguments    :        string arg - the string to check
 * Returns      :        string - the reformatted string
 */
public string
merge_words(string arg)
{
    string *words;
    string *new_words = ({});

    words = explode(arg, " ");

    foreach(string this_word: words)
    {
        new_words += ({ capitalize(this_word) });
    }

    return implode(new_words, "_");
} /* merge_words */


/*
 * Function name:        illegal_text
 * Description  :        Check for any characters we don't want to allow
 *                       that could mess up our data
 * Arguments    :        string arg - the string to check
 * Returns      :        int 1 - illegal character found
 *                       int 0 - none found
 */
public int
illegal_text(string arg)
{
    int     found = 0;
    string *chars;
    string *illegal_chars = ({ "," });

    chars = explode(arg, "");

    foreach(string this_char: chars)
    {
        if (IN_ARRAY(this_char, illegal_chars))
        {
            found = 1;
        }
    }

    return found;
} /* illegal_text */
