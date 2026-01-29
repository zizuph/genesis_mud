/* Sarr */

string gMessage;

void
do_spell_ltell(object caster, object *targets)
{
    object target = targets[0];

    tell_object(caster,"Through the power of the Netherworld, "+
    "you send a thought to "+target->query_the_name(caster)+": "+
    gMessage+"\n");

    tell_object(target,"An image of "+caster->query_art_name(target)+
    " enters your mind, and a soft voice whispers: "+gMessage+"\n");

}

object *
target_tell_message(object caster, string arg)
{
    string who, what;
    if(!stringp(arg))
    {
        tell_object(caster,"You must cast ltell <who> <what>.\n");
        return ({});
    }
    if(sscanf(arg,"%s %s",who, what) != 2)
    {
        tell_object(caster,"You must cast ltell <who> <what>.\n");
        return ({});
    }
    gMessage = what;
    return spell_target_one_distant_living(caster,who);
}

void
ltell_conc(object caster, object* targets, string arg)
{
    tell_object(caster,"You shut your eyes and utter a prayer.\n");
    tell_room(E(caster),QCTNAME(caster)+" shuts "+HIS(caster)+" "+
    "eyes and utters something you can't understand.\n",caster);
}

int
create_spell_ltell(object caster, object *targets, string arg)
{
    if(!check_ok_cast(caster))
        return 1;
    set_spell_element(SS_ELEMENT_DEATH,5);
    set_spell_form(SS_FORM_TRANSMUTATION,5);
    set_spell_time(2);
    if(IS_DK(targets[0]) || IS_LP(targets[0]))
        set_spell_mana(10);
    else
        set_spell_mana(20);
    set_spell_effect(do_spell_ltell);
    set_spell_stationary(0);
    set_spell_vocal(0);
    set_spell_task(TASK_SIMPLE);
    set_spell_conc_message(ltell_conc);
    return 0;
}

