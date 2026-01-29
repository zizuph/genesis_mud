/*
    lterror.c

    Lich priest spell,
    included by lp_med.c (the medallion)
    
    Sarr
    Recoded and balanced by Fysix, 30 Jan 1998
 */

// Execute the spell, clones a spell object and moves
// it to the caster.
void
do_lterror_spell(object caster, object *targets, int *resist, int result)
{
object *spell_objects;

    // Configure the spell object
    spell_objects = make_spell_effect_object(LP_DIR + "obj/terror_sh",
        caster, targets, resist, result);

    spell_objects->set_spell_effect_desc("black terror");
    spell_objects->set_duration(caster->query_stat(SS_WIS) / 2);
}

// Configure the spell
int
create_spell_lterror(object caster, object *targets, string arg)
{
    // Fail spell when caster isn't of high enough level
    if (!check_ok_cast(caster))
        return 1;

    // Fail spell when caster already has terror around himself
    if (caster->query_terror_shadow())
    {
        tell_object(caster, "You already have terror around you.\n");
        return 1;
    }

    set_spell_conc_message(conc_message_hiss);
    set_spell_element(SS_ELEMENT_DEATH, 40);
    set_spell_form(SS_FORM_CONJURATION, 40);
    set_spell_time(3);
    set_spell_mana(100);
    set_spell_stationary(0);
    set_spell_ingredients(({"bloodweed", "coccinea", "tooth"})); 
    set_spell_task(TASK_ROUTINE);
    set_spell_effect(do_lterror_spell);

    return 0;   // success
}

