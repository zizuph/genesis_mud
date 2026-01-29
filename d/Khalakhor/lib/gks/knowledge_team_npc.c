/*
 * knowledge_team_npc.c
 *
 * This module will inherit support of npc teaming into
 * npc's. It allows you to specify a team leader or a team
 * follower, and set it up to only team once, or pick up
 * all straglers it passes when the leader wanders. It can
 * also be set to only accept certain straglers, so for
 * instance two teams of npc's can wander past one another
 * without messing them up.
 *
 * Only difference between this and 'team_npc.c' in this
 * directory is that this one also contains the GKS support.
 *
 * Khail - June 15/97
 */
#pragma strict_types

#include <macros.h>
#include "/d/Khalakhor/sys/defs.h"
#include "gks.h"

inherit "/d/Khalakhor/lib/gks/knowledge_npc";

int team_leader,
    team_follower,
    autoassist;
string team_name;

public void
set_team_leader()
{
    team_leader = 1;
}

public void
remove_team_leader()
{
    team_leader = 0;
}

public int
query_team_leader()
{
    return team_leader;
}

public void
set_team_follower()
{
    team_follower = 1;
}

public void
remove_team_follower()
{
    team_follower = 0;
}

public int
query_team_follower()
{
    return team_follower;
}

public void
set_team_name(string str)
{
    team_name = str;
}

public string
query_team_name()
{
    if (team_name)
        return team_name;
    return "";
}

public void
set_autoassist()
{
    autoassist = 1;
}

public void
remove_autoassist()
{
    autoassist = 0;
}

public int
query_autoassist()
{
    return autoassist;
}
   
public void
init_living()
{
    ::init_living();

  /* Here, we'll add a check for team followers to join */
  /* a team leader that arrives in their environment, */
  /* if they can. */
    if (!TP->query_team_leader())
        return;

  /* Can't join any team if already in one. */
    if (sizeof(TO->query_team()))
        return;

  /* If the npc isn't set to join a specific team, */
  /* join any team leader. */
    if (!team_name || !strlen(team_name))
    {
        tell_room(environment(TO), QCTNAME(TO) +
            " joined the team of " + QTNAME(TP) + ".\n");
        TP->team_join(TO);
        return;
    }

  /* If we've got a team name, and the potential leader */
  /* doesn't, don't join. */
    if (!TP->query_team_name() ||
        !strlen(TP->query_real_name()))
        return;

  /* Ok, we've met a potential leader, we aren't in */
  /* a team, and the team leader has our team name, */
  /* so join up. */
    tell_room(environment(TO), QCTNAME(TO) +
        " joined the team of " + QTNAME(TP) + ".\n");
    TP->team_join(TO);
}

public void
assist_me(object *myteam, object ob)
{
    myteam = filter(myteam, &operator(!=)(ob) @
        &->query_attack());
    myteam = filter(myteam, &->query_autoassist());
    myteam->command("$assist " + OB_NAME(TO));
}

public void
attack_object(object ob)
{
    object *myteam;

    if (sizeof(myteam = (object *)query_team_others()))
        set_alarm(0.5, 0.0, &assist_me(myteam, ob));
    ::attack_object(ob);
}

public void
attacked_by(object ob)
{
    object *myteam;

    if (sizeof(myteam = (object *)query_team_others()))
        set_alarm(0.5, 0.0, &assist_me(myteam, ob));
    ::attacked_by(ob);
}

