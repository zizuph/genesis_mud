/* This file makes your npcs auto-team with other npcs.
 * When an npcs enters a room, it'll check which of the
 * present npcs he can add to his team.
 * This means:
 *
 *   - No need to write team joining code in the rooms when cloning the npcs.
 *     (Clone two npcs into the room and they'll join automatically).
 *   - You can have a wandering npc which will pick up any suitable npc
 *     while going somewhere. Upon arrival, the team will be hard to beat... :)
 *
 * 1) Just inherit this file along with your /std/monster.
 *    in Krynn this is done with 'inherit AUTO_TEAM', defined in common/defs.h.
 * 2) Redefine init_living() to call init_team_pickup();
 * 28.6.2002 changed by Milan
 * 3) In create_monster(), call set_pick_up_team(<arg>); where arg is
 *    following:   an array of strings   eg.  ({"baaz","bozak"});
 *    The monster will then try to pick up only other npcs which respond to one
 *    of these names!
 *
 *
 *  Aridor, 07/95
 *
 * 29.12.1998 updated by Milan.
 * Added functions set_no_team_member() and query_no_team_member().
 * If query_no_team_member() returns true then NPC will not be picked
 * up into team. Also added check
 *
 * int query_not_accept_member(object ob)
 *
 * that allows you to specify further if two NPCs join the team. Thus you
 * can make e.g. join only dracoinians of the same color. This function can
 * be defined in NPC and if it returns 1 no joining happens.
 */

#include "/d/Krynn/common/defs.h"
#include <cmdparse.h>
#include <macros.h>

int gMax_team_size = 5, gNoTeamMember = 0;
string *gProspective_team = ({});

/* use this if you do not want this NPC to be picked into the team
 * It still can be a leader of team
 */
void
set_no_team_member(int i)
{
    gNoTeamMember = i;
}

/* if this returns nonzero, NPC will not be picked into the team */
int
query_no_team_member()
{
    return gNoTeamMember;
}

/* call this from create_monster() to add id strings of npcs to team with */
void
set_pick_up_team(string* str)
{
    if (!str)
      return;
    if (pointerp(str))
      gProspective_team = str;
    else if (stringp(str))
      gProspective_team = ({ str });
}

public string *
query_prospective_team()
{
    return gProspective_team + ({});
}

/* set the max team size (default 5), don't join anymore if team
 * reaches this size.
 */
void
set_max_team_size_auto_join(int i)
{
    gMax_team_size = i;
}

/* The corresponding query function.
 */
int
query_max_team_size_auto_join()
{
    return gMax_team_size;
}

static void
add_new_to_team(object who)
{
    int i;
    object *others;
    string *prospective;

    if (!who || E(who) != E(TO))
      return;

    if ((sizeof(TO->query_team_others()) + 1) >= gMax_team_size)
      return;

    if (sizeof(who->query_team_others()))
	return; /* this should never happen */

    if (TO->query_not_accept_member(who) || who->query_not_accept_member(TO))
	return;

    if (who->query_average_stat() > TO->query_average_stat() && !gNoTeamMember)
    {
	/* who is bigger than TO so he might become the leader instead */
	prospective = who->query_prospective_team();
	i = sizeof(prospective);
    	while(i--)
	    if (TO->id(prospective[i]))
	    {
		others = TO->query_team_others();
		i = sizeof(others);
		while (i--)
		{
		    TO->team_leave(others[i]);
		    who->team_join(others[i]);
		}
		who->team_join(TO);
		if(sizeof(others))
		{
		    tell_room(E(TO), QCTNAME(who) + " became the leader of "+
			QTNAME(TO)+"'s team.\n");
		}
		else
		{
		    tell_room(E(TO), QCTNAME(TO) + " joined the team of " +
			    QTNAME(who) + ".\n");
		}
		return;
	    }
    }
    if (TO->team_join(who))
	tell_room(E(TO), QCTNAME(who) + " joined the team of " +
		QTNAME(TO) + ".\n");
}

/* Call this from init_living() */
void
init_team_pickup()
{
    int i;

    if (interactive(TP) || !sizeof(gProspective_team) ||
	TO->query_leader() || !E(TO) || TP->query_no_team_member() ||
	sizeof(TP->query_team_others()))
      return;
    
    i = sizeof(gProspective_team);
    
    while(i--)
      if (TP->id(gProspective_team[i]))
      {
	  set_alarm(0.0, 0.0, &add_new_to_team(TP));
	  break;
      }
}
