inherit "/d/Genesis/race/shapeshift/shapeshift_creature";

#include "/d/Genesis/specials/debugger/debugger_tell.h"
#include "/d/Genesis/imbuement/imbuement.h"
#include "/d/Genesis/specials/defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

#define A_BITE  0                /* method of attack */

#define H_HEAD      0
#define H_BODY      1
#define H_LEFT_LEG  2
#define H_RIGHT_LEG 3
#define H_HIND      4

mapping player_hid_to_bear_hid = ([
        A_BODY  : H_BODY,
        A_L_ARM : H_LEFT_LEG,
        A_R_ARM : H_RIGHT_LEG,
        A_LEGS  : H_HIND,
        A_HEAD  : H_HEAD
    ]);

mapping hitloc_damage_effects = ([ H_BODY : ({ }),
                                   H_LEFT_LEG : ({ }),
                                   H_RIGHT_LEG : ({ }),
                                   H_HIND : ({ }),
                                   H_HEAD : ({ }) ]);

function *did_hit_imbue_effects = ({ });

// Prototypes
private void convert_armour_imbues();
private void convert_weapon_imbues();

void
create_shapeshift_creature()
{
    set_race_name("bear");
    set_adj(({"small", "white"}));
    set_short("small white bear");
    set_long("This is a small white bear, that's actually a mouse. While it looks cute, you sense "
        + "that there's more to him as meets the eye.\n");

    if (!IS_CLONE)
        return;

    set_gender(G_MALE);
    set_stats(({ 150, 150, 150, 100, 100, 100 }));

    refresh_living();

    add_prop(CONT_I_WEIGHT, 1000); /* weight = 1 kilogram */
    add_prop(CONT_I_HEIGHT, 60); /* height = 6 centimeters */
    add_prop(CONT_I_VOLUME, 220); /* volume = 220 milliliters */

    /* Wep_type,   to_hit,   pen,   Dam_type,   %usage,   attack_desc */
    set_attack_unarmed(A_BITE,   30, 30, W_IMPALE, 80, "sharp teeth");

    /* Hit_loc, *Ac against (impale/slash/bludgeon/magic), %hit, hit_desc */
    set_hitloc_unarmed(H_HEAD, ({ 5, 7, 3, 2 }), 30, "head");
    set_hitloc_unarmed(H_BODY, ({ 2, 4, 8, 0 }), 60, "body");
    set_hitloc_unarmed(H_LEFT_LEG, ({ 3, 0, 1, 0 }), 10, "left foreleg");
    set_hitloc_unarmed(H_RIGHT_LEG, ({ 3, 0, 1, 0 }), 10, "right foreleg");
    set_hitloc_unarmed(H_HIND, ({ 3, 0, 1, 0 }), 10, "hindquarters");

    set_shapeshift_duration(300);
}


public void
hook_prepare_shapeshift_target()
{
    // Handle skill conversion
    // Handle resistances
    // Handle hit / pen / ac 
    // Handle stats
    // Handle quickness
    // Handle health conversion
    // Handle fatigue / stuffed 
    // Todo: check for handling of weapons like the mage bane while in the holding room

    convert_weapon_imbues();
    convert_armour_imbues();

    add_cmdsoul(ABILITY_DIR + "guilds/souls/spell_manager_soul");
    update_hooks();
}

// Generic imbue handling

/*
 * Function name: imbue_shadows
 * Description:   Goes over an objects shadows to find all imbues
 * Arguments:     ob - the object to check for imbues
 * Returns:       A list of imbues (or empty if none)
 */
private object *
imbue_shadows(object ob) 
{
    object *shadows = ({ });
    while (ob = shadow(ob, 0)) 
    {
        if (ob->has_imbue_shadow()) shadows += ({ ob });
    }
    return shadows;
}

/*
 * Function name: handle_imbue
 * Description:   Convert imbues that are not weapon / armour damage related
 * Arguments:     imbue - the imbue to convert 
 */
private void
handle_imbue(object imbue)
{
    send_debug_message("handle_imbue", 
        sprintf("Convert imbue %O for shapeshifting\n", imbue));

    // TODO effect_healing_shadow
} 

// Weapon imbue handling
private void
bane_strike_message(object imbue, object item_owner, object enemy,
    string hitloc_desc, string hit_desc, string damage_desc, int damage)
{
    string damage_msg = imbue->query_damage_msg();

    item_owner->catch_msg(capitalize(damage_msg) + " your "
      + " claws and " + hit_desc + " the " + hitloc_desc
      + " of " + QTNAME(enemy) + "!\n" + capitalize(enemy->query_pronoun())
      + " looks " + damage_desc + ".\n");

    enemy->catch_msg(capitalize(damage_msg) + " "
      + QTNAME(item_owner) + "'s claws and " + hit_desc
      + " your " + hitloc_desc + "!\n"
      + "You are " + damage_desc + ".\n");

    item_owner->tell_watcher(capitalize(damage_msg) + " "
      + QTNAME(item_owner) + "'s claws and " + hit_desc
      + " the " + hitloc_desc + " of " + QTNAME(enemy) + "!\n"
      + capitalize(enemy->query_pronoun()) + " looks " + damage_desc
      + ".\n", enemy);
}

private void
bane_imbue_effect(object imbue, int aid, string hdesc, int phurt, object enemy, 
    int dt, int phit, int dam, int hid)
{
    send_debug_message("hit_imbue", sprintf("Trigger bane effect %O\n", imbue));
    imbue->check_race(this_object(), enemy, hid, &bane_strike_message(imbue), 0);
}

private void
elemental_strike_message(object imbue, object item_owner, object enemy,
    string hitloc_desc, string hit_desc, string damage_desc, int damage)
{
    string *damage_msgs = imbue->query_damage_msgs();

    item_owner->catch_msg(capitalize(damage_msgs[0]) + " your "
      + " claws and " + hit_desc + " the " + hitloc_desc
      + " of " + QTNAME(enemy) + "!\n" + capitalize(enemy->query_pronoun())
      + " looks " + damage_desc + " by the " + damage_msgs[1] + ".\n");

    enemy->catch_msg(capitalize(damage_msgs[0]) + " "
      + QTNAME(item_owner) + "'s claws and " + hit_desc
      + " your " + hitloc_desc + "!\n"
      + "You are " + damage_desc + " by the " + damage_msgs[1] + ".\n");

    item_owner->tell_watcher(capitalize(damage_msgs[0]) + " "
      + QTNAME(item_owner) + "'s claws and " + hit_desc
      + " the " + hitloc_desc + " of " + QTNAME(enemy) + "!\n"
      + capitalize(enemy->query_pronoun()) + " looks " + damage_desc
      + " by the " + damage_msgs[1] + ".\n", enemy);
}

private void
damage_imbue_effect(object imbue, int aid, string hdesc, int phurt, object enemy, 
    int dt, int phit, int dam, int hid)
{
    send_debug_message("hit_imbue", sprintf("Trigger damage effect %O\n", imbue));
    imbue->elemental_strike(this_object(), enemy, hid, &elemental_strike_message(imbue));
}

private void
poison_imbue_effect(object imbue, int aid, string hdesc, int phurt, object enemy, 
    int dt, int phit, int dam, int hid)
{
    send_debug_message("hit_imbue", sprintf("Trigger poison effect %O\n", imbue));
}

private void
slow_imbue_effect(object imbue, int aid, string hdesc, int phurt, object enemy, 
    int dt, int phit, int dam, int hid)
{
    send_debug_message("hit_imbue", sprintf("Trigger slow effect %O\n", imbue));
}

public varargs int
cr_did_hit(int aid, string hdesc, int phurt, object enemy, int dt,
           int phit, int dam, int hid)
{
    if (phurt > 0) 
    {
        foreach(function effect : did_hit_imbue_effects) {
            set_alarm(0.0, 0.0, &effect(aid, hdesc, phurt, enemy, dt, phit, dam, hid));
        }
    }
    
    return 0;
}

/*
 * Function name: convert_weapon_imbues
 * Description:   Handle offensive weapon imbues
 */
private void 
convert_weapon_imbues()
{
    foreach(object weapon : get_player()->query_weapon(-1))
    {
        if (!weapon->has_imbue_shadow()) continue;

        foreach(object imbue : imbue_shadows(weapon))
        {
            string imbue_init = function_exists("init_imbue_shadow", imbue);

            if (function_exists("race_damage", imbue)) 
            {
                send_debug_message("convert_weapon_imbues",
                            sprintf("Found bane imbue %O on %s\n", imbue, 
                                weapon->short()));
                did_hit_imbue_effects += ({ &bane_imbue_effect(imbue) });
            } 
            else if (function_exists("elemental_strike", imbue)) 
            {
                send_debug_message("convert_weapon_imbues",
                            sprintf("Found damage imbue %O on %s\n", imbue, 
                                weapon->short()));
                did_hit_imbue_effects += ({ &damage_imbue_effect(imbue) });
            }
            else if (imbue_init == SHADOW_DIR + "effect_poison_shadow")
            {
                send_debug_message("convert_weapon_imbues",
                            sprintf("Found poison imbue %O on %s\n", imbue, 
                                weapon->short()));
                did_hit_imbue_effects += ({ &poison_imbue_effect(imbue) });
            }
            else if (imbue_init == SHADOW_DIR + "effect_slow_shadow")
            {
                send_debug_message("convert_weapon_imbues",
                            sprintf("Found slow imbue %O on %s\n", imbue, 
                                weapon->short()));
                did_hit_imbue_effects += ({ &slow_imbue_effect(imbue) });
            }
            else handle_imbue(imbue);
        }
    }
}

// Armour imbue handling

/*
 * Function name: cr_got_hit
 * Description:   Called from the combat object when we get hit, we use this
 *                to similate the got_hit function on arour that triggers
 *                imbues.
 * Arguments:     hid:   The hitloc id
 *                ph:    The %hurt
 *                att:   Attacker
 *                aid:   The attack id
 *                dt:    The damagetype
 *                dam:   The damage in hitpoints
 */
public varargs void
cr_got_hit(int hid, int ph, object att, int aid, int dt, int dam)
{
    if (ph == 0) return;

    object *effects = hitloc_damage_effects[hid];
    if (!pointerp(effects) || !sizeof(effects)) return;

    foreach(object effect : effects) 
    {
        // TODO: Handle imbue on hit
        send_debug_message("shapeshift_armour_imbue",
            sprintf("TODO trigger armour imbue on %O\n", effect));
        effect->check_race(this_object(), att, hid, &bane_strike_message(effect), 1);
    }
}

/*
 * Function name: convert_armour_imbues
 * Description:   Maps imbues on armours to hit locations on the bear
 *                and triggers handling of non bane imbues
 */
private void 
convert_armour_imbues()
{
    object *other_imbues = ({ });
    foreach(int hid : ({ A_BODY, A_L_ARM, A_R_ARM, A_LEGS, A_HEAD })) 
    {
        int bear_hid = player_hid_to_bear_hid[hid];
        mixed *hitloc = get_player()->query_combat_object()->query_hitloc(hid);
        if (!pointerp(hitloc[4])) continue;

        foreach(object armour : hitloc[4]) 
        {
            if (!armour->has_imbue_shadow()) continue;

            foreach(object imbue : imbue_shadows(armour)) 
            {
                // Bane imbues also trigger when an armour gets hit
                if (function_exists("race_damage", imbue)) 
                {
                    send_debug_message("convert_armour_imbues",
                        sprintf("Found bane imbue %O on %s (from %s)\n", imbue, 
                            hitloc[2], armour->short()));

                    hitloc_damage_effects[bear_hid] += ({ imbue });
                } 
                else 
                {
                    if (member_array(imbue, other_imbues) == -1) 
                    {
                        other_imbues += ({ imbue });
                    }
                }
            }
        }
    } 

    map(other_imbues, handle_imbue);
}