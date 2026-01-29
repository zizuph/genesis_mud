/* Sarr */


public void
do_lhands_spell(object caster, object *targets, int *r, int res)
{
    object *hands,target;
    int time;
    int power;

    target = targets[0];

    hands =
    make_spell_effect_object(LP_DIR+"obj/doom_hands",caster,targets,r,res);

    time = caster->query_stat(SS_OCCUP);
    power = MIN(200,(3 * time)) - r[0];

    hands->set_spell_effect_desc("doom hands");
    hands->set_power(power);
    hands->set_remove_time(time);
    hands->move(ENV(target));

    tell_room(E(TO),"From out of the ethereal mist on the ground, "+
    "sickly-yellow glowing hands emerge and grab onto the legs of "+
    QTNAME(target)+"!\n",({target}));

    tell_object(target,"From out of the ethereal mist on the ground, "+
    "sickly-yellow glowing hands emerge and grab onto your legs!\n");

}

public void
conc_lhands_mess(object caster, object *targets, string arg)
{
    tell_object(caster,"As you weave your hands, they begin to glow a "+
    "sickly yellow color.\n");
    tell_room(ENV(caster),"As "+QTNAME(caster)+" weaves "+HIS(caster)+
    "hands, they begin to glow a sickly yellow color.\n",caster);
}

public int
create_spell_lhands(object caster, object *targets, string arg)
{
    if(!check_ok_cast(caster))
        return 1;
    if(!present("rot_ob",caster) )    
    {
        tell_object(caster,"You must be under the influence "+
        "of a Rot potion.\n");
        return 1;
    }
    set_spell_element(SS_ELEMENT_DEATH,40);
    set_spell_form(SS_FORM_CONJURATION,45);
    set_spell_time(3);
    set_spell_mana(100);
    set_spell_ingredients(({"two bloody dismembered hands"})); 
    set_spell_target_verify(spell_verify_present);
    set_spell_stationary(0);
    set_spell_offensive(1);
    set_spell_conc_message(conc_lhands_mess);
    set_spell_effect(do_lhands_spell);
    set_spell_task(TASK_ROUTINE);
    set_spell_resist(spell_resist);
    set_spell_resist_task(TASK_DIFFICULT);

    return 0;
}

