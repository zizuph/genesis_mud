/* Sarr */


int lfh;

public int
spell_resist_illusion(object caster, object target, int element,
    int difficulty)
{
    int res;

    res = max(0, min(100,
        target->resolve_task(difficulty,
        ({ SKILL_WEIGHT, 20, SS_FORM_ABJURATION,
           SKILL_WEIGHT, 30, SS_FORM_ILLUSION,
           SKILL_WEIGHT, 30, SS_AWARENESS,
           SKILL_WEIGHT, 20, SS_SPELLCRAFT,
           SKILL_WEIGHT, 40, TS_INT,
           SKILL_WEIGHT, 40, TS_WIS,
           SKILL_WEIGHT, 20, TS_DIS }))));

    res += combine_resistances(target,
        ({ MAGIC_I_RES_MAGIC, MAGIC_I_RES_ILLUSION }));

    return min(res, 100);
}

object *
target_lhealth(object caster, string arg)
{
    string str2,str3;
    object *obs, ob;
    if(!arg)
    {
        tell_object(caster,"Cast what?\n");
        return ({});
    }
    if(sscanf(arg,"%s as %s",str2,str3) != 2)
    {
        tell_object(caster,"Lhealth who as what?\n");
        return ({});
    }
    if(str3 != "dying" && str3 != "full")
    {
        tell_object(caster,"You must enter either dying or full.\n");
        return ({});
    }
    if(str3 == "dying")
        lfh = 1;
    else
        lfh = 0;
    if(str2 == "myself")
        return ({ caster });

    obs = PARSE_THIS(str2,"[the] %l");    

    if(sizeof(obs))
        ob = obs[0];
    if(ob && present(ob,ENV(caster)) )
    {
        return ({ob});
    }
    tell_object(caster,"There is no such mortal present.\n");
    return ({});
}

void
do_lhealth_spell(object caster, object *targets, int *res, int result)
{
    int time;
    object *hsh;

    if(result < res[0] && caster != targets[0])
    {
        tell_object(caster,"Your target resists your magical prayer.\n");
        tell_object(targets[0],"You feel a slight tingle, but then its gone.\n");
        return;
    }

    hsh = make_spell_effect_object(LP_DIR+"obj/health_sh",caster,targets,
           0,0);
    hsh->set_spell_effect_desc("illusion health");
    time = caster->query_stat(SS_WIS);
    time = time * 2;
    hsh->set_remove_time(time,lfh);

    if(caster == targets[0])
    {
        tell_object(caster,"You feel the illusion taking effect.\n");
        tell_room(E(caster),"The air around "+QTNAME(caster)+" sparkles "+
        "for a moment.\n",caster);
        return;
    }
    tell_object(caster,"You claps your hands together in front of "+
    targets[0]->query_the_name(caster)+" and the air around "+HIM(targets[0])+" "+
    "sparkles for a moment.\n");

    tell_object(targets[0],caster->query_The_name(targets[0])+" claps "+HIS(caster)+" "+
    "hands together in front of you, and the air around you sparkles "+
    "for a moment.\n");

    tell_room(E(caster),QCTNAME(caster)+" claps "+HIS(caster)+" hands "+
    "together in front of "+QTNAME(targets[0])+", and the air around "+
    HIM(targets[0])+" sparkles for a moment.\n",({caster,targets[0]}));
}

public void
conc_lhealth_mess(object caster, object *targets, string arg)
{
    tell_object(caster,"You utter a prayer to the Horror.\n");
    tell_room(ENV(caster),QCTNAME(caster)+" utters something "+
    "incomprehensible.\n", caster);
}

public int
create_spell_lhealth(object caster, object *targets, string arg)
{
    if(!check_ok_cast(caster))
        return 1;
    if(targets[0]->query_health_shadow())
    {
        tell_object(caster,"It is already under the effects of this spell.\n");
        return 1;
    }
    set_spell_element(SS_ELEMENT_DEATH,5);
    set_spell_form(SS_FORM_ILLUSION,5);
    set_spell_time(3);
    set_spell_mana(35);
    set_spell_ingredients(({"glowshroom"})); 
    set_spell_target_verify(spell_verify_present);
    set_spell_effect(do_lhealth_spell);
    set_spell_task(TASK_SIMPLE);
    set_spell_resist(spell_resist_illusion);
    set_spell_resist_task(TASK_DIFFICULT);
    set_spell_conc_message(conc_lhealth_mess);

    return 0;
}

