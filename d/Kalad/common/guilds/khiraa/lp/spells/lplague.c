/* Sarr */


public void
do_lplague_spell(object caster, object *targets, int *res, int resu)
{
    object poi;
    int time;
    object target = targets[0];
    
    if (res[0] > resu)
    {
        tell_object(caster,"Your target resists the spell!\n");
        return;
    }

    tell_object(target,caster->query_The_name(target)+" points both "+
    "hands towards you; a putrid yellow ray shoots from them and "+
    "strikes you in the chest!\n");
    tell_object(caster,"You points both of your hands at "+
    target->query_the_name(caster)+" and a putrid yellow ray shoots from "+
    "them, striking "+HIM(target)+" in the chest!\n");
    tell_room(ENV(caster),QCTNAME(caster)+" points both hands towards "+
    QTNAME(target)+"; a putrid yellow ray shoots from them and strikes "+
    HIM(target)+" in the chest!\n", ({target,caster}));

    time = (caster->query_stat(SS_WIS) * 6);

    tell_object(target,"You feel very sick suddenly!\n");
    poi = clone_object(LP_DIR+"obj/disease");
    poi->set_strength(MAX(100,caster->query_stat(SS_WIS)));
    poi->set_time(time);
    poi->move(target);
    poi->start_poison();
}

public void
conc_lplague_mess(object caster, object *targets, string arg)
{
    tell_object(caster,"Your eyes burn a sickly yellow as you weave "+
    "your hands in intricate patterns and chant the prayer.\n");
    tell_room(ENV(caster),QCTNAME(caster)+"'s eyes burn a sickly yellow "+
    "as "+HE(caster)+" weaves "+HIS(caster)+" hands in intricate "+
    "patterns and chants unholy words.\n",caster);
}

public int
plague_resist(object caster, object target, int element,
    int difficulty)
{
    return combine_resistances(target,
        ({ MAGIC_I_RES_MAGIC, MAGIC_I_RES_POISON }));
}

public int
create_spell_lplague(object caster, object *targets, string arg)
{
    if(!check_ok_cast(caster))
        return 1;

    set_spell_element(SS_ELEMENT_DEATH,35);
    set_spell_form(SS_FORM_CONJURATION,30);
    set_spell_time(2);
    set_spell_mana(80);

    set_spell_ingredients(({"plague doll"}));
    set_spell_target_verify(spell_verify_present);
    set_spell_offensive(1);
    set_spell_stationary(0);
    set_spell_no_reveal(0);
    set_spell_effect(do_lplague_spell);
    set_spell_task(TASK_ROUTINE);
    set_spell_conc_message(conc_lplague_mess);
    set_spell_resist_task(TASK_DIFFICULT);
    set_spell_resist(plague_resist);

    return 0;
}
