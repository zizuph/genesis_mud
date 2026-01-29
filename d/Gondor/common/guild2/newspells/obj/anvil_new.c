/*
 * /d/Gondor/common/guild2/newspells/obj/anvil.c
 * This is the spell object of the morgul gostangwedh spell.
 *
 * Chmee, 16.07.2001
 */
#include "../spells.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <filter_funs.h>

inherit "/std/object";
inherit SPELL_OBJECT;

#include <macros.h>
#include <ss_types.h>

#define HE(x)   (x)->query_pronoun()
#define HIS(x)  (x)->query_possessive()
#define HIM(x)  (x)->query_objective()
#define NAME(x) (x->query_npc() ? file_name(x) : x->query_cap_name())

int _already_dispelled = 0;     /*A flag serving to avoid recurences in
                                 *leave_env() after remove_object() is
                                 *called from dispell_spell_effect()      */
int _Weight, _Volume, _Quickness_change, _Anvil_alarm, _Anvil_id;
float _Time_left;
string _Victim, _Mage;

public int inflate_anvil( int weight, int volume );
public void change_anvil( void );
string wizinfo( void );
void do_die(object killer)

void create_object()
{
    set_name( ({ "anvil", "curse"}) );
    set_adj( "morgul" );
    set_short( "morgul curse" );
    set_pshort( "morgul anvils" );
    set_long( "A dread morgul curse that chains its victim. It slows the "+
        "target's breath and movement.\n" );
    add_prop( OBJ_I_NO_STEAL, 1 );
    add_prop( OBJ_I_NO_GIVE, 1 );
    add_prop( OBJ_I_NO_DROP,  1 );
    set_no_show();

    add_prop( OBJ_S_WIZINFO, wizinfo );
}

/*
 * This function is rather empty since most important things happen in
 * externally called inflate_anvil() and enter_env().
 */
public int setup_spell_effect()
{
    set_spell_effect_desc( "gostangwedh curse" );
    if (!::setup_spell_effect())
    {
        return 0;
    }
    return 1;
}

/*
 * Function     : inflate_anvil
 * Description  : This function is called from the spell because it needs
 *                the weight and volume of the used ingredient as arguments.
 *                It calculates all the important parameters like the power
 *                and the duration time.
 * Arguments    : int weight, volume   - the weight and volume of
 *                the curse object calculated from gosta_ingr2
 * Return values: Success 1 or failure 0.
 */
public int inflate_anvil( int weight, int volume )
{
    _Anvil_id = 0;
    _Weight = weight;
    _Volume = volume;
    _Quickness_change = spell_power+ spell_caster->query_stat( SS_OCCUP )*
        2* _Weight/ 120000;
    if (spell_caster->query_wiz_level())
    {
        _Time_left = 60.0;
    }
    else
    {
        _Time_left = itof( 28* spell_power+ 30* (spell_caster->query_stat(
            SS_OCCUP )- 80)+ random( 300 ) );
    }
    _Victim = spell_target->query_name();
    _Mage = spell_caster->query_name();
    change_anvil();
    return move( spell_target, 1 );
}

public void change_anvil( void )
{
 int _old, _new;

    add_prop( OBJ_I_WEIGHT, _Weight );
    add_prop( OBJ_I_VOLUME, _Volume );
    _old = spell_target->query_prop( LIVE_I_QUICKNESS );
    _new = _old - _Quickness_change;
    spell_target->add_prop( LIVE_I_QUICKNESS, _new );

    _Anvil_alarm = set_alarm( _Time_left, 0.0, dispel_spell_effect );
    if (!_Anvil_id)
    {
        _Anvil_id = _Anvil_alarm;
        SPELL_INHERIT->log_spell( "gostangwedh", _Mage+ " cursed "+ 
            _Victim+ " with the curse nr. "+ _Anvil_id+ " for "+
            ftoi( _Time_left/ 60.0+ 0.5 )+ "[min].  (Weight: "+
            (_Weight/1000)+ "[kg])  (Volume: "+ (_Volume/1000)+ "[l])  "+
            "(Quickness (old/change/new): ("+ _old+ "/"+ _Quickness_change+
            "/"+ _new+ ")" );
    }
    else                        /*This is an old curse.                   */
    {
        spell_target->catch_tell( "You are cursed!\n" );
        SPELL_INHERIT->log_spell( "gostangwedh", "The anvil nr. "+
            _Anvil_id+ " returned to "+ _Victim+ ". The remaining time: ("+
            ftoi( _Time_left/ 60.0+ 0.5 )+ "[min])." );
    }
    return;
}

varargs public int dispel_spell_effect( object dispeller )
{
    if (objectp( spell_target ))
    {
        spell_target->add_prop( LIVE_I_QUICKNESS, spell_target->query_prop(
            LIVE_I_QUICKNESS )+ _Quickness_change );
        spell_target->remove_magic_effect( this_object() );
        _already_dispelled = 1;

        if (sizeof( get_alarm( _Anvil_alarm ) ) == 0)
        {
            spell_target->catch_tell( "You feel a great relief as the "+
                "powers of Mordor release their grip.\n" );
            spell_target->command( "$sigh relieved" );
            SPELL_INHERIT->log_spell( "gostangwedh", _Victim+ " cursed "+
                "with the curse nr. "+ _Anvil_id+ " has been relieved." );
        }
        else
        {
            SPELL_INHERIT->log_spell( "gostangwedh", _Victim+ " has left "+
                "the realms or the curse nr. "+ _Anvil_id+
                " has been dispelled." );
            remove_alarm( _Anvil_alarm );
        }
    }
    else
    {                           /*An extremely strange occurance indeed.  */
        SPELL_INHERIT->log_spell( "gostangwedh", _Victim+ " cursed with "+
            "the curse nr. "+ _Anvil_id+ " couldn't be found." );        
    }
    remove_object();
    return 1;
}

string wizinfo()
{
 mixed *call;

    call = get_alarm( _Anvil_alarm );
    if (sizeof( call ) == 0)
    {
        return "This is a bugged spell object. Please do the following:\n"+
            "1. Try calling dispel_spell_effect in it.\n"+
            "2. If the above fails, Destruct -D it and\n"+
            "3. Ask the player to quit and log in back.\n";
    }
    _Time_left = call[2];
    return "The spell object for the 'gostangwedh' spell of Morgul Mages. "+
        "It curses "+ _Victim+ " by decreasing "+ HIS( spell_target )+
        " LIVE_I_QUICKNESS property by "+ _Quickness_change+ ". It also "+
        "burdens "+ HIM( spell_target )+ " by extra "+ (_Weight/ 1000)+
        "[kg] and occupies "+ (_Volume/1000)+ "[l] of space in "+
        HIS( spell_target )+ " inventory. The remaining time: "+
        ftoi( _Time_left/ 60.0+ 0.5 )+ "[min].\nIf for some reason you "+
        "need to dispell this spell, rather then destructing this object "+
        "try calling dispel_spell_effect in it.\n"; 
}

string query_auto_load()
{
 mixed *call;
    call = get_alarm( _Anvil_alarm );
    if (sizeof( call ) == 0)
    {
        return 0;
    }
    _Time_left = call[2];
    return MASTER+ ":"+ _Victim+ "&&"+ _Mage+ "&&"+ ftoa( _Time_left)+ " "+
        _Weight+ " "+ _Volume+ " "+ _Quickness_change+ " "+ _Anvil_id;
}

public void init_arg( string arg )
{
 string *temp;
    temp = explode( arg, "&&" );
    _Victim = temp[0];
    _Mage = temp[1];
    sscanf( temp[2], "%f%d%d%d%d", _Time_left, _Weight, _Volume,
        _Quickness_change, _Anvil_id );
    if (_Time_left <= 0.0)
    {
        dispel_spell_effect();
    }
    spell_target = find_living( lower_case( _Victim ) );
    change_anvil();
}

string query_recover()
{
    return 0;
}

public void leave_env( object from, object to )
{
    if (!_already_dispelled && _Anvil_alarm && (to != spell_target))
    {
        _already_dispelled = 1;
        dispel_spell_effect();
    }
    ::leave_env( from, to );
}

void do_die(object killer)
{

    object room = environment(this_object());

    if (query_hp() < 1)
    {
            spell_target->catch_tell( "You feel a great relief as the "+
                "powers of Mordor release their grip.\n" );
            spell_target->command( "$sigh relieved" );
            SPELL_INHERIT->log_spell( "gostangwedh", _Victim+ " cursed "+
                "with the curse nr. "+ _Anvil_id+ " has been relieved." );
        remove_object();
    }
    return ::do_die(killer);


}