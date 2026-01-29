/* Sarr */

int drain_amount;


object *
target_ldrainm(object caster, string arg)
{
    int amt;
    string st2;
    object ob,*obs;

    if(!stringp(arg) || sscanf(arg,"%s by %d",st2,amt) != 2)
    {
        tell_object(caster,"Cast ldrainm <target> by <amount>\n");
        return ({});
    }

    if(member_array(amt,({2,3,4,6,8}) ) == -1)
    {
        tell_object(caster,"You cannot drain yourself by that amount.\n");
        return ({});
    }

    drain_amount = amt;
    obs = PARSE_THIS(st2,"[the] %l");
    if(sizeof(obs))
        ob = obs[0];
    if(ob && present(ob,environment(caster)) )
    {
        return ({ob});
    }

    tell_object(caster,"There is no such mortal present.\n");
    return ({});
}

void
do_ldrainm_spell(object caster, object *targets, int *re, int resu)
{
    int hp_trans;
    object target;
    target = targets[0];

    tell_object(caster,"You embrace "+target->query_the_name(caster)+
    " tightly, and you feel 1/"+drain_amount+" of your current life "+
    "force leave you and flow into "+HIS(target)+".\n");

    tell_object(target,caster->query_The_name(target)+" embraces you "+
    "tightly, and you feel new health flow into your body.\n");
    tell_room(E(caster),QCTNAME(caster)+" embraces "+QTNAME(target)+
    " tightly, and their bodies glow slightly.\n",({target,caster}));

    hp_trans = caster->query_hp() / drain_amount;
    caster->heal_hp(-hp_trans);
    hp_trans = hp_trans * 2; /* ratio 1/2 */
    target->heal_hp(hp_trans);
}

public int
create_spell_ldrainm(object caster, object *targets, string arg)
{
    if(!check_ok_cast(caster))
        return 1;
    if(!present("skaltakur_ob",caster))
    {
        tell_object(caster,"You must be under the influence of "+
        "a skaltakur potion.\n");
        return 1;
    }

    set_spell_element(SS_ELEMENT_DEATH,55);
    set_spell_form(SS_FORM_TRANSMUTATION,40);
    set_spell_time(2);
    set_spell_mana(100);
    set_spell_ingredients(({"skull"}));
    set_spell_target_verify(spell_verify_present);
    set_spell_task(TASK_ROUTINE);
    set_spell_conc_message(conc_message_drain);
    set_spell_effect(do_ldrainm_spell);
    set_spell_stationary(0);
    set_spell_no_reveal(0);
    
    return 0;
}

