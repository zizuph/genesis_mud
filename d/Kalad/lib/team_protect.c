/*
 *  Ckrik March 2004
 *
 *      Inherit this if you have some VIP NPC that needs
 *      to be protected by his/her team.  By inheriting
 *      this file in the VIP, all other team members have
 *      to be killed in order for the VIP to be attacked.
 *
 *      void set_vip_importance(int n)
 *           Call this function to set the priority at
 *           which the VIP is protected in case there
 *           are two in the same team.  The VIP with the
 *           higher importance in the team will be
 *           protected by NPCs of lower importance.
 *           Importance should be an integer >= 1.  NPCs
 *           that do not use this lib will automatically
 *           have an importance of 0.  NPC in the same
 *           team with the same importance will not
 *           protect each other.  Setting importance to
 *           0 implies that the NPC will not be protected
 *           at all.
 *
 *      int query_vip_importance()
 *           Returns the importance of the NPC.
 *
 *      void protect_vip_message_hook(object attacker, object protector, 
 *                                    object vip)
 *           Redefine this function if you want to
 *           customize what message is shown when the team
 *           members step in to protect the VIP.
 *
 *     Ckrik GENEROUSLY gave Mirandus permission in 2022 to use this
 *     code nearly verbatim in Kalad. He is awesome.
 */
#pragma strict_types
#include <macros.h>
inherit "/d/Kalad/std/active_monster_base.c";
inherit "/std/combat/unarmed";

static int importance = 1;

public void
set_vip_importance(int n)
{
    if (n >= 0)
    {
        importance = n;
    }
}

public int
query_vip_importance()
{
    return importance;
}

public void 
protect_vip_message_hook(object attacker, object protector, object vip)
{
    attacker->catch_msg(QCTNAME(protector) + " steps in between you " +
        "and " + QTNAME(vip) + " drawing your attack.\n");
    attacker->tell_watcher(QCTNAME(protector) + " steps in between " +
        QTNAME(attacker) + " and " + QTNAME(vip) +
        " drawing " + QTPNAME(attacker) + " attack.\n",
        attacker);
}

static int
less_important(object obj)
{
    if (obj->query_vip_importance() < importance)
    {
        return 1;
    }
    return 0;
}

public varargs mixed
hit_me(int wcpen, int dt, object enemy, int attack_id, int target_hitloc)
{
    object *team;
    object protector, to = this_object();

    int i;

    /* Trap some nasty runtime error */
    if (!objectp(enemy) || !objectp(to))
    {
        return ::hit_me(wcpen, dt, enemy, attack_id, target_hitloc);
    }

    /* VIP protection disabled or hit_me came from someone not 
     * attacking the living
     */
    if (importance <= 0 || enemy->query_attack() != to)
    {
        return ::hit_me(wcpen, dt, enemy, attack_id, target_hitloc);
    }

    team = to->query_team_others();
    team = filter(team, less_important);
    if (!sizeof(team))
    {
        return ::hit_me(wcpen, dt, enemy, attack_id, target_hitloc);
    }
    /* Select a protector with the greatest amount of HP
     * left
     */
    protector = team[0];
    for (i = 1; i < sizeof(team); i++)
    {
        if (team[i]->query_hp() > protector->query_hp())
	      {
	          protector = team[i];
	      }
    }
    /* Take over the attacks from the VIP */
    enemy->attack_object(protector);
    protect_vip_message_hook(enemy, protector, to);
    return ::hit_me(wcpen, dt, enemy, attack_id, target_hitloc);
}
