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
    if (present( "_morgul_aura", targets[0] ))
    {
        caster->catch_tell( "But you are already protected by the "+
            "Chill of Death!\n" );
        return;
    }
    if (random(100) <= resist[0])
    {
        caster->catch_tell( "You have resisted your own spell!\n" );
        return;
    }

    caster->catch_tell( "With the power the Dark Lord has bestowed "+
        "upon you, you call the Chill of Death.\n" );
    can_see_caster( caster )->catch_msg( "Employing Dark Sorcery, "+ 
        QTNAME( caster )+ " calls upon the Chill of Death.\n" );

    setuid();
    seteuid(getuid());
    make_spell_effect_object( query_spell_object(), caster, targets,
        resist, result );
    IDLENESS->increase_activity( caster, COMBAT_SPELL );
}

public varargs int
config_spell( object caster, object *targets, string argument )
{
    set_spell_name( "ringurth" );
    set_spell_desc( "Conjure a protective shroud of death." );
    set_spell_target( spell_target_caster );

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
    set_spell_time(spell_resolve_time( caster->query_stat(SS_OCCUP),7,15 ));
    set_spell_mana( 50 );
    set_spell_task( TASK_SIMPLE );
    set_spell_element( SS_ELEMENT_DEATH, 37 );
    set_spell_form( SS_FORM_CONJURATION, 35 );
    if (caster->query_wiz_level())
    {
        set_spell_ingredients( 0 );
    }
    else
    {
        set_spell_ingredients(({ "ringurth_ingr1",
            "ringurth_ingr2" }));
    }
    set_spell_resist( spell_resist_beneficial );
    set_spell_object( SPELL_OBJ_DIR + "aura" );
    set_spell_peaceful(1);
    set_spell_visual( 0 );
    set_spell_vocal( 0 );
    return 0;
}
