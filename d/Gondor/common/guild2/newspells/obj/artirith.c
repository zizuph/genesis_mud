#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "../spells.h"

#define LOC_SENSE_BONUS 20
#define AWARENESS_BONUS 20
#define TRACKING_BONUS  20

#define SKILL_CAP 100

inherit SPELL_OBJECT;
inherit "/std/shadow";

int loc_sence_gain, awareness_gain, tracking_gain;

private nomask int f_artirith_duration( int var1, int var2 );


                                /*There is a support for this spell in the
                                 *~Gondor/common/guild2/mage_robe.c
                                 *A command 'etendae' dispelling artirith is
                                 *defined there.                          */
varargs public int
dispel_artirith( object dispeler )
{
    spell_target->add_prop( OBJ_I_INVIS,
        (int)spell_target->query_prop( OBJ_I_INVIS )- 5 );
    spell_target->add_prop( LIVE_I_SEE_INVIS,
        (int)spell_target->query_prop( LIVE_I_SEE_INVIS )- 5 );
    spell_caster->remove_prop( LIVE_M_MOUTH_BLOCKED );
    spell_caster->set_skill_extra( SS_LOC_SENSE,
        spell_caster->query_skill_extra( SS_LOC_SENSE )- loc_sence_gain );
    spell_caster->set_skill_extra( SS_AWARENESS,
        spell_caster->query_skill_extra( SS_AWARENESS )- awareness_gain );
    spell_caster->set_skill_extra( SS_TRACKING,
        spell_caster->query_skill_extra( SS_TRACKING )- tracking_gain );
    spell_target->catch_tell(
        "You return from the realm of shadows!\n" );
    tell_room( environment( spell_target ), "The dark cloud consolidates, "+
        "and "+ QNAME( spell_target )+ " steps out of it.\n", spell_target);
    remove_spell_effect_object();
    return 1;
}

int
query_morgul_invis()
{
    return 1;
}

void
dispel_morgul_invis()
{
    dispel_artirith();
}

public void
attack_object( object ob )
{
    spell_target->catch_msg( "You cannot fight while you are in "+
        "the realm of shadows, so you materialize again.\n" );
    dispel_artirith();
    shadow_who->attack_object( ob );
}

public void
attacked_by( object ob )
{
    spell_target->catch_tell( "You can not fight while you are in the "+
        "realm of shadows, so you materialize again.\n" );
    dispel_artirith();
    shadow_who->attacked_by( ob );
}

/* Routine added to secure from cheating Mages. 
   I might add a reduction in rank in this routine as well...
   
       Toby, 2008-04-21
 */
void
spell_ending_if_combat()
{
    if(spell_caster->query_attack())
    {
        spell_target->catch_tell( "The Dark Lord sence you are in combat, "+
        "which can not be while you are in the realm of shadows, so he "+
        "forces you to materialize again.\n" );
        dispel_artirith();
    }
    else
    {
        set_alarm(5.0, 0.0, spell_ending_if_combat );
    }
}

void
spell_ending()
{
    spell_target->catch_tell( "You feel that you will soon return from "+
        "the realm of shadows.\n" );
    set_alarm( 20.0, 0.0, dispel_artirith );
}

public int
setup_spell_effect()
{
 int v_artirith_duration, temp;

    set_spell_effect_desc( "artirith" );
    if (!::setup_spell_effect())
    {
        return 0;
    }
    if (!shadow_me( spell_target ))
    {
        return 0;
    }
    loc_sence_gain = LOC_SENSE_BONUS* spell_caster->query_skill(
        SS_SPELLCRAFT )/ 100 + random( 6 );
    awareness_gain = AWARENESS_BONUS* spell_caster->query_skill(
        SS_SPELLCRAFT )/ 100 + random( 6 );
    tracking_gain = TRACKING_BONUS* spell_caster->query_skill(
        SS_SPELLCRAFT )/ 100 + random( 6 );
    v_artirith_duration = f_artirith_duration( spell_power,
        spell_caster->query_stat( SS_OCCUP ));
    spell_target->add_prop( OBJ_I_INVIS,
        (int)spell_target->query_prop( OBJ_I_INVIS)+ 5 );
    spell_target->add_prop( LIVE_I_SEE_INVIS,
       (int)spell_target->query_prop( LIVE_I_SEE_INVIS )+ 5 );
    spell_caster->add_prop( LIVE_M_MOUTH_BLOCKED,
        "Your words sink in the thick air.\n" );

    temp = spell_caster->query_skill( SS_LOC_SENSE );
    if ((temp+ loc_sence_gain ) > SKILL_CAP)
    {
        loc_sence_gain = SKILL_CAP- temp;
    }
    temp = spell_caster->query_skill( SS_AWARENESS );
    if ((temp+ awareness_gain ) > SKILL_CAP)
    {
        awareness_gain = SKILL_CAP- temp;
    }
    temp = spell_caster->query_skill( SS_TRACKING );
    if ((temp+ tracking_gain ) > SKILL_CAP)
    {
        tracking_gain = SKILL_CAP- temp;
    }
    spell_caster->set_skill_extra( SS_LOC_SENSE,
        spell_caster->query_skill_extra( SS_LOC_SENSE )+ loc_sence_gain );
    spell_caster->set_skill_extra( SS_AWARENESS,
        spell_caster->query_skill_extra( SS_AWARENESS )+ awareness_gain );
    spell_caster->set_skill_extra( SS_TRACKING,
        spell_caster->query_skill_extra( SS_TRACKING )+ tracking_gain );

    set_alarm(itof( v_artirith_duration ), 0.0, spell_ending );

    /* Adding a check to see if the Mage is in combat at any time, Toby 2008-04-21 */
    set_alarm(10.0, 0.0, spell_ending_if_combat );

/*
    SPELL_INHERIT->log_spell( "artirith", "Caster: "+ spell_caster->
        query_cap_name()+ ", duration: "+ v_artirith_duration+ "[s], "+
        "location sence gain: "+ loc_sence_gain +", awareness gain: "+
        awareness_gain +", tracking gain: "+ tracking_gain );
*/
}

                                /*This is about 50 minutes.               */
private nomask int f_artirith_duration( int var1, int var2 )
{
    return 25* var1 + 10* var2 + random( 300 );
}

                                /*Set to remain compatible with non MM
                                  spells such as a dispel magic spell.    */
varargs public int dispel_spell_effect( object dispeler )
{
    dispel_artirith( dispeler );
}
