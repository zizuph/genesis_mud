/*
 * /d/Sparkle/area/jade/obj/burden.c
 * A module for a holdable item that slows the room-to-room movement of the
 * holder. As this is a minimally intrusive addition to an item of another
 * class, it does not compete for enter_env() and leave_env()
 * Define those functions in the heir and there call
 * burden_enter_env and burden_leave_env with the same arguments
 *
 * Martin Berka (Mar), 2017-03-05 Sparkle
 */

#pragma no_clone
#pragma save_binary
#pragma strict_types

inherit "/lib/holdable_item"; //To throw something, you must hold it.

#include <composite.h> //Plural handling for mobs
#include <stdproperties.h>
#include <wa_types.h> //For holding
#include <macros.h>
#include "/d/Shire/sys/defs.h"
#include <cmdparse.h> //For paralyze functionality


/* Definitions */
#define HELPER_PATH "/d/Sparkle/area/jade/obj/burden_helper"

/* Global variables */
int     delayed_inv,
        delayed_env,
        delayed_release,
        //slow_cmd_alarm,
        burden_time_limit; //Alarm indicating maximum time burden can be borne
float   time_delay; //Time which player must wait between moves
mapping mob_members; //Stores NPC's responding to beacon and their origins
object  helper;  //The burden_helper object that handles paralysis
string  burdened,   //Name of player who can carry burden - "" = any
        last_path,  //Path of last room from which burden was carried
        fail_message, //Message displayed when action is not allowed yet.
        planned_cmd; //What the player wants to do next

/* Prototypes */
void burden_release_effect(int param = 0);
void check_carried(int force_ending = 0);
void check_new_room();
//void finally_exit(object departing_player);
void new_room_hook(object last_room, object new_room, object player);
//void set_time_delay(float new_delay = -1.0);
//void stop(string cmd);


/*
 * Function name: mob_return
 * Description  : Sends all NPC's summoned by the beacon back where they came
 *      from.
 * Arguments    : (int) send_home (1) or not (0)
 */
void
mob_return(int send_home = 1)
{
    foreach(string responder_file: m_indexes(mob_members))
    {
        object responder = find_object(responder_file);
        if (responder)
        {
            //unset_follow() not behaving, so instead, follow the near-kidnapped
            //around for their protection
            //responder->set_follow(TO->query_name());

            if (send_home) //Send all mob members back where they were before
            {
                object curr_loc = environment(responder);
                //Make sure they are not still where they started

                if (file_name(curr_loc) != mob_members[responder_file])
                {
                    if (strlen(mob_members[responder_file]))
                    {
                        //Attempt to move, and notify if successful
                        if (!responder->move(mob_members[responder_file]))
                        {
                            tell_room(curr_loc, QTNAME(responder)
                                + " hurries away.\n", ({responder}) );
                            tell_room(environment(responder), QNAME(responder)
                                + " arrives.\n", ({responder}) );
                            find_player("mar")->catch_msg("Mob "
                                + responder_file + " returned.\n");
                        }
                        else
                        {
                            find_player("mar")->catch_msg("Mob "
                                + responder_file + " stuck.\n");
                        }
                    }
                    else
                    {
                        tell_room(curr_loc, QTNAME(responder)
                            + " hurries away.\n", responder );
                        responder->remove_object();
                        find_player("mar")->catch_msg("Mob "
                            + responder_file + " deleted.\n");
                    }
                }
            }
        }
        else
        {
            find_player("mar")->catch_msg("Mob " + responder_file
                + " not found.\n");
        }
        m_delkey(mob_members, responder_file);
    }
}


/*
 * Function name: mob_me
 * Description  : Summons a mob of NPCs from adjacent rooms
 *      (matching wildmatch'ed file_paths) to
 *      the bearer, optionally attacking them. Optionally enforces maximum
 *      summoned from elsewhere. If minimum number of NPC's not met, will clone
 *      additional ones.
 * Arguments    : (string array) paths of NPCs suitable for mob - for wildmatch
 *                (string) name of player of interest
 *                (int) maximum number of existing NPCs to summon
 *                (int) minimum number of NPCs to deliver
 */
void
mob_me(string *filepaths = ({}), string player_name = "", int max_summon = 0,
    int min_size = 0)
{
    object player = find_player(player_name);
    object this_room;

    if (!sizeof(filepaths))
    {
        return;
    }

    if (!mob_members)
    {
        mob_members = ([]); //Initialize
    }

    object *mob_arriving = ({});

    if (!player)
    {
        this_room = environment(TO);
    }
    else
    {
        this_room = environment(player);
    }

    foreach(string mobber_path: m_indexes(mob_members))
    {
        object old_mobber = find_object(mobber_path);
        if (!old_mobber) //Probably died
        {
            m_delkey(mob_members, mobber_path);
            continue;
        }
        if (environment(old_mobber) != this_room)
        {
            mob_arriving += ({old_mobber});
            tell_room( environment(old_mobber),
                QTNAME(old_mobber) + " leaves in pursuit.\n",
                ({old_mobber}) );
        }
    }

    string room_path = file_name(this_room);
    object *nearby_rooms = this_room->query_exit_rooms();

    string *nearby_cmds, nearby_path, cmd_to_here;
    int exit_to_here;
    object candidate, nearby_room;

    if (max_summon)
    {
        if (m_sizeof(mob_members) < min_size )
        {
            foreach (object candidate : all_inventory(this_room))
            {
                foreach(string pattern: filepaths)
                {
                    if (wildmatch( pattern+"*", file_name(candidate) )
                        && !IN_ARRAY(candidate, mob_arriving))
                    {
                        mob_members[file_name(candidate)] =
                            file_name(environment(candidate));
                        candidate->set_chat_time(0); //No mob chats in battle
                    }
                }
            }
        }

        if (m_sizeof(mob_members) < min_size )
        {
            foreach (string nearby_path : nearby_rooms)
            {
                nearby_room = find_object(nearby_path);
                exit_to_here = member_array(room_path,
                    nearby_room->query_exit_rooms());

                if (exit_to_here > -1)
                {
                    nearby_cmds = nearby_room->query_exit_cmds();
                    cmd_to_here = nearby_cmds[exit_to_here];

                    foreach (object candidate : all_inventory(nearby_room))
                    {
                        foreach(string pattern: filepaths)
                        {
                            if (wildmatch( pattern, file_name(candidate) )
                                && !IN_ARRAY(candidate, mob_arriving))
                            {
                                mob_members[file_name(candidate)] =
                                    file_name(environment(candidate));
                                mob_arriving += ({candidate});
                                tell_room( nearby_room, QTNAME(candidate)
                                    + " leaves " + cmd_to_here + ".\n",
                                    ({candidate}) );

                                if (m_sizeof(mob_members) >= max_summon)
                                {
                                    break;
                                }
                            }
                        }
                    }
                }
                if (m_sizeof(mob_members) >= max_summon)
                {
                    break;
                }
            }
        }

        if (sizeof(mob_arriving) == 1)
        {
            tell_room( this_room, QCNAME(mob_arriving[0]) + " arrives.\n", 0);
        }
        else if (sizeof(mob_arriving) > 1)
        {
            tell_room(this_room, "A mob consisting of "
                + COMPOSITE_LIVE(mob_arriving) + " arrives.\n", 0);
        }
    }

    if (m_sizeof(mob_members) < min_size)
    {
        for (int i = min_size - m_sizeof(mob_members); i > 0; --i)
        {
            object new_mobber = clone_object(one_of_list(filepaths));
            new_mobber->set_chat_time(200);

            mob_members[file_name(new_mobber)] = "";
            mob_arriving += ({new_mobber});
        }
    }

    foreach (object mobber: mob_arriving)
    {

        mobber->move(this_room); //Arrivals will be reported in bulk
        if (player)
        {
            if (mobber->query_enemy() != player)
            {
                mobber->attack_object(player);
            }
        }
    }
    set_this_player(player); //move() causes the NPC's to take over
}


/*
 * Function name: burden_enter_env
 * Description  : When someone takes the object, they must hold it, and be
 *      burdened by it.
 * Arguments    : (object) the destination
 *                (object) the old location
 */
void
burden_enter_env(object dest, object old)
{
    if (!delayed_env) {
        //Immediately apply delays to block quicktyper abuse
        if (living(dest))
        {
            burdened = query_living_name(dest);
            if (!helper)
            {
                helper = clone_object(HELPER_PATH);
                helper->deliver(environment(dest));
            }
            else
            {
                helper->move(environment(dest));
            }
            helper->set_fail_message("You are still tired.\n");

//            if (!time_delay)
//            {
//                set_time_delay();
//            }
//            slow_cmd_alarm = set_alarm(time_delay, 0.0, &finally_exit(dest));
            dest->add_stun();

            //But delay hold message until AFTER taking.
            set_alarm(0.2, 0.0, &burden_enter_env(dest, old));
            delayed_env = 1;
        }
        return;
    }
    delayed_env = 0;

    if (living(dest))
    {
        if (!query_held()) //If not held already, hold it.
        {
            mixed hold_result = command_hold();
            if (stringp(hold_result))
            {
                dest->catch_msg(hold_result + "\n");

                //Same result as if player successfully held, quickly released.
                TO->move(environment(dest));
                //slow_cmd_alarm = 0;
                helper->remove_object();
                dest->remove_stun();
                return;
            }
        }
    }
}


/*
 * Function name: burden_leave_env
 * Description  : When burden is put down, movement becomes easy again.
 * Arguments    : (object) the old location
 *                (object) the destination
 */
void
burden_leave_env(object old, object dest)
{
    holdable_item_leave_env(old, dest);

    if (living(old)) //Removed by player?
    {
        //slow_cmd_alarm = 0;
        helper->remove_object();
        old->remove_stun(); //Player can fight again
        check_carried();
    }
}


/*
 * Function name: burden_release_effect
 * Description  : Dummy function to override to add a custom effect when the
 *      burden is no longer held.
 * Arguments    : (int) Generic parameter for use by overriding functions
 */
void
burden_release_effect(int param = 0)
{
    /* Your effect here */
}


/*
 * Function name: burden_release_effect
 * Description  : Dummy function to override to add a custom effect when the
 *      burden first held.
 */
void
burden_started_hook()
{
    /* Your effect here */
}


/*
 * Function name: check_carried
 * Description  : Checks that burden is still in player's possession
 * Arguments    : (int) force_ending (0 - no - by default)
 */
void
check_carried(int force_ending = 0)
{
    object container = environment();
    if (!living(container)) //In an unliving container
    {
        object meta_container = environment(container);
        if (!meta_container) //In a room, release directly.
        {
            burden_release_effect(1);
            return;
        }
        if (!living(meta_container)) //The container is not carried by a living
        {
            TO->move(meta_container); //And is probably in a room
            tell_room(container, QCTNAME(TO)
                + " falls out of the " + container->query_short() + " .\n", 0);
            burden_release_effect(1);
            return;
        }
    }
    container->add_stun(); //Refresh the stun, just in case.

    if (strlen(burdened)) //A player name is set
    {
        if (force_ending || query_living_name(container) != burdened)
            //Either carried by wrong living, or we don't care who has it
        {
            TO->move(environment(container)); //Force release
            //tell_room(container, QCTNAME(TO) + " falls to the ground.\n", 0);
            burden_release_effect(1);
            return;
        }
    }
    set_alarm(5.0, 0.0, "check_carried");
}


/*
 * Function name: check_new_room
 * Description  : Checks whether a new room has been entered and slows it if so
 */
void
check_new_room()
{
    write("ROOM CHECKED");
    object player = find_player(burdened);
    object new_room = environment(player);
    object last_room = find_object(last_path);
    if (new_room != last_room)
    {
        helper->move(new_room);
        player->add_stun(); //Changing rooms removes stun
        new_room_hook(last_room, new_room, player);
        last_path = file_name(new_room);

    }
    //update_actions(); //Ensure that the new room's actions do not get in front
}


/*
 * Function name: drop_on_release
 * Description  : Burden cannot be carried without holding; inform and move to
 *          the dropper's room.
 * Arguments    : (object) The room where this was released and thus dropped
 */
void
drop_on_release(object drop_room)
{
    TO->move(drop_room);
}




/*
 * Function name: new_room_hook
 * Description  : Hook for effect of entering a new room with the burden
 * Arguments    : (object) The player with the burden
 *                (object) The previous room
 *                (object) The newly entered room
 */
void
new_room_hook(object last_room, object new_room, object player)
{
    /* Your effect here */
}


/*
 * Function name: query_burdened
 * Description  : Return name of burden-carrier to outside function
 * Returns      : (string) Name
 */
string
query_burdened()
{
    return burdened;
}


/*
 * Function name: set_last_path
 * Description  : Setter for last_path string
 * Arguments    : (object) The new last_path value
 */
 void
 set_last_path(string new_path) {
   last_path = new_path;
 }


/*
 * Function name: release
 * Description  : Override of holdable_item.c:release() - drop the burden in
 *      the room after release, since it cannot be carried without being held.
 *      Let the player move immediately.
 * Returns      : (int) 0 - permission for dropping granted
 */
int
release()
{
    if (!delayed_env)   //If there is not already a pending move
    {
        /* Wait until release is complete to avoid releasing twice. Save room,
         * as this could change by the time the alarm calls to drop.
         */
        object drop_room = environment(this_player());
        set_alarm(0.2, 0.0, &drop_on_release(drop_room));

        //slow_cmd_alarm = 0;
    }
    return 0;
}


/*
 * Function name: start_burden
 * Description  : Set the player who may carry the burden and their time limits
 * Arguments    : (string) player_name - name of player who must carry the
 *      gauntlet (default "": any player)
 *                (float) start_limit - max time before burden must be held
 *                (float) end_limit - max time before burden auto-release
 *      triggers (default 0.0: no limit)
 */
void
start_burden(string player_name = "", float start_limit = 0.0,
    float end_limit = 0.0)
{
    burdened = player_name;
    object last_room = 0;

    if (find_player(burdened))
    {
        last_room = environment(find_player(burdened));
    }
    if (!last_room)
    {
        last_room = environment(environment());
    }
    if (!last_room)
    {
        last_room = environment();
    }
    last_path = file_name(last_room);

    if (start_limit > 0.0)
    {
        burden_time_limit = set_alarm(start_limit, 0.0, "check_carried");
    }
    if (end_limit > 0.0)
    {
        burden_time_limit = set_alarm(end_limit, 0.0, &check_carried(1));
    }
    burden_started_hook();
}
