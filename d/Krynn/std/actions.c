/*
 * This file defines a few standard actions which are inherited into npcs.
 *
 * When these functions are called, the npc is supposed to do something
 * like the action, he is not required to though. If action_insult is called
 * the npc might do nothing.
 */
#include <macros.h>
#include <stdproperties.h>

/*
 * Function Name: action_assist
 * Description  : Assist a friend against someone.
 * Arguments    : object - the friend to assist
 */
public varargs void
action_assist(object friend = 0)
{
    if (objectp(friend) && friend->query_attack())
    {
        command("assist " + OB_NAME(friend));
        return;
    }
    
    command("assist");
}

/*
 * Function Name: action_attack
 * Description  : Attempt to attack someone.
 *                
 * Arguments    : object - the enemy to attack
 */
public void
action_attack(object enemy)
{
    if (!objectp(enemy))
        return;
    
    command("kill " + OB_NAME(enemy));
}

/*
 * Function Name: action_greet
 * Description  : Should make the NPC greet the target somehow.
 *                A Draconian might salute a superior. A farmer
 *                might bow to a lord.
 */
public void
action_greet(object target)
{
    if (!objectp(target) || environment(target) != environment())
        return;
    
    if (!CAN_SEE_IN_ROOM(this_object()) || !CAN_SEE(this_object(), target))
        return;
    
    command("say to " + OB_NAME(target) + " Greetings.");
}

/*
 * Function Name: action_insult
 * Description  : Should make the npc insult the target.
 *                The insult should depend upon the characther
 *                of the npc.
 */
public void
action_insult(object target)
{
    if (!objectp(target) || environment(target) != environment())
        return;

    if (!CAN_SEE_IN_ROOM(this_object()) || !CAN_SEE(this_object(), target))
        return;

    switch (random(3))
    {
    case 0:
        command("say to " + OB_NAME(target) + 
            " Was your mother a gully dwarf?");
        break;
    default:
        break;
    }
}

/*
 * Function Name: action_introduce
 * Description  : The NPC introduces itself to someone.
 * Arguments    : object - target to introduce to or 0 if it should
 *                         introduce to everyone.
 */
public varargs
action_introduce(object target = 0)
{
    if (!CAN_SEE_IN_ROOM(this_object()) || 
        this_object()->query_prop(LIVE_I_NEVERKNOWN))
        return; 
    
    if (!objectp(target))
    {
        command("introduce me");
        return;
    }
    
    if (environment(target) != environment() ||
        !CAN_SEE(this_object(), target))
        return;
    
    command("introduce me to " + OB_NAME(target));
}
