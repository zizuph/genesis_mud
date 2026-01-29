#include <ss_types.h>
#include <composite.h>
#include <filter_funs.h>

int
strike(string str)
{
    object ob, *obj;
    string how, where, *hitlocs;
    int    res, hindex;

    hindex = -1;
    res = 0;

    if(strlen(str))
    {
        res = parse_command (str, environment (this_player ()),
            "[the] %l [on] [the] %s", obj, where);

        if (res <= 0)
        {
            obj = ({ this_player()->query_attack() });

            res = parse_command (str, environment (this_player ()),
                "[on] [the] %s", where);
        }

        if (res <= 0)
            res = 0;
        else
        {
            if (sizeof (obj))
            {
                obj = FILTER_LIVE(obj);
            }
        }

    }
 
    /* What are we attacking anyway? */
    if (res > 0)
    {
        if (!sizeof(obj))
        {
            notify_fail("Choose a more appropriate target.\n");
            return 0;
        }

        ob = obj[0];
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

    /* Are we even allowed to attack it?  Use m_may_special_attack(),
     * which is defined in the guild shadow, to find out.
     */
    if (stringp(how = 
        this_player()->m_may_special_attack(ob, "strike")))
    {
        write(how);
        return 1;
    }
 
    if ((ob->query_average_stat()) > (2 * (this_player()->query_stat(SS_DIS) + 
        this_player()->query_stat(SS_WIS) / 10)))
    {
	write("You don't dare try to strike " + 
            ob->query_the_name(this_player()) + ".\n");
	return 1;
    }

    hitlocs = m_query_hitloc_descs (ob);

    /* check to see if we can hit them where we wanted to     */
    if (strlen(where) && ((hindex = member_array(where, hitlocs)) < 0))
    {
        this_player()->catch_msg(QCTNAME(ob) + " does not seem to have "
            + LANG_ADDART(where) + ".\nPossible areas you can strike on "
            + QTNAME(ob) + " are: " + COMPOSITE_WORDS(hitlocs) + ".\n");
        return 1;
    }

    /* The shadow takes care of the rest */
    this_player()->m_start_strike(ob, m_query_hitloc_str_id(ob, where), where);

    return 1;
}

