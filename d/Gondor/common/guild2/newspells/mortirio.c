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
    string cast_descr;

    if (check_mage( caster ))
    {
        return;
    }
    if (targets[0]->query_mortirio_effect())
    {
        caster->catch_tell( "Your intended target is already "+
            "under the effects of mortirio.\n" );
        return;
    }
    if (caster->query_mortirio_effect() && targets[0] == caster) //Check this
    {
        caster->catch_tell( "You are already under the effects of mortirio.\n" );
        return;
    }
    if (random(100) <= resist[0])
    {
        caster->catch_tell( "Your spell was resisted.\n" );
        return;
    }

    cast_descr = one_of_list( ({
                 "With the power the Dark Lord has bestowed upon you, ",
                 "Letting the power of the Dark Lord flow through you, ",
                 "With the power the Black master has bestowed upon you, ",
                 "The power of Black master flows with ease through your undead body as ",
                 "The Dark Lord's power flows through your undead body as ",
                                       }) );

    if (targets[0] == caster)
    {
        caster->catch_tell( "You start chewing the black potato.\n"+
            cast_descr + "you cast "+
            "Mortirio, chanting silently in a rasping voice: " +
            "Anno nin tur morth, Belegir Morui!\n" );
        can_see_caster( caster )->catch_msg( QCTNAME(caster)+ 
            " starts chewing something and mumbles strange words.\n"+
              "Suddenly, "+ caster->query_possessive()+ " eyes begin "+
              "to glow like red coals.\n" );
    }
    else
    {
        targets[0]->catch_tell( caster->query_The_name(targets[0] )+
            " starts chewing something and silently rasps strange words.\n"+
            "Then "+ caster->query_pronoun()+ " glares at you with "+
            "piercing eyes.\nSuddenly, your eyes start to tingle "+
            "strangely.\n");
        caster->catch_tell( "You start chewing the black potato.\n"+
            cast_descr + "you cast Mortirio "+
            "on "+ targets[0]->query_the_name(caster)+ ",\nchanting "+
            "silently in a rasping voice: Anno tur morth, Belegir Morui!\n" +
        capitalize( targets[0]->query_possessive() )+ " eyes begin to "+
            "glow like red coals.\n" );
        (can_see_caster(caster) - targets)->catch_msg( QCTNAME( caster )+
            " starts chewing something and mumbles strange words.\nThen "+
            caster->query_pronoun() + " glares at " + QTNAME( targets[0] )+
            " with piercing eyes.\n" );
        tell_room( environment(caster), "Suddenly, the eyes of "+
            QTNAME( targets[0])+ " begin to glow like red coals.\n",
            ({ caster, targets[0] }) );
    }
    setuid();
    seteuid( getuid() );
    make_spell_effect_object( query_spell_object(), caster, targets,
        resist, result );
    IDLENESS->increase_activity( caster, SMALL_SPELL );
}

public varargs int
config_spell( object caster, object *targets, string argument )
{
    set_spell_name( "mortirio" );
    set_spell_desc( "Grant someone vision in darkness." );
    set_spell_target( spell_target_one_present_living );

    if (!default_morgul_spell_setup( caster ))
    {
        return 1;
    }
    set_spell_time(spell_resolve_time( caster->query_stat(SS_OCCUP),6,12 ));
    set_spell_mana( 30 );
    set_spell_task( TASK_SIMPLE );
    set_spell_element( SS_ELEMENT_AIR, 25 );
    set_spell_form( SS_FORM_ENCHANTMENT, 25 );
    if (caster->query_wiz_level())
    {
        set_spell_ingredients( 0 );
    }
    else
    {
        set_spell_ingredients( ({ "mortirio_ingr1" }) );
    }
    set_spell_resist( spell_resist_beneficial );
    set_spell_peaceful( 1 );
    set_spell_visual( 0 );
    set_spell_object( SPELL_OBJ_DIR + "mortirio" );
    return 0;
}
