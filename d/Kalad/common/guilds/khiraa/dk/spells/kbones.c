/* Sarr */

void
kbones_conc(object caster, object *targets, string arg)
{
    tell_object(caster,"A white glow envelopes your body as "+
    "you chant to the Horror.\n");
    tell_room(E(caster),"A white glow envelopes "+QTNAME(caster)+"'s "+
    "body as "+HE(caster)+" chants eerie words.\n",caster);
}

void
do_spell_kbones(object caster, object *targets, int *resist, int result)
{
    object *shad;
    int time;
    
    shad = make_spell_effect_object(DK_DIR+"obj/bones_sh",caster,targets,resist,result);
    shad->set_spell_effect_desc("unholy bone shield");
    time = 10 +  ( caster->query_stat(SS_WIS) / 4);
    time += result;

    shad->set_remove_time(time);
}

int
create_spell_kbones(object caster, object *targets, string arg)
{
    if(!check_ok_cast(caster))
        return 1;

    if(caster->query_bones_shadow())
    {
        tell_object(caster,"You are already under the effect of "+
        "Bone Shield.\n");
        return 1;
    }

    set_spell_element(SS_ELEMENT_DEATH,30);
    set_spell_form(SS_FORM_TRANSMUTATION,30);
    set_spell_time(4);
    set_spell_mana(55);
    set_spell_ingredients(({"vinerot","bloodweed","skull"})); 
    set_spell_effect(do_spell_kbones);
    set_spell_stationary(0);
    set_spell_task(TASK_ROUTINE);
    set_spell_conc_message(kbones_conc);
    return 0;
}

