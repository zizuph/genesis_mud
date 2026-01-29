#pragma strict_types

#include "../spells.h"
#include <macros.h>
#include <stdproperties.h>
#include <language.h>

inherit "/std/object";
inherit SPELL_OBJECT;
inherit SPELL_RESIST;

#define NAME(x) (x->query_npc() ? file_name(x) : x->query_cap_name())

private nomask int f_poison_duration( int var1, int var2 );
private nomask int f_poison_strength( int var1 );
private nomask int f_cloud_duration( int var1, int var2 );
private nomask string long_descr();

object poison = 0;
int v_poison_duration, v_poison_strength, v_cloud_duration, _Cloud_alarm;
private object *affected = ({});

string no_get()
{
    say( QCTNAME( this_player() )+ " tries to get a grip on the cloud "+
        "but all "+ this_player()->query_pronoun()+ " manages is to wave "+
        "silly around in the empty air.\n" );
    return "You try to get a grip on the cloud.\n"+
        "But all you manage is to wave around in the air stupidly.\n";
}

void
create_object()
{
    set_name( "cloud" );
    add_name( ({ "poison cloud", "poison","_Morgul_Sulambar_Cloud" }) );
    add_adj( ({ "poison", "yellow", "stinking" }) );
    set_short( "pale yellow cloud" );
    set_pshort( "pale yellow clouds" );
    set_long( long_descr );
    add_prop( OBJ_I_WEIGHT, 50 );
    add_prop( OBJ_I_VOLUME, 1000000 );
    add_prop( OBJ_M_NO_STEAL, 1 );
    add_prop( OBJ_M_NO_GET, no_get );
    return;
}

private nomask string long_descr()
{
 mixed *call;
 object observer = this_player();
 string output = "A pale yellow cloud is hanging in the air here. It "+
     "fills the area with an incredible stench reminding you of foul eggs "+
    "and carbide.\n";
                                /*The following conditions could be included
                                  in one 'if' command but I made it this way
                                  because of some test logging and later
                                  decided it is more readable this way.   */
    if ((observer->query_stat( SS_WIS )+
        10* observer->query_skill( SS_ALCHEMY )) > 150)
    {
        if (observer->resolve_task( TASK_FORMIDABLE,
            ({ SKILL_WEIGHT, 1000, SS_ALCHEMY,
            SKILL_WEIGHT, 100, TS_WIS  }) ) > 0)
        {
            call = get_alarm( _Cloud_alarm );
            if (call[2] < 30.0)
            {
                output += "It looks rather unstable now and is going to "+
                    "dissipate any moment.\n";
            }
            else if (call[2] < 90.0)
            {
                output += "It's going to dissipate pretty soon.\n";
            }
            else if (call[2] < 180.0)
            {
                output += "It looks still thick but you appraise it "+
                    "should start dissipating rather soon.\n";
            }
            else if (call[2] < 330.0)
            {
                output += "It looks rather stable and you are pretty "+
                    "sure it is going to last a while.\n";
            }
            else if (call[2] < 480.0)
            {
                output += "It looks very stable and you appraise it "+
                    "will remain intact for a couple of minutes.\n";
            }
            else
            {
                output += "The cloud looks very fresh and the magic that "+
                    "keeps it from dissipating is still strong.\n";
            }
        }
    }
    return output;
}

void
test_run_away( object victim )
{
 int r;

    if (!objectp( victim ) ||
        !present( victim, environment( this_object() ) ))
    {
        return;
    }

    r = victim->query_stat( SS_CON )* 100/ victim->query_base_stat( SS_CON );
    r = 2* (100 - r);

    if (random( 100 ) < r)
    {
        victim->run_away();
    }
}

void do_poison( object victim )
{
 int i, result;
 object *inv;

    if ((victim->query_prop( MORGUL_I_SULAMBAR_RES )) ||
        (victim->query_prop( LIVE_I_UNDEAD )) ||
        (victim->query_wiz_level()))
    {
        return;
    }
    victim->catch_msg( "When you take a breath, the stinking cloud makes "+
        "you feel dizzy.\n" );
    tell_room( environment( this_object() ), QCTNAME( victim )+
        " suddenly looks quite pale and sick.\n", victim );

    result = spell_resist_poison( spell_caster, victim, spell_element,
        TASK_DIFFICULT+ 150 );

    if (random( 100 ) <= result)
    {
        victim->catch_tell( "You manage not to breathe in any of "+
            "the toxic fumes.\n");
        return;
    }
                                /*Let us find the WoD poison in a victim. */
    poison = 0;
    inv = all_inventory( victim );
    i = sizeof( inv );
    while (i--)
    {
        if (inv[i]->id( "Morgul_Sulambar_Poison" ))
        {
            poison = inv[i];
            break;
        }
    }
                                /*If the poison wasn't found...           */
    if (!objectp( poison ))
    {
        poison = clone_object( SPELL_OBJ_DIR+ "sulambar_poison" );
        poison->set_time( v_poison_duration );
        poison->set_strength( v_poison_strength );
        poison->move( victim, 1 );
        poison->start_poison( spell_caster );
        poison->increase_dose( v_poison_duration + 10, v_poison_strength );
    }
    else
    {
        poison->increase_dose( v_poison_duration, v_poison_strength );
        test_run_away( victim );
    }

    if (!(victim->query_npc()))
    {
        if (member_array( victim, affected ) == -1)
        {
            SPELL_INHERIT->log_spell( "sulambar", victim->query_cap_name()+
                " inhaled WoD in "+ LANG_THESHORT( environment(
                this_object() ) )+ "." );
            affected += ({ victim });
        }
    }
}

void
do_try_poison()
{
 object *victims;

    victims = filter( all_inventory( environment( this_object() ) ),
        living);

    if (!sizeof( victims ))
    {
        return;
    }
    map( victims, do_poison );
}

varargs public int
dispel_spell_effect( object dispeller )
{
    remove_alarm( _Cloud_alarm );
    tell_room( environment( this_object() ), "The pale yellow cloud gets "+
        "thinner and thinner.\nIt seems to have completely disappeared "+
        "now, and you can breathe more freely again.\n" );
    remove_spell_effect_object();

    return 1;
}

public int
setup_spell_effect()
{
 float f;
    set_spell_effect_desc( "sulambar cloud" );

    if (!::setup_spell_effect())
    {
        return 0;
    }

    v_poison_duration = f_poison_duration( spell_power,
        spell_caster->query_stat( SS_OCCUP ) );
    v_poison_strength = f_poison_strength( spell_power );
    v_cloud_duration  = f_cloud_duration( spell_power,
        spell_caster->query_stat( SS_OCCUP ) );

    move( environment( spell_caster ), 1 );
    SPELL_INHERIT->log_spell( "sulambar", "Cloud created by "+
        NAME( spell_caster )+ " in "+ file_name( environment(
        this_object() ) )+ " lasting for "+ v_cloud_duration+ "[s]." );
    _Cloud_alarm = set_alarm( itof( v_cloud_duration ), 0.0,
        dispel_spell_effect );
    do_try_poison();
    f = itof( 15 + ((100 - spell_power) / 20) );
    set_alarm( f, f, do_try_poison );

}

                                /*67 for a maxed mage. It's not a terribly
                                 *important parameter.                    */
private nomask int f_poison_strength( int var1 )
{
    return var1;
}
                                /*About 18 minutes for 150occ mage.       */
private nomask int f_poison_duration( int var1, int var2 )
{
    return var1* 9 + var2* 3;
}
                                /*About 14 minutes for 150occ mage.       */
private nomask int f_cloud_duration( int var1, int var2 )
{
    return var1* 6 + var2* 3;
}

/*
 * Function     : change_duration_time
 * Description  : This function was created mostly to support dramalgos'es
 *                ability to disperse the cloud. Take it into account when
 *                you start modifying it for some other purposes.
 * Arguments    : float _time - the change. Negative if you want to decrese
 *                the duration. Positive otherwise.
 * Return values: 1 if anything was changed, 0 otherwise.
 */
public nomask int change_duration_time( float _time )
{
 mixed *call;
 float _time_left;
    call = get_alarm( _Cloud_alarm );
    _time_left = call[2]+ _time;
    if (_time_left < 1.0)
    {
        return 0;
    }
    remove_alarm( _Cloud_alarm );
    _Cloud_alarm = set_alarm( _time_left, 0.0, dispel_spell_effect );
    return 1;
}

void enter_env( object to, object from )
{
    if (calling_program( -3 ) !=
        "d/Gondor/common/guild2/newspells/sulambar.c")
    {
        SPELL_INHERIT->log_spell( "sulambar", "WoD planted by "+
            NAME( this_player() )+ " in "+ file_name( to ) );
    }
    ::enter_env( to, from );
}

public void leave_env( object from, object to )
{
    if (!objectp( to ))
    {
        remove_alarm( _Cloud_alarm );
    }
    ::leave_env( from, to );
}
