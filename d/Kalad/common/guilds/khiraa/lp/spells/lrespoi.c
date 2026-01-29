/* Sarr */


public void
do_lrespoi_spell(object caster, object *targets, int *r, int res)
{
    int time;
    object *ob;

    time = random(100) + (4 * caster->query_stat(SS_OCCUP));

    if(caster != targets[0])
    {
        tell_object(caster,"You point towards "+
        targets[0]->query_the_name(caster)+" and "+
        "watch as a green ray strikes "+HIS(targets[0])+" chest.\n");
        tell_object(targets[0],caster->query_The_name(targets[0])+
        " points at you and "+
        "a green ray shoots out and strikes you in the chest!\n");
        tell_room(ENV(caster),QCTNAME(caster)+" points at "+QTNAME(targets[0])+
        " and a green ray shoots out and strikes "+HIM(targets[0])+" in "+
        "the chest!\n",({caster,targets[0]}));
    }
    ob = make_spell_effect_object(LP_DIR+"obj/rp_shield",caster,targets,0,0);
    ob->set_spell_effect_desc("poison shield");
    ob->set_remove_time(time);
}

public void
conc_lrespoi_mess(object caster, object *targets, string arg)
{
    tell_object(caster,"You chant eerie prayers unto the Horror as you "+
    "weave your green glowing hands in intricate patterns.\n");
    tell_room(ENV(caster),QCTNAME(caster)+" chants eerie words as "+
    HE(caster)+" weaves "+HIS(caster)+" green glowing hands in "+
    "mysterious patterns.\n",caster);
}

public int
create_spell_lrespoi(object caster, object *targets, string arg)
{
    if(!check_ok_cast(caster))
        return 1;
    if(targets[0]->query_respoi_shadow())
    {
        tell_object(caster,"It is already under the resist poison shield.\n");
        return 1;
    }
    set_spell_element(SS_ELEMENT_DEATH,30);
    set_spell_form(SS_FORM_CONJURATION,30);
    set_spell_ingredients(({"nightshade","corpse of rat"}));
    set_spell_time(4);
    set_spell_mana(80);
    set_spell_task(TASK_ROUTINE);
    set_spell_effect(do_lrespoi_spell);
    set_spell_target_verify(spell_verify_present);
    set_spell_conc_message(conc_lrespoi_mess);
    return 0;
}

