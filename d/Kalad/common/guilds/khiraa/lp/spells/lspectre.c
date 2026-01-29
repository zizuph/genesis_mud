/* Sarr */

void
do_lspectre_spell(object caster, object *targets, int *r, int result)
{
    object controler;
    float time;
    object target = targets[0];

    tell_object(caster,"You summon the spectre correctly.\n");

    tell_room(E(caster),QCTNAME(caster)+" closes his eyes and seems "+
    "to be in a trance.\n",caster);

    controler = clone_object(LP_DIR+"obj/spectre_control");
    controler->move(caster);
    controler->set_master(caster,ENV(target));

    time = itof(caster->query_stat(SS_OCCUP) + caster->query_stat(SS_WIS) +
                random(101));
    controler->set_remove_time(time);
}

public int
create_spell_lspectre(object caster, object *targets, string arg)
{
    if(!check_ok_cast(caster))
        return 1;
    if(present("_spectre_obj",caster) )
    {
        tell_object(caster,"You are already controling a "+
        "spectre.\n");
        return 1;
    }
    if(targets[0]->query_wiz_level())
    {
        tell_object(caster,"There is no such mortal in the realms.\n");
        return 1;   
    }
    if(ENV(targets[0])->query_prop(ROOM_M_NO_TELEPORT) ||
       ENV(targets[0])->query_prop(ROOM_M_NO_MAGIC) ||
       ENV(targets[0])->query_prop(ROOM_M_NO_TELEPORT_TO) ||
       ENV(targets[0])->query_prop(ROOM_M_NO_TELEPORT_FROM) ||
       ENV(targets[0])->query_prevent_snoop())
    {
        tell_object(caster,"The room your target is in is "+
        "protected by strange magical powers.\n");
        return 1;
    }

    set_spell_element(SS_ELEMENT_DEATH,10);
    set_spell_form(SS_FORM_CONJURATION,10);
    set_spell_time(4);
    set_spell_mana(55);
    set_spell_ingredients(({"eye","myrtleberry"})); 
    set_spell_effect(do_lspectre_spell);
    set_spell_task(TASK_ROUTINE);
    set_spell_conc_message(conc_lhealth_mess);
    return 0;
}
