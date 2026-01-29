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
#include <stdproperties.h>
#include "../defs.h"

/* Definitions */
#define     SURVEY_PROP ("_tutorial_survey_prop")
#define     SURVEY_FILE ("new_player_survey")

/* Global Variables */
public int      Survey_Position = 0;
public int      Current_Question = 0;
public int      Current_Range = 0;
public string  *Questions = ({
                    "How old are you?",
                    "What is your gender?",
                    "In what city do you live?",
                    "In what country do you live?",
                    "Are you new to Genesis?",
                    "How long has it been since your last visit?",
                    "Where did you hear about Genesis?",
                    "Where did you see the poster?",
                    "How did you like the poster?",
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
                    "[9] Poster looked:     ",
                         });
public mixed   *Choices_Made = allocate(sizeof(Questions));
public mixed   *Answers = ({ ({
                    "[1] under 18",
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
public void     enter_env(object dest, object old);
public void     do_survey(object who); 
public void     survey_answer(string arg, object who);


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
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_I_VOLUME, 1);
    add_prop(OBJ_I_WEIGHT, 1);

    set_long("This item cannot be seen.\n");
    
    setuid();
    seteuid(getuid());
} /* create_object */


/*
 * Function name: enter_env
 * Description  : This function is called each time this object enters a
 *                new environment. If you mask it, be sure that you
 *                _always_ call the ::enter_env(dest, old) function.
 * Arguments    : object dest - the destination we are entering.
 *                object old  - the location we came from. This can be 0.
 *
 * When the survey enters an interactive environment (aka a player) we
 * begin the survey process.
 */
public void
enter_env(object dest, object old)
{
    set_alarm(2.0, 0.0, &do_survey(dest));
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
        who->catch_tell("\nThank you for participating in the New Player"
          + " Survey!\n\n");
        who->catch_tell("Answering the following questions typically"
          + " takes between 2 and 4 minutes.\nLet's begin ...\n\n");
    }
    else
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
    int     i;

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

        Choices_Made[Current_Question] = atoi(arg);
    }

    who->catch_tell("Current_Question = " + Current_Question + "\n");
    who->catch_tell("Survey_Position = " + Survey_Position + "\n");

    if (Survey_Position >= (sizeof(Questions) - 1))
    {
        who->catch_tell("Survey Complete!\n\n");

        foreach(mixed this_choice: Choices_Made)
        {
            switch (i)
            {
                case 2:
                case 3:
                    who->catch_tell("\t" + Review[i] + this_choice + "\n");
                    break;
                default:
                    this_choice--;
                    who->catch_tell("\t" + Review[i]
                        + Answers[i][this_choice][4..] + "\n");
                    break;
            }

            i++;
        }

        return;
    }

    Current_Question++;
    Survey_Position++;

    do_survey(who);
} /* survey_answer */