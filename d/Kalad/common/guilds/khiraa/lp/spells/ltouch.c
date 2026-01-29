/*
    ltouch.c
    
    Lich Priest spell,
    included by lp_med.c (the medallion)
    
    Sarr
    Recoded and balanced by Fysix, Feb 1998
 */

// Do my own resistance check
int
spell_ltouch_resist(object caster, object target, int element,
    int difficulty)
{
    int res;

    // Sum of skill weights should be 200, see man general tasks    
    res = max(0, min(100,
        target->resolve_task(difficulty, ({
        SKILL_WEIGHT, 70, element, 
        SKILL_WEIGHT, 80, SKILL_AVG, SS_FORM_ABJURATION,
        SS_SPELLCRAFT, SKILL_END,
        SKILL_WEIGHT, 50, TS_CON,
        }))));

    // Addition of general resistance
    res += combine_resistances(target,
        ({ MAGIC_I_RES_MAGIC, MAGIC_I_RES_COLD }));

    return min(res, 100);
}

// Execute the spell
void
do_ltouch_spell(object caster, object *targets, int *resist, int result)
{
    int max_time, time;
    object *stunob, target;

    target = targets[0];

    // Calculate maximum stun time
    max_time = 5 + (caster->query_stat(SS_WIS) / 3);

    // The more resistance, the shorter the stun
    // Time ranges from -max_time..max_time
    time = (max_time * (50 - resist[0])) / 50;

    // if the time is shorter than 0 the target resists too much
    if (time <= 0)
    {
        tell_object(caster, "Your target resists your death touch.\n");
        return;
    }


    // Give some messages
    tell_object(caster, "You lash out your skeletal hand at " +
    target->query_the_name(caster) + " and strike " + HIM(target) +
        " with " + "a blood-freezing coldness.\n");
    tell_object(target, caster->query_The_name(target) + " lashes out " +
        "at you with " + HIS(caster) +
        " skeletal hand and strikes you with " +
        "a blood-freezing coldness.\n");
    tell_room(ENV(caster), QCTNAME(caster) + " lashes out at " +
        QTNAME(target) + " with " + HIS(caster) +
        " skeletal hand and strikes " + HIM(target) +
        " with a blood-freezing coldness.\n",
        ({target, caster}));

    // Create the stun object
    stunob = make_spell_effect_object(LP_DIR + "obj/ghoul_stun",
        caster, targets, resist, result);
    stunob->set_spell_effect_desc("ghoul stun");
    stunob->set_remove_time(time);

}

// Configure the spells
int
create_spell_ltouch(object caster, object *targets, string arg)
{
    if (!check_ok_cast(caster))
        return 1;

    if (targets[0]->query_ghoul_stun() )
    {
        tell_object(caster, targets[0]->query_The_name(caster) +
            " is already stunned!\n");
        return 1;
    }

    set_spell_element(SS_ELEMENT_DEATH, 50);
    set_spell_form(SS_FORM_TRANSMUTATION, 50);
    set_spell_time(2);
    set_spell_mana(85);
    set_spell_offensive(1);
    set_spell_stationary(0);
    set_spell_ingredients(({"drudgeworth", "bloodweed", "finger"}));
    set_spell_resist(spell_ltouch_resist);
    set_spell_resist_task(TASK_DIFFICULT);
    set_spell_target_verify(spell_verify_present);
    set_spell_task(TASK_ROUTINE);
    set_spell_conc_message(conc_message_chant);
    set_spell_effect(do_ltouch_spell);

    return 0;   // Success
}
