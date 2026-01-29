#pragma strict_types
#pragma save_binary
 
inherit "/std/shadow";

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>
#include <composite.h>

#include "guild.h"

#define MAX_RAGE                100
#define PERCENT_DAMAGE            8

int     kender_rage;
mapping list_kenders;
mixed   rage_alarm;

public void
remove_kender_rage()
{
    if (shadow_who->query_uncontrollable_anger())
        shadow_who->remove_uncontrollable_anger();
    
    shadow_who->catch_msg("You manage to regain a bit of your " +
    "self control.\n");
    tell_room(environment(shadow_who), QCTNAME(shadow_who) +
    " seems to be regaining " + shadow_who->query_possessive() +
    " self control.\n", shadow_who);
    
    remove_shadow();
}

public int
query_kender_rage()
{
    return kender_rage;
}

public int
turned_aggression(object actor)
{
    object shadow;
    find_player("carnak")->catch_msg("hmm 1\n");
    
    if (!objectp(shadow_who->query_attack()) ||
        shadow_who->query_attack() != actor)
    {
        if (shadow_who->query_uncontrollable_anger())
            shadow_who->remove_uncontrollable_anger();
    
        if (objectp(shadow_who->query_attack()))
            shadow_who->stop_fight(shadow_who->query_attack());
        
        shadow_who->attack_object(actor);
    }
    
    if (actor->query_prop(SPECIAL_ATTACKS) >= 0)
        return 1;
    
    setuid();
    seteuid(getuid());
    
    shadow = clone_object(UNCONTROLLABLE_ANGER);
    shadow->shadow_me(shadow_who);
    shadow->set_anger_target(shadow_who);
    
    return 1;
}

public varargs int
add_kender_rage(int task, object actor)
{
    int     rage,
            etask;
    string  name,
            ename;
    
    if (!intp(task))
        return 0;
    
    if (!objectp(actor))
    {
        kender_rage = min(MAX_RAGE, (kender_rage + task));
        return 1;
    }
    
    name = actor->query_real_name();
    task = (((1000 / max(kender_rage, 30)) + (task*task) / 50) / 4);
    
    find_player("carnak")->catch_msg(kender_rage + " : " + task + "\n");
    
    if (!mappingp(list_kenders))
        list_kenders = ([]);
    
    if (!pointerp(list_kenders[name]))
    {
        list_kenders += ([ name : ({ time(), task }) ]);
    }
    else
    {
        rage = min(MAX_RAGE, list_kenders[name][1] + task);
        list_kenders[name] = ({ time(), rage });
    }

    kender_rage = min(MAX_RAGE, (kender_rage + task));
    
    if (objectp(shadow_who->query_attack()))
        ename = shadow_who->query_attack()->query_real_name();
    
    if (pointerp(list_kenders[ename]))
        etask = max(0, (rage - list_kenders[ename][1]));
    
    if ((etask ? etask : (task / 2)) < random(100))
        if (actor->query_prop(SPECIAL_ATTACKS) >= 0)
            return 1;
        else if (random(5))
            return 1;
    
    find_player("carnak")->catch_msg("aggro\n");
    
    turned_aggression(actor);
    
    return 1;
}

public varargs int
subtract_kender_rage(int task, object actor)
{
    int     rage;
    string  name;

    if (!intp(task))
        return 0;

    if (kender_rage - task <= 0)
    {
        remove_kender_rage();
    }
    
    if (!objectp(actor))
    {
        kender_rage = max(0, (kender_rage - task));
        return 1;
    }

    name    = actor->query_real_name();

    if (!pointerp(list_kenders[name]))
        return 0;
    
    rage = max(0, list_kenders[name][1] - task);
    list_kenders[name] = ({ time(), rage });

    kender_rage = max(0, (kender_rage - task));

    return 1;
}

void
init_rage_decay()
{
    if (rage_alarm)
        return;
    
    rage_alarm = set_alarm(2.0, 2.0, &subtract_kender_rage(1));
}

public int
query_skill(int skill)
{
    if (!kender_rage)
        return shadow_who->query_skill(skill);
    
    if (!IN_ARRAY(skill, ({ SS_UNARM_COMBAT, SS_WEP_SWORD,
                            SS_WEP_POLEARM,  SS_WEP_AXE,
                            SS_WEP_KNIFE,    SS_WEP_CLUB,
                            SS_WEP_MISSILE,  SS_WEP_JAVELIN,
                            SS_DEFENCE,      SS_PARRY })))
        return shadow_who->query_skill(skill);
    
    return max(0, (shadow_who->query_skill(skill) - max(kender_rage, 5)));
}

varargs public mixed
hit_me(int wcpen, int dt, object attacker, int attack_id, int target_hitloc = -1)
{
    string *kenders;
    object *party,
            player;
    mixed   hitres;
    int     damage;
    
    hitres  = shadow_who->hit_me(wcpen, dt, attacker, attack_id, target_hitloc);
    party   = attacker->query_team() + ({ attacker });
    kenders = filter(party->query_real_name(), &operator(>)(, -1) @
              &member_array(, m_indexes(list_kenders)));

    
    if (sizeof(kenders) && !random(sizeof(attacker->query_team())))
    {
        foreach(string name: kenders)
        {
            if (!objectp(player = find_player(name)))
                continue;
            
            if (player->query_prop(SPECIAL_ATTACKS) < 1)
                continue;
            
            if (environment(player) != environment(shadow_who))
                continue;
            
            damage += hitres[3];
        }
        
        // ADD DESCRIPTION FOR INCREASED DMG!!
        
        damage -= ((damage * (100 - PERCENT_DAMAGE)) / 100);
        shadow_who->heal_hp(-damage);
    }

    return hitres;
}