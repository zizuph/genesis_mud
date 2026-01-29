/*
 * Monster Teaming Functions
 *
 * Split out of monster.c
 */
#pragma strict_types
#include "/d/Khalakhor/sys/defs.h"
#include <macros.h>


static int Leader;
static int Follower;
static int Autoassist;
static string Name;

public void
set_team_leader()
{
    Leader = 1;
}

public void
remove_team_leader()
{
    Leader = 0;
}

public int
query_team_leader()
{
    return Leader;
}

public void
set_team_follower()
{
    Follower = 1;
}

public void
remove_team_follower()
{
    Follower = 0;
}

public int
query_team_follower()
{
    return Follower;
}

public string
set_team_name(string str)
{
    Name = str;
}

public string
query_team_name()
{
    if (Name)
        return Name;
    return "";
}

public void
set_autoassist()
{
    Autoassist = 1;
}

public void
remove_autoassist()
{
    Autoassist = 0;
}

public int
query_autoassist()
{
    return Autoassist;
}

/*
 * Team pickup decisions
 */
void
init_team()
{
    /* No teaming if not set to be a follower! */
    if (!(TO->query_team_follower()))
        return;

    /* Leaders won't join other leaders */
    if (TO->query_team_leader())
        return;

    /* Followers can only join leaders */
    if (!TP->query_team_leader())
        return;

    /* Can't join any team if already in one. */
    if ((sizeof(TO->query_team_others())) > 0)
        return;

    /* Don't join if no team names set */
    if (strlen(TO->query_team_name()) == 0)
        return;

    /* Don't join if our team names are dissimilar */
    if ((TO->query_team_name()) != (TP->query_team_name()))
        return;

    /* Ok, we've met a potential leader, we aren't in */
    /* a team, and the team leader has our team name, */
    /* so join up. */
    tell_room(environment(TO), QCTNAME(TO) +
        " joined the team of " + QTNAME(TP) + ".\n");
    this_player()->team_join(TO);
}
