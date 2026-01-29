/* 
 * Modifications: restore_components(gReq_ingrs_found) added 
 *              : to unmark the components for later use. (old bug)
 *              : Also in spell_inherit.
 *              : Toby, 11 Aug, 2008
 *
 */

#include "spells.h"
#include <macros.h>
#include <composite.h>
#include <filter_funs.h>
#include "/d/Gondor/common/guild2/lib/morgul_defs.h"

#define HE(x)   (x)->query_pronoun()
#define HIS(x)  (x)->query_possessive()
#define HIM(x)  (x)->query_objective()

#define VOLUME_MODIFIER 20

inherit SPELL_INHERIT;

public int
query_spell_pretarget()
{
    return 0;
}

void
hook_targets_gone()
{
    write( "Unable to focus Dramalgos at anything you send it at void.\n" );
}

int weight_modifier( int weight )
{
    return ftoi( 708.0* pow( itof( weight ), 0.5) );
}
                                /*Unused.                                 */
//int volume_modifier( int volume );

void
resolve_spell( object caster, object *targets, int *resist, int result )
{
 int i,j, _ingr_weight, _ingr_volume, _anvil_weight;
 object anvil, *spect_caster, *spect_target;

    if (check_mage( caster ))
    {
        return;
    }
    
    /*if(sizeof(targets) || !objectp(targets[0]))
    {
        caster->catch_tell( "Your quarry has escaped your presence and " + 
            "you can not cast the Chains of Terror.\n" );
        restore_components(gReq_ingrs_found);
        return;
    }*/

    if(parse_command( "morgul curse", all_inventory( targets[0] ), "%o", anvil ))
    {
        caster->catch_tell( targets[0]->query_The_name( caster )+ 
            " is already cursed with the Chains of Terror.\n" );
        restore_components(gReq_ingrs_found);
        return;
    }
    
    resist[0] -= resist[0]* caster->query_skill( SS_SPELLCRAFT )*
        RESISTANCE_MODIFIER/ 10000;

    if (random(100) < resist[0])
    {
        caster->catch_tell( targets[0]->query_The_name( caster )+
            " resists your spell.\n");
        IDLENESS->increase_activity( caster, SMALL_SPELL );
        restore_components(gReq_ingrs_found);
        return;
    }
    
                          /*These are all who can't see the caster
                                 *excluding the caster and the target.    */
    spect_caster = FILTER_LIVE( all_inventory( environment( caster ) )-
        ({ caster, targets[0] }) );
    spect_caster = spect_caster - FILTER_IS_SEEN( caster, spect_caster );
                                /*These are all who can't see the target
                                 *excluding the caster and the target.    */
    spect_target = FILTER_LIVE( all_inventory( environment( targets[0] ) )-
        ({ caster, targets[0] }) );
    spect_target = spect_target - FILTER_IS_SEEN( targets[0], spect_target );


    caster->catch_tell( "With the power the Dark Lord has bestowed upon "+
        "you, you cast the Chains of Terror onto "+ targets[0]->
        query_the_name( caster )+ ".\nRaising your arms, you chant at "+
        "your victim:\n\t'Anto nin tur, gwedi kotumo-lya na engwidh o "+
        "gost.'\n" );

    targets[0]->catch_tell( "Employing Dark Sorcery, "+ caster->
        query_the_name( targets[0] )+ " calls the Power of the Dark Lord "+
        "upon you!\nYou feel as if a heavy weight is put down upon your "+
        "limbs like chains of iron.\n" );

    tell_room( environment( caster ), "Employing Dark Sorcery, "+
        QTNAME( caster )+ " calls upon the Power of the Dark Lord upon "+
        QTNAME( targets[0] )+ ".\n"+ capitalize( HE( caster ) )+ " raises "+
        HIS( caster )+ " arms at "+ HIM( targets[0] )+ " and rasps a few "+
        "menacing words.\n", ({ targets[0], caster, spect_caster }) );
        
    spect_caster->catch_msg( "You hear "+ QTNAME( caster )+
        " rasping a few menacing words.\n" );
    anvil = make_spell_effect_object( query_spell_object(), caster, targets,
        resist, result );
    j = sizeof( gReq_ingrs_found );
    for (i=0;i<j;i++)
    {
        if (gReq_ingrs_found[i]->id( "gosta_ingr2" ))
        {
            break;
        }
    }

    if (caster->query_wiz_level())
    {
        _ingr_weight = 1000;
        _ingr_volume = 1000;
    }
    else
    {
        _ingr_weight = gReq_ingrs_found[i]->query_prop( OBJ_I_WEIGHT );
        _ingr_volume = gReq_ingrs_found[i]->query_prop( OBJ_I_VOLUME );
    }
    _anvil_weight = weight_modifier( _ingr_weight );
    anvil->inflate_anvil( _anvil_weight, VOLUME_MODIFIER* _ingr_volume );
    j = _anvil_weight* 100/ (targets[0]->query_prop( CONT_I_MAX_WEIGHT )-
        targets[0]->query_prop( OBJ_I_WEIGHT ));
    switch (j)
    {
    case 0..24:
        targets[0]->catch_tell(
            "You bend down under the will of Mordor.\n" );
        tell_room( environment( caster ), QCTNAME( targets[0] )+
            " bends down under the will of Mordor.\n",
            ({ targets[0], spect_target }) );
        break;
    case 25..49:
        targets[0]->catch_tell( "You moan slightly as the curse of Mordor "+
            "falls over your shoulders.\n" );
        tell_room( environment( caster ), QCTNAME( targets[0] )+ " moans "+
            "slightly as the curse of Mordor falls over "+ HIS( targets[0])+
            " shoulders.\n", ({ targets[0], spect_target }) );
        break;
    case 50..74:
        targets[0]->catch_tell( "You sweat profusely trying to budge "+
            "the unnatural weight of your body.\n" );
        tell_room( environment( caster ), QCTNAME( targets[0] )+ " starts "+
            "sweating profusely while struggling with some invisible "+
            "weight.\n", ({ targets[0], spect_target }) );
        break;
    case 75..99:
        targets[0]->catch_tell( "You feel your heart is going to jump "+
            "out of your chest when you try not to fall aground under this"+
            "sudden burden.\n" );
        tell_room( environment( caster ), QCTNAME( targets[0] )+ " suddenly"+
            " looks pale and heavily catching "+ HIS( targets[0] )+
            " breath tries not to fall down.\n",
            ({ targets[0], spect_target }) );
        break;
    default:
        targets[0]->catch_tell( "You heavily fall down on the ground.\n" );
        tell_room( environment( caster ), QCTNAME( targets[0] )+ " falls "+
            "down on the ground and doesn't look like "+ HE( targets[0] )+
            "'s going to get up any time soon.\n",
            ({ targets[0], spect_target }) );
    }
    IDLENESS->increase_activity( caster, RARE_SPELL );
}

int config_spell( object caster, object *targets, string args )
{
    set_spell_name( "gostangwedh" );
    set_spell_desc( "Chains of Terror." );
    set_spell_target( my_spell_target_one_valid_enemy );
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
    set_spell_mana( 70 );
    set_spell_time(max(spell_resolve_time( caster->query_stat(SS_OCCUP),2,6 ), COMBAT_SPELL_I_MIN_PREP_TIME) );
    set_spell_form( SS_FORM_TRANSMUTATION, 40 );
    set_spell_element( SS_ELEMENT_DEATH, 65 );
    set_spell_object( SPELL_OBJ_DIR + "anvil" );
    set_spell_offensive( 0 );
    set_spell_vocal( 1 );
    if (caster->query_wiz_level())
    {
        set_spell_ingredients( 0 );
    }
    else
    {
        set_spell_ingredients(({"gosta_ingr1", "gosta_ingr2"}));
    }
    return 0;
}
