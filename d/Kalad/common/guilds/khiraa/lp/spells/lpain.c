/* Sarr */

void
do_lpain_spell(object caster, object *targets, int *res, int result)
{
    object *sh;
    int time;
    object target = targets[0];

    time = 2 * caster->query_stat(SS_WIS);

    if(result < res[0])
    {
        caster->catch_msg("Your spell fails against "+QTNAME(target)+
        ".\n");
        return;
    }
    sh = make_spell_effect_object(LP_DIR+"obj/pain_sh",caster,targets,0,0);
    sh->set_spell_effect_desc("pain curse");
    tell_object(caster,"With your hand glowing a putrid green color, "+
    "you point at "+target->query_the_name(caster)+" and hiss: Pain.\n");
    tell_object(target,"With "+HIS(caster)+" hand glowing a putrid "+
    "green color, "+caster->query_the_name(target)+" points at you "+
    "hissing: Pain.\n");
    tell_room(E(caster),"With "+HIS(caster)+" hand glowing a putrid "+
    "green color, "+QTNAME(caster)+" points at "+QTNAME(target)+
    " hissing: Pain.\n",({caster,target}));
    
    sh->set_remove_time(time);
}

public void
conc_lpain_mess(object caster, object *targets, string arg)
{
    tell_object(caster,"As you chant your unholy prayer, your hands "+
    "start to glow with a putrid green aura.\n");
    tell_room(ENV(caster),"As "+QTNAME(caster)+" chants unholy sounding "+
    "words, "+HIS(caster)+" hands start to glow with a putrid green "+
    "aura.\n",caster);
}

public int
create_spell_lpain(object caster, object *targets, string arg)
{
    if(!check_ok_cast(caster))
        return 1;
    if(targets[0]->query_pain_shadow())
    {
        tell_object(caster,"This living is already under this spell's "+
        "effects.\n");
        return 1;
    }
    set_spell_element(SS_ELEMENT_DEATH,50);
    set_spell_form(SS_FORM_TRANSMUTATION,40);
    set_spell_time(3);
    set_spell_mana(100);
    set_spell_ingredients(({"skull","mindleech","nightshade"}));
    set_spell_effect(do_lpain_spell);
    set_spell_conc_message(conc_lpain_mess);
    set_spell_task(TASK_ROUTINE);
    set_spell_resist(spell_resist);
    set_spell_resist_task(TASK_DIFFICULT);
    return 0;
}

