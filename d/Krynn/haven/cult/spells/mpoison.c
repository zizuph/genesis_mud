object *target_mpoison(string str);
void mpoison_mess(object caster, object *targets);

string
mpoison_fail()
{
    return "The spell slips from your mental grasp, and fails.\n";
}

int
do_mpoison()
{
    return cast_spell();
}

void
create_spell_mpoison(string arg)
{
    set_spell_element(SS_ELEMENT_DEATH,20);
    set_spell_form(SS_FORM_ENCHANTMENT,20);
    set_spell_time(3);
    set_spell_mana(50);
    set_find_target(target_mpoison);
    set_spell_ingredients(({"handful of dirt"}));
    set_spell_message(mpoison_mess);
    set_spell_task(TASK_ROUTINE,0);
    set_spell_fail(mpoison_fail);
}

object
*target_mpoison(string arg)
{
    object *obs,ob;
    set_this_player(query_caster());
    if(!arg)
    {
	write("You need to specify a target.\n");
	return ({});
    }
    obs = PARSE_THIS(arg,"[the] %l");
    if(!sizeof(obs))
    {
	write("You find no such living being.\n");
	return ({});
    }
    ob = obs[0];

    /* Commented out for now...
    if(TP->query_rank_level() == 0)
    set_spell_task(TASK_DIFFICULT,0);
    if(TP->query_rank_level() == 1)
    set_spell_task(TASK_ROUTINE,0);
    if(TP->query_rank_level() == 2)
    set_spell_task(TASK_ROUTINE,0);
    */

    return ({ob});
}

void
mpoison_mess(object caster, object *targets)
{
    float time;
    object target,poison;
    target = targets[0];
    time = itof(10);
    target->catch_msg(QCTNAME(caster)+" suddenly tosses a handful of "+
      "dirt onto your skin!\n");
    caster->catch_msg("You jerk your hand up, tossing the handful of dirt "+
      "onto "+QTNAME(target)+"'s skin.\n");
    caster->tell_watcher(QCTNAME(caster)+" suddenly tosses a handful of "+
      "dirt onto "+QTNAME(target)+"'s skin!\n", target);
    seteuid(getuid());
    poison = clone_object("/d/Krynn/haven/cult/obj/madness");
    poison->move(target);
    poison->set_power_level(9);
    poison->start_poison();
}

