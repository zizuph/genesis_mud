
#include "../defs.h";
#include <formulas.h>

/*
 * Removed Calm Code, as it was no longer being used.
 */
 
/*
 * Making Obfuscated disappear once the vampire is in combat
 * February 2009.
 * Rationale:
 *  Obfuscate will be changed so that the effect collapses entirely 
 *  when combat is begun. While the victim was able to see what was
 *  going on, the fact that others in the room were not made this a
 *  partial invisiblity effect, and destroyed logical combat mechanics
 *  for teams. No invisibility effects, even partial, will be allowed
 *  during combat for any guild abilities globally.
 */

/*
 * Changelog
 *  November 2009 - Added code to track PvP combat. VMeld is supposed to be
 *                  capable of being used when not in PvP, so that if dawn
 *                  hits them, it will allow them to protect themselves.
 *                  However, the problem is that there's no way to track
 *                  PvP correctly except by little hacks like this. Petros
 */

// Defines
#define     LAST_PVP_TIME       "_live_o_last_vamp_pvp"

public void
dispel_obfuscate_spell_effect(object ob)
{
    object * effects;
    
    effects = QSW->query_magic_effects();
    foreach (object effect : effects)
    {
        if (effect->id("_obfuscate_obj"))
        {
            effect->dispel_spell_effect(ob);
            break;
        }
    }
}

/*
 * Function name:   attack_object
 * Description:     Start attacking, the actual attack is done in heart_beat
 * Arguments:       The object to attack
 */
public void
attack_object(object ob)
{
    // Upon attacking someone, check to see if obfuscated. If so, we
    // remove the spell effect object
    dispel_obfuscate_spell_effect(ob);

    if (interactive(ob))
    {
        QSW->add_prop(LAST_PVP_TIME, time());
    }
            
    QSW->attack_object(ob);
}

/*
 * Function name:   attacked_by
 * Description:     This routine is called when we are attacked.
 * Arguments:       ob: The attacker
 */
public void 
attacked_by(object ob)
{
    // Upon being attacked by someone, check to see if obfuscated. If so,
    // we remove the spell effect object.
    dispel_obfuscate_spell_effect(ob);
    
    if (interactive(ob))
    {
        QSW->add_prop(LAST_PVP_TIME, time());
    }
    
    QSW->attacked_by(ob);
}

public int 
query_not_attack_me(object attacker, int att_id)
{
    if (TO->query_mist())
    {
        attacker->catch_msg(TO->query_name() + " cannot be attacked.\n");
        return 1;
    }

    return QSW->query_not_attack_me(attacker, att_id);
}

public int
query_vampire_in_pvp()
{
    // There are two ways to tell whether someone is in PvP or not.
    // 1. Last time attacked by or attacking another player is within relaxed
    //    timeframe
    // 2. Enemy list contains other players
    // 3. Other players contain Vampire in their enemy lists.
        
    // 1. Check for Last Recorded PvP Time
    int last_recorded_pvp = QSW->query_prop(LAST_PVP_TIME);    
    if ((F_RELAX_TIME_AFTER_COMBAT(last_recorded_pvp) + last_recorded_pvp) > time())
    {
        return 1;
    }
    
    // 2. Check if enemy list contains other players
    object * other_player_enemies = filter(QSW->query_enemy(-1), interactive);
    if (sizeof(other_player_enemies) > 0)
    {
        // We also update the last pvp time
        QSW->add_prop(LAST_PVP_TIME, time());
        return 1;
    }
    
    // 3. Check if other players enemy lists contain this vampire
    object * players = filter(users(), sizeof @ &->query_enemy(-1));
    foreach (object player : players)
    {
        if (IN_ARRAY(QSW, player->query_enemy(-1)))
        {
            // We also update the last pvp time
            QSW->add_prop(LAST_PVP_TIME, time());
            return 1;
        }
    }
    
    // If it passes all three conditions, the vamp is not in PvP
    return 0;
}
