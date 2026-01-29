/* Sarr */

void
do_ldetect_spell(object caster, object *targets, int *rez, int res)
{
    int i;
    mixed *id;
    object ob;
    int val,index,cwis;

    cwis = caster->query_stat(SS_WIS);
    val = caster->query_skill(SS_SPELLCRAFT);

    ob = targets[0];
    id = ob->query_prop(MAGIC_AM_ID_INFO);
    val = res * ( cwis/ 4);
    val -= (rez[0] * val) / 100;

    if(sizeof(id))
    {
        for(i=1;i<sizeof(id);i+=2)
        {
            if(val >= id[i])
                index = i-1;
        }
    }
    else
    {
        tell_object(caster,"There is nothing magical about the "+
        ob->short()+".\n");
        return;
    }

    if(stringp(id[index]))
    {
        tell_object(caster,"You discover the following about the "+
        ob->short()+":\n");
        tell_object(caster,id[index]+"\n");
        return;
    }

    if(res)
    {
        tell_object(caster,"You sense the "+ob->short()+" is magical, "+
        "but cannot discern exactly how.\n");
        return;
    }

    tell_object(caster,"You discover nothing about the "+
    ob->short()+".\n");
}

public void
conc_ldetect_mess(object caster, object *targets, string arg)
{
    tell_object(caster,"You close your eyes and focus your powers "+
    "in the Horror.\n");
    tell_room(environment(caster),QCTNAME(caster)+" closes "+HIS(caster)+
    " eyes and intones a prayer.\n",caster);
}

public int
create_spell_ldetect(object caster, object *targets, string arg)
{
    if(!check_ok_cast(caster))
        return 1;

    set_spell_element(SS_ELEMENT_DEATH,15);
    set_spell_form(SS_FORM_DIVINATION,10);
    set_spell_time(2);
    set_spell_mana(50);
    set_spell_ingredients(({"eye","madwort"}));
    set_spell_task(TASK_ROUTINE);
    set_spell_effect(do_ldetect_spell);
    set_spell_target_verify(spell_verify_present);
    set_spell_conc_message(conc_ldetect_mess);
    set_spell_resist_task(TASK_DIFFICULT);
    set_spell_resist(spell_resist_identify);
    return 0;
}
