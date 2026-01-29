#include <macros.h>
#include <tasks.h>
#include <ss_types.h>
#include "spells.h"
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
    write( "You disperse the powers drawn from the reamls of the "+
        "shadows.\n" );
}

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
        caster->catch_tell(targets[0]->query_The_name( caster )+ 
            " resists your spell.\n");
        return;
    }

    targets[0]->catch_tell( caster->query_The_name( targets[0] )+
        " mumbles strange words and looks you deep into the eyes.\n" +
        "Suddenly you feel confused. You seem to have forgotten "+
        "something.\n" );

    tell_room( environment( caster ), QCTNAME( caster )+
        " mumbles strange words and looks deep into the eyes of "+
        QTNAME( targets[0] )+ ".\n"+ QCTNAME( targets[0] )+ " suddenly "+
        "looks confused and has a vacuous look.\n",
        ({ caster, targets[0] }) );

    caster->catch_tell( "With the power the Dark Lord has bestowed upon "+
        "you, you cast Nifarist on "+ targets[0]->query_the_name(caster) +
        ", praying silently: Danarist kothni nifni, Belegir Morui!\n"+
        capitalize( targets[0]->query_pronoun() ) +
        " suddenly looks confused and has a vacuous look.\n" );

    setuid();
    seteuid( getuid() );
    targets[0]->remove_remembered( caster->query_real_name() );
    IDLENESS->increase_activity( caster, RARE_SPELL );
}

public varargs int
config_spell(object caster, object *targets, string argument)
{   
    set_spell_name( "nifarist" );
    set_spell_desc( "Make someone forget who you are." );
    set_spell_target( spell_target_one_other_present_living );
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

    set_spell_time(spell_resolve_time( caster->query_stat(SS_OCCUP),6,18 ));
    set_spell_mana( 60 );
    set_spell_task( TASK_ROUTINE/2 );
    set_spell_element( SS_ELEMENT_AIR, 20 );
    set_spell_form( SS_FORM_ENCHANTMENT, 34 );
    if (caster->query_wiz_level())
    {
        set_spell_ingredients(0);
    }
    else
    {
        set_spell_ingredients(({"nifarist_ingr1",}));
    }
    set_spell_resist_task( TASK_DIFFICULT );
    set_spell_resist( spell_resist );
    set_spell_peaceful(1);
    set_spell_visual( 0 );
    set_spell_vocal( 0 );
    return 0;
}
