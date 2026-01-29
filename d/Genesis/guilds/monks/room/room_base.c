/*
 * File:    room_base
 * Creator: Cirion, 1998.04.18
 * Purpose: add some nice functionality to the rooms in
 *          the monk's guild hall.
 */
#pragma strict_types
#include "defs.h"
#include <filter_funs.h>
#include <composite.h>
#include <ss_types.h>
#include <tasks.h>
inherit "/std/room";
inherit MONKLIB;

#define STATUE_FILE MONK_LIB + "monk_descriptions"

static int fsize;
static string statue_desc;
static mapping entrance_msg = ([ ]);
static mapping view_entrance_msg = ([ ]);
private int entrance_time;
static object comp_npc;

// climb information, used in a number of rooms
static string climb_destination;
static int climb_difficulty;
static string *climb_messages = ({});
static string *climb_locations = ({});

/*
 * Function name: virtual_desc
 *
 * Description: An experiment in more dynamic descriptions based
 * on the current state of the area. It just uses
 * VBFC's to change the room description based
 * on the state of the room, and is set up using the
 * macro VIRTUAL_DESC.
 *
 * An example of this would be:
 *
 * set_long("The massive gates of this greate hall "
 *     + VIRTUAL_DESC("query_gate_open", "stand wide open",
 *       "stand shut to the world") + ".\n");
 *
 * When evaluating the string, it will call the function
 * query_gate_open() in the room. If the function returns
 * true, then the string returned will be the second
 * argument, otherwise the string will be the third.
 *
 * Agruments:
 *   func_name: The name of the function to call
 *   true_desc: The string to return if the function evaluates to true
 *   false_desc: The string to return if the function evaluates to false
 */
string
virtual_desc(string func_name, string true_desc, string false_desc)
{
    if(call_other(TO, func_name))
        return true_desc;
    else
        return false_desc;
}

/*
 * Function name: filter_see_me
 * Description:   Checks to see if the player passed in can
 *                see this_player()
 * Arguments:     the living to check for
 * Returns:       1 if the player can see this_player()
 */
int
filter_see_me(object who)
{
    if(CAN_SEE_IN_ROOM(who) && CAN_SEE(who, this_player()))
        return 1;
    else
        return 0;
}

/*
 * called by the macro VBFC_SAY(x), will simply send a
 * say() message to the room.
 */
string
vbfc_say(string str)
{
    // Send the message to all the players that can see this_player()
    // we only send to those we can see, because the VBFC_SAY() macro will
    // typically be used for extra messages to others in the room when
    // examining objects, performing actions, etc.
    (filter(all_inventory(environment(this_player())), filter_see_me)
        - ({ this_player() }))->catch_msg(QCTNAME(this_player()) + " " + str);
    
    // return a dummy empty string.
    return "";
}

/*
 * Sometimes we want add_cmd_item() messages to also be seen
 * by 3rd party observers. In order to achieve this, we
 * can append on a VBFC to the end of the message that will
 * send a say() command to the room when evaluated.
 *
 * In this way, we can add simple actions that are viewable
 * by 3rd party observers with the call to:
 *
 * add_third_cmd_item("air", "smell", "You smell the fresh air.\n",
 *     "breathes in the fresh air.\n");
 */
public varargs int
add_third_cmd_item(mixed names, string *cmd_arr, mixed desc_arr, mixed other_arr)
{
    int   i;

    if(pointerp(desc_arr))
    {
        // If they are arrays, they need to match!
        if(pointerp(other_arr) && (sizeof(other_arr) == sizeof(desc_arr)))
        {
            for(i=0;i<sizeof(desc_arr);i++)
                desc_arr[i] += VBFC_SAY(other_arr[i]);
        }
    }
    else if(stringp(desc_arr))
    {
        // If one is a string, the other needs to be as well
        if(stringp(other_arr))
        {
            desc_arr += VBFC_SAY(other_arr);
        }
    }


    // now add the cmd_item as normal.
    return add_cmd_item(names, cmd_arr, desc_arr);
}


/*
 * Function name: resolve_room_path
 * Description:   Resolve a partial room file
 *                specification to the full path.
 * Arguments:     place - the room file or object
 * Returns:       the fully qualified path to the room
 */
mixed
resolve_room_path(mixed place)
{
    string *parts;

    /* If the place can consist of only the filename. Then we should add the
     * complete path name from the filename from this room.
     */
    if (stringp(place) &&
        (place[0] != '/') &&
        (place[0] != '@'))
    {
        parts = explode(file_name(this_object()), "/");
        parts[sizeof(parts) - 1] = place;
        place = implode(parts, "/");
    }

    return place;
}

/*
 * If we have defined some messages to be sent to the player upon
 * entering the room, check for them here and send the message
 * to the player.
 *
 * This is set up with the macro ENTRANCE_MSG(from, msg). E.g.,
 *
 * ENTRANCE_MSG("north", "You enter the great hall from the north.\n");
 *
 * Thus, if the player entering the room came from the room that
 * was from the north of it, they will receive the message.
 */
public void
enter_inv(object to, object from)
{
    int     room, i;
    string  from_cmd;
    mixed   msg;
    string  *places;

    ::enter_inv(to, from);

    // only players see entrance messages...
    if(!interactive(to))
        return;

    // no entrance messages defined...
    if(!m_sizeof(entrance_msg))
        return;

    // check to see if the room we came from is in our list
    // of exit rooms.
    room = member_array(MASTER_OB(from), query_exit_rooms());

    // came from somewhere else other than one of the
    // room's exits (teleported, etc.)
    if((room == -1) || (room >= sizeof(query_exit_cmds())))
        return;

    from_cmd = query_exit_cmds()[room];    

    msg = entrance_msg[from_cmd];

    if(functionp(msg)) // message definition is a function
        msg(to);
    else if(stringp(msg)) // else send the string message to the player
        to->catch_tell(msg);


    // If we specified to send a message when someone
    // enters the room, then do so.
    places = m_indices(view_entrance_msg);

    if(sizeof(places) && (entrance_time < (time() + 1)))
    {
        // only send the message if we have not done so for
        // at least one second (to prevent spam when a large
        // group of players enters somewhere).
        entrance_time = time();

        for(i=0;i<sizeof(places);i++)
        {
            if(find_object(resolve_room_path(places[i])))
                tell_room(resolve_room_path(places[i]),
                    view_entrance_msg[places[i]]);
        }
    }

    return;
}

/*
 * Function name: living_view
 * Description:   Some of these rooms will allow players to
 *                see livings in other rooms. This function
 *                will return a VBFC that will call
 *                living_seen() to describe the seen livings
 *                in the other room.
 * Arguments:     where - the name of the room where livings
 *                    can be seen from here.
 *                message - the message describing them if
 *                    they are seen.
 *                message2 - the message if no one is seen (default
 *                    is "")
 * Returns:       the VBFC that will describe the livings
 */
varargs string
living_view(string where, string message, string message1 = "", string message2 = "")
{
    where = resolve_room_path(where);

    return VBFC("living_seen:" + file_name(TO)
        + "|" + where + "|" + message + "|" + message1
        + "|" + message2);
}

/*
 * Function name: living_seen
 * Description:   Called by a VBFC from living_view, this
 *                will describe any livings viewable from
 *                this room.
 * Arguments:     where - name of the room where we can see things
 *                msg - prefix of the message used to describe
 *                    the livings
 *                msg1 - suffix of the description
 *                msg2 - message to send when we cannot see
 *                    any livings
 * Returns:       The string description of the livings
 */
string
living_seen(string where, string msg, string msg1, string msg2)
{
    object ob, *livings;
    string desc;

    ob = find_object (where);

    if(!ob)
        return msg2; // room is not loaded, so there are no livings

    livings = FILTER_CAN_SEE(FILTER_LIVE(all_inventory(ob)), this_player());

    if(!sizeof(livings))
        return msg2;

    return msg + COMPOSITE_LIVE(livings) + msg1;
}

string
describe_statues(int top)
{
    int i, min, max;
    string statues, *parts, desc, name, *descs = ({});

    if(fsize != file_size(STATUE_FILE))
    {
        // set the file size flag, so we do not read in the file each time
        fsize = file_size(STATUE_FILE); 
        // read in the file
        statues = read_file(STATUE_FILE);
        parts = explode(statues, "\n"); // break it up line by line

        if(top)
        {
            min = 0;
            max = sizeof(parts)/2;
        }
        else
        {
            min = sizeof(parts)/2;
            max = sizeof(parts);
        }

        for(i=min;i<max;i++)
        {
            sscanf(parts[i], "%s (%s)", desc, name);
            if(strlen(desc))
                descs += ({ LANG_ADDART(desc) });
        }

        statue_desc = COMPOSITE_WORDS(descs);
    }

    return statue_desc;
}

/*
 * Function name: msk_setup_training
 * Description:   Setup training in a room that is a training
 *                room for the monks. It will cone and configure
 *                the training objects. See ~monks/lib/train.c
 *                for details and documentation.
 * Arguments:     type - the type of guild to setup for (either
 *                    SS_LAYMAN or SS_OCCUP)
 *                skills - array of skills that will be trained
 *                    in this room.
 * Returns:       the training object.
 */
public object
msk_setup_training(int type, int *skills)
{
    object train_ob;

    reset_euid();

    train_ob = clone_object(MONK_LIB + "train");
    train_ob->mt_setup_skills_config(type, skills);
    train_ob->move(this_object());

    return train_ob;
}

/*
 * Function name: set_composite_npc
 * Description:   Enable the description of the NPC in the room, via
 *                a VBFC.
 * Arguments:     npc - the npc object we will check for before evaluating
 *                    the VBFC.
 */
void
set_composite_npc(object npc)
{
    comp_npc = npc;
}

/*
 * Function name: evaluate_composite_npc
 * Description:   Called via a VBFC in a room object, will check
 *                to see if the NPC we registered is present and
 *                exists, and in that case, will return its
 *                room compiste description.
 * Caveat:        You can have only one composite NPC description
 *                per room.
 * Returns:       The string that is the NPC's description in the room
 */
string
evaluate_composite_npc()
{
    if(objectp(comp_npc) && present(comp_npc))
        return comp_npc->query_monk_composite_desc();
    else
        return " ";
}


/*
 * Function name: set_climb_info
 * Description:   Setup climbing from this room
 * Arguments:     dest - the destination room to move the player
 *                    if they are successful
 *                difficulty - the climb task difficulty (e.g., TASK_NORMAL)
 *                places - array of objects to accept (e.g., ({ "wall", "stone" }))
 *                msgs - array (size 4) of messages to give to the player:
 *                    1: success for player
 *                    2: success for those people viewing the player
 *                    3: fail for player
 *                    4: fail for those viewing the player
 *                    5: success for those people in the room in which the
 *                        player arrives.
 * Returns:        void
 */
void
set_climb_info(string dest, int difficulty, string *places, string *msgs)
{
    if(sizeof(msgs) != 5)
        return;

    climb_destination = resolve_room_path(dest);
    climb_difficulty = difficulty;
    climb_messages = msgs;
    climb_locations = places;
}


/*
 * Function name: climb_action
 * Description:   Perform the climb action that was specified
 *                previousley using set_climb_info
 * Arguments:     The string passed as an argument to the command
 * Returns:       1 if success, 0 for failure
 */
int
climb_action (string str)
{
    object tp = this_player();

    notify_fail(capitalize(query_verb()) + " what?\n");

    if(!strlen(str))
        return 0;

    // parse out 'up' and 'the'
    sscanf(str, "up %s", str);
    sscanf(str, "down %s", str);
    sscanf(str, "the %s", str);

    // are we trying to climb a valid place?
    if(member_array(str, climb_locations) == -1)
        return 0;

    if(sizeof(climb_messages) != 5)
    {
        throw("Invalid climb_messages array set.");
        return 1;
    }

    if (tp->resolve_task(climb_difficulty, ({TS_STR, SS_CLIMB})) <= 0)
    {
        write(climb_messages[2] + "\n");
        say(QCTNAME(tp) + " " + climb_messages[3] + "\n");
    }
    else
    {
        write(climb_messages[0] + "\n");
        say(QCTNAME(tp) + " " + climb_messages[1] + "\n");
        tp->move_living("M", climb_destination, 1, 0);
        say(QCNAME(tp) + " " + climb_messages[4] + "\n");
    }

    return 1;
}

void
init ()
{
    ::init();

    if(sizeof(climb_locations))
    {
        add_action(climb_action, "climb");
        add_action(climb_action, "scale");
    }
}

