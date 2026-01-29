/* Sarr */


void
do_lspeed_spell(object caster, object *targets, int *resist, int result)
{
    int time;
    object *shs;
    time = caster->query_stat(SS_WIS) + random(caster->query_stat(SS_WIS));
    shs = make_spell_effect_object(LP_DIR+"obj/revenant_sh",caster,targets,0,0);
    shs->set_spell_effect_desc("unholy speed");
    shs->set_remove_time(time);
}

void
conc_lspeed_message(object caster, object *targets, string arg)
{
    tell_object(caster,"You clench your hands into fists as they begin to "+
    "glow a sickly green color.\n");
    tell_room(ENV(caster),QCTNAME(caster)+" clenches "+HIS(caster)+" hands "+
    "into fists as they begin to glow a sickly green color.\n",caster);
}

public int
create_spell_lspeed(object caster, object *targets, string arg)
{
    if(!check_ok_cast(caster))
        return 1;
    if(!present("celerity_ob",caster))
    {
        tell_object(caster,"You must be under the influence "+
        "of a Celerity potion.\n");
        return 1;
    }
    if(caster->query_revenant_shadow())
    {
        tell_object(caster,"You are already under the effects of unholy speed.\n");
        return 1;
    }
    set_spell_element(SS_ELEMENT_DEATH,15);
    set_spell_form(SS_FORM_TRANSMUTATION,15);    
    set_spell_task(TASK_ROUTINE);
    set_spell_time(1);
    set_spell_mana(85);
    set_spell_ingredients(({"rib"})); 
    set_spell_target_verify(spell_verify_present);
    set_spell_effect(do_lspeed_spell);
    set_spell_conc_message(conc_lspeed_message);
    set_spell_stationary(0);
    set_spell_no_reveal(0);
    return 0;
}

