void
do_linvis_spell(object caster, object *targets, int *resist, int result)
{
    object *shads;
    int time;

    time = (result * 3) + (3 * caster->query_stat(SS_WIS)) + 
        (2 * caster->query_stat(SS_INT));

    shads = make_spell_effect_object(LP_DIR+"obj/invis_shadow",caster,targets,0,0);
    shads->set_spell_effect_desc("invisibility");

    shads->set_remove_time(time);
}

void
conc_message_linvis(object caster, object *targets, string arg)
{
    tell_object(caster,"You softly chant the unholy prayers to the Horror.\n");
    tell_room(ENV(caster),QCTNAME(caster)+" softly whispers something.\n",caster);
}

public int
create_spell_linvis(object caster, object *targets, string arg)
{
    if(!check_ok_cast(caster))
        return 1;
    if(caster->query_invis_shadow())
    {
        tell_object(caster,"You are already under invisibility.\n");
        return 1;
    }
    set_spell_element(SS_ELEMENT_DEATH,30);
    set_spell_form(SS_FORM_ILLUSION,40);

    set_spell_time(3);
    set_spell_mana(80);
    set_spell_ingredients(({"kuko","lore"})); 
    set_spell_target_verify(spell_verify_present);
    set_spell_conc_message(conc_message_linvis);
    set_spell_effect(do_linvis_spell);
    set_spell_task(TASK_ROUTINE);

    return 0;
}

