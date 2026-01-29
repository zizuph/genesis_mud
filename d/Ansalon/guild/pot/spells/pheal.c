/*
 * pHeal
 */

#pragma strict_types

inherit "/d/Ansalon/guild/pot/spells/std_pot_spell";

#include "/d/Ansalon/common/defs.h"
#include "../spells.h"
#include "../guild.h"
#include <macros.h>
#include <tasks.h>  

/* Function name: query_spell_level
 * Description:   Internally used by the standing system
 * Returns:       int - the spell level
 */
int
query_spell_level()
{
    return 4;
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
resolve_spell(object caster, object *targets, int *resist, int result)
{
    object tar = targets[0];

    if (tar == caster)
    {
        if (tar->query_alignment() > 100)
        {
            caster->catch_tell("You feel pain shriveling through your " +
                "body.\n");
            all_msgbb(QCTNAME(caster) + " shivers as if in some kind " +
                "of pain.\n", caster);
        }
        else
        {
            caster->catch_tell("You feel new health infusing your body.\n");
            all_msgbb(QCTNAME(caster) + " straightens up, looking more " +
                "hale.\n", caster);
        }
    }
    else
    {
        if (tar->query_alignment() > 100)
        {
            caster->catch_tell("You place your hands on " +
                tar->query_the_name(caster) + ", and " + HE(tar) +
                " shivers as if in some kind of pain.\n");
            tar->catch_tell(caster->query_The_name(tar) + " places " +
                HIS(caster) + " hands on you, and you feel pain " +
                "shriveling through your body.\n");
            all_msgbb(QCTNAME(caster) + " places " + HIS(caster) +
                " hands on " + QTNAME(tar) + ", and " + HE(tar) +
                " shivers as if in some kind of pain.\n", caster, tar);
        }
        else
        {
            caster->catch_tell("You place your hands on " +
                tar->query_the_name(caster) + ", and " + HE(tar) +
                " shivers as " + HIS(tar) + " wounds are healed.\n");
            tar->catch_tell(caster->query_The_name(tar) + " places " +
                HIS(caster) + " hands on you, and you shiver as your " +
                "wounds are healed.\n");
            all_msgbb(QCTNAME(caster) + " places " + HIS(caster) +
                " hands on " + QTNAME(tar) + ", and " + HE(tar) +
                " shivers as " + HIS(tar) + " wounds are healed.\n", caster,
                tar);
        }
    }

    if (caster->query_attack())
        caster->skill_bonus(result/5);
    else
        caster->skill_bonus(result/10);

    result = ((2 + caster->query_priest_level()) * result * (100 - resist[0])) / 100;

    GUILD_ADMIN->log(caster, "pheal",tar->query_real_name() + ": " + result);

    if (result > 220)
        result = 220;

    if (tar->query_alignment() > 100 &&
        !environment(tar)->query_prop(ROOM_M_NO_ATTACK) &&
        !tar->query_prop(OBJ_M_NO_ATTACK))
    {
        tar->heal_hp(-result);
        if (tar->query_npc() && !tar->query_attack())
            tar->command("$kill " + OB_NAME(caster));
            
        if (tar->query_hp() <= 0)
            tar->do_die(caster);
    }
    else if (tar->query_alignment() <= 100)
        tar->heal_hp(result);
}

public int
pheal_resist(object caster, object target, int element, int difficulty)
{
    if (target->query_alignment() > 100)
        return spell_resist_basic(caster, target, element, difficulty);
    else
        return spell_resist_healing(caster, target, element, difficulty);
}

/*
 * Function name: config_spell
 * Description:   configure the spell
 * Arguments:     object caster   - the caster
 *                object *targets - array of spell targets found
 *                string argument - arguments to the spell invocation
 * Returns:       1/0 - spell configured/not configured (cannot be cast)
 */
public varargs int
config_spell(object caster, object *targets, string arg)
{
    set_spell_name("pheal");
    set_spell_desc("Minor healing of yourself or others");

    set_spell_element(SS_ELEMENT_LIFE, 20);
    set_spell_form(SS_FORM_TRANSMUTATION, 25);

    set_spell_time(4);
    set_spell_mana(50);

    set_spell_task(TASK_ROUTINE);

//    set_spell_resist(spell_resist_healing);
    set_spell_resist(pheal_resist);
    set_spell_target(spell_target_one_present_living);
    set_spell_target_verify(spell_verify_present);

#ifndef NO_INGREDIENTS
    set_spell_ingredients(({"heart"}));
#endif

    set_spell_vocal(1);

    return 0;
}
