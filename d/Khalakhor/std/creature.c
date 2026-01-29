/* File         : /d/Khalakhor/std/creature.c
 * Creator      : Teth@Genesis
 * Copyright:   : Daniel Mosquin
 * Date         : October 12, 1998         
 * Purpose      : Khalakhor standard creature, to be inherited by all
 *                creatures. These are non-humanoid npcs!      
 * Related Files: /std/creature.c
 * Comments     :
 * Modifications: Improved and updated - Teth, Jan 27 2002
 *                Added teaming module.
 */

#pragma save_binary
#pragma strict_types

#include <macros.h>
#include <math.h>
#include <std.h>
#include <stdproperties.h>
#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/sys/paths.h"

inherit "/std/creature";
inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/combat/unarmed";

// Teaming
void set_team_leader();
void remove_team_leader();
int query_team_leader();
void set_team_follower();
void remove_team_follower();
int query_team_follower();
string set_team_name(string str);
string query_team_name();
void set_autoassist();
void remove_autoassist();
int query_autoassist();
void team_up_check();

// Teaming
int Leader;
int Follower;
int Autoassist;
string Name;

public void
reset_khalakhor_creature()
{
}

public void
create_khalakhor_creature()
{
}

nomask void
reset_creature()
{
    reset_khalakhor_creature();
}

nomask void
create_creature()
{

    set_name("_Khalakhor_creature");

    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(LIVE_M_NO_ACCEPT_GIVE, 1);

    seteuid(getuid(this_object()));

    create_khalakhor_creature();
    reset_creature();
}

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
   
public void
init_living()
{
    ::init_living();

    /* Delay the team check - so that they don't join before
       arriving in the room */
    set_alarm(0.5, 0.0, "team_up_check");
}

public void
team_up_check()
{
  /* Here, we'll add a check for team followers to join */
  /* a team leader that arrives in their environment, */
  /* if they can. */
  
  /* No teaming if not set to be a follower! */
    if (!(TO->query_team_follower()))
        return;

  /* Leaders won't join other leaders */
    if (TO->query_team_leader())
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
        
  /* If we've got a team name, and the potential leader */
  /* doesn't, don't join. */
//    if (!TP->query_team_name() ||
//        !strlen(TP->query_real_name()))
//        
//        return;

  /* If the npc isn't set to join a specific team, */
  /* join any team leader. */
//    if (!Name || !strlen(Name))
//    {
//        tell_room(environment(TO), QCTNAME(TO) +
//            " joined the team of " + QTNAME(TP) + ".\n");
//        TP->team_join(TO);
//        return;
//    }

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

