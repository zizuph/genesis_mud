#include "spells.h"
#include <composite.h>
#include <macros.h>
#include <formulas.h>
#include <ss_types.h>
#include <tasks.h>
#include <wa_types.h>
#include "/std/combat/combat.h"
#include "/d/Gondor/common/guild2/lib/morgul_defs.h"

#define NAME(x) (x->query_npc() ? file_name(x) : x->query_cap_name())


inherit SPELL_INHERIT;

static int bolt_pen;
static string bolt_desc;

public void set_bolt_pen( int pen );
public void set_bolt_desc( string desc );
void desc_bolt_damage( object caster, object target, mixed *result );
void desc_bolt_cast( object caster, object *targets );
int calculate_dramalgos_pen( object caster );
public mixed *do_bolt_damage( object caster, object target, int pen );
public void desc_bolt_miss( object caster, object target );
public int try_to_hit( object caster, object target );

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

/*
 * Function name: set_bolt_pen
 * Description:   Set the "pen" for the attack.  Damage is calculated
 *                from this value.
 * Arguments:     int pen - the pen value
 */
public void
set_bolt_pen( int pen )
{
    bolt_pen = pen;
}

/*
 * Function name: set_bolt_desc
 * Description:   Set the description or type of the bolt (ice, water,
 *                fire, etc.)
 * Arguments:     string desc - the bolt description
 */
public void
set_bolt_desc( string desc )
{
    bolt_desc = desc;
    set_spell_name( desc+ "bolt" );
    set_spell_desc( "Shoot a bolt of "+ desc+ " at a target." );
}

void
desc_bolt_damage( object caster, object target, mixed *result )
{
    string how, what, bolt;
    int phit = result[0];

    bolt = "a single bolt";
    what = "misses ";
    how = "";

    if (phit > 0)
    {
        what = "strikes ";
    }
    if (phit > 10)
    {
        how = " hard";
    }
    if (phit > 20)
    {
        bolt = "a sharp bolt";
    }
    if (phit > 30)
    {
        bolt = "three small bolts";
        what = "strike ";
        how = "";
    }
    if (phit > 40)
    {
        bolt = "three spear-shaped bolts";
    }
    if (phit > 50)
    {
        what = "slam against ";
    }
    if (phit > 60)
    {
        bolt = "three large spear-shaped bolts";
    }
    if (phit > 70)
    {
        how = ", driving you back";
    }
    if (phit > 80)
    {
        what = "smash ";
        how = " onto the ground";
    }
    if (phit > 90)
    {
        what = "squash ";
        how = " to pulp on the ground";
    }

    log_spell( "dramalgos", caster->query_name()+ " creates a "+
        bolt_pen +" pen bolt, which did "+ result[3]+ " damage to "+
        NAME( target ) );
    IDLENESS->increase_activity( caster, COMBAT_SPELL );

    caster->catch_tell( "With a quick gesture you release the Stormwind "+
        "against "+ target->query_the_name(caster)+ ".\n"+ capitalize(bolt)+
        " of wind "+ what+ target->query_objective()+ how + ".\n" );
    target->catch_tell( caster->query_The_name( target )+ " makes a low "+
        "whistling noise, then quickly gestures in your direction.\n"+
        capitalize( bolt )+ " of wind "+ what+ "you"+ how+ ".\n" );
    caster->tell_watcher( QCTNAME(caster)+ " makes a low whistling noise, "+
        "then quickly gestures in "+ QTPNAME( target )+ " direction.\n"+
        capitalize( bolt )+ " of wind "+ what+ target->query_objective()+
        how+ ".\n", target );
}

void
desc_bolt_cast( object caster, object *targets )
{
    caster->catch_tell( "With the power of the Dark Lord has bestowed "+
        "upon you, you call the Storm Wind.\n" );
}

int
calculate_dramalgos_pen( object caster )
{
    return F_PENMOD( 40+ random( 21 ),
        caster->query_skill( SS_ELEMENT_AIR )+
        caster->query_skill( SS_FORM_CONJURATION )/ 2+
        caster->query_stat( SS_OCCUP ) );
}

public mixed *
do_bolt_damage( object caster, object target, int pen )
{
 int ran, i, j, hit, *hloc_ids, ac;
 object cob;
 mixed *hloc;

    /* Pick a hitlocation and apply armour mod to pen */
    ran = random( 100 );
    cob = target->query_combat_object();
    hloc_ids = cob->query_hitloc_id();
    hit = -1;
    j = 0;
    
    for (i = 0; i < sizeof(hloc_ids); i++)
    {
        hloc = cob->query_hitloc(hloc_ids[i]);
    
        j += hloc[HIT_PHIT];
        if (j >= ran)
        {
            hit = hloc_ids[i];
            break;
        }
    }
    return target->hit_me( pen, W_BLUDGEON, caster, hloc_ids[i] );
}

/*
 * Function name: desc_bolt_miss
 * Description:   Write out some text describing the missed attack.  This can
 *                be redefined for custom messages.
 * Arguments:     object caster - the caster
 *                object target - the target
 */
public void
desc_bolt_miss(object caster, object target)
{
    string bolt = "The bolt of " + bolt_desc + " misses ";

    target->catch_tell(bolt + "you.\n");
    caster->catch_tell(bolt + target->query_the_name(caster) + ".\n");
    caster->tell_watcher_miss(bolt + QCTNAME(target) + ".\n", target);
}

public int
try_to_hit(object caster, object target)
{

    return (target->resolve_task( TASK_FORMIDABLE, ({TS_DEX, SS_DEFENSE}),
    caster, ({SKILL_AVG, TS_INT, TS_WIS, SKILL_END, SS_FORM_CONJURATION}))
      < 0);
}


/*
 * Function name: resolve_spell
 * Description:   Complete the casting of the spell
 * Arguments:     object caster   - the caster
 *                object *targets - an array of targets
 *                int *resist     - resistance percentages corresponding to
 *                                  each target
 *                int result      - how well the spell was cast
 */
public void
resolve_spell( object caster, object *targets, int *resist, int result )
{
 int wind_attack, magic_attack;
 mixed *hitresult, *magicresult;

    if (!objectp( targets[0] ))
    {
        caster->catch_tell( "There is something wrong with your target."+
            "Bugreport this event.\n" );
        return;
    }
    if (targets[0]->id( "_Morgul_Sulambar_Cloud" ))
    {
        caster->catch_tell( "You blow fiercely trying to disperse the "+
            "toxic vapours.\n" );
        tell_room( environment( caster ), QCTNAME( caster )+ "blows "+
            "fiercely at the "+ targets[0]->short()+ ".\n", caster );
        targets[0]->change_duration_time( -180.0- itof( random( 120 ) ) );
        return;
    }
    desc_bolt_cast( caster, targets );

    if (!try_to_hit( caster, targets[0]) )
    {
        desc_bolt_miss( caster, targets[0] );
        return;
    }

    wind_attack = bolt_pen/ 2;
    magic_attack = bolt_pen- wind_attack;

    hitresult = do_bolt_damage( caster, targets[0], wind_attack );
    resist[0] -= resist[0]* caster->query_skill( SS_SPELLCRAFT )*
            RESISTANCE_MODIFIER/ 10000;
    magic_attack -=  magic_attack* resist[0]/ 100;
    magicresult = targets[0]->hit_me( magic_attack, MAGIC_DT, caster,
        -1, hitresult[1] );
    hitresult[3] += magicresult[3];
    hitresult[0] = 100* hitresult[3]/
        (targets[0]->query_hp()+ hitresult[3]);
    hitresult[2] += magicresult[2];
    desc_bolt_damage( caster, targets[0], hitresult );
         
    if (targets[0]->query_hp() <= 0)
    {
        targets[0]->do_die( caster );
    }
}

int
config_spell( object caster, object *targets, string arg )
{
    set_bolt_desc(  "stormwind" );
    set_spell_name( "dramalgos" );
    set_spell_desc( "Stormwind." );
    set_spell_target( my_spell_target_one_valid_enemy );
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
    set_spell_time(spell_resolve_time( caster->query_stat(SS_OCCUP),2,4 ));
    set_spell_mana( 30 );
    set_spell_task( TASK_SIMPLE );
    // Old values 40, 70
    set_spell_element( SS_ELEMENT_AIR, 34 );
    set_spell_form( SS_FORM_CONJURATION, 40 );
    bolt_pen = calculate_dramalgos_pen( caster );
    if (caster->query_wiz_level())
    {
        set_spell_ingredients( 0 );
    }
    else
    {
        set_spell_ingredients( ({ "dramalgos_ingr1", "leftover" }) );
    }
    set_spell_offensive( 1 );
    set_spell_resist( spell_resist );
    set_spell_visual( 0 );
    set_spell_vocal( 0 );
}
