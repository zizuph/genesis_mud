/*
 * Tamer Maneuver Shadow
 *
 * Allows a tamer to rescue his pet, or send his pet to the front.
 */
#include <composite.h>
#include <stdproperties.h>
#include <std.h>
#include <macros.h>

#include "defs.h"

inherit "/std/shadow";

#include "/d/Genesis/specials/debugger/debugger_tell.h"

// Global Variables
static mapping  gRescueMap = ([]);

// Prototypes
public status   query_protector_health_limit(object protector);

public void
remove_tamer_maneuver_shadow()
{
    object protector;
    
    if (objectp(protector = gRescueMap[shadow_who]["protector"]) &&
        !interactive(protector))
    {
        protector->remove_hook(HOOK_TAMER_HEAL_HP, this_object());
        
        if (query_protector_health_limit(protector))
        {
            shadow_who->catch_msg(QCTNAME(protector) + " retreats due to the "
            + "extent of " + protector->query_possessive() + " wounds.\n");
            tell_room(environment(protector), QCTNAME(protector) + " retreats "
            + "due to the extent of " + protector->query_possessive() + " "
            + "wounds.\n", ({ protector, shadow_who }), protector);
        }
    }
    
    foreach(object attacker, mapping list: gRescueMap)
    {
        if (!objectp(attacker) || attacker == shadow_who)
            continue;
        
        if (!objectp(list["OldTarget"]) || !CAN_SEE_IN_ROOM(attacker) ||
            environment(list["OldTarget"]) != environment(attacker) ||
            !CAN_SEE(attacker, list["OldTarget"]))
            continue;
        
        if (!interactive(attacker) && objectp(attacker->query_attack()))
        {
            attacker->attack_object(list["OldTarget"]);
            tell_room(environment(attacker), QCTNAME(attacker) + " turns to "
            + "attack " + QTNAME(list["OldTarget"]) + ".\n",
            ({ attacker, list["OldTarget"] }), attacker);
            list["OldTarget"]->catch_msg(QCTNAME(attacker) + " turns to attack "
            + "you.\n");
            continue;
        }
        
        attacker->catch_msg("You glimpse an opening to resume your assault on "
        + QTNAME(list["OldTarget"]) + ".\n");
    }
    
    remove_shadow();
}

public status
has_tamer_maneuver_shadow()
{
    object *list;

    list  = m_indexes(gRescueMap);
    list &= all_inventory(environment(shadow_who));
    if (sizeof(list - ({ shadow_who })))
        return 1;
    
    set_alarm(0.0, 0.0, &remove_tamer_maneuver_shadow());
    return 0;
}

public int
query_protector_health_limit(object protector)
{
    int max_health, health, p_health;
    
    if (interactive(protector))
        return 0;
    
    max_health = protector->query_max_hp();
    p_health = shadow_who->query_max_hp();
    health = protector->query_hp();
    
    /* check if health is below 50% limit */
    
    if ((((max_health - health) * 100) / p_health) > 50)
        return 1;
    
    return 0;
}

public void
update_protector_health(object protector)
{
    if (query_protector_health_limit(protector))
        remove_tamer_maneuver_shadow();
}

public void
remove_maneuver_enemies()
{
    foreach(object index, mapping value : gRescueMap)
    {
        if (index != shadow_who)
            m_delkey(gRescueMap, index);
    }
    
    remove_tamer_maneuver_shadow();
}

public void
set_maneuver_enemies(object *enemies, object protector)
{
    foreach(object attacker: enemies)
    {
        if (!mappingp(gRescueMap[attacker]))
        {
            gRescueMap[attacker] = ([
                "NewTarget" : protector,
                "OldTarget" : shadow_who,
            ]);
        }
        
        attacker->catch_msg("You turn to attack " + QTNAME(protector) + ".\n");
        protector->catch_msg(QCTNAME(attacker) + " turns to attack you.\n");
        tell_room(environment(attacker), QCTNAME(attacker) + " turns to attack "
        + QTNAME(protector) + ".\n", ({ attacker, protector}), protector);
        attacker->attack_object(protector);
    }
}

public status
set_maneuver_protector(object protector)
{
    if (!objectp(protector))
        return 0;
    
    if (!interactive(protector))
    {
        if (query_protector_health_limit(protector))
        {
            set_alarm(0.0, 0.0, &remove_tamer_maneuver_shadow());
            return 0;
        }
        
        protector->add_hook(HOOK_TAMER_HEAL_HP, &update_protector_health());
    }
    
    if (!mappingp(gRescueMap[shadow_who]))
        gRescueMap[shadow_who] = ([]);
    
    gRescueMap[shadow_who]["protector"] = protector;
    
    return 1;
} /* set_protector */

public void
hook_attacked_message(object attacker, object protector)
{
    if (protector->query_prop(LIVE_O_STEED) != shadow_who &&
        protector->query_steed() != shadow_who)
    {
        attacker->catch_msg(QCTNAME(protector) + " intervenes in your attempt "
        + "to attack " + QTNAME(shadow_who) + ", you turn to attack "
        + shadow_who->query_objective() + " instead.\n");
    
        protector->catch_msg("You intervene in " + QTPNAME(attacker)
        + " attempt to attack " + QTNAME(shadow_who) + ", forcing "
        + attacker->query_objective() + " to attack you instead.\n");
    
        shadow_who->catch_msg(QCTNAME(protector) + " intervenes in "
        + QTPNAME(attacker) + " attempt to attack you, forcing "
        + attacker->query_objective() + " to attack " + QTNAME(protector) + " "
        + "instead.\n");
    
        tell_room(environment(protector), QCTNAME(protector) + " intervenes in "
        + QTPNAME(attacker) + " attempt to attack " + QTNAME(shadow_who)
        + ".\n", ({ attacker, shadow_who, protector }), shadow_who);
        
        return;
    }
    
    attacker->catch_msg("You attempt to attack the " + QTNAME(shadow_who) + ", "
    + "but " + QTNAME(protector) + " maneuver " + protector->query_possessive()
    + " mount out of harms way, facing you head on.\n");
    protector->catch_msg("You maneuver " + QTNAME(shadow_who) + " out of harms "
    + "way, facing " + QTNAME(attacker) + " head on.\n");
    tell_room(environment(shadow_who), QCTNAME(protector) + " maneuvers "
    + QTNAME(shadow_who) + " out of harms way, facing " + QTNAME(attacker)
    + " head on.\n", ({ shadow_who, protector, attacker }), shadow_who);
} /* hook_attacked_message */

/*
 * Function name:   attacked_by
 * Description:     This routine is called when we are attacked.
 * Arguments:       (object) attacker - the attacker.
 * Returns:         Nothing
 */
public void
attacked_by(object attacker)
{
    object protector;
    
    if (!mappingp(gRescueMap[shadow_who]) ||
        !objectp(protector = gRescueMap[shadow_who]["protector"]) ||
        environment(protector) != environment(shadow_who) ||
        !CAN_SEE_IN_ROOM(protector) || !CAN_SEE(protector, attacker) ||
        protector == attacker || query_protector_health_limit(protector) ||
        !IN_ARRAY(attacker, m_indexes(gRescueMap)))
        return shadow_who->attacked_by(attacker);
    
    attacker->attack_object(protector);
    set_alarm(0.0, 0.0, &hook_attacked_message(attacker, protector));
} /* attacked_by */

