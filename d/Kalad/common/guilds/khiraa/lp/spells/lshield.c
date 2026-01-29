/* Sarr */


void
do_lshield_spell(object caster, object *targets)
{
    int time;
    object *dsh;
    time = (5 * caster->query_stat(SS_WIS)) + (2 * caster->query_stat(SS_INT));

    if(caster == targets[0])
    {
        tell_object(caster,"You clap your hands loudly.\n");
        tell_room(E(caster),QCTNAME(caster)+" claps "+HIS(caster)+" hands "+
        "loudly.\n",caster);
        dsh = make_spell_effect_object(LP_DIR+"obj/death_sh",caster,targets,0,0);
        dsh->set_spell_effect_desc("death shield");
        dsh->set_remove_time(time);
        return;
    }
    tell_object(caster,"You draw a circle in the air around "+
    targets[0]->query_the_name(caster)+" with your finger.\n");
    tell_object(targets[0],caster->query_The_name(targets[0])+" draws "+
    "a circle in the air around you with "+HIS(caster)+" finger.\n");
    tell_room(E(caster),QCTNAME(caster)+" draws a circle in the air "+
     "around "+QTNAME(targets[0])+" with "+HIS(caster)+" finger.\n",
    ({targets[0],caster}));
    dsh = make_spell_effect_object(LP_DIR+"obj/death_sh",caster,targets,0,0);
    dsh->set_spell_effect_desc("death shield");

    dsh->set_remove_time(time);
}

public void
conc_message_lshield(object caster, object *targets, string arg)
{
    tell_object(caster,"You weave your hands in an intricate pattern as a "+
    "foul black mist begins to encircle your body.\n");
    tell_room(ENV(caster),QCTNAME(caster)+" weaves "+HIS(caster)+" hands in "+
    "an intricate pattern as a foul black mist begins to encircle "+HIS(caster)+
    "body.\n",caster);
}

public int
create_spell_lshield(object caster, object *targets, string arg)
{
    int who = 0;
    if(!check_ok_cast(caster))
        return 1;
    if(targets[0] == caster)
        who = 1;
    if(targets[0]->query_death_shield())
    {
        tell_object(caster, (who ? "You are" : CAP(HE(targets[0]))+" is")+
        " already under a death shield!\n");
        return 1;
    }

    set_spell_element(SS_ELEMENT_DEATH,15);
    set_spell_form(SS_FORM_CONJURATION,15);
    set_spell_time(2);
    if(who)
        set_spell_mana(75);
    else
        set_spell_mana(110);
    set_spell_ingredients(({"rib","nightshade"})); 
    set_spell_target_verify(spell_verify_present);
    set_spell_task(TASK_ROUTINE);
    set_spell_conc_message(conc_message_lshield);
    set_spell_effect(do_lshield_spell);
    set_spell_stationary(0);
    set_spell_no_reveal(0);

    return 0;
}
