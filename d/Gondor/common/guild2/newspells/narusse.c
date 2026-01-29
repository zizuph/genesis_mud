#pragma save_binary
#pragma strict_types

#include "spells.h"
#include <ss_types.h>
#include <tasks.h>
#include <macros.h>
#include "/d/Gondor/common/guild2/lib/morgul_defs.h"

inherit SPELL_RESIST;
inherit SPELL_INHERIT;

public object *spell_target_one_wielded_weapon( object caster, string str );

public object *
spell_target_one_wielded_weapon( object caster, string str )
{
    mixed *oblist;

    oblist = caster->query_weapon( -1 );

    if (!sizeof(oblist))
    {
        caster->catch_tell( "You don't have a weapon wielded.\n" );
        return ({});
    }
    if (sizeof(oblist) > 1)
    {
        caster->catch_tell( "You can't cast this spell with more "+
            "than one weapon wielded.\n" );
        return ({});
    }
    if (caster->query_prop( "_live_i_narusse_enhanced" ))
    {
        caster->catch_tell( one_of_list( ({ 
            "You are already under the effect of the narusse spell.\n",
            "Your undead body already surges with the powers of Narusse!\n",
            }) )  );
        return ({});
    }
/*
    if (!(oblist[0]->query_dt() & W_SLASH))
    {
        caster->catch_tell("You can only cast this on a bladed weapon.\n");
        return ({});
    }
*/
    return oblist;
}

                                /*We set spell_target_verify which prints
                                 *its own message.                        */
void
hook_targets_gone()
{
    return;
}

void
resolve_spell( object caster, object *targets, int *resist, int result )
{
 int soaked;

    if (check_mage( caster, 1 ))
    {
        return;
    }   
    if (targets[0]->query_flame_blade())
    {
        caster->catch_tell( "The fires of Orodruin have already been " +
            "summoned upon the " + targets[0]->short() + ".\n" );
        return;
    }
    if (random(100) <= resist[0])
    {
        caster->catch_tell( "Your weapon resists the spell.\n" );
        return;
    }

    caster->catch_tell( one_of_list( ({
        "Using the power the Dark Lord has bestowed upon you, you ",
        "Letting the power of the Dark Lord flow through your undead " +
        "body, you ",
        "Letting the Black Masters power flow through your undead " +
        "body, you ", }) ) +
        "summon the flames of Orodruin on the "+
        targets[0]->short()+ ", shouting:\n\tTulo lacho Orodruin! "+
        "Minno russenna!\n" );
    can_see_caster(caster)->catch_msg(QCTNAME(caster)+ " raises "+ 
        caster->query_possessive()+ " "+ targets[0]->short()+
        " high into the air.\n" );
    tell_room( environment(caster), QCTNAME(caster)+ " calls out in "+ 
        "a dark rasping voice:\n\tTulo lacho Orodruin! Minno russenna!\n", caster );

    if (caster->query_morgul_invis())
    {
        caster->catch_tell( "Narusse pulls you out from the realm of "+
            "shadows.\n" );
        caster->dispel_morgul_invis();
    }

    caster->catch_tell( "Casting the spell dehydrates you.\n" );
    soaked = caster->query_soaked();
    if (result > soaked)
    {
        caster->catch_tell( "Your parched body is hurt by the "+
            "flames summoned upon the "+ targets[0]->short()+ ".\n" );
        caster->set_soaked(0);
        caster->heal_hp(soaked - result);
        if (caster->query_hp() < 0)
        {
            caster->do_die( this_object() );
        }   
    }
    else
    {
        caster->set_soaked( soaked - result );
    }
    setuid();
    seteuid( getuid() );
    make_spell_effect_object( query_spell_object(), caster, targets,
        resist, result);
    IDLENESS->increase_activity( caster, COMBAT_SPELL );
}

public varargs int
config_spell( object caster, object *targets, string argument )
{
    set_spell_name( "narusse" );
    set_spell_desc( "Summon the fires of Orodruin upon a blade." );
    set_spell_target( spell_target_one_wielded_weapon );

                                /*The spell is not being configured for   *
                                 *a casting attempt, and therefore should *
                                 *not return 1                            */
    if (!objectp( caster ))
    {
        return 0;
    }

    set_spell_target_verify( spell_target_one_wielded_weapon );
    set_free_hands( 0 );
    if (!default_morgul_spell_setup( caster ))
    {
        return 1;
    }
    set_spell_time(spell_resolve_time( caster->query_stat(SS_OCCUP),8,16 ));
    set_spell_mana( 100 );
    set_spell_task( TASK_ROUTINE );
    set_spell_element( SS_ELEMENT_FIRE, 20 );
    set_spell_form( SS_FORM_ENCHANTMENT, 40 );
    if (caster->query_wiz_level())
    {
        set_spell_ingredients( 0 );
    }
    else
    {
        set_spell_ingredients( ({ "narusse_ingr1", "narusse_ingr2", }) );
    }
    set_spell_resist( weapon_spell_resist );
    set_spell_peaceful( 1 );
    set_spell_object( SPELL_OBJ_DIR + "narusse_sh" );
    set_spell_visual( 0 );
    return 0;
}
