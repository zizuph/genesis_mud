/* Sarr */


object *target_lterror(string arg);
void lterror_mess(object caster, object *targets);

int
do_lterror()
{
    if(!check_ok_cast(4))
        return 0;
    return cast_spell();
}

void
create_spell_lterror(string arg)
{
    set_spell_element(SS_ELEMENT_DEATH,40);
    set_spell_form(SS_FORM_CONJURATION,40);
    set_spell_time(3);
    set_spell_mana(100);
    set_spell_ingredients(({"bloodweed","coccinea","tooth"})); 
    set_find_target(target_lterror);
    set_spell_message(lterror_mess);
    set_spell_task(TASK_ROUTINE,0);
}

object
*target_lterror(string arg)
{
    if(query_caster()->query_terror_shadow())
    {
        tell_object(query_caster(),"You already have terror around you.\n");
        return ({});
    }
    return ({query_caster()});
}

void
lterror_mess(object caster, object *targets)
{
    int time;
    object tsh;
    seteuid(getuid());
    time = caster->query_stat(SS_WIS) / 2;
    tsh = clone_object(LP_DIR(obj/terror_sh));
    tsh->shadow_me(caster);
    tsh->set_remove_time(time);
}

