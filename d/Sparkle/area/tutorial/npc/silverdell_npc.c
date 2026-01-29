/*
 *  /d/Sparkle/area/tutorial/npc/silverdell_npc.c
 *
 *  The standard file for npcs in Greenhollow
 *
 *  Created August 2004, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit "/std/monster";

#include <login.h>
#include <macros.h>


/* prototypes */
public void        create_silverdell_npc();
public void        create_monster();
public void        add_silverdell_asks();
public string      greenhollow_answer();
public string      silverdell_answer();
public string      job_answer();
public string      game_answer();
public string      lars_answer();
public string      help_answer();
public void        catch_question(string question);
public int         not_here_func();
public string      default_answer();
public string      name_answer();
public void        add_introduced(string name);
public void        react_intro(object tp);
public void        return_object(object obj, object to);
public void        enter_inv(object ob, object from);


/* global variables */
static string       OrigQuestion;
public string       Job_Response;


public void        set_job_response(string s) { Job_Response = s; }
public string      query_job_response() { return Job_Response; }



/*
 * Function name:        create_silverdell_npc
 * Description  :        dummy routine for inheriting files
 */
public void
create_silverdell_npc()
{
} /* create_silverdell_npc */


/*
 * Function name:        create_monster
 * Description  :        set up some standard things for the
 *                       people of Greenhollow
 */
public void
create_monster()
{
    add_name("_silverdell_npc");

    set_job_response("Odd as it sounds, I don't really have a job"
      + " other than to stand around and talk to people such as"
      + " yourself.");
    set_default_answer(VBFC_ME("default_answer"));
    add_silverdell_asks();
    default_config_npc(15);

    add_prop(OBJ_M_NO_ATTACK, "Lars protects these people. You cannot"
      + " harm them.\n");

    create_silverdell_npc();
    set_not_here_func("not_here_func");
} /* create_monster */




/*
 * Function name:        add_silverdell_asks
 * Description  :        These are the standard asks defined for the
 *                       people of Greenhollow. They can be redefined in
 *                       inheriting npcs for more specific responses
 */
public void
add_silverdell_asks()
{
    add_ask( ({ "town", "greenhollow", "town of greenhollow",
                "city", "village" }),
        VBFC_ME("greenhollow_answer"));
    add_ask( ({ "game", "genesis" }),
        VBFC_ME("game_answer"));
    add_ask( ({ "lars" }), 
        VBFC_ME("lars_answer"));
    add_ask( ({ "help", "money" }),
        VBFC_ME("help_answer"));
    add_ask( ({ "job", "occupation", "work", "career" }),
        VBFC_ME("job_answer"));
    add_ask( ({ "land", "lands", "area", "silverdell", "region", "evil" }),
        VBFC_ME("silverdell_answer"));
} /* add_silverdell_asks */



/*
 * Function name:       greenhollow_answer
 * Description  :       response to an add_ask
 */
public string
greenhollow_answer()
{
    switch (random(3))
    {
    case 0:
        command("say I love living in Greenhollow. Life here is about"
              + " helping people like you.");
        break;
    case 1:
        command("say This little town has just about everything you"
              + " might need in it. Please explore it!");
        break;
    case 2:
        command("say Lars made a bargain with us here in Greenhollow."
              + " We keep our promise, and he keeps his.");
        break;
    }
    return "";
} /* greenhollow_answer */


/*
 * Function name:        job_answer
 * Description  :        repond to an add_ask
 */
public string
job_answer()
{
    command("smile polite");
    command("say " + Job_Response);

    return "";
} /* job_answer */


/*
 * Function name:       game_answer
 * Description  :       response to an add_ask
 */
public string
game_answer()
{
    switch (random(3))
    {
    case 0:
        command("say Genesis is the first LPMUD. It was created"
              + " by Lars many years ago.");
        break;
    case 1:
        command("say People have been playing Genesis for years"
              + " and years. We hope you will too!");
    case 2:
        command("say Genesis is a huge game. You really won't"
              + " believe how much there is to see and do here.");
        break;
    }
    return "";
} /* game_answer */


/*
 * Function name:        silverdell_answer
 * Description  :        respond to an add_ask
 */
public string
silverdell_answer()
{
    if (CHECK_TUTORIAL_BIT(DESTROYER_BIT))
    {
        command("say Silverdell was a wonderful land until you came,"
          + " along you horrible monster!");
    }
    else if (CHECK_TUTORIAL_BIT(SAVIOR_BIT))
    {
        command("say Silverdell is a land of peace and beauty once again,"
          + " thanks to you! You are a hero to us all!");
    }
    else
    {
        command("say Silverdell is a beautiful land. I just wish we could"
          + " rid it of the evil that plagues it.");
    }

    return "";
} /* silverdell_answer */


/*
 * Function name:       lars_answer
 * Description  :       response to an add_ask
 */
public string
lars_answer()
{
    command("say Lars was a student at Chalmers Institute of"
          + " Technology. Not only is he the founder of this"
          + " game, but he remains here to help out those who"
          + " play. Lars made a bargain with us here in Greenhollow."
          + " In return for showing new players how to get along"
          + " in the game, he gives us eternal protection from"
          + " harm. Rumour has it that he even has struck a bargain"
          + " with Death itself!");
    return "";
} /* lars_answer */


/*
 * Function name:       help_answer
 * Description  :       response to an add_ask
 */
public string
help_answer()
{
    command("say The best help I can offer right now is to tell you"
          + " to explore this area completely, and read all of the"
          + " tutorial signs that we have set up for you.");
    return "";
} /* help_answer */


/*
 * Function name:       catch_question
 * Description  :       intercept /std/act/asking.c's catch_question() to:
 *                      1) strip leading "for", "about" and trailing "?"
 *                      2) remember the original question
 * Arguments:           string question -- whatever the player asked
 */
public void
catch_question(string question)
{
    string      *tmp_arr,                       /* preps/verbs of interest */
                stuff1, stuff2, stuff3;         /* tmp strings */

    if (objectp(query_attack()))
    {
        return; /* no answers if fighting */
    }

    OrigQuestion = question;
    if (strlen(question))
    {
        /* strip off leading "for", "about" and trailing " ?" */
        tmp_arr = ({ "for", "about" });
        if (parse_command(question, ({}), "%p %s", tmp_arr, stuff1))
        {
            question = stuff1;
        }
        if (sscanf(question, "%s ?", stuff1) ||
            sscanf(question, "%s?", stuff1))
        {
            question = stuff1;
        }
    }
    ::catch_question(question);
} /* catch_question */


/*
 * Function name:       not_here_func
 * Description  :       called when player asks question & leaves
 * Returns      :       0 -> don't answer the question
 */
public int
not_here_func()
{
     command("peer");
     command("shout Nice talking with you!");
     return 0;
} /* not_here_func */


/* 
 * Function name:       default_answer
 * Description  :       give the default response to questions
 */
public string
default_answer()
{
    command("smile . "+this_player()->query_real_name());
    command("say I'm not sure I have much to say about that.");
    return "";
} /* default_answer */


/* 
 * Function name:       name_answer
 * Description  :       respond to questions about name
 *
 */
public string
name_answer()
{
    object      tp = this_player();

    /* probably unnecessary, since we set not_here_func, but ... */
    if (!objectp(tp))
    {
        return "";
    }

    command("smile");
    command("say It is good to meet you, "+
        this_player()->query_race_name()+".");
    command("say I wish you well.");

    return "";
} /* name_answer */


/*
 * Function name:       add_introduced
 * Description  :       Add the name of a living who has introduced to us
 * Arguments    :       string name -- name of the introduced living
 */
public void
add_introduced(string name)
{
    /* wizards always know the npc name, so query_met() is true.
     * however, assume that if a wiz intro'd, we should respond
     */
    if (interactive(this_player()) &&
        CAN_SEE_IN_ROOM(this_object()) &&
        CAN_SEE(this_object(), this_player()) &&
        (!this_player()->query_met(query_name()) ||
         this_player()->query_wiz_level()))
    {
        set_alarm(1.0, 0.0, &react_intro(this_player()));
    }
} /* add_introduced */


/*
 * Function name:        react_intro
 * Description  :        respond to introduction
 * Arguments    :        object tp -- the person who intro'd
 */
public void
react_intro(object tp)
{
    if (environment(tp) != environment())
    {
        command("hmm");
        return;
    }

    switch(random(6))
    {
    case 0:
        command("bow court "+tp->query_real_name());
        break;
    case 1:
        command("say So good to meet you!");
        break;
    case 2:
        command("say A very nice name you have.");
        break;
    case 3:
        command("say Lars said there'd be more of you coming soon.");
        break;
    case 4: 
        command("smile .");
        command("nod appr");

        break;
    case 5:
        command("say So nice to see more new faces around.");
        break;
    }
} /* react_intro */


/* 
 * Function name:        return_object
 * Description  :        have npcs give things they are given back
 *                       to players
 * Arguments    :        object obj - the object given
 *                       object to  - the player who gave it
 */
public void
return_object(object obj, object to)
{
    command("say Thanks, but I don't think I need that.");
    command("give " + OB_NAME(obj) + " to " + OB_NAME(to));
    if (environment(obj) == this_object())
    {
       command("drop " + OB_NAME(obj));
    }
} /* return_object */


/* 
 * Function name: enter_inv
 * Description:   Called when objects enter this container or when an
 *                object has just changed its weight/volume/light status.
 * Arguments:     ob: The object that just entered this inventory
 *                from: The object from which it came.
 */
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!objectp(ob) || !objectp(from) || !living(from))
        return;

    set_alarm(0.5, 0.0, &return_object(ob, from));
} /* enter_inv */

/*
 * Function name:       npcsize
 * Description  :       set CONT_I_HEIGHT, CONT_I_WEIGHT and
 *                      CONT_I_VOLUME of an npc to give the 
 *                      desired appearance
 * Arguments    :       object npc -- the npc
 *              :       string hdesc -- the desired height desc
 *                                       (e.g., "tall")
 *              :       string wdesc -- the desired width desc
 *                                      (e.g., "plump")
 * Returns      :       1 on success, 0 on failure
 *
 * This function is copied from /d/Gondor/workroom.c. It was created
 * by Gnadnar to fix problems with npcs looking other than they should.
 */
public int
npcsize(object npc, string hdesc, string wdesc)
{
    int         hindex,
                windex,
                *spread,
                spreadsize,
                height,
                *raceattr;

    if (!objectp(npc) ||
        !npc->query_npc() ||
        !strlen(hdesc) ||
        !strlen(wdesc))
    {
        return 0;
    }
    raceattr = RACEATTR[npc->query_race()];
    if (sizeof(raceattr) < 6 ||
        raceattr[0] <= 0 ||
        raceattr[4] <= 0 ||
        raceattr[5] <= 0)
    {
        return 0;
    }
    if (hdesc == "normal")
    {
        hdesc = "of normal length";
    }
    if ((hindex = member_array(hdesc, HEIGHTDESC)) < 0)
    {
        return 0;
    }
    if (wdesc == "normal")
    {
        wdesc = "of normal width";
    }
    if ((windex = member_array(wdesc, WIDTHDESC)) < 0)
    {
        return 0;
    }
    spread = SPREAD_PROC;
    spreadsize = sizeof(spread);
    if (hindex >= spreadsize ||
        windex >= spreadsize)
    {
        return 0;
    }

    height = ((raceattr[0] * spread[hindex]) / 100);
    npc->add_prop(CONT_I_HEIGHT, height);
    npc->add_prop(CONT_I_WEIGHT,
        (((raceattr[5] * spread[windex]) / 100) * height));
    npc->add_prop(CONT_I_VOLUME,
        (raceattr[4] * 1000));
    return 1;
} /* npcsize */
