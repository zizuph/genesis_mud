/*
 * Modification log
 * Feb 12, 2006 Altrus
 * Changed the calculation for the 'strength' variable in
 * 'setup_spell_effect()'. Calculates for a higher maximun,
 * but if it reaches above 75, maximum will be set to 75.
 * (Previous maximum was 50, so this is a significant change)
 * To balance this change, the power of dark sight for a
 * third party target (not the caster) will be 15 levels
 * lower than that possible for the caster.
 *
 */
#pragma save_binary
#pragma strict_types

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "../spells.h"

#define NAME(x) (x->query_npc() ? file_name(x) : x->query_cap_name())

inherit SPELL_OBJECT;
inherit "/std/shadow.c";


static int     strength;

private nomask int f_mortirio_duration( int var1, int var2 );
varargs public int dispel_mortirio( object dispeler );

public int
setup_spell_effect()
{
 int mortirio_duration;
 int strength_org;

    set_spell_effect_desc( "darkvision" );

    if (!::setup_spell_effect())
    {
        return 0;
    }

    if (shadow_me( spell_target ) != 1)
    {
        spell_caster->catch_tell( "Mortirio failed, please leave "+
            "bug report about this.\n" );
        remove_spell_effect_object();
        return 0;
    }

    mortirio_duration = f_mortirio_duration( spell_power,
        spell_caster->query_stat( SS_OCCUP ));
                                /*Can be 50 at best.                      */
                          /* Added a random of 25 according to text above to try
                             and balance the spell as stated. A few lines later
                             the max is changed if it is a full mage that cast 
                             the spell. In according to the fact they now actually
                             can get higher levels on other targets I made it 
                             so that the time can get 1/3 shorter.
                             Toby, 2006-11-26
                           */
    if(spell_caster->query_morgul_level() > 12)
        strength = random( (spell_power + random(spell_caster->query_morgul_level()) + 2 ) )/ 5; 
    else
        strength = random( (spell_power + random(spell_caster->query_morgul_level()) ) )/ 5;

   // strength = random( spell_power )/ 5;

    if(strength > 125)
	    strength = 125;

    if (spell_target != spell_caster)
    {
        strength = strength - 15;
    }
    strength_org = strength;
    strength = max( 1, strength );
            /* Caster is full mage? */
    if(spell_caster->query_morgul_level() > 12)
    {
        if(spell_target != spell_caster)
        {
            strength = max( 2, strength );
            set_alarm( itof( mortirio_duration - random(mortirio_duration/3) ), 0.0, dispel_mortirio );
        }
        else
        {
            strength = max( 3, strength );
            set_alarm( itof( mortirio_duration ), 0.0, dispel_mortirio );
        }
    }
    else
    {
        strength = max( 1, strength );
        set_alarm( itof( mortirio_duration ), 0.0, dispel_mortirio );
    }
    
   // set_alarm( itof( mortirio_duration ), 0.0, dispel_mortirio );
    spell_target->add_prop( LIVE_I_SEE_DARK,
        (int)spell_target->query_prop( LIVE_I_SEE_DARK )+ strength );
    spell_target->add_prop( LIVE_I_SEE_INVIS,
        (int)spell_target->query_prop( LIVE_I_SEE_INVIS ) + 1 );
                                /*Mages have glowing eyes by default.     */
    if (!IS_MORGUL_MAGE( spell_target ))
    {
        spell_target->add_subloc(query_spell_effect_desc(), this_object());
    }
/* I have accumulated enough statistics and find the further logging
 * useless.  Toby activated logging again 2006-11-26 */
    SPELL_INHERIT->log_spell( "mortirio", "Caster: "+ spell_caster->
        query_cap_name()+ ", target: "+ NAME( spell_target )+
        ", duration: "+ (mortirio_duration+ 30)/ 60+ "[min], boost: "+
        strength + ", spell_power: " + spell_power + ", original strength: " + strength_org);
 
    return 1;
}

int
query_mortirio_effect()
{
    return 1;
}

varargs public int
dispel_mortirio( object dispeler )
{
    spell_target->add_prop( LIVE_I_SEE_DARK,
        (int)spell_target->query_prop( LIVE_I_SEE_DARK ) - strength );
    spell_target->add_prop(LIVE_I_SEE_INVIS,
        (int)spell_target->query_prop( LIVE_I_SEE_INVIS ) - 1 );
    spell_target->catch_tell( "You feel that your vision "+
        "becomes normal again.\n" );
    SPELL_INHERIT->can_see_caster(spell_target)->catch_msg(
        QCTPNAME(spell_target) + " eyes stop glowing like red coals.\n" );
    if (!IS_MORGUL_MAGE( spell_target ))
    {
        spell_target->remove_subloc( query_spell_effect_desc() );
    }
    remove_spell_effect_object();
    return 1;
}

                                /*Set to remain compatible with non MM
                                  spells such as a dispel magic spell.    */
varargs public int
dispel_spell_effect( object dispeler )
{
    dispel_mortirio( dispeler );
}

public string
show_subloc( string subloc, object on, object for_obj )
{
    if (subloc == "eyes" && for_obj != on)
    {
        return "";
    }
    if (on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS) ||
        subloc != query_spell_effect_desc())
    {
        return shadow_who->show_subloc( subloc, on, for_obj );
    }
    if (for_obj != on)
    {
        return capitalize(on->query_possessive())+ " eyes glow like "+
            "bright red hot coals.\n";
    }
}

/*
 * Function name : f_mortirio_duration
 * Description   : returns the duration of the mortirio spell in seconds.
 *               : It should be around 5+ (0-20) +- 5 minutes. An average
 *               : mage with guild exp == 100 with keep the spell for about
 *               : 25 minutes. Note there is no upper limit for the duration
 *               : of this spells. A mage with SS_OCCUP == 200 may keep
 *               : mortirio as long as 40 minutes.  
 * Arguments:    : int var1 - should be spell_power
 *               : int var2 - spell_caster->query_stat( SS_OCCUP )
 */
private nomask int f_mortirio_duration( int var1, int var2 )
{
    return 12* var1 + 8* var2 + random( 300 );
}
