/*
 * Generic functions used within the spells. Originally this was
 * placed in a generic spell inherit, but with the
 * new base system, each spell inherits from it's standard spell from
 * the specials library. Thus, to properly override these functions, this
 * file needs to be #included into the spells, not inherited.
 *
 * Originally created by Eowul, Oktober 2009, modified and used
 * by Nerull for the Warlocks.
 */
 
#include <macros.h>
#include <filter_funs.h>
#include <ss_types.h>
#include "../guild.h"

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


