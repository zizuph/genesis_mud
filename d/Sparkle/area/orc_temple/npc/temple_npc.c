/*
 *  /d/Sparkle/area/orc_temple/npc/temple_goblin.c
 *
 *  This is the base file for all npcs in the orc temple.
 *
 *  Created November 2010, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/std/monster";

#include <macros.h>
#include "../defs.h"


/* Global Variables */
static string       OrigQuestion;
public string       Job_Response;
public string      *Dungeon_Response;
public string      *Demon_Response;
public string      *Prisoner_Response;
public string      *Priest_Response;
public string      *Runt_Response;
public string      *Warrior_Response;
public string       Jailer_Response;
public string       Hp_Response;
public string       Give_Response = "Keep your things to yourself!";

/* Prototypes */
public string         create_temple_npc();
nomask string         create_monster();
public string         varied_response(string responses);
public void           catch_question(string question);
public void           add_introduced(string name);
public void           react_intro(object tp);
public void           intro_responses(object tp);
public int            not_here_func();
public void           return_object(object obj, object to);
public void           enter_inv(object ob, object from);
public void           assist_npc(object enemy);
public void           get_assistance(object enemy);

/* These routines are redefined in inheriting files to give personality
 * to the way in which the npcs do or do not help one another in fights.
 */
public void           ask_for_assistance()     { } 
public void           assist()                 { }          
public void           not_assist()             { } 
public void           not_ask_for_assistance() { }

/* These routines give individual personalities for answers to various
 * standard questions about the dungeon, etc.
 */
public void     set_job_response(string s)       { Job_Response = s;      }
public void     set_dungeon_response(string *s)  { Dungeon_Response = s;  }
public void     set_demon_response(string *s)    { Demon_Response = s;    }
public void     set_prisoner_response(string *s) { Prisoner_Response = s; }
public void     set_priest_response(string *s)   { Priest_Response = s;   }
public void     set_runt_response(string *s)     { Runt_Response = s;     }
public void     set_warrior_response(string *s)  { Warrior_Response = s;  }
public void     set_jailer_response(string s)    { Jailer_Response = s;   }
public void     set_hp_response(string s)        { Hp_Response = s;       }
public void     set_give_response(string s)      { Give_Response = s;     }







/*
 * Function name:        temple_npc
 * Description  :        dummy function to be replaced in inheriting files
 */
public string
create_temple_npc()
{
} /* create_temple_npc */


/*
 * Function name:        create_monster
 * Description  :        The constructor for the monster
 */
nomask string
create_monster()
{
    setuid();
    seteuid(getuid());

    set_not_here_func("not_here_func");

    create_temple_npc();
} /* create_monster */


/*
 * Function name:        add_dungeon_asks
 * Description  :        These are the standard asks defined for the
 *                       Army of Darkness npcs. They can be redefined in
 *                       inheriting npcs for more specific responses
 */
public string
add_dungeon_asks()
{
    add_ask( ({ "dungeon", "dungeons", "prison", "jail", "temple" }),
        "say " + ("@@varied_response|dungeon@@"), 1);
    add_ask( ({ "demon", "arch demon", "demons", "yogsothoth" }),
        "say " + ("@@varied_response|demon@@"), 1);
    add_ask( ({ "prisoner", "prisoners" }), 
        "say " + ("@@varied_response|prisoner@@"), 1);
    add_ask( ({ "job", "work", "occupation" }),
        "say " + Job_Response, 1);
    add_ask( ({ "priest", "priests", "orcish priest", "orcish priests" }),
        "say " + ("@@varied_response|priest@@"), 1);
    add_ask( ({ "runt", "runts", "orcish runt", "orcish runts" }),
        "say " + ("@@varied_response|runt@@"), 1);
    add_ask( ({ "warrior", "warriors", "orcish warrior", "orcish warriors" }),
        "say " + ("@@varied_response|warrior@@"), 1);
    add_ask( ({ "high priest", "kerchak" }),
        "say " + Hp_Response, 1);
    add_ask( ({ "jailer", "orcish jailer" }),
        "say " + Jailer_Response, 1);
} /* add_dungeon_asks */


/*
 * Function name:        varied_response
 * Description  :        allow the npc to make one of a few different
 *                       responses to an ask
 * Arguments    :        string arg - which topic we're using
 * Returns      :        string - the specific response
 */
public string
varied_response(string arg)
{
    string *responses;

    switch (arg)
    {
        case "dungeon":
            responses = Dungeon_Response;
            break;
        case "demon":
            responses = Demon_Response;
            break;
        case "prisoner":
            responses = Prisoner_Response;
            break;
        case "priest":
            responses = Priest_Response;
            break;
        case "warrior":
            responses = Warrior_Response;
            break;
        case "runt":
            responses = Runt_Response;
            break;
    }

    return one_of_list(responses);
} /* varied_response */


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
        command("emote looks around as if trying to find someone.");
        return;
    }

    if (query_real_name() == HIGH_PRIEST)
    {
        command("introduce me");
        return;
    }

    intro_responses(tp);
} /* react_intro */


/*
 * Function name:        intro_responses
 * Description  :        provide responses to an introduction
 * Arguments    :        object tp - this_player()
 *
 * This should be redefined in inheriting npcs for flavor variation.
 */
public void
intro_responses(object tp)
{
} /* intro_responses */


/*
 * Function name:       not_here_func
 * Description  :       called when player asks question & leaves
 * Returns      :       0 -> don't answer the question
 */
public int
not_here_func()
{
     command("peer");
     return 0;
} /* not_here_func */


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
    if (query_race_name() == "goblin" && obj->id("coin"))
    {
        command("grin greed");
        command("say Keeping that!");
        return;
    }

    if (obj->id("key"))
    {
        command("say Hey! Where you get that?!");
        command("say I keep! You get out!");
        return;
    }

    command("say " + Give_Response);
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
    {
        return;
    }

    set_alarm(0.5, 0.0, &return_object(ob, from));
} /* enter_inv */


/*
 * Function name:        run_away
 * Description  :        npcs that run around are *annoying* We don't
 *                       have these do that.
 */
public void
run_away()
{
    command("emote wails in desperation!");
}


/*
 * Function name:        assist_npc
 * Description  :        Have npcs help one another ... sometimes
 * Arguments    :        object enemy - who attacked us
 */
public void 
assist_npc(object enemy)
{
    if (member_array(enemy, this_object()->query_enemy(-1)) >= 0) 
    {
        return;
    }

    if (!random(3))
    {
        assist();   
        this_object()->attack_object(enemy);
    }
    else
    {
        not_assist();
    }
}


/*
 * Function name:        get_assistance
 * Description  :        Have npcs ask for assistance ... sometimes
 * Arguments    :        object enemy - the one who attacked us
 */
public void
get_assistance(object enemy)
{
    if (!random(2))
    {
        ask_for_assistance();

        filter(all_inventory(environment()), 
          &->id(ORC_TEMPLE_NPC))->assist_npc(enemy);
    }
    else
    {
        not_ask_for_assistance();
    }
} /* get_assistance */
