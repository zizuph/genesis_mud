
/* 

Description:

 This spell drains mana from a victim and gives a portion to the caster.


ChangeLog:
 Do not modify this file without updating this ChangeLog


 27 May 2006, Gorboth:
   Doubled amount of mana gained from target.



*/

#pragma save_binary
#pragma strict_types

#include "spells.h"
#include <ss_types.h>
#include <tasks.h>
#include <macros.h>
#include "/d/Gondor/common/guild2/lib/morgul_defs.h"

#define NAME(x) (x->query_npc() ? file_name(x) : x->query_cap_name())

inherit SPELL_INHERIT;

public int
query_spell_pretarget()
{
    return 0;
}

void
hook_targets_gone()
{
    write( "You disperse the power drawn from the realm of the shadows.\n");
}

void
resolve_spell( object caster, object *targets, int *resist, int result )
{
 int mana_drained, mana_gained, spell_power, temp, temp2;
 string success, temp3 = "undefined";

    if (check_mage( caster ))
    {
        return;
    }
    caster->catch_tell( "You start chewing the garlic bulb.\nWith the "+
        "power the Dark Lord has bestowed upon you, you call Emptyhead,\n"+
        "\tpraying silently: Anno ruth a losso dol, Belegir Morui!\nThen "+
        "you breath into the face of "+ targets[0]->query_the_name(caster)+
        ".\n" );
    targets[0]->catch_tell( caster->query_The_name( targets[0])+ 
        " start chewing something and mumbles strange words.\n" +
        "Suddenly, "+ caster->query_pronoun() + " breathes a "+
        "cloud of garlic stench into your face.\n" );
    tell_room( environment( caster), QCTNAME( caster )+ 
        " starts chewing something and mumbles strange words.\n"+
        "Suddenly, "+ caster->query_pronoun() + " breathes a cloud of "+ 
        "garlic stench into the face of "+ QTNAME( targets[0] )+
        ".\n", ({ caster , targets[0] }) );

    /* Maxed Apprentice - 36, mage - 59
     * Revision: I changed the formula to double this as a recompense
     *           for the change to herb consuption. Lets see if this
     *           ends up making sense. - Gorboth, May 2006
     */
    spell_power = ( caster->query_skill( gElement_skill )+
        caster->query_skill( gForm_skill )+ gElement_needed+
        gForm_needed )/ 4;

    mana_drained = targets[0]->query_mana()* (20+ random( spell_power ))/
        100;

//  mana_gained = mana_drained* (40+ random( 21 ))/ 100; /* old formula */
    mana_gained = mana_drained* (40+ random( 21 ))/ 50; /* new formula */
    resist[0] -= resist[0]* caster->query_skill( SS_SPELLCRAFT )*
        RESISTANCE_MODIFIER/ 10000;
    if (random(100) <= resist[0])
    {
        caster->catch_tell( "You feel sick.\n" );
        caster->command( "$puke" );
        can_see_caster( caster )->catch_msg( QCTNAME( caster ) + 
            " casts a spell.\n" );
        caster->catch_tell( targets[0]->query_The_name( caster ) + 
            " is too strong and resists the effects of the spell.\n" +
            "The power of Sauron turns against you, you feel "+
            "mentally drained.\n" );
/*    Logging removed since enough statistical data has been acumulated.
        if (caster->query_mana() < mana_gained)
        {
            mana_gained = caster->query_mana();
        }
                                //Division by 0 protection.
        if ((temp = caster->query_mana()) == 0)
        {
            temp = 0;
        }
        else
        {
            temp = mana_gained* 100/ temp;
        }
        log_spell( "dollost", "Spell backfired draining "+
            caster->query_name()+ " of "+ mana_gained+ " ("+ temp+
            "%) mana points." );
*/
        caster->add_mana( -mana_gained );
        IDLENESS->increase_activity( caster, SMALL_SPELL );
        return;
    }
    targets[0]->catch_tell( "You feel sick.\n" );
    targets[0]->command( "$puke" );
    targets[0]->add_mana( -mana_drained );

                                /*Some division by 0 protections.         */
    if ( (temp2 = targets[0]->query_max_mana()) == 0)
    {
        log_spell( "dollost", NAME( targets[0] )+ " has 0 max mana!!!" );
        temp2 = 1;
    }
                                /*If the caster if fully restored.        */
    if ((temp = caster->query_max_mana()- caster->query_mana()) <
        mana_gained)
    {
        success = "You feel mentally fully restored.\n";
        if (!(targets[0]->query_npc()))
        {
            if (mana_drained != 0)
            {
                temp3 = (temp*100/mana_drained)+ "%";
            }
            log_spell( "dollost", caster->query_cap_name()+ " drained "+
                mana_drained+ " ("+ mana_drained* 100/ temp2+
                "%) mana from "+ targets[0]->query_cap_name()+ " with "+
                temp3+ " effeciency and gained "+ temp+
                " mana points restoring "+ caster->query_objective()+
                "self completely." );
        }
    }
    else
    {
        switch ( mana_gained )
        {
        case 0..60:
            success = "You feel almost no effect.\n";
            break;
        case 61..100:
            success = "You feel mentally a little strengthened.\n";
            break;
        case 101..150:
            success = "You feel mentally somewhat strengthened.\n";
            break;
        case 151..200:
            success = "You feel mentally strengthened.\n";
            break;
        case 201..250:
            success = "You feel mentally stronger.\n";
            break;
        case 251..300:
            success = "You feel mentally much stronger.\n";
            break;
        case 301..400:
            success = "You feel a tide of mental power.\n";
            break;
        case 401..500:
            success = "You feel a great tide of mental power.\n";
            break;
        case 501..600:
            success = "You feel an immense tide of mental power.\n";
            break;
        default:
            success = "You feel almost drunk by an abundant flow of "+
                "mental power.\n";
            break;
        }
        if (!(targets[0]->query_npc()))
        {
            if (mana_drained != 0)
            {
                temp3 = (temp*100/mana_drained)+ "%";
            }
            log_spell( "dollost", caster->query_cap_name()+ " drained "+
                mana_drained+ " ("+ mana_drained* 100/ temp2+
                "%) mana from "+ targets[0]->query_cap_name()+ " with "+
                temp3+ " effeciency and gained "+ mana_gained+
                " mana points." );
        }
    }
    caster->add_mana( mana_gained );
    caster->catch_tell( "You cast the spell successfully.\n"+ success );
    can_see_caster( caster )->catch_msg( QCTNAME( caster ) + 
        " casts a spell successfully.\n" );
    IDLENESS->increase_activity( caster, COMBAT_SPELL );
}

public varargs int
config_spell( object caster, object *targets, string argument )
{
    set_spell_name( "dollost" );
    set_spell_desc( "Emptyhead." );
    set_spell_target( spell_target_one_other_present_living );

                                /*The spell is not being configured for   *
                                 *a casting attempt, and therefore should *
                                 *not return 1                            */
    if (!objectp( caster ))
    {
        return 0;
    }

    set_free_hands( 0 );
    if (!default_morgul_spell_setup( caster ))
    {
        return 1;
    }
    set_spell_time(COMBAT_SPELL_I_MIN_PREP_TIME);
    set_spell_mana( 60 );
    set_spell_task( TASK_SIMPLE );
    set_spell_form( SS_FORM_CONJURATION, 30 );
    set_spell_element( SS_ELEMENT_DEATH, 36 );
    set_spell_resist_task( TASK_DIFFICULT );
    if (caster->query_wiz_level())
    {
        set_spell_ingredients( 0 );
    }
    else
    {
        set_spell_ingredients( ({ "dollost_ingr", "dollost_ingr2" }) );
    }
    set_spell_resist( spell_resist );
    set_spell_offensive( 1 );
    set_spell_visual( 0 );
    return 0;
}
