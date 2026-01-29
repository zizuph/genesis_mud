/*
 *  /d/Sparkle/area/city/obj/cadets_checklist.c
 *
 *  This object is given out by Carlsan Fountaine, the Town Crier
 *  as part of the Local Questmasters tour in Sparkle.
 *
 *  Using it, player are asked to find the two guild npcs for the
 *  Cadets and Academics school in Gelan, and have them sign it.
 *
 *  Created June 2011, by Cooper Sherry (Gorboth)
 */

#pragma strict_types

inherit "/std/object";

#include <cmdparse.h>
#include <language.h>
#include <macros.h>
#include <stdproperties.h>
#include "../defs.h"

/* Definitions */
#define         XANIA_PROP     "_sparkle_tour_cadets_xania_asked"
#define         XORFIN_PROP    "_sparkle_tour_cadets_xorfin_asked"


/* Global Variables */
public int      QuestMaster_1 = 0;  /* Xania   */
public int      QuestMaster_2 = 0;  /* Xorfin  */


/* Prototypes */
public void     create_object();
public void     init();
public string   describe();
public int      finished_form();
public void     check_finished_msg(object who);
public int      submit_form(string arg);

public void     set_qm1(int i) { QuestMaster_1 = i; }
public void     set_qm2(int i) { QuestMaster_2 = i; }



/*
 * Function name:        create_object
 * Description  :        The constructor
 */
public void
create_object()
{
    set_name("document");
    add_name(CADETS_CHECKLIST);
    add_name( ({ "checklist", "list", "form" }) );
    add_adj( ({ "check", "official", "looking", "official-looking" }) );

    set_short("official-looking document");
    set_long("@@describe@@");

    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_M_NO_SELL, "That would not be a good idea.\n");
    add_prop(OBJ_M_NO_DROP, "You'd better hang on to that. If you want"
      + " someone to check it, you can <submit> it to them.\n");
    add_prop(OBJ_I_VOLUME, 2);
    add_prop(OBJ_I_WEIGHT, 1);

    add_cmd_item( ({ "list", "checklist", "check list",
                     "document", "official document",
                     "official-looking document" }),
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
    add_action(submit_form, "give");
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
    string  not_yet = "   (not yet signed)  |\n";
    string  done1   = "             Xania   |\n";
    string  done2   = "             Xorfin  |\n";
    string  q1 = ((QuestMaster_1) ? done1 : not_yet);
    string  q2 = ((QuestMaster_2) ? done2 : not_yet);

    form_txt = "\n"
    + "  ,------------------------------------------------------------,.\n"
    + "  ---.---------------------------------------------------------  \\\n"
    + "     |                                                            |\n"
    + "     |   By authority of the Sparkle Magistrate, any persons who  |\n"
    + "     |   are able to acquire signatures upon this form will have  |\n"
    + "     |   been shown to further good relations with the township   |\n"
    + "     |   of Gelan in the lands of Calia.                          |\n"
    + "     |                                                            |\n"
    + "     | ========================================================== |\n"
    + "     |  Signature will indicate:              Signed by:          |\n"
    + "     | ========================================================== |\n"
    + "     |  Approval of Mistress of the Academy  " + q1
    + "     |  Approval of Founder of the Cadets    " + q2
    + "     | ========================================================== |\n"
    + "     |                                                            |\n"
    + "     |   Simply <submit> this form to Xania and Xorfin of the     |\n"
    + "     |   Gelan School and Academy to acquire their signatures.    |\n"
    + "     |   Take one of the ships from the Sparkle piers to Calia,   |\n"
    + "     |   and then use the magic map to find your way into the     |\n"
    + "     |   city of Gelan, where the school will appear on the map.  |\n"
    + "     |                                                            |\n"
    + "     |   Once both persons have added their signatures to this    |\n"
    + "     |   form, the owner should return to Sparkle, find Carlsan,  |\n"
    + "     |   and <submit> the form for approval and reward.           |\n"
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
        QuestMaster_2)
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
        who->catch_msg("\nIt looks as if you have acquired all of the"
          + " needed signatures! You can now return and <submit> your"
          + " document to Carlsan.\n");
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
    string *quest_masters = ({ "xania",
                               "xorfin" });

    if (!strlen(arg))
    {
        notify_fail("What do you wish to submit?\n");
        return 0;
    }

    npcs = PARSE_THIS(arg, 
               "[the] [check] [official] [looking] [official-looking]"
             + " 'list' / 'checklist' / 'document' / 'form' [to] [the] %i");
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
            notify_fail("The document is not for a committee. Please"
              + " submit it only to one person at a time.\n");
            return 0;
            break;
    }

    if (!living(npc))
    {
        write("You hold your document out to the "
          + npc->short() + " with a big eager grin on your face."
          + " After a few tense minutes of anticipation, you realize"
          + " that there is not likely to be a response.\n");
        return 1;
    }

    if (interactive(npc))
    {
        write("You get the feeling that person will not be interested"
          + " in dealing with your document.\n");
        return 1;
    }

    if (!this_player()->check_seen(npc))
    {
        write("You'll need to make sure "
          + npc->query_pronoun() + " can see you first.\n");
        return 1;
    }

    write("You submit your document to " 
        + npc->query_the_name(this_player()) + " for a signature.\n");
    tell_room(QCTNAME(this_player()) + " hands a document of some"
      + " kind to " + QTNAME(npc) + ".\n", this_player());

    complete = npc->check_remaining_quests(this_player());

    switch(lower_case(npc->query_name()))
    {
        case "xania":
                if (!QuestMaster_1)
                {
                    npc->command("emote reads the document and"
                      + " smiles softly.");
                    npc->command("say Ah, another come from Sparkle to"
                      + " learn of the Academy, yes? Excellent. I shall"
                      + " now instruct you as to our purpose. Those who" 
                      + " wish to learn the ways of magic may study here"
                      + " in our halls. Please <look> at the room here to"
                      + " discover how to join, if you feel that is your"
                      + " path. I will now add my signature to your"
                      + " document. Be well, my friend.");
                    npc->command("emote signs the document and"
                      + " returns it.");
                    QuestMaster_1 = 1;
                    return 1;
                }

                if (this_player()->query_prop(XANIA_PROP) == "done")
                {
                    npc->command("chuckle polite");
                    npc->command("say Perhaps you are confused? I have"
                      + " already signed your document. It is time"
                      + " to move on, my friend!");
                    return 1;
                }

                npc->command("smile apprec");
                npc->command("say As you can see if you <exa document>"
                  + " I have already signed your document, making it"
                  + " as official as I am able.");
                this_player()->add_prop(XANIA_PROP, "done");
                return 1;
            break;
        case "xorfin":
                if (!QuestMaster_2)
                {
                    npc->command("emote reads the document and"
                      + " smiles softly.");
                    npc->command("say Oho! More come from Sparkle to"
                      + " see the life of a Cadet, eh? Yes. Have an"
                      + " ear then, friend, and learn. Those who" 
                      + " wish to hone their skills can do so with us"
                      + " in our halls. Please <look> at the room here to"
                      + " discover how to join, if you feel up to the"
                      + " challenge. I'll go ahead and add my signature to your"
                      + " document. Fortune speed you, my friend.");
                    npc->command("emote signs the document and"
                      + " returns it.");
                    QuestMaster_2 = 1;
                    return 1;
                }

                if (this_player()->query_prop(XORFIN_PROP) == "done")
                {
                    npc->command("chuckle polite");
                    npc->command("say Perhaps you are confused? I have"
                      + " already signed your document. It is time"
                      + " to move on, my friend!");
                    return 1;
                }

                npc->command("smile apprec");
                npc->command("say As you can see if you <exa document>"
                  + " I have already signed your document, making it"
                  + " as official as I am able.");
                this_player()->add_prop(XORFIN_PROP, "done");
                return 1;
            break;
        case "carlsan":
            break;
        default:
            npc->command("emote looks at the document, frowning"
              + " in confusion.");
            write("Perhaps you should submit it to someone who is actually"
              + " listed on the document, instead?\n");
            return 1;
            break;
    }

    npc->awake_check();
    npc->command("emote peers sleepily at the document.");

    if (!finished_form())
    {
        npc->command("say Oh, it looks like you've still got some work"
          + " to do here. Please get both of the signatures from the"
          + " school and then <submit> it to me when you are done.");
        npc->command("emote returns the document.");
        return 1;
    }

    npc->react_cadets_checklist(this_player());

    set_alarm(0.0, 0.0, "remove_object");

    return 1;
} /* submit_form */