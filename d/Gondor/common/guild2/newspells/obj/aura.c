#pragma save_binary
#pragma strict_types

#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "/d/Gondor/defs.h"
#include "../spells.h"

inherit SPELL_OBJECT;
inherit "/std/armour.c";

private nomask int f_ringurth_duration( int var1, int var2 );
varargs public int dispel_ringurth( object dispeller );

void
create_armour()
{
    set_name( ({"aura", "aura of death", }) );
    add_name( "_morgul_aura" );
    add_name( "deathaura") ;
    set_adj( "death" );
    set_short( "aura of death" );
    set_long( "A magical aura of the forces of death that surround and "+
        "protect your body.\n" );
    add_prop( OBJ_I_VALUE,    0 );
    add_prop( OBJ_I_VOLUME,   0 );
    add_prop( OBJ_I_WEIGHT,   0 );
    add_prop( OBJ_I_INVIS,    4 );
    add_prop( OBJ_I_NO_DROP,  1 );
    add_prop( OBJ_I_RES_MAGIC,   100 );
    add_prop( OBJ_I_RES_DEATH,   100 );
    add_prop( OBJ_I_RES_LIFE,    100 );
    add_prop( OBJ_I_RES_COLD,     50 );
    add_prop( OBJ_I_RES_FIRE,     50 );
    add_prop( OBJ_I_IS_MAGIC_ARMOUR, 1 );
    add_prop( OBJ_S_WIZINFO, "@@wizinfo@@" );
    add_prop( MAGIC_AM_MAGIC, ({ 100, "conjuration" }) );
    add_prop( MAGIC_AM_ID_INFO, ({
        "The aura will protect your entire body against brute, physical "+
        "attacks.\n", 0}) );

    set_default_armour( 20+ random(11), A_MAGIC );

    set_likely_cond( 0 );
    set_likely_break( 0 );
}

string
wizinfo()
{
    return "The spellobject for the 'ringurth' spell of the Morgul Mages.\n"
    + "A magical armour of armour class "+query_ac()+ ".\n"
    + "Magic form: conjuration, strength: " + 100 + ".\n";
}

varargs public int
dispel_spell_effect( object dispeller )
{
    dispel_ringurth( dispeller );
}

varargs public int
dispel_ringurth( object dispeller )
{
    spell_target->remove_subloc( query_spell_effect_desc() );
    spell_target->remove_arm( this_object() );
    spell_target->remove_magic_effect( this_object() );
    spell_target->catch_tell( "The chill of death departs silently, "+
        "leaving you feeling less protected.\n" );
    tell_room( environment( spell_target ), "Warmth creeps back into your "+
        "bones as the chill of death surrounding "+ QTNAME( spell_target )+
        " departs.\n", spell_target );
    remove_spell_effect_object();
    return 1;
}

public int
setup_spell_effect()
{
 int ringurth_duration;

    set_spell_effect_desc( "morgul death aura" );

    if (!::setup_spell_effect())
    {
        return 0;
    }
    ringurth_duration = f_ringurth_duration( spell_power,
        spell_caster->query_stat( SS_OCCUP ));

    spell_target->catch_tell( "A cloud appears and envelopes you in "+
        "response.\n" );
    tell_room( environment( spell_target ), "You shiver as the chill of "+
        "death surrounds "+ QTNAME( spell_target )+ " and pushes warmth "+
        "out of your bones.\n", spell_target );

    set_alarm( itof( ringurth_duration ), 0.0, dispel_ringurth );
    spell_target->add_subloc( query_spell_effect_desc(), this_object() );
    spell_target->wear_arm( this_object() );
    spell_target->add_magic_effect( this_object() );
}

public string
show_subloc(string subloc, object on, object for_obj)
{
    if (on->query_prop( TEMP_SUBLOC_SHOW_ONLY_THINGS ) ||
        subloc != query_spell_effect_desc())
    {
        return environment( this_object())->
            show_subloc( subloc, on, for_obj );
    }

    if (for_obj == on)
    {
        return "A cold, comforting shadow surrounds your body.\n";   
    }
    else
    {
        return "A cold, ever-shifting shadow surrounds "+ 
            on->query_possessive() + " body.\n";
    }
}

int *
query_shield_slots()
{
    return ({ A_HEAD, A_BODY, A_L_ARM, A_R_ARM, A_LEGS });
}

/*
 *  A magical aura cannot break, but where other armours break,
 *  this one will just disappear.
 */
varargs void
remove_broken(int silent = 0)
{
}

string query_recover() { return 0; }

/*
 * Function name : f_ringurth_duration
 * Description   : returns the duration of the ringurth spell in seconds.
 *               : It should be around 7+ (0-25) +- 5 minutes. An average
 *               : mage with guild exp == 100 with keep the aura for about
 *               : 25 minutes. Note there is no upper limit for the duration
 *               : of this spells. A mage with SS_OCCUP == 200 may keep
 *               : his aura as long as 50 minutes.  
 * Arguments:    : int var1 - should be spell_power
 *               : int var2 - spell_caster->query_stat( SS_OCCUP )
 */
private nomask int f_ringurth_duration( int var1, int var2)
{
    return 8* var1 + 10* var2 + random(300);
}
