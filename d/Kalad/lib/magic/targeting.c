/*
    /d/Kalad/lib/magic/targeting.c
    
    Extension to /d/Genesis/magic/targeting.c
    
    Fysix, Feb 1998
 */
#pragma strict_types
#pragma save_binary

inherit "/d/Genesis/magic/targeting";

// Combination of the standard targeting on other living and enemy
// Target on a present player as specified, otherwise on enemy
public object *
spell_target_one_other_present_living_or_enemy(object caster, string str)
{
    return (str ? spell_target_one_other_present_living(caster, str) :
        spell_target_one_present_enemy(caster, str));
}
