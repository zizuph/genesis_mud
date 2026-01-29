/* Sarr */

void
do_lclone_spell(object caster, object *targets, int *resist, int result)
{
    object my_clone, *enemies;
    int i,amt;

    amt = 5 + random(4); // # of clones to make

    if(caster == targets[0])
    {
        tell_object(caster,"Several copies of yourself spring into "+
        "being out of your body!\n");
        tell_room(E(caster),"Several copies of "+QTNAME(caster)+" "+
        "spring into being out of "+HIS(caster)+" body!\n",caster);
    }

    else
    {
        tell_object(targets[0],"Several copies of yourself spring into "+
        "being out of your body!\n");
        tell_room(E(targets[0]),"Several copies of "+QTNAME(targets[0])+
        " spring into being out of "+HIS(targets[0])+" body!\n",targets[0]);
    }

    for(i=0;i<amt;i++)
    {
        my_clone = clone_object(LP_DIR+"obj/ecto_clone");
        my_clone->set_up_clone(caster,targets[0]);
        my_clone->move_living("M",E(targets[0]));
        if(amt == random(amt))
            targets[0]->move_living("M",E(targets[0]));
    }
    enemies = targets[0]->query_enemy(-1);
    if(targets[0]->query_attack())
        targets[0]->stop_fight(targets[0]->query_attack());
    for(i = 0; i <sizeof(enemies); i++)
    {
        if(present(enemies[i],ENV(targets[0])))
        {
            tell_object(enemies[i],"Your combat concentration is disrupted and "+
            "you stand confused.\n");
            enemies[i]->stop_fight(targets[0]);
        }
    }
}

public void
conc_message_lclone(object caster, object *targets, string arg)
{
    tell_object(caster,"You chant the unholy prayer as you weave your hands.\n");
    tell_room(ENV(caster),QCTNAME(caster)+" chants eerie words as "+HE(caster)+
    " weaves "+HIS(caster)+" hands.\n",caster);
}

public int
create_spell_lclone(object caster, object *targets, string arg)
{
    if(!check_ok_cast(caster))
        return 1;

    set_spell_element(SS_ELEMENT_DEATH,10);
    set_spell_form(SS_FORM_ILLUSION,20);
    set_spell_time(2);
    set_spell_mana(55);
    set_spell_task(TASK_ROUTINE);
    set_spell_ingredients(({"lore","pepper"})); 
    set_spell_target_verify(spell_verify_present);
    set_spell_conc_message(conc_message_lclone);
    set_spell_effect(do_lclone_spell);
    return 0;
}
