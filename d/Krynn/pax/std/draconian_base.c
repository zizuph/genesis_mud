/*
 * This is INCLUDED into some draconians in pax.
 *
 * A few functions to team the draconians, and aid
 * eachother in battle.
 *
 * The description functions is made by Jeremiah.
 *
 * 950506 by Rastlin
 *
 * 6. may 1999 Milan (no autoattack DA members until they do not attack)
 */

#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include <stdproperties.h>

public void remove_descr();

/*
 * Function name: aggressive_attack
 * Description:   We are aggressive, let us attack
 * Arguments:	  ob - the object to attack
 */
public void
aggressive_attack(object ob)
{
    if (ob->query_dragonarmy_occ_member() &&
	!ob->query_prop("_attacked_in_pax"))
	return; /* do not attack */

    ::aggressive_attack(ob);
}



/*
 * Function:	attacked_by
 * Arguments:	attacker - The attacker
 * Description:	This function is called when somebody attacks this object
 */
public void
hook_attacked(object attacker)
{
    /* We still want to do the hooks in the base */
    ::hook_attacked(attacker);

    remove_descr();
    attacker->add_prop("_attacked_in_pax", 1);
}

/*
 * Funtion Name: add_desc
 * Description : Adds the pax specific extra shorts.
 */
public void
add_descr(string description)
{
    add_prop(LIVE_S_EXTRA_SHORT, " " + description);
}

/*
 * Function:	remove_descr
 * Description:	Remove the extra description
 */
public void
remove_descr()
{
    remove_prop(LIVE_S_EXTRA_SHORT);
}

void
attack_object(object ob)
{
    remove_descr();
    ::attack_object(ob);
}

/*
 * Function:	second_life
 * Arguments:	killer - The one who killed me.
 * Description:	Hmmm... If I was a team leader, select a new leader
 *		and rebuild the team, otherwise do nothing.
 */
public int
hook_killed(object killer)
{
    object *team;
    object leader;
    int i = -1, size, max;

    if ((team = query_team()) && (size = sizeof(team)))
    {
	while (++i < size)
	    if (max < team[i]->query_average_stat())
	    {
	        max = team[i]->query_average_stat();
	        leader = team[i];
	    }

	i = -1;

        TO->team_leave(leader);

        while (++i < size)
	    if (leader != team[i])
		leader->team_join(team[i]);
    }
}
