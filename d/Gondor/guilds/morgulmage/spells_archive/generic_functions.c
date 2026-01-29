/*
 * Generic functions used within the morgul spells. Originally this was
 * placed in a generic spell inherit for the morgul mages, but with the
 * new base system, each spell inherits from it's standard spell from
 * the specials library. Thus, to properly override these functions, this
 * file needs to be #included into the spells, not inherited.
 *
 * Eowul, Oktober 2009
 */
 
#include <macros.h>
#include <filter_funs.h>
#include <ss_types.h>
#include "../morgulmage.h"
#include "/d/Genesis/specials/debugger/debugger_tell.h"

object *can_see_caster(object caster)
{
    if (!objectp(caster)) return ({});
    return FILTER_IS_SEEN(caster, FILTER_PLAYERS(all_inventory(
        environment(caster)))- ({ caster }) );
}

public int
query_spell_guild_strength()
{
    if(!IS_MEMBER(this_player())) return 0;
    if(this_player()->query_wiz_level()) return 100;
    if(this_player()->query_npc()) return 100;
    return MAX(0, MIN(100, (this_player()->query_stat(SS_OCCUP) * 100) / 150));
}


#ifndef LIVE_I_MAINTAINED_EFFECTS
#define     LIVE_O_MAINTAINED_EFFECTS   "_live_o_maintained_effects"
#endif

public int
query_has_maintained_spell_effect(object target, mixed filenames)
{
    if (!pointerp(filenames)) filenames = ({ filenames });

    object * effects = target->query_prop(LIVE_O_MAINTAINED_EFFECTS);
    if (!pointerp(effects)) effects = ({});
    
    foreach(object effect : effects) {
        if (objectp(effect) 
            && (member_array(MASTER_OB(effect), filenames) != -1)) {
            return 1;
        }
    }
    
    return 0;
}

public void
add_maintained_spell_effect(object target, mixed obs) {
    if (!pointerp(obs)) obs = ({ obs });
    object *effects = target->query_prop(LIVE_O_MAINTAINED_EFFECTS);
    
    if (!pointerp(effects)) effects = obs;
    else effects += obs;
    
    effects -= ({ 0 }); // clear deleted effects
    target->add_prop(LIVE_O_MAINTAINED_EFFECTS, effects);
}

public int
query_has_spell_effect(object target, mixed filenames)
{
    if (!pointerp(filenames)) filenames = ({ filenames });

    object *effects = target->query_magic_effects();
    if (!pointerp(effects)) effects = ({});
  
    foreach(object effect : effects) {
        if (objectp(effect) 
            && (member_array(MASTER_OB(effect), filenames) != -1)) {
            return 1;
        }
    }
    
    return 0;
}

public void
dispel_artirith(object player)
{
    foreach(object spelleffect : player->query_magic_effects())
    {
        if (spelleffect->query_spell_effect_name() == "artirith")
        {
            spelleffect->dispel_spell_effect(player);
            return;
        }
    }
}

public float
adjust_time_by_rank(float base = 1.0) 
{
    float guild_strength = itof(query_spell_guild_strength());
    float multiplier = base + ((100.0 - guild_strength) / 200.0);

    send_debug_message("debug_morgulmage", 
        sprintf("Time factor adjusted for rank %f, from %f to %f",
            guild_strength, base, multiplier));

    return multiplier;        
}

