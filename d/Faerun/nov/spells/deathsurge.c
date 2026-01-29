/*
 * The deathsurge spell for Nov.
 *
 * 23/4/2004 - Tilorop
 *
 */
 

#pragma strict_types

inherit "/d/Genesis/newmagic/spell";

#include <ss_types.h>
#include <tasks.h>
#include <composite.h>
#include <macros.h>
#include <wa_types.h>

static int harm_pen;

public void
set_harm_pen(int pen)
{
    harm_pen = pen;
}

public void
create_spell()
{
    set_spell_name("deathsurge");
    set_spell_desc(">Jolts the target with negative enery<");
    set_spell_time(2);
    set_spell_mana(50);
    set_spell_task(TASK_ROUTINE);
    set_spell_element(SS_ELEMENT_DEATH, 40);
    set_spell_form(SS_FORM_CONJURATION, 30);
    set_spell_ingredients(({ }));
    set_spell_resist(spell_resist);
    set_spell_target_verify(spell_verify_present);
    set_spell_stationary(0);
    set_spell_offensive(1);
    set_spell_vocal(0);

    set_spell_target(spell_target_one_other_present_living);

    
    set_harm_pen(300);

    
    ::create_spell();
}

public mixed *
do_harm_damage(object caster, object target, int pen)
{
    return target->hit_me(pen, MAGIC_DT, caster, -1);
}


public void
desc_harm_damage(object caster, object target, mixed *result)
{
    string how;

    switch (result[3])
    {
        case 0..20:
            how = "barely hurt";
            break;
        case 21..50:
            how = "slightly hurt";
            break;
        case 51..80:
            how = "somewhat hurt";
            break;
        case 81..110:
            how = "rather hurt";
            break;
        case 111..140:
            how = "hurt";
            break;
        case 141..170:
            how = "very hurt";
            break;
        default:
            how = "extremely hurt";
            break;
    }

    target->catch_tell("You feel " + how + ".\n");
    caster->catch_tell(target->query_The_name(caster) + " appears " +
        how + ".\n");
    caster->tell_watchers(QCTNAME(target) + " appears " + how + ".\n",
        target);
}


public void
desc_harm_cast(object caster, object *targets)
{
    string msg;

    caster->catch_tell("You channel a jolt of negative energy into " + 
        FO_COMPOSITE_ALL_LIVE(targets, caster) + ".\n");

    msg = " points " + caster->query_possessive() + 
        " index finger at you.\n";
    targets->catch_tell(({
        caster->query_Met_name() +  msg,
        capitalize(caster->query_nonmet_name()) + msg,
        "" }));
                           
    targets->catch_tell("You feel a jolt of cold negative energy " +
        "through your body.\n");

    caster->tell_watcher(QCTNAME(caster) + " points " + 
        caster->query_possessive() + " index finger at " +
        QCOMPLIVE + ".\n", targets);
}


public void
resolve_spell(object caster, object *targets, int *resist, int result)
{
    int i;
    mixed *hitresult;

    desc_harm_cast(caster, targets);

    for (i = 0; i < sizeof(targets); i++)
    {
        hitresult = do_harm_damage(caster, targets[i], 
            harm_pen * (100 - resist[i]) / 100);
        desc_harm_damage(caster, targets[i], hitresult);
         
        if (targets[i]->query_hp() <= 0)
        {
            targets[i]->do_die(caster);
        }
    }
}

