/*
 *  /d/Sparkle/area/city/obj/local_qm_checklist.c
 *
 *  This object is given out by Carlsan Fountaine, the Town Crier
 *  as part of the Local Questmasters tour in Sparkle.
 *
 *  Using it, player are asked to find and complete all quests given
 *  out by the npcs on the checklist.
 *
 *  Note: If new local quest npcs appear in the Sparkle domain 
 *        and are appropriate for young players, they should be
 *        incorporated into this quest.
 *
 *  Created April 2011, by Cooper Sherry (Gorboth)
 *
 *  Updated July 22, 2016 by Gronkas - changed reported typos line 120 pp.
 *
 */

#pragma strict_types

inherit "/std/object";

#include <cmdparse.h>
#include <language.h>
#include <macros.h>
#include <stdproperties.h>
#include "../defs.h"

/* Definitions */
#define         NIKOLON_PROP   "_sparkle_tour_qm_nikolon_asked"
#define         KARKADELT_PROP "_sparkle_tour_qm_karkadelt_asked"
#define         MENERIAL_PROP  "_sparkle_tour_qm_menerial_asked"


/* Global Variables */
public int      QuestMaster_1 = 0;  /* Nikolon   */
public int      QuestMaster_2 = 0;  /* Karkadelt */
public int      QuestMaster_3 = 0;  /* Menerial  */


/* Prototypes */
public void     create_object();
public void     init();
public string   describe();
public int      finished_form();
public void     check_finished_msg(object who);
public int      submit_form(string arg);

public void     set_qm1(int i) { QuestMaster_1 = i; }
public void     set_qm2(int i) { QuestMaster_2 = i; }
public void     set_qm3(int i) { QuestMaster_3 = i; }



/*
 * Function name:        create_object
 * Description  :        The constructor
 */
public void
create_object()
{
    set_name("list");
    add_name(LOCAL_QM_CHECKLIST);
    add_name( ({ "checklist", "form" }) );
    add_adj( ({ "check" }) );

    set_short("checklist");
    set_long("@@describe@@");

    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_M_NO_SELL, "That would not be a good idea.\n");
    add_prop(OBJ_M_NO_DROP, "You'd better hang on to that. If you want"
      + " someone to check it, you can <submit> it to them.\n");
    add_prop(OBJ_I_VOLUME, 2);
    add_prop(OBJ_I_WEIGHT, 1);

    add_cmd_item( ({ "list", "checklist", "check list" }),
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
    string  not_yet = "      no [ ]         |\n";
    string  done    = "         [X] yes     |\n";
    string  q1 = ((QuestMaster_1) ? done : not_yet);
    string  q2 = ((QuestMaster_2) ? done : not_yet);
    string  q3 = ((QuestMaster_3) ? done : not_yet);

    form_txt = "\n"
    + "  ,------------------------------------------------------------,.\n"
    + "  ---.---------------------------------------------------------  \\\n"
    + "     |                                                            |\n"
    + "     |   By authority of the Sparkle Magistrate, any persons able |\n"
    + "     |   to complete this checklist will be known as friend to    |\n"
    + "     |   the City, and are thereby granted both monetary reward   |\n"
    + "     |   and acknowledgement for deeds well done.                 |\n"
    + "     |   Simply <submit> this form to the persons listed below    |\n"
    + "     |   and they will sign it if all tasks are complete.         |\n"
    + "     |                                                            |\n"
    + "     | ========================================================== |\n"
    + "     |  Person to Find:  Location:            Tasks Completed:    |\n"
    + "     | ========================================================== |\n"
    + "     |  Nikolon          The Sparkle Library " + q1
    + "     |  Karkadelt        The Enchanter's Shop" + q2
    + "     |  Menerial         Green Oaks          " + q3
    + "     | ========================================================== |\n"
    + "     |                                                            |\n"
    + "     |   This form should not be marked as completed unless the   |\n"
    + "     |   bearer has adequately completed all tasks that can be    |\n"
    + "     |   given by the person in question.                         |\n"
    + "     |                                                            |\n"
    + "     |   Once all persons have signed off on having their tasks   |\n"
    + "     |   completed, the owner should return to Carlsan and        |\n"
    + "     |   <submit> it for approval and reward.                     |\n"
    + "     |                                                            |\n"
    + "  -------------------------------------------------------------. /\n"
    + "  `-------------------------------------------------------------`\n\n";

    set_alarm(0.5, 0.0, &check_finished_msg(this_player()));

    return form_txt;
} /* describe */


/*
 * Function name:        finished_form
 * Description  :        See if the player has completed the checklist
 * Returns      :        int 1 - completed
 *                       int 0 - not yet completed
 */
public int
finished_form()
{
    if (QuestMaster_1 &&
        QuestMaster_2 &&
        QuestMaster_3)
    {
        return 1;
    }

    return 0;
} /* finished_form */


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
        who->catch_msg("\nIt looks as if you have completed the"
          + " checklist! You can now return and <submit> it to"
          + " Carlsan.\n");
    }

    return;
} /* check_finished_msg */



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
    int     complete;
    object  reward;
    object *npcs;
    object  npc;
    string *quest_masters = ({ "nikolon",
                               "karkadelt",
                               "menerial" });

    if (!strlen(arg))
    {
        notify_fail("What do you wish to submit?\n");
        return 0;
    }

    npcs = PARSE_THIS(arg, 
               "[the] [check] 'list' / 'checklist' / 'form' [to] [the] %i");
    notify_fail("Submit what to whom?\n");

    switch(sizeof(npcs))
    {
        case 0:
            return 0;
            break;
        case 1:
            npc = npcs[0];
            break;
        default:
            notify_fail("The checklist is not for a committee. Please"
              + " submit it only to one person at a time.\n");
            return 0;
            break;
    }

    if (!living(npc))
    {
        write("You hold your checklist out to the "
          + npc->short() + " with a big eager grin on your face."
          + " After a few tense minutes of anticipation, you realize"
          + " that there is not likely to be a response.\n");
        return 1;
    }

    if (interactive(npc))
    {
        write("You get the feeling that person will not be interested"
          + " in dealing with your checklist.\n");
        return 1;
    }

    if (!this_player()->check_seen(npc))
    {
        write("You'll need to make sure "
          + npc->query_pronoun() + " can see you first.\n");
        return 1;
    }

    write("You submit your checklist to " 
        + npc->query_the_name(this_player()) + " for approval.\n");
    tell_room(QCTNAME(this_player()) + " hands a checklist of some"
      + " kind to " + QTNAME(npc) + ".\n", this_player());

    complete = npc->check_remaining_quests(this_player());

    switch(lower_case(npc->query_name()))
    {
        case "nikolon":
            if (complete)
            {
                if (!QuestMaster_1)
                {
                    npc->command("emote reads the checklist and"
                      + " smiles happily.");
                    npc->command("say Of course, I'll be happy to"
                      + " mark your checklist. I am still very grateful"
                      + " for the help you have given me.");
                    npc->command("emote marks the checklist and"
                      + " returns it.");
                    QuestMaster_1 = 1;
                    return 1;
                }

                if (this_player()->query_prop(NIKOLON_PROP) == "done")
                {
                    npc->command("chuckle polite");
                    npc->command("say Perhaps you are confused? I have"
                      + " already marked your checklist, and have"
                      + " already explained this to you. It is time"
                      + " to move on, my friend!");
                    return 1;
                }

                npc->command("smile apprec");
                npc->command("say As you can see if you <exa checklist>"
                  + " I have already marked you as having completed"
                  + " all the tasks I have to give you.");
                this_player()->add_prop(NIKOLON_PROP, "done");
                return 1;
            }

            if (this_player()->query_prop(NIKOLON_PROP) == "nope")
            {
                npc->command("smile patient");
                npc->command("say What about my explanation do you not"
                  + " understand, I wonder? Oh, very well ... again,"
                  + " I am not supposed to mark that checklist until"
                  + " you have helped me with my tasks. You can"
                  + " <ask> me about projects that I have if you wish"
                  + " to help me.");
                return 1;
            }

            npc->command("emote reads the checklist and nods.");
            npc->command("say I will be happy to help you with your"
              + " checklist. The idea is that you complete any tasks"
              + " that I have for you and then I will mark it. If you"
              + " would like to help me, you can <ask> me about"
              + " projects I am working on.");
            this_player()->add_prop(NIKOLON_PROP, "nope");
            return 1;

            break;
        case "karkadelt":
            if (complete)
            {
                if (!QuestMaster_2)
                {
                    npc->command("emote reads the checklist and"
                      + " nods silently.");
                    npc->command("say Yes, I will confirm that you have"
                      + " given me such assistance. Your help was very"
                      + " important, as I hope you realize.");
                    npc->command("emote marks the checklist and"
                      + " returns it.");
                    QuestMaster_2 = 1;
                    return 1;
                }

                if (this_player()->query_prop(KARKADELT_PROP) == "done")
                {
                    npc->command("eyebrow");
                    npc->command("say Why do you continue to show me"
                      + " this checklist? Our business on this matter"
                      + " is concluded.");
                    return 1;
                }

                npc->command("frown slight");
                npc->command("say Yes. Your checklist is complete"
                  + " so far as I am concerned. You should now take"
                  + " and <submit> it to the next interested party.");
                this_player()->add_prop(KARKADELT_PROP, "done");
                return 1;
            }

            if (this_player()->query_prop(KARKADELT_PROP) == "nope")
            {
                npc->command("eyebrow");
                npc->command("say Have I not been clear on this matter?"
                  + " You may <ask> me about the tasks I have mentioned"
                  + " so that we may attend to these important matters."
                  + " Only upon their completion will I deal with your"
                  + " checklist.");
                return 1;
            }

            npc->command("emote reads the checklist and nods.");
            npc->command("say Ah, excellent, yes. There are matters of"
              + " extreme importance at hand. You may <ask> me about"
              + " the tasks I have that deal with these matters. Should"
              + " you help me enough, I will be satisfied to mark your"
              + " checklist.");
            this_player()->add_prop(KARKADELT_PROP, "nope");
            return 1;

            break;
        case "menerial":
            if (complete)
            {
                if (!QuestMaster_3)
                {
                    npc->command("emote reads the checklist and"
                      + " nods appreciatively.");
                    npc->command("say Oh yes, of course I will"
                      + " mark your checklist. You have been immensely"
                      + " helpful to our community.");
                    npc->command("emote marks the checklist and"
                      + " returns it.");
                    QuestMaster_3 = 1;
                    return 1;
                }

                if (this_player()->query_prop(MENERIAL_PROP) == "done")
                {
                    npc->command("giggle merr");
                    npc->command("say Don't you remember? I have"
                      + " already marked your checklist, and have"
                      + " already explained this to you. It is time"
                      + " to move on, my friend!");
                    return 1;
                }

                npc->command("smile apprec");
                npc->command("say See here? If you <exa checklist> you'll"
                  + " notice I already marked you as having completed"
                  + " all of my tasks.");
                this_player()->add_prop(MENERIAL_PROP, "done");
                return 1;
            }

            if (this_player()->query_prop(MENERIAL_PROP) == "nope")
            {
                npc->command("smile patient");
                npc->command("say Oh, did you not understand when"
                  + " I explained it to you the first time?"
                  + " That's okay. I'll explain again."
                  + " I am not supposed to mark that checklist until"
                  + " you have helped me with my tasks. You can"
                  + " <ask> me about tasks that I have if you wish"
                  + " to help me.");
                return 1;
            }

            npc->command("emote reads the checklist and brightens.");
            npc->command("say I will certainly help you with your"
              + " checklist. You'll just need to complete the tasks"
              + " I have for you, and I'll do it! If you"
              + " would like to help me, you can <ask> me about"
              + " tasks.");
            this_player()->add_prop(MENERIAL_PROP, "nope");
            return 1;

            break;
        case "carlsan":
            break;
        default:
            npc->command("emote looks at the checklist, frowning"
              + " in confusion.");
            write("Perhaps you should submit it to someone actually"
              + " on the checklist, instead?\n");
            return 1;
            break;
    }

    npc->awake_check();
    npc->command("emote squints at the checklist.");

    if (!finished_form())
    {
        npc->command("say Oh, it looks like you've still got some work"
          + " to do here. Please get all the names checked off the"
          + " list and then <submit> it to me when you are done.");
        npc->command("emote returns the checklist.");
        return 1;
    }

    npc->react_localqm_checklist(this_player());

    set_alarm(0.0, 0.0, "remove_object");

    return 1;
} /* submit_form */
