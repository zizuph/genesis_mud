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
    if (random(100) <= resist[0])
    {
        caster->catch_tell( "Your spell has been resisted.\n" );
        return;
    }
    if (targets[0]->query_prop( LIVE_I_UNDEAD ))
    {
        caster->catch_tell( "Your target is undead so you won't find any "+
            "life force in it.\nYour spell fizzles.\n" );
        return;
    }
    if (member_array( "sauthacuith drain effect", 
        targets[0]->query_magic_effects()->query_spell_effect_desc()) != -1 )
    {
        caster->catch_tell( targets[0]->query_The_name( caster )+ 
            " is already under the effect of the sauthacuith spell.\n" );
        return;
    }
    if (caster->query_prop( "_live_i_sauthacuith_enhanced" ))
    {
        caster->catch_tell( "You have already been enhanced by the "+
            "another sauthacuith spell.\n");
        return;
    }
    caster->catch_tell( "Using the power the Dark Lord has bestowed "+
        "upon you, you draw upon the life-force of "+ targets[0]->
        query_the_name( caster )+ " and imbue it into your own.\n" );
    targets[0]->catch_tell( "Employing Dark Sorcery, "+
        caster->query_the_name( targets[0] )+ " stares coldly at you. "+
        "Your body convulses in nerve-racking pains.\n" );
    can_see_caster( caster )->catch_msg( "Employing Dark Sorcery, "+
        QTNAME( caster )+ " stares coldly at "+ QTNAME( targets[0] )+
        ".\n"+ QCTNAME( targets[0] )+ " screams in agony as "+
        targets[0]->query_possessive()+ " body convulses in pain.\n" );
    setuid();
    seteuid(getuid());
    make_spell_effect_object( query_spell_object(), caster, targets,
        resist, result );
    IDLENESS->increase_activity( caster, RARE_SPELL );
}

public varargs int
config_spell( object caster, object *targets, string argument )
{
    set_spell_name( "sauthacuith" );
    set_spell_desc( "Drain the lifeforce of a living." );
    set_spell_target( spell_target_one_other_present_living );

                                /*The spell is not being configured for   *
                                 *a casting attempt, and therefore should *
                                 *not return 1                            */
    if (!objectp(caster))
    {
        return 0;
    }

    if (!default_morgul_spell_setup( caster ))
    {
        return 1;
    }
    set_spell_time( max(6, COMBAT_SPELL_I_MIN_PREP_TIME) );
    set_spell_mana( 65 );
    set_spell_task( TASK_ROUTINE );
    set_spell_element( SS_ELEMENT_DEATH, 40 );
    set_spell_form( SS_FORM_ENCHANTMENT, 40 );
    if (caster->query_wiz_level())
    {
        set_spell_ingredients( 0 );
    }
    else
    {
        set_spell_ingredients(({ "sauthacuith_ingr1",
            "sauthacuith_ingr2", }));
    }
    set_spell_resist( spell_resist );
    set_spell_object( SPELL_OBJ_DIR + "sauthacuith" );
    set_spell_offensive( 1 );
    set_spell_vocal( 0 );
    return 0;
}
