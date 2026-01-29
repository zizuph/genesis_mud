/* Sarr */


object *target_ltouch(string arg);
void ltouch_mess(object caster, object *targets);

int
do_ltouch()
{
    if(!check_ok_cast(4))
        return 0;
    return cast_spell();
}

void
create_spell_ltouch(string arg)
{
    set_spell_element(SS_ELEMENT_DEATH,40);
    set_spell_form(SS_FORM_TRANSMUTATION,40);
    set_spell_time(2);
    set_spell_mana(85);
    set_spell_offensive();
    set_spell_ingredients(({"drudgeworth","bloodweed","finger"})); 
    set_find_target(target_ltouch);
    set_spell_message(ltouch_mess);
    set_spell_task(TASK_ROUTINE,0);
}

object
*target_ltouch(string arg)
{
    object ob,ob2,*obs;
    ob2 = query_caster();
    if(!arg || arg == "0")
    {
        if(ob2->query_attack())
            ob = ob2->query_attack();
    }
    if(!objectp(ob))
    {
        obs = PARSE_THIS(arg,"[the] %l");
        if(sizeof(obs))
            ob = obs[0];
    }
    if(ob && present(ob,E(ob2)) )
    {
        if(ob->query_stun_shadow())
        {
            tell_object(ob2,"It is already stunned!\n");
            return ({});
        }
        return ({ob});
    }
    tell_object(ob2,"There is no such mortal present.\n");
    return ({});
}

void
ltouch_mess(object caster, object *targets)
{
    int time;
    int res;
    object stunob,target;
    target = targets[0];
    seteuid(getuid());
    res = MAX(target->query_magic_res(MAGIC_I_RES_COLD), 
              target->query_magic_res(MAGIC_I_RES_DEATH));
    time = (query_spell_result()[0] / 4) + (caster->query_stat(SS_WIS)/4);
    time -= (time * res) / 100;
    if(query_spell_result()[0] < 
       target->resolve_task(TASK_DIFFICULT,({SKILL_WEIGHT,60,TS_CON,
    SKILL_AVG,SS_FORM_ABJURATION,SS_SPELLCRAFT,SKILL_END,SS_ELEMENT_LIFE})))
    {
        tell_object(caster,"Your target resists your death touch.\n");
        return;
    }
    stunob = clone_object(LP_DIR(obj/stun_sh));
    stunob->shadow_me(target);
    stunob->set_remove_time(time);

    tell_object(caster,"You lash out your skeletal hand at "+
    target->query_the_name(caster)+" and strike "+HIM(target)+" with "+
    "a blood-freezing coldness.\n");
    tell_object(target,caster->query_The_name(target)+" lashes out "+
    "at you with "+HIS(caster)+" skeletal hand and strikes you with "+
    "a blood-freezing coldness.\n");
    tell_room(E(caster),QCTNAME(caster)+" lashes out at "+QTNAME(target)+
    " with "+HIS(caster)+" skeletal hand and strikes "+HIM(target)+
    " with a blood-freezing coldness.\n",({target,caster}));
}
