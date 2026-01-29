/*
 *  This is a shadow that turns the shadowed living into an undead
 *  being, inheriting the following characteristics:
 *
 *  Positive
 *  x Cannot drown (Avenir and Calia drown objects)
 *    Implemented by the MAGIC_I_BREATH_WATER property
 *  x Immunity to poisons (100% resistance to poison element)
 *  x Natural Darkvision
 *  x Healing from Death Spells (negative energy heals undeads)
 *  x Cannot be stunned (implemented in mudlib)
 *
 *  Negative
 *  x Damage from Healing Spells (healing harms undeads)
 *  x Cannot eat or drink (or at least not gain the effects of
 *    either, herbs included)
 *  x Vulnerability to Life spells (effect amplification, 10-20%)
 *
 *  Created by Eowul, December 2009
 *
 *  Change log
 *  ----------
 *
 *  Ckrik 5/17/2022
 *      - Removed no fatigue from undead since many players
 *        have been running instant loot scripts and without
 *        fatigue as a speed bump they were making massive
 *        amounts of money.
 *      - In exchange, undeads are always stuffed and regenerate
 *        fatigue at an extra 30% rate.
 */
 
#include <stdproperties.h>
#include <files.h>
#include <wa_types.h>
#include <ss_types.h>
#include <formulas.h>
#include <poison_types.h>
#include <gmcp.h>
#include <state_desc.h>

inherit "/std/shadow";

#include "/d/Genesis/specials/debugger/debugger_tell.h"

#define LIFE_EFFECT_AMPLIFICATION   10

private int recursive_lock      = 0;

int fatigue_time;

/*
 * Function name: make_player_undead
 * Description  : Turns the given player into an undead
 * Arguments    : player - the player to turn undead
 */
private void make_player_undead(object player) {
    player->add_prop(LIVE_I_UNDEAD, 100);
    player->inc_prop(LIVE_I_SEE_DARK, 1);
    player->add_prop(OBJ_I_RES_POISON, 100);
    player->dec_prop(OBJ_I_RES_LIFE, LIFE_EFFECT_AMPLIFICATION);
    player->add_prop(MAGIC_I_BREATH_WATER, 100);
    player->add_prop(LIVE_M_NO_INGEST, "Eating has no effect on your undead body.\n");
    player->add_prop(LIVE_M_NO_DRINK, "Drinking has no effect on your undead body.\n");
    player->add_prop(LIVE_I_NO_STUN, 1);
}

/*
 * Function name: make_player_living
 * Description  : Remove the undead properties from the player
 * Arguments    : player - the player to turn alive again
 */
private void make_player_living(object player) {
    player->add_prop(LIVE_I_UNDEAD, 0);
    player->dec_prop(LIVE_I_SEE_DARK, 1);
    player->add_prop(MAGIC_I_RES_POISON, 0);
    player->inc_prop(MAGIC_I_RES_LIFE, LIFE_EFFECT_AMPLIFICATION);
    player->add_prop(MAGIC_I_BREATH_WATER, 0);
    player->remove_prop(LIVE_I_NO_STUN);
    player->remove_prop(LIVE_M_NO_DRINK);
    player->remove_prop(LIVE_M_NO_INGEST);
}


public void set_intoxicated(int i)
{
    //Do not set it
}

/*
 * Ckrik, 5/17/2022, disabled no fatigue to prevent endless
 * loot loops. In exchange undeads will be always stuffed
 * and regenerate fatigue at an extra 30% rate.
 */
#if 0 
public void add_fatigue(int i) 
{
    // Undead do not become fatigued
}

public void query_fatigue() 
{ 
    return shadow_who->query_max_fatigue(); 
}

public void set_fatigue(int i) {
    shadow_who->set_fatigue(shadow_who->query_max_fatigue());
}
#endif

public int
query_stuffed()
{
    return shadow_who->query_prop(LIVE_I_MAX_EAT);
}

void
calculate_fatigue()
{
    // Because the underlying object calls calculate_fatigue(), we need to
    // bypass it when the call originates from here.
    if (recursive_lock)
    {
        return;
    }
    int interval, stuffed, tmpstuffed, maximum, fatigue;

    interval = (time() - fatigue_time) / F_INTERVAL_BETWEEN_FATIGUE_HEALING;
    if (interval > 0)
    {
        stuffed = query_stuffed();
        
        recursive_lock = 1;
        fatigue = shadow_who->query_fatigue();
        recursive_lock = 0;
        
        fatigue_time += interval * F_INTERVAL_BETWEEN_FATIGUE_HEALING;
        // Ckrik, allow undeads to get 30% extra fatigue regeneration.
        fatigue += interval * F_FATIGUE_FORMULA(stuffed, shadow_who->query_prop(LIVE_I_MAX_EAT)) *
            130 / 100;
        fatigue = min(fatigue, shadow_who->query_max_fatigue());

        recursive_lock = 1;
        shadow_who->set_fatigue(fatigue);
        recursive_lock = 0;

        /* Update the GMCP information for players. */
        if (shadow_who->query_gmcp(GMCP_CHAR))
        {
            maximum = shadow_who->query_max_fatigue();
            shadow_who->gmcp_char(GMCP_CHAR_VITALS, GMCP_FATIGUE,
                GET_NUM_DESC_SUB(maximum - fatigue, maximum, SD_FATIGUE, SD_STAT_DENOM, 1));
        }
    }
}

// Shadow bookkeeping
public varargs int shadow_me(mixed to_shadow) {
    int result = ::shadow_me(to_shadow);
    if (result) make_player_undead(to_shadow);
    return result;
}

int has_undead_shadow()
{
    return 1;
}

void remove_undead_shadow()
{
    make_player_living(shadow_who);
    remove_shadow();
}

private int get_spell_element() 
{
    int last_element = -1;
    int current = 0;
    object previous = 0;
    while(objectp(previous = previous_object(current))) 
    {
        if (function_exists("query_spell_element_skill", previous)) 
        {
            last_element = previous->query_spell_element_skill();
        }
        
        if (function_exists("query_spell_element", previous))
        {
            last_element = previous->query_spell_element();
        }

        current--;
    }

    return last_element;
}

public varargs mixed hit_me(int wcpen, int dt, object attacker, int attack_id, int target_hitloc = -1) 
{
    if (dt == MAGIC_DT) 
    {
        int previous_spell_element = get_spell_element();
        if (previous_spell_element == SS_ELEMENT_DEATH) 
        {
            int heal_max = F_NEW_DAMAGE(wcpen, 100, 40) / 4;
            
            // Randomize heal_max a bit using similar formula to cb_hit_me
            heal_max += random(heal_max) + random(heal_max) + random(heal_max);

            send_debug_message("undead_shadow", sprintf("Player hit with "
                + "death magic with wcpen %i, healing for %i hp.", 
                wcpen, heal_max));
                
            shadow_who->catch_msg("You feel strengthened by the undead "
                + "energies unleashed upon you.\n");
            shadow_who->heal_hp(heal_max);
            
            return ({ 0, 0, 0, 0, 0 });
        }
    }
    return shadow_who->hit_me(wcpen, dt, attacker, attack_id, target_hitloc);
}

private void neutralize_poison(object poison)
{
    send_debug_message("undead_shadow", sprintf("Neutralizing poison %O\n",
        poison));
    poison->set_silent(2);
    
    mixed original_damage = poison->query_damage();
    mixed new_damage = ({ });
    for(int i = 0; i < sizeof(original_damage); i = i + 2) {
        if (original_damage[i] == POISON_USER_DEF) {
            new_damage += ({ original_damage[i], original_damage[i + 1] });
        }
    }
    poison->set_damage(new_damage);
}

void enter_inv(object ob, object from)
{
    if (objectp(ob) && IS_POISON_OBJECT(ob)) {
        neutralize_poison(ob);
    }
    shadow_who->enter_inv(ob, from);
}
