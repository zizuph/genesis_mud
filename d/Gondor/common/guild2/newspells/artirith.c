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
    resist[0] -= resist[0]* caster->query_skill( SS_SPELLCRAFT )*
        RESISTANCE_MODIFIER/ 10000;
    if (random(100) <= resist[0])
    {
        caster->catch_tell( "Your have resisted your spell.\n" );
        return;
    }
    if (caster->query_morgul_invis())
    {
        caster->catch_tell( "But you are already within the "+
            "realm of shadows.\n" );
        return;
    }
    can_see_caster( caster )->catch_msg( "Employing Dark Sorcery, " +
        QTNAME( caster )+ " calls upon the Power of Sauron.\n"+
        capitalize( caster->query_pronoun() )+ " throws "+
        caster->query_possessive()+ " black robe over "+
        caster->query_possessive()+ " head and mumbles a few words "+
        "and fades from your view.\n" );
    caster->catch_tell( "With the power the Dark Lord has bestowed upon "+
        "you, you call Artirith. You throw your robe over your head, and "+
        "mumble the dark words:\n\t'Noro nin minna fuine, ar tirith "+
        "ketymi!'\nThe lights get blurred. You feel a strange tranquility."+
        " The sounds seem to be muffled, yet you can hear any of them "+
        "very distinctly. Apparently you are in the realm of shadows.\n" );
    setuid();
    seteuid( getuid() );
    make_spell_effect_object( query_spell_object(), caster, targets,
        resist, result );
    IDLENESS->increase_activity( caster, COMBAT_SPELL );
}

public varargs int
config_spell(object caster, object *targets, string argument)
{
    set_spell_name( "artirith" );
    set_spell_desc( "Enter the realm of shadows." );
    set_spell_target( spell_target_caster );
                                /*The spell is not being configured for   *
                                 *a casting attempt, and therefore should *
                                 *not return 1                            */
    if (!objectp( caster ))
    {
        return 0;
    }
    set_free_hands( 0 );
    if (!default_morgul_spell_setup( caster ))
    {
        return 1;
    }
    set_spell_time(spell_resolve_time( caster->query_stat(SS_OCCUP),9,12 ));
    set_spell_mana( 100 );
    set_spell_task( TASK_ROUTINE+ 100 );
    set_spell_element( SS_ELEMENT_AIR, 50 );
    set_spell_form( SS_FORM_TRANSMUTATION, 40 );
    set_spell_resist( spell_resist_beneficial );
    set_spell_visual( 0 );
    set_spell_object( SPELL_OBJ_DIR + "artirith" );
    if (caster->query_wiz_level())
    {
        set_spell_ingredients( 0 );
    }
    else
    {
        set_spell_ingredients( ({"artirith_ingr1", }) );
    }
    return 0;
}
