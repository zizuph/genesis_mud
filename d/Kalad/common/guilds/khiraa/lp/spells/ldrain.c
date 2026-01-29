/* Sarr 
 * Updated 26.May.98 for new spellcasting and balance
 */

void
conc_message_drain(object caster, object *targets, string arg)
{
    tell_object(caster,"A sickly green aura envelopes your skeletal hands "+
    "as you lower your head and chant a prayer to the Horror.\n");
    tell_room(E(caster),"A sickly green aura envelopes "+QTNAME(caster)+"'s "+
    "hands as "+HE(caster)+" lowers "+HIS(caster)+" head and chants eerie "+
    "words.\n",caster);
}

void
do_ldrain_spell(object caster, object *targets, int *resist, int result)
{
    string str;
    int res, pen,dam, hr;
    object target = targets[0];
    
    pen = F_PENMOD(MIN(90,caster->query_stat(SS_OCCUP) / 2),
          caster->query_skill(SS_FORM_TRANSMUTATION) +
          caster->query_skill(SS_ELEMENT_DEATH));

    dam = (pen/2) + random((pen/2));

    dam -= (dam * resist[0]) / 100;

    hr = (pen * 100) / 1200;

    switch(hr)
    {
        case 0..10:    
            str = "slightly";
        break;
        case 11..25:
            str = "somewhat";
        break;
        case 26..30:
            str = "strongly";
        break;
        case 31..50:
            str = "greatly";
        break;
        case 51..70:
            str = "extremely";
        break;
        default:
            str = "enourmously";
    }

    tell_object(caster,"You strike at "+target->query_the_name(caster)+
    " with your skeletal hand, and drain the life from "+HIM(target)+
    "!\n");
    tell_object(caster,"You feel "+str+" healthier.\n");
    tell_object(target,caster->query_The_name(target)+" strikes "+
    "you with "+HIS(caster)+" skeletal hand, and drains the "+
    "life from you!\n");
    tell_object(target,"You feel "+str+" drained.\n");
    tell_room(E(caster),QCTNAME(caster)+" strikes out at "+
    QTNAME(target)+" with "+HIS(caster)+" skeletal hand, and drains "+
    "the life from "+HIM(target)+"!\n",({caster,target}));

    tell_object(caster,"DEBUG damage: "+dam+"\n");
    caster->heal_hp(dam);    
    target->heal_hp(-dam);

    if(target->query_hp() <= 0)
        target->do_die(caster);
}

int
spell_ldrain_resist(object caster, object target, int element,
    int difficulty)
{
    int res;

    res = max(0, min(100, 
        target->resolve_task(difficulty,
        ({ SKILL_WEIGHT, 40, SS_FORM_ABJURATION,
           SKILL_WEIGHT, 40, element,
           SKILL_WEIGHT, 30, SS_SPELLCRAFT,
           SKILL_WEIGHT, 30, TS_INT,
           SKILL_WEIGHT, 40, TS_WIS,
           SKILL_WEIGHT, 20, TS_DIS }))));

    res += combine_resistances(target, 
        ({ MAGIC_I_RES_MAGIC, resistance_map[element] }));

    return min(res, 100);
}

int
create_spell_ldrain(object caster, object *targets, string arg)
{
    if(!check_ok_cast(caster))
        return 1;

    if(!present("skaltakur_ob",caster) )
    {
        tell_object(caster,"You must be under the influence "+
        "of a Skaltakur potion.\n");
        return 1;
    }

    set_spell_element(SS_ELEMENT_DEATH,55);
    set_spell_form(SS_FORM_TRANSMUTATION,40);
    set_spell_time(2);
    set_spell_mana(100);
    set_spell_offensive(1);
    set_spell_ingredients(({"skull"}));
    set_spell_resist(spell_ldrain_resist);
    set_spell_target_verify(spell_verify_present);
    set_spell_task(TASK_ROUTINE);
    set_spell_conc_message(conc_message_drain);
    set_spell_effect(do_ldrain_spell);
    set_spell_stationary(0);
    set_spell_no_reveal(0);

    set_spell_resist_task(TASK_DIFFICULT);

    return 0; // Success
}
