/*
 * File:     npc.c
 * Created:  Cirion 1998.05.26
 * Purpose:  inheritable npc object for all kaheda NPCs
 * Modification Log:
 *
 */
#pragma strict_types

#include "defs.h"
#include <ss_types.h>
#include <money.h>
#include <options.h>
#include <math.h>
#include <composite.h>


inherit "/std/monster";
inherit "/d/Genesis/lib/intro";

inherit MONKLIB;

public void refresh_ask_list ();

private mixed mn_composite_desc;
private object mn_composite_room;

public mapping ask_mapping_redirect;
public mixed ask_list = ({ });
private static string *base_questions = ({ });

public void
m_save_npc ()
{
    seteuid (getuid (this_object ()));

    // this needs to be done since save_object() saves
    // all public variables, and NPCs seem to have an
    // awful ot of these (as well as the fact that there
    // is no save_array() efun).
    ask_mapping_redirect = ([ "asks" : ask_list ]);    
    save_map(ask_mapping_redirect, 
        MONK_NPC + query_real_name ());
    refresh_ask_list ();
}

public void
m_restore_npc ()
{
    seteuid (getuid (this_object ()));
    ask_mapping_redirect = restore_map(MONK_NPC
        + query_real_name ());

    if (m_sizeof (ask_mapping_redirect))
    {
        ask_list = ask_mapping_redirect ["asks"];
        refresh_ask_list ();
    }
}



public string
council_extra_long (object who)
{
    if (!who || !objectp (who))
        who = this_player ();

    if (m_query_council_member (who, 1))
    {
        return "    As a Council member, you may 'instruct' "
            + "this monk to respond to "
            + "specific questions with a certain answer.\n";
        return "";
    }
    else
        return "";
}

public string
long (mixed for_obj)
{
    return ::long (for_obj) + council_extra_long (for_obj);
}

/*
 * Function name: create_monk
 * Description:   function to be redefined by the inheriting
 *                object in which variables are set up.
 */
public void
create_monk ()
{

}

/*
 * Function name: create_monster
 * Description:   creator for the monster. Set to nomask so
 *                inheriting objects are forced to use the
 *                create_monk () function.
 */
public nomask void
create_monster ()
{
    ::create_monster();

    reset_euid ();

    create_monk ();
    seteuid (getuid (this_object ()));
    m_restore_npc ();
}

/*
 * Function name: set_height_weight
 * Description:   Function to set the weight and height
 *                of an NPC.
 * Arguments:     feet (float) - height in feet
 *                pounds - weight in pounds
 */
void
set_height_weight(float feet, int pounds)
{
    int centimeters, grams;

    grams = (pounds * 454); // 453.6, actually
    centimeters = ftoi(feet * 30.5);

    add_prop(CONT_I_HEIGHT, centimeters);
    add_prop(CONT_I_WEIGHT, grams);
}

/*
 * Function name: init_monk
 * Description:   initializes some default values for
 *                the npc.
 * Arguments:     level: the guild level the monk will be set
 *                to (default = 1)
 */
public varargs nomask void
init_monk (int level = 60)
{
    object    shadow;

    set_stats (({ random (level) + 50, random (level) + 50, random (level) + 50,
        random (level) + 50, random (level) + 50, random (level) + 50 }));

    set_base_stat (SS_OCCUP, random (level) + 50);
    set_base_stat (SS_LAYMAN, random (level) + 50);

    set_skill (SS_UNARM_COMBAT, MAX (10, random(level)));
    set_skill (SS_DEFENCE, MAX (10, random(level)));
    set_skill (MONK_SKILL_FOCUS, MAX (10, random(level)));
    set_skill (MONK_SKILL_STRIKE, MAX (10, random(level)));
    set_skill (MONK_SKILL_PLEXUS, MAX (10, random(level)));
    set_skill (SS_AWARENESS, MAX (10, random(level)));
    set_skill (SS_LANGUAGE, MAX (10, random(level)));
    set_skill (SS_BLIND_COMBAT, MAX (10, random(level)));
    set_skill (SS_SWIM, MAX (10, random(level)));
    set_skill (SS_CLIMB, MAX (10, random(level)));
    set_skill (SS_LOC_SENSE, MAX (10, random(level)));
    set_skill (SS_HERBALISM, MAX (10, random(level)));

    set_height_weight(5.8, 120); // 5'8" tall, 120 pounds default


    add_prop (NPC_I_NO_LOOKS, 1); // I usually describe appearance myself

    add_name ("monk");


    shadow = clone_object(MONK_OCC_SHADOW);
    shadow->shadow_me(this_object(), MONK_OCC_TYPE, MONK_OCC_STYLE, MONK_OCC_NAME);

}


/*
 * Function name: introduce
 * Description:   Called when someone introduces to this NPC,
 *                it defines the command they will use.
 * Arguments:     who - the object introducing themselves
 */
public void
introduce(object who)
{
    set_alarm(1.0, 0.0, &command("introduce myself to " + OB_NAME(who)));

    if(this_object()->query_gender() == G_FEMALE)
    {
        set_alarm(2.0, 0.0, &command(ONEOF(({"smile sweetly",
            "curtsey gracefully", "nod warm", "smile softly" }))));
    }
    else // male
    {
        // do nothing, for now
    }

} 

/*
 * Function name: equip_monk
 * Description:   give some standard equipment
 *                to the monk npc, as well as the equipment
 *                we specified in the parameters.
 * Arguments:     money: array of integers specifying the
 *                amount of money to clone to the monk, in
 *                the form of ({ cc, sc, gc, pc })
 *                equipment: array of strings of equipment to
 *                clone to the monk. Can be the full filename,
 *                of the name of equipment in the MONK_OBJ dir.
 * Returns:       void
 */
public varargs nomask void
equip_monk (int *money = ({}), string *ob_names = ({}))
{
    object arm;
    int    i;
    string ob_name;

    // give the npc the money we specified
    for (i = 0; i < sizeof (money) && i < sizeof (MONEY_TYPES); i++)
    {
        if (money[i] > 0)
            MONEY_MAKE (money[i], MONEY_TYPES[i])->move (TO, 1);
    }

    // clone in the equipment we specified. reset_euid() is handled
    // in the create function.
    for (i = 0; i < sizeof (ob_names); i++)
    {
        ob_name = ob_names[i];

        // is the file a fully qualified path name? If not,
        // check also the MONK_OBJ directory.
        if (file_size (ob_name + ".c") <= 0)
            ob_name = MONK_OBJ + ob_name;

        clone_object (ob_name)->move (TO, 1);
    }

    // default equipment that all monks should have
    arm = clone_object (MONK_OBJ + "robe");
    arm->randomize (TO);
    arm->move (TO, 1);

    catch(clone_object (MONK_OBJ + "shirt")->move(TO, 1));
    catch(clone_object (MONK_OBJ + "belt")->move(TO, 1));
    catch(clone_object (MONK_OBJ + "sandals")->move(TO, 1));
    catch(clone_object (MONK_OBJ + "pants")->move(TO, 1));

    command ("wear all");
    command ("wield all");
}

/*
 * Function name: special_attack
 * Description:   this is called every round by the combat
 *                object. We will always attempt to use our
 *                special attacks whenever we can.
 * Arguments:     victim: the enemy
 * Returns:       1 if we will be using the special attack instead
 *                of a normal attack, 0 otherwise.
 * Note:          this instance of the function always returns 0,
 *                since a special attack command just starts preparation
 *                for the special attack, which will be executed
 *                after a delay. Thus, we do not want to block normal
 *                combat operations.
 */
public int
special_attack (object victim)
{
    if(!random(2))
    {
        // command return 1 if it was successfully executed. if
        // it wasn't, maybe our npc was not an occup monk. In any
        // case, allow us to fall out of the if statement and try
        // for mstrike.
        if (command ("plexus"))
            return 0;
    }

    // else try to use mstrike
    command ("mstrike");

    return 0;
}


/*
 * Function name: monk_say
 * Description:   have the monk say something. If a monk
 *                langauge is evenr implemented, this can be
 *                an easy way to have the monk use a special
 *                command for speaking to fellow monks.
 * Arguments:     str: the string to speak
 *                delay: the delay in which it will be spoken
 *                (default is -1, which means no delay)
 *                to_whom: the person to whom the monk is
 *                speaking (default is this_player())
 * Returns:       if the delay is -1, the return value from
 *                the command () function call, otherwise the
 *                alarm_id of the delayed action.
 */
int
monk_say (string str, int delay = -1, object to_who = this_player ())
{
    string speak_command;

    speak_command = "say";

    if (delay >= 0)
        return set_alarm (itof (delay), 0.0, &command (speak_command + " " + str));
    else
        return command (speak_command + " " + str);

}


/*
 * Monk descriptions sometimes appear in a room description.
 */

/*
 * Function name: set_monk_room_composite
 * Description:   Sets the monks description as appearing in the
 *                room's composite description.
 * Arguments:     composite_desc - string to show or string function to
 *                    call to get our description in the room's desc.
 *                which_room - room in which this feature is enabled
 */
public varargs void
set_monk_room_composite(mixed composite_desc, object which_room = environment(this_object()))
{
    mn_composite_desc = composite_desc;
    mn_composite_room = which_room;
}

/*
 * Function name: query_no_show_composite
 * Description:   Redifines function that will check to see if
 *                the monk shows up in the room description or
 *                as a regular NPC. It will check to see if the
 *                player entered the room with OPT_BRIEF on, in
 *                which case we want to show the NPC normally in the room.
 *                Otherwise, the NPC will show up in the composite
 *                description of the room.
 * Returns:       1 if the monk does not show up normally, but
 *                instead in the lonk description of the room.
 */
public int
query_no_show_composite()
{
    object    player;
    int       brief, look_verb, recurse_count;

    // not set -- return the current noshow setting
    if(!objectp(mn_composite_room))
        return ::query_no_show_composite();

    // check to see if we are in the room where we are supposed
    // to show up in the long desc
    if(environment(this_object()) != mn_composite_room)
        return ::query_no_show_composite();

    // recurse back through the chain of calling objects to
    // obtain the player that is checking our composite desc
    recurse_count = -1;
    while( (!interactive(player = calling_object(recurse_count))) && (objectp(player)) )
        recurse_count--;

    // not a player requesting our description
    if(!interactive(player))
        return ::query_no_show_composite();

    brief = player->query_option(OPT_BRIEF);
    look_verb = ((query_verb() == "look") || (query_verb() == "l"));

    // player typed "look" to examine the room desc: composite
    // in room description is active
    if(look_verb)
        return 1;

    // player (hopefully) entered the room in brief mode: turn off
    // composite mode;
    if(brief)
        return ::query_no_show_composite();

    return 1; // fall through: composite desc is on
}

/*
 * Function name: query_monk_composite_desc
 * Description:   Returns the compiste setting for room descriptions
 *                of this monk. May have been set to either a function
 *                or string.
 * Returns:       The composite description of the monk that was set
 *                in the room.
 */
public string
query_monk_composite_desc()
{
    function   comp_func;

    if(functionp(mn_composite_desc))
    {
        // need to put this in a function var to avoid compile
        // errors.
        comp_func = mn_composite_desc;
        return comp_func();

    }
    else if(stringp(mn_composite_desc))
        return mn_composite_desc;
    else
        return " ";
}

/*
 * Function name: vbfc_one_living
 * Description:   Used for emotes in add_acts, will return the
 *                name of one interactive in the area.
 * Returns:       the name of a random person in the room
 */
string
vbfc_one_living()
{
    object *livings, who;

    livings = filter(all_inventory(environment(this_object())), interactive);

    if (sizeof (livings) <= 0)
        return "";

    who = livings[random(sizeof(livings))];
    return who->query_name();
}


public mixed
find_ask (string str)
{
    int             i;
    string         *ask_questions;

    for (i = 0; i < sizeof (ask_list); i++)
    {
        if (sizeof (ask_list [i]) > 0)
        {
            ask_questions = ask_list [i][0];

            if (!pointerp (ask_questions))
                continue;

            if (member_array (str, ask_questions) > -1)
                return ask_list [i];
        }
    }

    return 0;
}

/*
 * Function:        instruct
 * Description:     Command that council members are able to
 *                  issue on NPCs to allow them to instruct the
 *                  NPC to respond to a specific question (or
 *                  set of questions) with a certain answer.
 */
public int
instruct (string str)
{
    string          question;
    string          answer;
    string          dummy;
    mixed           ask_info;
    string         *questions;
    int             i;
    int             j;
    int             k;

    if (!m_query_council_member (this_player ()))
        return 0;

    notify_fail ("As a Council member, if you want to instruct "
        + "this monk to answer "
        + "a certain question with a certain answer, do "
        + "'instruct monk to answer <question> with the repsonse "
        + "<response>'.\nFor example, 'instruct monk to answer "
        + "joining with the response You may join the Order by "
        + "applying in the eastern temple at the alter'.\nYou can "
        + "designate multiple questions for a single reponse by doing "
        + "'instruct monk to answer <question1;question2;question3...> "
        + "with the response <answer>.\nYou can also "
        + "'instruct monk to answer <question> with nothing' in "
        + "order to remove a previous response.\n'instruct list' will "
        + "list all the questions I am currently answering.\n");

    if (!strlen (str))
        return 0;

    if (str == "list")
    {
        write ("Current questions I will repond to:\n");

        for (j = 0; j < sizeof (ask_list); j++)
        {
            if (pointerp (ask_list [j]) && sizeof (ask_list[j]) > 0)
            {
                write (COMPOSITE_WORDS (ask_list[j][0]) + "\n");
            }
        }

        return 1;
    }

    parse_command (str, ({}), "%s 'to' 'answer' %s 'with' 'the' "
        + "'response' %s", dummy, question, answer);

    if (!strlen (question))
        return 0;

    if (!strlen (answer))
        return 0;

    if (answer == "nothing")
    {
        ask_info = find_ask (question);

        if (!pointerp (ask_info) || ask_info == 0)
        {
            command ("say I am not currently answering that question "
                + "with anything...");
            return 1;
        }

        command ("say I will no longer answer the question '"
            + question + "' with any reponse.");

        ask_list -= ({ ask_info });
        m_save_npc ();
        refresh_ask_list ();

        return 1;
    }

    // let's not go overboard -- max out at 99 for the number of
    // questions we can answer.
    if (sizeof (ask_list) > 99)
    {
        command ("say Sorry, I can't remember any more answers for your "
            + "questions!");
        command ("say You will need to remove some other quesitons before "
            + "I can answer new ones.");
        return 1;
    }

    // multiple questions are delimited by ';'
    questions = explode (question, ";");

    for (i = 0; i < sizeof (questions); i++)
    {
        if (pointerp (find_ask (questions [i])))
        {
            command ("say Sorry, but I am already answering the "
                + "question '" + questions [i] + ".");
            return 1;
        }
    }

    ask_list += ({ ({ questions, "say " + answer, 1 }) });

    seteuid (getuid (this_object ()));
    m_save_npc ();
    refresh_ask_list ();

    command ("say I will answer with that question with the "
        + "response '" + answer + "' from now on.");
    return 1;
}

public varargs int
add_ask(mixed questions, string answer, int command = 0)
{
	int			i;

	if (stringp (questions))
		base_questions += ({ questions });
	else if (pointerp (questions))
		{
		for (i = 0; i < sizeof (questions); i++)
			base_questions += ({ questions [i] });
		}

	return ::add_ask (questions, answer, command);
}


/*
 * Function:        refresh_ask_list
 * Purpose:         rebuild the NPCs ask list, since masking
 *                  query_ask () will not have the NPC respond
 *                  to those question.
 */
public void
refresh_ask_list ()
{
    int             i;
    int             j;
    int             k;
    mixed           ask_arr;

    ask_arr = query_ask ();

    // wipe out all previous questions.
    for (j = 0; j < sizeof (ask_arr); j++)
    {
        if (pointerp (ask_arr [j]) && sizeof (ask_arr [j]) > 0)
        {
            for (k = 0; k < sizeof (ask_arr[j][0]); k++)
            {
				// make sure the ask was not previously defined in
				// the NPC.
				if (member_array (ask_arr[j][0][k], base_questions) == -1)
                	remove_ask (ask_arr[j][0][k]);
            }
        }
    }

    for (i = 0; i < sizeof (ask_list); i++)
    {
        if (pointerp (ask_list [i]) && sizeof (ask_list [i]) == 3)
            ::add_ask (ask_list [i][0], ask_list [i][1],
                ask_list [i][2]);
    }
}

public void
init_living ()
{
    ::init_living ();
    add_action (instruct, "instruct");

}

