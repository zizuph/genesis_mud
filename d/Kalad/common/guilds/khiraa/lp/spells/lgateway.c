/* Sarr */


void
do_lgateway_spell(object caster, object *targets)
{
    int time, wis;
    wis = caster->query_stat(SS_WIS);
    time = wis + (2 * random(wis)) + 30;

    tell_object(caster,"You spread your arms toward the "+targets[0]->short()+
    ".\n");

    tell_room(E(caster),QCTNAME(caster)+" spreads "+HIS(caster)+" arms "+
    "towards the "+targets[0]->short()+".\n",caster);

    if(targets[0]->test_create_portal() != 1)
    {
        tell_object(caster,"Something has gone wrong with the stones.\n");
        return;
    }

    targets[0]->create_portal(time,caster);
}
void
conc_message_lgateway(object caster, object *targets,string arg)
{
    tell_object(caster,"You kneel to the ground and clasp your hands "+
    "together as you chant unholy prayers to the Horror.\n");
    tell_room(E(caster),QCTNAME(caster)+" kneels to the ground and "+
    "clasps "+HIS(caster)+" hands together as "+HE(caster)+" chants "+
    "eerie unknown words.\n",caster);
}

public int
create_spell_lgateway(object caster, object *targets,string arg)
{
    object groom;
    if(!check_ok_cast(caster))
        return 1;
    if(ENV(caster)->query_prop(ROOM_M_NO_TELEPORT) ||
       ENV(caster)->query_prop(ROOM_M_NO_TELEPORT_TO) ||
       ENV(caster)->query_prop(ROOM_M_NO_TELEPORT_FROM) )
    {
        tell_object(caster,"You cannot cast this spell here.\n");
        return 1;
    }
    if(!targets[0]->id("_babi_unholy_stones_"))
    {
        tell_object(caster,"You can only cast this on the "+
        "unholy stones of Babi.\n");
        return 1;
    }    
    call_other(KHIRAA+"temple/rooms/t7","??");
    groom = find_object(KHIRAA+"temple/rooms/t7");

    if(!objectp(groom))
    {
        tell_object(caster,"Error.\n");
        return 1;
    }
    if(present("_gateway_",groom))
    {
        tell_object(caster,"There is already a gateway "+
        "opened to the Netherworld, you must wait till it shuts.\n");
        return 1;
    }
    if(targets[0]->test_create_portal() != 1)
    {
        tell_object(caster,"Something is not right with the "+
        "stones.\n");
        return 1;
    }

    set_spell_element(SS_ELEMENT_DEATH,20);
    set_spell_form(SS_FORM_CONJURATION,20);
    set_spell_time(4);
    set_spell_mana(98);
    set_spell_ingredients(({"glowshroom","suranie","tooth"}));
    set_spell_target_verify(spell_verify_present);
    set_spell_effect(do_lgateway_spell);
    set_spell_conc_message(conc_message_lgateway);
    set_spell_task(TASK_ROUTINE);

    return 0;
}

