/* Faugoroth - the Choking Horror.
 * Notes by Chmee:
 * After the time I notice that this spell creates most balance problems.
 * This is mainly because of  add_attack_delay() call. So if you plan to
 * code a mage proof dragon (or whatever) here you have what this spell do.
 * The spell is a death enchantment.
 * It calls add_panic(), add_fatique() and non cumulative add_attack_delay()
 * in a victim.
 * Darkness doubles the spell power.
 * Keep in mind that mages reduce the resistance factors of their targets
 * in all spells using their spellcraft. When I write these words 100 spell-
 * craft reduces the target's resistance by 60%. Full mages can train their
 * spellcraft up to 90 what yields 54% resistance reduction.
 * For exact formulas look in the resolve_spell() function.
 * 29.06.2001 Chmee
 * I'm now very satisfied by the currentmost formula. It should take into
 * account all balance problems. It gives a victim a chance to retaliate,
 * preserves a risk of failure for a mage (the chance of imposing a combat
 * delay depends on a target's fatigue) while not losing its effeciency.
 * I tested the spell on an Ansalon blue dragon and achieved a reasonable
 * ratio of successes to failures.
 * 17.06.2003 Chmee
 * The ban on add_fatigue() destructed the balance of this spell. I find it
 * hard to fine tune it now.
 */
#include "spells.h"
#include <macros.h>
#include <composite.h>
#include "/d/Gondor/common/guild2/lib/morgul_defs.h"

inherit SPELL_INHERIT;

#define NAME(x)   (x->query_npc() ? file_name(x) : x->query_cap_name())

public int
query_spell_pretarget()
{
    return 0;
}

void
hook_targets_gone()
{
    write( "Unable to focus Faugoroth at anything you send it at void.\n" );
}

void
resolve_spell( object caster, object *targets, int *resist, int result )
{
 int power, impact, f_panic, f_fatique, f_stuffed, f_dealy = 0;
 string target_how, watcher_how, impact_adjverb;

    if (check_mage( caster ))
    {
        return;
    }
                                /*Apprentices - 38, mages - 60            */
    power = ( caster->query_skill( gElement_skill )+ caster->query_skill(
        gForm_skill ) + gElement_needed + gForm_needed )/ 4;

                                /*Randomize it a little (+ up to 20%)     */
    power += power* random( 21 )/ 100;

    if (!CAN_SEE_IN_ROOM( targets[0] ))
    {
        power *= 2;
    }

    resist[0] -= resist[0]* caster->query_skill( SS_SPELLCRAFT )*
        RESISTANCE_MODIFIER/ 10000;
    power -= power* resist[0]/ 100;

    if (power <= 0)
    {
        caster->catch_tell( "Your spell was resisted completely." );
        IDLENESS->increase_activity( caster, SMALL_SPELL );
        return;
    }
    caster->catch_tell( "With the power the Dark Lord has bestowed " +
        "upon you, you call the Choking Horror.\n" );
                                        /*Now, since the f_panic defines
                                          the range of applied spell
                                          effects and is a primary effect
                                          itself it needs to be reduced.  */
    f_panic = (3+ power/ 3 + caster->query_stat( SS_OCCUP )/ 18)*
        (10 + targets[0]->query_stat(SS_DIS)* 3)/ 100;
    targets[0]->add_panic( f_panic );
                                        /*App. - 40, mage - 66            */
/* O.k. we can't affect fatigue directly any more. 
    f_fatique = power;
    targets[0]->add_fatigue( -f_fatique );
*/
                                /*This remedy is not really well balanced
                                  and doesn't fit nicely to the issued
                                  messages but I still hope that the
                                  add_fatigie() bann is going to be removed
                                  and the old code can be restored.*/
    f_stuffed = min( power, 100 )* targets[0]->query_stuffed()/ 100;
    targets[0]->eat_food( -1* f_stuffed );
    targets[0]->command( "$puke" );
    
                                        /*App. - 32[s], mage - 99[s]      */
/*
    impact = (targets[0]->query_max_fatigue()- targets[0]->query_fatigue())*
        100/ targets[0]->query_max_fatigue();
*/
                                /*Impact for messages is now calculated
                                  accordingly to panic level.              */
    impact = 100* targets[0]->query_panic()/
        (10 + targets[0]->query_stat(SS_DIS) * 3);
    if ((!targets[0]->query_prop( LIVE_I_ATTACK_DELAY )) &&
        (random( 100 ) < impact ))
    {
        f_dealy   = power* caster->query_stat( SS_OCCUP )/100;
        targets[0]->add_attack_delay( f_dealy, 1 );
    }
    else                                /*Let us increase the delay insigni-
                                         *ficantly in the case of failure.*/
    {
        f_dealy = query_spell_time();
        targets[0]->add_attack_delay( f_dealy, 0 );
    }
    if (!(targets[0]->query_npc()))
    {
        log_spell( "faugoroth", "(Power: "+ power+ ")  (Panic added: "+
            f_panic + ")  (Food removed: "+ f_stuffed+ ")  (Attack Delay: "+
            f_dealy + ")  (Caster: "+ caster->query_cap_name()+
            ")  (Target: "+ targets[0]->query_cap_name()+ ")" );
    }
/*
    if (!(targets[0]->query_npc()))
    {
        log_spell( "faugoroth", "(Power: "+ power+ ")  (Panic added: "+
            f_panic + ")  (Food removed: "+ f_stuffed+
            ")  (Attack Delay: "+ f_dealy + ")  (Caster: "+
            caster->query_cap_name()+ ")  (Target: "+
            targets[0]->query_cap_name()+ ")" );
    }
*/
    IDLENESS->increase_activity( caster, COMBAT_SPELL );
    switch (impact)
    {
    case 1..20:
        target_how = "You tremble a little";
        watcher_how = " trembles a little";
        break;
    case 21..40:
        target_how = "You are quaking as if you are bitter cold";
        watcher_how = " is quaking as if "+ targets[0]->query_pronoun()+ 
            " were bitter cold";
        break;
    case 41..60:
        target_how = "You feel utter desperation and exhaustion "+
        "creeping over you";
        watcher_how = " looks desperate and exhausted";
        break;
    case 61..80:
        target_how = "You struggle with panic as a dark terror creeps "+
            "over you, making it impossible to flee";
        watcher_how = " struggles with panic as a dark shadow creeps over "+
        targets[0]->query_objective();
        break;
    default:
        target_how = "You slump to your knees, overcome with despair";
        watcher_how = " slumps to "+ targets[0]->query_possessive()+
            " knees, overcome with despair";
    }
    caster->tell_watcher( QCTNAME( caster )+ " stares threateningly at "+
            QTNAME( targets[0] )+ ".\n"+ QCTNAME( targets[0] )+
            watcher_how+ ".\n", targets[0], caster );

    caster->catch_tell( "You cast the Choking Horror against "+
        targets[0]->query_the_name( caster )+ ".\n" +
        capitalize( targets[0]->query_pronoun() )+ watcher_how+ ".\n" );

    targets[0]->catch_tell( caster->query_The_name(targets[0] )+ " stares "+
        "at you with eyes like burning coals.\n"+ target_how+ ".\n" );
    if (f_dealy > query_spell_time())
    {
        switch (f_dealy)
        {
        case 1..30:
            impact_adjverb = "slightly ";
            break;
        case 31..60:
            impact_adjverb = "somewhat ";
            break;
        case 61..90:
            impact_adjverb = "";
            break;
        case 91..120:
            impact_adjverb = "rather ";
            break;
        default :
            impact_adjverb = "very ";
        }
        tell_room( environment( caster), QCTNAME( targets[0] )+ 
            " looks "+ impact_adjverb+ "dizzy.\n", targets[0] );
        targets[0]->catch_tell( "You feel "+ impact_adjverb+ "dizzy.\n" );
    }
}

int
config_spell( object caster, object *targets, string args )
{
    set_spell_name( "faugoroth" );
    set_spell_desc( "Choking horror." );
    set_spell_target( my_spell_target_one_valid_enemy );
                                /*The spell is not being configured for   *
                                 *a casting attempt, and therefore should *
                                 *not return 1                            */
    if (!objectp( caster ))
    {
        return 0;
    }
    set_free_hands( 0 );

                                /*Special configuration for morgul npcs.  */
    if (caster->query_npc())
    {
        set_spell_stationary( 0 );
        set_spell_time( spell_resolve_time( caster->query_stat( SS_OCCUP ),
            4, 8 ));
        set_spell_mana( 70 );
        set_spell_task( TASK_SIMPLE );
        set_spell_form( SS_FORM_ENCHANTMENT, 34 );
        set_spell_element( SS_ELEMENT_DEATH, 38 );

        set_spell_ingredients( 0 );
        set_spell_offensive( 1 );
        set_spell_resist( spell_resist );
        set_spell_visual( 0 );
        set_spell_vocal( 0 );
        return 0;
    }

    if (!default_morgul_spell_setup( caster ))
    {
        return 1;
    }
    set_spell_mana( 70 );
    set_spell_time( max(spell_resolve_time( caster->query_stat( SS_OCCUP ),
        4, 8 ), COMBAT_SPELL_I_MIN_PREP_TIME));
    set_spell_form( SS_FORM_ENCHANTMENT, 34 );
    set_spell_element( SS_ELEMENT_DEATH, 38 );
    set_spell_task( TASK_ROUTINE/ 2 );
    set_spell_offensive( 1 );
    set_spell_visual( 0 );
    set_spell_vocal( 0 );
    if (caster->query_wiz_level())
    {
        set_spell_ingredients( 0 );
    }
    else
    {
        set_spell_ingredients( ({ "faugoroth_ingr1" }) );
    }
    return 0;
}
