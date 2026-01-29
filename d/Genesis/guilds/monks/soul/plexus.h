#include "defs.h"

int
plexus(string str)
{
    object ob, *target_list;
    string how;

    if (!m_query_monk(this_player(), SS_OCCUP) && !this_player()->query_wiz_level())
    {
        return 0;
    }


    /* What are we attacking anyway? */
    if (strlen(str))
    {
        if (!sizeof(target_list = parse_this(str, "[the] %l")))
        {
            notify_fail("Choose a more appropriate target.\n");
            return 0;
        }

        ob = target_list[0];

        if (ob != this_player()->query_attack())
        {
            // if they player is not currently attacking the target,
            // initiate an attack. This is done by just calling the kill()
            // function in /cmd/live/social. While this is a rather odd
            // way of doing it, and may be error-prone, it allows
            // the plexus attack to always comply with current mudlib restrictions
            // on attacking.
            notify_fail("You are not able to attack that target.\n");
            if(!(this_player()->command("kill " + str)))
                return 0;
            else if (ob != this_player()->query_attack())
                return 1;

        }
    }
    /* if the player doesn't specify a target, we assume the player's
     * current enemy.
     */
    else if (!(ob = this_player()->query_attack()))
    {
        write("But you aren't in battle with anyone!\n");
        return 1;
    }

    /* Is the attacker already busy? */
    if (this_player()->query_monk_special_active())
    {
        write("You are already preparing an attack.\n");
        return 1;
    }

    /* Are we even allowed to attack it?  Use can_attack_with_monk_special(),
     * which is defined in the guild shadow, to find out.
     */
    if (stringp(how = 
        this_player()->m_may_special_attack(ob, "plexus")))
    {
        write(how);
        return 1;
    }

    /* The shadow takes care of the rest */
    this_player()->m_start_plexus(ob);

    return 1;
}

