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
 */

#include "/d/Krynn/common/defs.h"
#include <cmdparse.h>
#include <macros.h>

int gMax_team_size = 5, gTeamed = 0;
string *gProspective_team = ({});

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
    int ret, i;
    object leader, *others;

    //find_player("rastlin")->catch_msg(sprintf("J1 %O\n", TO));
    //find_player("aridor")->catch_msg(sprintf("J1 %O\n", TO));
    
    if (!who || E(who) != E(TO))
      return;
    //find_player("rastlin")->catch_msg(sprintf("J2 %O\n", TO));
    //find_player("aridor")->catch_msg(sprintf("J2 %O\n", TO));

    if ((sizeof(TO->query_team_others()) + 1) >= gMax_team_size)
      return;
    //find_player("rastlin")->catch_msg(sprintf("J3 %O\n", TO));
    //find_player("aridor")->catch_msg(sprintf("J3 %O\n", TO));

/*    if (!(leader = who->query_leader()))
	leader = who;
    find_player("rastlin")->catch_msg(sprintf("J4 %O\n", TO));
    find_player("aridor")->catch_msg(sprintf("J4 %O\n", TO));
*/
    if (who->query_average_stats() > TO->query_average_stats())
    {
	others = who->query_team_others();
    //find_player("rastlin")->catch_msg(sprintf("J5 %O\n", TO));
    //find_player("aridor")->catch_msg(sprintf("J5 %O\n", TO));

	i = sizeof(others);
	while (i--)
	{
	    who->team_leave(others[i]);
	    others[i]->set_leader(TO);
	    TO->team_join(others[i]);
	}

	who->set_leader(TO);
	TO->team_join(who);
	say(QCTNAME(TO) + " became the leader of the team.\n");
    }
    else
    {
	//find_player("rastlin")->catch_msg(sprintf("J7 %O\n", TO));
	//find_player("aridor")->catch_msg(sprintf("J7 %O\n", TO));

	who->set_leader(TO);
	ret = TO->team_join(who);
	
	if (ret)
	  tell_room(E(TO), QCTNAME(who) + " joined the team of " +
		    QTNAME(TO) + ".\n");
    }
}

/* Call this from init_living() */
void
init_team_pickup()
{
    int i;
    if (interactive(TP) || !sizeof(gProspective_team) || gTeamed || !E(TO) ||
	sizeof(TP->query_team_others()))
      return;
    
    i = sizeof(gProspective_team);
    
    while(i-- && !gTeamed)
      if (TP->id(gProspective_team[i]))
      {
	  set_alarm(3.0, 0.0, &add_new_to_team(TP));
	  if (TO->query_leader())
	    gTeamed = 1;
	  break;
      }
}
