/* cling_sh.c created by Shiva@Genesis
 * This handles the majority of the work for the vampire guild's 
 * "cling" command.  It allows one living to use his/her hunting
 * abilities to follow another living.
 */

inherit "/std/shadow";

#include "../guild.h"
#include <macros.h>
#include <tasks.h>

#define SW shadow_who
#define TIME     0
#define ALARM_ID 1

static mapping cling_map = ([]);

int remove_cling_shadow() 
{ 
    remove_shadow(); 
    return 1;
}

static int sight_test(object looker, object target)
{
    return (CAN_SEE_IN_ROOM(looker) && CAN_SEE(looker, target));
}

mapping query_cling_map() { return cling_map; }

/*
 *    Function: add_cling_follower
 * Description: add someone to the list of followers
 *   Arguments: object who - whom to add
 */
void add_cling_follower(object who)
{
    if (!cling_map[who])
    {
        cling_map[who] = ({ 0, 0 });
    }
  
    if (who->query_prop(VAMP_O_CLING) != SW)
    {
        who->add_prop(VAMP_O_CLING, SW);
    }
}

/*    Function: remove_cling_follower
 * Description: remove someone from the list of followers
 *   Arguments: object who - whom to remove
 */
void remove_cling_follower(object who)
{
    if (!m_sizeof(cling_map = m_delete(cling_map, who)))
    {
        remove_shadow();
    }
  
    if (who->query_prop(VAMP_O_CLING) == SW)
    {
        who->remove_prop(VAMP_O_CLING);
    }
}

object *query_cling_followers() 
{ 
    return ((object *)m_indices(cling_map) - ({ 0 }));
}

/*    Function: cling2
 * Description: Execute the exit command and apply thirst and fatigue
 *   Arguments: object who - the follower
 *              string how - the exit command to use
 *              object whence - the room from with the followed living
 *                              moved.
 */
static void
cling2(object who, string how, object whence)
{
    if (who->query_prop(VAMP_O_CLING) != SW)
    {
        remove_cling_follower(who);
        return;
    }
  
    /* If a follower moves on his/her own, "cling" can no longer
     * do it for him.
     */
    if (environment(who) != whence)
    {
        if (!present(SW, environment(who)))
        {
            who->catch_tell("You seem to have lost track of " +
                SW->query_the_name(who) + ".\n");
        }
    
        return;
    }
  
    who->add_fatigue(3);
    if (!random(3))
    {
        who->add_thirst(1);
    }
  
    set_this_player(who);
  
    // execute the exit command
    this_player()->command("$" + how);
}

/* 
 *    Function: do_cling
 * Description: Test to see if a follower is able to follow and
 *              set up the according delay if so.
 *   Arguments: string how - the exit command to use
 *              object whence - the room from which the followed living
 *                              is moving
 *              object who - the follower
 */
static void
do_cling(string how, object whence, object who)
{
    int res, mod = 0;
    float delay;
    object *enemies;
  
    if (who->query_prop(VAMP_O_CLING) != SW)
    {
        remove_cling_follower(who);
        return;
    }
  
    if (SW->query_prop(OBJ_I_HIDE))
    {
        /* The living must have attempted to sneak away, but
         * wasn't totally successful.  I'll treat that as an
         * attempt to elude the follower and make the follow
         * test more difficult.
         */
        mod += 25 + random(75);
    }
  
    if (sizeof(enemies = ((object *)who->query_enemy(-1) - ({ SW }))))
    {
        /* make following more difficult for each person attacking us
         * (other than the person we're following).
         */
        mod += sizeof(filter(enemies, &operator(==)(who) @ &->query_attack())) *
            100;
    }
  
    /* Reminder:  Add bonus for mulitple vamps clinging */
  
    res = min(100, who->resolve_task(TASK_ROUTINE + mod, 
        ({ SKILL_WEIGHT, 60, SS_HUNTING,
           SKILL_WEIGHT, 40, SS_AWARENESS,
           SKILL_WEIGHT, 50, TS_INT,
           SKILL_WEIGHT, 50, TS_DEX })));
  
    if (res > 0)
    {
        /* add a delay based upon the success of the above resolve_task */
        if ((delay = itof(70 - res) / 30.0) > 0.0)
        {
            cling_map[who][ALARM_ID] = set_alarm(delay, 0.0, 
                &cling2(who, how, whence));
        }
        else
        {
            cling_map[who][ALARM_ID] = 0;
            cling2(who, how, whence);
        }
    
        return;
    }
  
    /* Fail!  follower has 30 seconds to catch up */
    who->catch_tell("You seem to have lost track of " +
        SW->query_the_name(who) + ".\n");
}

/* 
 *    Function: update_followers
 * Description: update the list of followers, removing those
 *              who are no longer around and those who have
 *              lost us.
 */
void
update_followers()
{
    int i, t;
    object *clingers;
  
    cling_map = m_delete(cling_map, 0);
    clingers = m_indices(cling_map);
  
    for (i = 0; i < sizeof(clingers); i++)
    {
        if (clingers[i]->query_prop(VAMP_O_CLING) != SW)
        {
            remove_cling_follower(clingers[i]);
            continue;
        }
    
        t = cling_map[clingers[i]][TIME];
        if (t && t < time())
        {
            clingers[i]->catch_tell("You are no longer following " +
                SW->query_the_name(clingers[i]) + ".\n");
    
            remove_cling_follower(clingers[i]);
        }
    }
}

/* 
 *    Function: move_living
 * Description: Do the standard move_living stuff and set up
 *              to try to move our followers
 *   Arguments: see /std/living
 *     Returns: see /std/living
 */
varargs int
move_living(string how, mixed to_dest, int dont_follow, int no_glance)
{
    object whence;
    object *who_move, *followers;
    int ret, i, index;
    string *exit_cmds;
  
    update_followers();
  
    whence = environment(SW);
    ret = SW->move_living(how, to_dest, dont_follow, no_glance);
  
    /* the move failed, so we don't need to continue */
    if (ret)
    {
        return ret;
    }
  
    followers = m_indices(cling_map);
  
    // followers have 30 seconds to catch up
    for (i = 0, who_move = ({ }); i < sizeof(followers); i++)
    {
        /* Check to see if the follower has changed targets or
         * stopped clinging altogether.
         */
        if (followers[i]->query_prop(VAMP_O_CLING) != SW)
        {
            remove_cling_follower(SW);
            continue;
        }
    
        /* Only followers present in the room will be able
         * to cling.
         */
        if (environment(followers[i]) == whence)
        {
            if (sight_test(followers[i], SW))
            {
                who_move += ({ followers[i] });
            }
      
            cling_map[followers[i]][TIME] = time() + 30;
        }
        else if (!cling_map[followers[i]][TIME])
        {
            cling_map[followers[i]][TIME] = time() + 30;
        }
    }

    if (!sizeof(who_move))
    {  
        return ret;
    }

    if (objectp(to_dest))
    {
        to_dest = file_name(to_dest);
    }
  
    if (!stringp(to_dest))
    {
        return ret;
    }
  
    /* Make sure the destination is connected to the current
     * environment by a regular exit: followers should not cling
     * if we have been teleported far away
     */
    if ((index = member_array(to_dest, whence->query_exit_rooms())) >= 0)
    {
        /* Find the appropriate command to use to follow */
        exit_cmds = whence->query_exit_cmds();
    
        if (sizeof(exit_cmds) <= index)
        {
            return ret;
        }
    
        /* Make each present player who is following do so */
        map(who_move, &do_cling(exit_cmds[index], whence));
    }
  
    return ret;
}

/*
 *    Function: init_living
 * Description: called whenever we meet another living...updates
 *              the list of followers and checks to see if the
 *              living we have met is a follower
 */
void 
init_living()
{
    int index, i, alarm;
  
    SW->init_living();
  
    update_followers();
  
    if (cling_map[this_player()])
    {
        if (this_player()->query_prop(VAMP_O_CLING) != SW)
        {
            remove_cling_follower(this_player());
            return;
        }
    
        if (sight_test(this_player(), SW))
        {
            /* We've met back up with someone who was following us
             * before the delay on his move was up...we should stop
             * him from moving now.
             */
            if (alarm = cling_map[this_player()][ALARM_ID])
            {
                remove_alarm(cling_map[this_player()][ALARM_ID]);  
            }
      
            cling_map[this_player()][ALARM_ID] = 0;
        }
    
        cling_map[this_player()][TIME] = 0;
    }
}
