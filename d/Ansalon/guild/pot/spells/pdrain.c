/*
 * pDrain
 */
 
#pragma strict_types

inherit "/d/Ansalon/guild/pot/spells/std_pot_spell";

#include "/d/Ansalon/common/defs.h"
#include "../spells.h"
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>

/* Function name: query_spell_level
 * Description:   Internally used by the standing system
 * Returns:       int - the spell level
 */
int
query_spell_level()
{
    return 6;
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
    object tp, tar = targets[0];
    int procm, procf, mod;
    string loc = ({ "head", "arm", "chest" })[random(3)], msg, omsg;
    
    procm = 100 - ((tar->query_max_mana() - tar->query_mana()) * 100 /
        tar->query_max_mana());
    procf = 100 - ((tar->query_max_fatigue() - tar->query_fatigue()) * 100 /
        tar->query_max_fatigue());

    if (resist[0] < 40)
        resist[0] = 40;

#ifdef 0
    int proc = ((tar->query_stat(SS_WIS) * 2 + resist[0] +
        tar->query_stat(SS_INT) / 6) * 100) / (caster->query_stat(SS_WIS) +
        caster->query_stat(SS_INT) + caster->query_skill(SS_FORM_DIVINATION));
    int diff = (caster->query_stat(SS_WIS) + caster->query_stat(SS_INT) +
        caster->query_skill(SS_FORM_DIVINATION)) -
        (tar->query_stat(SS_WIS) * 2 + resist[0] +
        tar->query_stat(SS_INT) / 6);
#endif


    if (result < 5)
    {
        caster->catch_tell("You try to reach out and grab " +
            tar->query_the_name(caster) + " but " + HE(tar) +
            " evades your attempt.\n");
        tar->catch_tell(caster->query_The_name(tar) + " tries " +
            "reach out and grab but you evade " + HIS(caster) +
            " attempt.\n");
        all_msgbb(QCTNAME(caster) + " tries to reach out and " +
            "grab " + QTNAME(tar) + " but " + HE(tar) + " evades " +
            "the attempt.\n", caster, tar);

        return;
    }

    switch (result)
    {
        case 6..25:
            msg = "shiver slightly";
            omsg = "shivers slightly";
            mod = random(15);
            break;
        case 26..50:
            msg = "shiver";
            omsg = "shivers";
            mod = random(10);
            break;
        case 51..85:
            msg = "shiver violently";
            omsg = "shivers violently";
            mod = random(5);
            break;
        default:
            msg = "shiver violently and your skin turns cold";
            omsg = "shivers violently and " + HIS(tar) + " skin turns white";
            mod = random(2);
            break;
    }

    find_player("stralle")->catch_tell("resist[0]: " + resist[0] + ", mod: " + mod + ", procm: " + procm + ", tar_mana: " + tar->query_mana() + "\n");

    if (procm < 40)
    {
        caster->catch_tell("You reach out and grab " +
            tar->query_the_name(caster) + "'s " + loc + " and " + HE(tar) +
            " " + omsg + " from the touch.\nWith the touch you try to " +
            "draw the mental and physical strength out of your victim " +
            "to invigourate your own mental strength but realise there " +
            "was not much to begin with in that weak mind.\n");
        tar->catch_tell(caster->query_The_name(tar) + " reaches out " +
            "with " + HIS(caster) + " hands for your " + loc + " and you " +
            msg + " from the touch.\n");
        all_msgbb(QCTNAME(caster) + " reaches out with " + HIS(caster) +
            " hands for " + QTNAME(tar) + "'s " + loc + " and " + HE(tar) +
            " " + omsg + " from the touch.\n", caster, tar);
        tar->command("$shiver");

        return;
    }

    caster->catch_tell("You reach out and grab " +
        tar->query_the_name(caster) + "'s " + loc + " and " + HE(tar) +
        " " + omsg + " from the touch.\nWith the touch you draw the " +
        "mental and physical strength out of your victim to invigorate " +
        "your own mental strength.\n");
    tar->catch_tell(caster->query_The_name(tar) + " reaches out " +
        "with " + HIS(caster) + " hands for your " + loc + " and you " +
        msg + " from the touch.\nYou suddenly feel mental and physical " +
        "fatigue.\n");
    all_msgbb(QCTNAME(caster) + " reaches out with " + HIS(caster) +
        " hands for " + QTNAME(tar) + "'s " + loc + " and " + HE(tar) +
        " " + omsg + " from the touch.\n", caster, tar);
    tar->command("$shiver");

    find_player("stralle")->catch_tell("T mana: " + tar->query_mana() + " ... C mana: " + caster->query_mana() + "\n");

    tar->add_fatigue(-(tar->query_fatigue() *
        ((procf * (100 - (resist[0] + (mod * 2)))) / 100) / 100));
    tar->add_mana(-(tar->query_mana() *
        ((procm * (100 - (resist[0] - mod))) / 100) / 100));

    caster->add_mana(tar->query_mana() *
        ((procm * (100 - (resist[0] + (mod * 3)))) / 100) / 100);

    find_player("stralle")->catch_tell("T mana: " + tar->query_mana() + " ... C mana: " + caster->query_mana() + "\n");
#ifdef 0
    tar->set_fatigue(tar->query_fatigue() - diff / 2);
    tar->set_mana(tar->query_mana() - diff * 3);

    caster->set_mana(caster->query_mana() + diff * 2);
#endif

    if (!interactive(tar) && !tar->query_attack() &&
        !tar->query_prop(OBJ_M_NO_ATTACK) && F_DARE_ATTACK(tar, caster))
        tar->command("$kill " + caster->query_real_name());
}

public object *
pdrain_target(object caster, string str)
{
    if (!stringp(str) || (str == ""))
        return spell_target_one_present_enemy(caster, str);
    else
        return spell_target_one_other_present_living(caster, str);
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
config_spell(object caster, object *targets, string argument)
{
    set_spell_name("pdrain");
    set_spell_desc("Draining a mind to transfer it to you");

    set_spell_time(4);
    set_spell_mana(45);
    set_spell_task(TASK_SIMPLE);
    set_spell_element(SS_ELEMENT_LIFE, 30);
    set_spell_form(SS_FORM_TRANSMUTATION, 24);
    set_spell_ingredients(({ "lady's slipper", "belladonna", "leftover" }));
    set_spell_resist(spell_resist);
    set_spell_resist_task(TASK_ROUTINE + 100);
    set_spell_target(pdrain_target);
    set_spell_target_verify(spell_verify_present);
    set_spell_stationary(1);

    return 0;
}
