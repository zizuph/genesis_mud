#pragma save_binary
#pragma strict_types

#include "spells.h"
#include <ss_types.h>
#include <tasks.h>
#include <macros.h>
#include "/d/Gondor/common/guild2/lib/morgul_defs.h"

inherit SPELL_INHERIT;

public int
query_spell_pretarget()
{
    return 0;
}

void
hook_targets_gone()
{
    write( "Unable to focus Morthul at anything you dissipate the poison "+
        "in the air.\n" );
}

void
resolve_spell( object caster, object *targets, int *resist, int result )
{
    if (check_mage( caster ))
    {
    return;
    }
    // Can't poison the undead.
    if (targets[0]->query_prop( LIVE_I_UNDEAD ))
    {
        caster->catch_tell( "Your spell has no effect on the undead.\n" );
        return;
    }
    resist[0] -= resist[0]* caster->query_skill( SS_SPELLCRAFT )*
        RESISTANCE_MODIFIER/ 10000;
    if (random( 100 ) <= resist[0])
    {
        caster->catch_tell( "Your attempt to poison "+
            targets[0]->query_the_name(caster) + " was resisted.\n" );
            return;
    }
    tell_room( environment( caster ), QCTNAME( caster )+
        " hisses coldly at "+ QTNAME( targets[0] )+ ".\n", 
        ({caster, targets[0]}) ); 
    caster->catch_tell("With a cold hiss, you poison "+
        targets[0]->query_the_name( caster )+ " with the Black Breath.\n" );
    targets[0]->catch_tell( caster->query_The_name( targets[0] ) + 
        " hisses coldly at you.\n" );
    setuid();
    seteuid(getuid());
    make_spell_effect_object( query_spell_object(), caster, targets,
        resist, result );
    IDLENESS->increase_activity( caster, RARE_SPELL );
}

public varargs int
config_spell( object caster, object *targets, string argument )
{
    set_spell_name( "morthul" );
    set_spell_desc( "Black Breath." );
    set_spell_target( my_spell_target_one_valid_enemy );
                                /*The spell is not being configured for   *
                                 *a casting attempt, and therefore should *
                                 *not return 1                            */
    if (!objectp( caster ))
    {
        return 0;
    }
    set_free_hands( 0 );

                                /*Special configuration for morgul npcs.  */
    if (caster->query_npc())
    {
        set_spell_stationary( 0 );
        set_spell_time( spell_resolve_time( caster->query_stat( SS_OCCUP ),
            4, 16 ));
        set_spell_mana( 100 );
        set_spell_task( TASK_SIMPLE );
        set_spell_element( SS_ELEMENT_DEATH, 60 );
        set_spell_form( SS_FORM_ENCHANTMENT, 50 );
        set_spell_object( SPELL_OBJ_DIR+ "black_breath" );
        set_spell_ingredients( 0 );
        set_spell_offensive( 1 );
        set_spell_resist( spell_resist );
        set_spell_visual( 0 );
        set_spell_vocal( 0 );
        return 0;
    }

    if (!default_morgul_spell_setup( caster ))
    {
        return 1;
    }
    set_spell_time( max(spell_resolve_time( caster->query_stat( SS_OCCUP ),
        4, 8 ), COMBAT_SPELL_I_MIN_PREP_TIME) );
    set_spell_mana( 100 );
    set_spell_task( TASK_ROUTINE );
    set_spell_element( SS_ELEMENT_DEATH, 60 );
    set_spell_form( SS_FORM_ENCHANTMENT, 50 );
    if (caster->query_wiz_level())
    {
        set_spell_ingredients( 0 );
    }
    else
    {
        set_spell_ingredients( ({ "morgurth" }) );
    }
    set_spell_resist( spell_resist );
    set_spell_offensive( 1 );
    set_spell_visual( 0 );
    set_spell_vocal( 0 );
    set_spell_object( SPELL_OBJ_DIR+ "black_breath" );
    return 0;
}
