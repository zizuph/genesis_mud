#pragma save_binary
#pragma strict_types

#include "spells.h"
#include <ss_types.h>
#include <tasks.h>
#include <macros.h>
#include "/d/Gondor/common/guild2/lib/morgul_defs.h"

inherit SPELL_INHERIT;

void
resolve_spell( object caster, object *targets, int *resist, int result )
{
    if (check_mage( caster ))
    {
        return;
    }
    if (member_array( "windfence", 
        targets[0]->query_magic_effects()->query_spell_effect_desc()) != -1 )
    {
        if (targets[0] == caster)
        {
            caster->catch_tell( "You are already protected by the Wind "+
                "Fence!\n" );
            return;
        }
        else
        {
            caster->catch_tell( targets[0]->query_The_name( caster )+ 
                " is already protected by the Wind Fence!\n" );
            return;
        }
    }
    if (random( 100 ) <= resist[0])
    {
        caster->catch_tell( "Your spell has been resisted.\n" );
        return;
    } 

    if (targets[0] != caster)
    {
                                /*Effectively a double bonus.             */
        IDLENESS->increase_activity( caster, 2*COMBAT_SPELL );
    }
    else
    {
        IDLENESS->increase_activity( caster, COMBAT_SPELL );
    }
    setuid();
    seteuid(getuid());
    make_spell_effect_object( query_spell_object(), caster, targets,
        resist, result );
    
}

public varargs int
config_spell( object caster, object *targets, string argument )
{
    set_spell_name( "ephessul" );
    set_spell_desc( "Summon the protection of Windfence for someone." );
    set_spell_target( spell_target_one_present_living );
                                /*The spell is not being configured for   *
                                 *a casting attempt, and therefore should *
                                 *not return 1                            */
    if (!objectp( caster ))
    {
        return 0;
    }

    if (!default_morgul_spell_setup( caster ))
    {
        return 1;
    }
    set_spell_time(spell_resolve_time( caster->query_stat(SS_OCCUP),6,11 ));
    set_spell_mana( 50 );
    set_spell_task( TASK_SIMPLE );
    set_spell_element( SS_ELEMENT_AIR, 40 );
    set_spell_form( SS_FORM_ENCHANTMENT, 50 );
    if (caster->query_wiz_level())
    {
        set_spell_ingredients(0);
    }
    else
    {
        set_spell_ingredients( ({ "ephessul_ingr1" }) );
    }
    set_spell_resist( spell_resist_beneficial );
    set_spell_peaceful( 1 );
    set_spell_object( SPELL_OBJ_DIR+ "ephessul" );
    set_spell_visual( 0 );
    return 0;
}
