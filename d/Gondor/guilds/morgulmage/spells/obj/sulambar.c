#pragma strict_types
#pragma save_binary

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <tasks.h>

#include "/d/Genesis/specials/local.h"
inherit SPELL_OBJ_DIR + "spell_obj_base";
inherit "/d/Genesis/specials/resist";

#define _NO_PREP_TIME_ADJUSTMENT
#include "../generic_functions.c"

object *affected = ({ });
int cloud_installed = 0;
int poison_alarm = -1;

string no_get()
{
    say( QCTNAME( this_player() )+ " tries to get a grip on the cloud "+
        "but all "+ this_player()->query_pronoun()+ " manages is to wave "+
        "silly around in the empty air.\n" );
    return "You try to get a grip on the cloud.\n"+
        "But all you manage is to wave around in the air stupidly.\n";
}

public void 
create_spell_object()
{

    set_spell_effect_desc("Wind of Doom");
 
    add_prop(OBJ_I_WEIGHT, 50);
    add_prop(OBJ_I_VOLUME, 1000000);
    add_prop(OBJ_M_NO_STEAL, 1);
    add_prop(OBJ_M_NO_GET, no_get);
    
    unset_no_show();
    unset_no_show_composite();
}

/*
 * Function:    setup_spell_effect
 * Description: This is called to set up all the things for the
 *              spell. Must call the parent's setup_spell_effect
 *              in order to get the maintainence stuff.
 */
public int
setup_spell_effect()
{
    int result = ::setup_spell_effect();
    if (!result)
    {
        return result;
    }

    set_name("cloud");
    add_name(({ "poison cloud", "poison","_Morgul_Sulambar_Cloud" }));
    add_adj(({ "poison", "yellow", "stinking" }));
    set_short("pale yellow cloud");
    set_pshort("pale yellow clouds");

    set_long("A pale yellow cloud hangs over the area like a putrid fog. Its "
        + "fumes are akin to those of rancid pork - staggeringly horrible for "
        + "any living being to endure.\n");

    set_dispel_time(500 + random(150));

    return result;
}

void
test_run_away( object victim )
{
    if (!objectp( victim ) || !present(victim, environment(this_object())))
    {
        return;
    }

    int r = victim->query_stat( SS_CON )* 100/ victim->query_base_stat( SS_CON );
    r = 2* (100 - r);

    if (random( 100 ) < r)
    {
        victim->run_away();
    }
}

void do_poison(object victim)
{
    if ((victim->query_prop( MORGUL_I_SULAMBAR_RES )) ||
        (victim->query_prop( LIVE_I_UNDEAD )) ||
        (victim->query_wiz_level()))
    {
        return;
    }
    
    if (environment(victim) != environment(this_object())) 
    {
        return;
    }

    int result = spell_resist_poison(query_effect_caster(), victim, spell_element,
        TASK_DIFFICULT+ 150 );

    if (random( 100 ) <= result)
    {
        victim->catch_tell( "You manage not to breathe in any of "+
            "the toxic fumes.\n");
        return;
    }
    
    victim->catch_msg("When you take a breath, the stinking cloud makes "
        + "you feel dizzy.\n");
    tell_room(environment(this_object()), QCTNAME(victim) 
        + " suddenly looks quite pale and sick.\n", victim);
        

    object poison = present(MORGUL_ID_SULAMBAR_POISON, victim);

    int duration = MAX(100, MIN(150, query_spell_effect_power())) * 5;
    int strength = MIN(query_spell_effect_power(), 100);

    if (!objectp(poison))
    {
        send_debug_message("sulambar", "Added sulambar poison for "
            + victim->query_real_name());
        // send_debug_message("sulambar", sprintf("Spell power %d", 
        //    query_spell_effect_power()));

        poison = clone_object(MORGUL_SPELL_OBJ_DIR + "sulambar_poison");
        poison->set_time(duration);
        poison->set_strength(strength); 

       // send_debug_message("sulambar", sprintf("Created poison %O, "
       //     + "time remaining %d", poison, poison->query_time()));

        poison->move(victim, 1);
        poison->start_poison(query_effect_caster());
    }
    else
    {
        send_debug_message("sulambar", "Increased sulambar poison for "
            + victim->query_real_name());
        poison->increase_dose(duration, strength);
        test_run_away(victim);
    }
}

void init()
{
    ::init();
    set_alarm(0.1, 0.0, &do_poison(this_player()));
}

void poison_environment()
{
    object *victims = filter(all_inventory(environment(this_object())),
        living);

    map(victims, do_poison);
}

void enter_env(object to, object from)
{
    ::enter_env( to, from );
    if(objectp(to) && (to->query_prop(ROOM_I_IS))) 
    {
        if (poison_alarm == -1) {
            poison_alarm = set_alarm(15.0, 15.0, poison_environment);
        }
    }    
}

public void leave_env( object from, object to )
{
    ::leave_env( from, to );
    if (poison_alarm != -1)
    {
        remove_alarm(poison_alarm);
        poison_alarm = -1;
    }
}

/*
 * Function:    hook_spell_effect_started
 * Description: Override this to customize the message when this spell effect
 *              is added to th target.
 */
public void
hook_spell_effect_started()
{
    object target = query_effect_target();
    object caster = query_effect_caster();

    object *_who_can_see = can_see_caster(caster);

    caster->catch_msg("A few inches in front of your eyes, a dense dark "
        + "cloud appears.\nThe cloud forms almost a perfect sphere and "
        + "grows quickly. When the cloud is threatening to envelope "
        + "you, you make a quick gesture with both arms.\nQuickly "
        + "the cloud turns into a pale yellow colour and spreads into "
        + "the surrounding areas.\n");
        
    _who_can_see->catch_msg("A few inches in front of " 
        + caster->query_objective() + ", a dark dense cloud appears.\nThe "
        + "cloud forms an almost perfect sphere and grows quickly.\nWhen "
        + "the cloud is threatening to envelope " + caster->query_objective() 
        + ", " + QTNAME(caster) + " makes a quick gesture with both arms.\n"
        + "Quickly the cloud turns into a pale yellow colour and spreads "
        + "into the surrounding areas.\n");
        
    tell_room(target, "Unexpectedly, out of nowhere, a dark "
        + "dense cloud appears.\nThe cloud forms an almost perfect sphere "
        + "and grows quickly.\nSuddenly the cloud turns into a pale yellow "
        + "colour and spreads into the surrounding areas.\n", 
        _who_can_see + ({ caster }));
}

/*
 * Function:    hook_spell_effect_ended
 * Description: Override this to customize the message when this spell effect
 *              is dispelled.
 */
public void
hook_spell_effect_ended()
{
    object target = query_effect_target();

    tell_room(target, "The pale yellow cloud gets thinner and thinner.\n"
        + "It seems to have completely disappeared now, and you can breathe "
        + "more freely again.\n");
}

/*
 * Function:    hook_spell_effect_warn_fading
 * Description: Override this to customize the message for when
 *              the effect has only a minute left.
 */
public void
hook_spell_effect_warn_fading()
{
    object caster = query_effect_caster();
    
    if (objectp(caster))
    {
        caster->catch_tell("You sense the Wind of Doom is about to "
            + "disperse.\n");
    }
}

/* 
 * Function:    hook_spell_effect_not_maintained
 * Description: Override this to describe the effect when the caster
 *              cannot maintain the effect.
 */
public void
hook_spell_effect_not_maintained()
{
    object caster = query_effect_caster();
    
    if (objectp(caster))
    {
        caster->catch_tell("You are mentally unable to maintain "
            + "the Wind of Doom.\n");
    }    
}

