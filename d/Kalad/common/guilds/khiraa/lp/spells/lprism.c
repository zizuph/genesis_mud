/* Sarr */


public void
do_lprism_spell(object caster, object *targets, int *res, int result)
{
    int time;
    object *dsh;

    dsh = make_spell_effect_object(LP_DIR+"obj/prism_sh",caster,targets,0,0);
    dsh->set_spell_effect_desc("prism shield");
    time = caster->query_stat(SS_WIS);

    if(caster == targets[0])
    {
        time = caster->query_stat(SS_WIS) + caster->query_stat(SS_INT);
        tell_object(caster,"You draw a triangle in the air around you "+
        "with your finger.\n");
        tell_room(E(caster),QCTNAME(caster)+" draws a triangle in the "+
        "air around "+HIM(caster)+" with "+HIS(caster)+" finger.\n",caster);
        dsh->set_remove_time(time);
        return;
    }

    tell_object(caster,"You draw a triangle in the air around "+
    targets[0]->query_the_name(caster)+" with your finger.\n");
    tell_object(targets[0],caster->query_The_name(targets[0])+" draws "+
    "a triangle in the air around you with "+HIS(caster)+" finger.\n");
    tell_room(E(caster),QCTNAME(caster)+" draws a triangle in the air "+
     "around "+QTNAME(targets[0])+" with "+HIS(caster)+" finger.\n",
    ({targets[0],caster}));

    dsh->set_remove_time(time);
}
public void
conc_lprism_message(object caster, object *targets, string arg)
{
    tell_object(caster,"Your hands begin to glow an ethereal white as you "+
    "weave them through the air, chanting prayers to the Horror.\n");
    tell_room(ENV(caster),QCTNAME(caster)+"'s hands begin to glow an ethereal "+
    "white as "+HE(caster)+" weaves them through the air and chants "+
    "strange words.\n",caster);
}

public int
create_spell_lprism(object caster, object *targets, string arg)
{
    if(!check_ok_cast(caster))
        return 1;
    if(targets[0]->query_prism_shield())
    {
        tell_object(caster,"This being is already under "+
        "a prism shield.\n");
        return 1;
    }
    set_spell_element(SS_ELEMENT_DEATH,80);
    set_spell_form(SS_FORM_CONJURATION,70);
    set_spell_time(3);
    set_spell_mana(200);
    set_spell_task(TASK_ROUTINE);
    set_spell_ingredients(({"shield","drakeroot","numbis"}));
    set_spell_effect(do_lprism_spell);
    set_spell_conc_message(conc_lprism_message);
    set_spell_no_reveal(0);
    set_spell_target_verify(spell_verify_present);
    set_spell_stationary(0);

    return 0;
}
