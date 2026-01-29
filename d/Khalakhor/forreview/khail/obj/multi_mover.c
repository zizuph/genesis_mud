/*
 * multi_mover.c
 * 
 * Coded: Stexx, June 23/95
 *
 * multi_mover is used to handle large groups of npc's travelling together
 * under the command of a player.
 * The team of npcs is created much the same way as players invite other
 * players to join their team. Once the npc team is assembled, players
 * issue orders which the team will follow.
 * Teams can be directed to attack specific livings (bad news for someone
 * trying to ambush a team leader), ordered to exit in certain directions,
 * ordered to follow the team leader, etc.
 */

#include "/d/Immortal/std/domain.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <composite.h>

#define LIVE_I_POTENTIAL_TEAM_MEMBER "_live_i_potential_team_member_"
inherit STDOBJECT;

object *team_members;     /* All the npc's that are 'teamed' */
int team_is_following;
object team_leader;

void follow_me(string str);
void
create_object()
{
  set_name("multi_mover");
  set_short("multi mover");
  set_long("Stexx's multi mover.\n");
  
  add_item(({"team","group","unit"}), "@@check_team");

  add_prop(OBJ_I_WEIGHT, 0);
  add_prop(OBJ_I_VOLUME, 0);
  add_prop(OBJ_M_NO_DROP, 1);
  add_prop(OBJ_M_NO_GIVE, 1);
  add_prop(OBJ_M_NO_SELL, 1);
}

string
check_team()
{
  if(!team_members || !sizeof(team_members))
    return "You have no followers in a team.\n";
  else
    return "Your team consists of "+COMPOSITE_LIVE(team_members)+".\n";
}
void
init()
{
  ::init();
  team_leader = environment(TO);
  add_action("order_team", "order");
  add_action("recruit_team_member", "recruit");
  add_action("dismiss_team_member", "dismiss");
  add_action("check_follow", "");
}

int
order_team(string str)
{
string *tmp;
object commander;
int i, index;
string next_room;

  NF("Order what? The team to do something?\n");

  if(!strlen(str))
    return 0;

  tmp = explode(str, " ");

  /* Is the player trying to order the team to do something? */
  if(tmp[0] != "team")
    return 0;

  /* Are there any livings in the team? */
  if(!sizeof(team_members))
    {
    NF("You are not leading a team to order around.\n");
    return 0;
    }

  /* Is this_player() the team leader? Probably not necessary, but... */
  if(TP != team_leader)
    {
    NF("You are not the leader of this team.\n"); 
    return 0;
    }

  /* Don't need the 'team' part of the command array any more */
  tmp = tmp[1..];

  if(tmp[0] == "follow")
    {
    TP->catch_msg("You bark: Team! Follow me!\n");
    say(QCTNAME(TP)+" barks: Team! Follow me!\n");
    TP->catch_msg("The team will follow you wherever you go now, unless "+
      "you order them to stay put.\n");
    team_is_following = 1;
    return 1;
    }

  if(tmp[0] == "move")
    {
    str = implode(tmp[1..]," ");
    if(member_array(str, environment(TP)->query_exit_cmds()) < 0)
      {
      NF("There is no direction "+str+" for the team to move in.\n");
      return 0;
      }
    else
      {
      TP->catch_msg("You bark: Team! Move "+str+"!\n");
      say(QCTNAME(TP)+" barks: Team! Move "+str+"!\n");
      tell_room(environment(team_members[0]), "A group of "+ 
        COMPOSITE_LIVE(team_members) +" heads off "+str+
        ".\n", team_members);
      commander = TP;
      index = member_array(str, environment(TP)->query_exit_cmds());
      next_room = environment(commander)->query_exit_rooms()[index];
      
      for(i = 0; i < sizeof(team_members); i++)
        {
        set_this_player(team_members[i]);
        if(!environment(commander)->query_exit_functions()[index])
          team_members[i]->move_living("M", next_room, 0, 0);
        }
      
      set_this_player(commander);

      tell_room(find_object(next_room), "A group of "+
        COMPOSITE_LIVE(team_members) +" arrives.\n", team_members);
      return 1;
      }
    }
  return 0;
}

/*
 * Function name: check_follow
 * Description: Any time the player issues a command, it checks to see
 *              if they've moved somewhere, if they have, the team follows.
 */
int
check_follow(string str)
{
  if(!team_is_following)
    return 0;

  if(member_array(str, environment(TP)->query_exit_cmds()) < 0)
    return 0;
  else
    set_alarm(0.5, 0.0, &follow_me(str));
  return 0;
}

void
follow_me(string str)
{
int i;  

  tell_room(environment(team_members[0]), "The team heads off in unison "+
    "to the "+str+".\n", team_members);
  for(i = 0; i < sizeof(team_members); i++)
    {
    team_members[i]->move_living("M",environment(TP), 0, 0);
    }
  tell_room(environment(team_members[0]), "A team of "+
    COMPOSITE_LIVE(team_members)+" arrives in unison.\n",
    team_members);
}

int
recruit_team_member(string str)
{
int i;
object tobj;

  NF("Recruit whom?\n");

  if(!strlen(str))
    return 0;

  if(!present(str, environment(TP)))
    return 0;

  if(interactive(present(str, environment(TP))))
    {
    TP->catch_msg(capitalize(str)+" would not be a good team member.\n");
    NF("");
    return 0;
    }

  tobj = present(str, environment(TP));

  if(!tobj->query_prop(LIVE_I_POTENTIAL_TEAM_MEMBER))
    {
    TP->catch_msg(QCTNAME(tobj)+" would not be a good team member.\n");
    NF("");
    return 0;
    }

  if(tobj->query_stat(SS_DIS) > TP->query_stat(SS_DIS))
    {
    TP->catch_msg(QCTNAME(tobj)+" has no faith in your ability to lead.\n");
    NF("");
    return 0;
    }

  TP->catch_msg(QCTNAME(tobj) +" is willing to follow you.\n");
  if(!team_members || !sizeof(team_members))
    {
    tell_room(environment(TP), QCTNAME(tobj)+" stands tall and prepares to "+
      "follow "+QTNAME(TP)+", to the death, if necessary.\n", TP);
    team_members = ({tobj});
    }
  else
    {
    tell_room(environment(TP), QCTNAME(tobj)+" falls into place among "+
      "the group of "+COMPOSITE_LIVE(team_members)+" lead by "+
      QCTNAME(TP)+".\n", TP);
    team_members += ({tobj});
    }

  return  1;
}

int
dismiss_team_member(string str)
{
object dismissed;

  if(!present(str, environment(TP)))
    {
    NF("You can't dismiss someone who isn't around to hear the "+
      "dismissal.\n");
    return 0;
    }

  if(!team_members || !sizeof(team_members))
    {
    NF("You don't have any followers to dismiss.\n");
    return 0;
    }

  dismissed = present(str, environment(TP));

  if(member_array(dismissed, team_members) < 0)
    {
    TP->catch_msg(QCTNAME(dismissed)+" is not a team member to dismiss.\n");
    NF("");
    return 0;
    }

  TP->catch_msg("You dismiss "+QCTNAME(dismissed)+" from your ranks.\n");
  tell_room(environment(TP), QCTNAME(TP)+" dismisses "+QTNAME(dismissed)+
    "from "+TP->query_possessive()+" ranks.\n", TP);
  team_members -= ({dismissed});

  return 1;
}
