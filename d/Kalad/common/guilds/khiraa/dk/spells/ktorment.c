/* Sarr 
 * 10.March.98
 */

void
ktorment_conc(object caster, object *targets, string arg)
{
    tell_object(caster,"Your eyes begin to glow a sickly yellow "+
    "color as you chant your unholy prayer.\n");
    tell_room(E(caster),QCTNAME(caster)+"'s eyes begin to glow a "+
    "sickly yellow color as "+HE(caster)+" chants unholy sounding "+
    "words.\n",caster);
}


void
do_spell_ktorment(object caster, object *targets)
{
    object head_ob;    
    object ob = targets[0];

    if(ob->id("head"))
    {
        tell_object(caster,"You wave your head over the "+ob->singular_short()+
        ", chanting unholy words.\n");
        tell_room(E(caster),QCTNAME(caster)+" waves "+HIS(caster)+" hand over "+
        "the "+ob->singular_short()+", chanting unholy words.\n",caster);
        tell_room(E(caster),"The "+ob->singular_short()+" glows for a moment.\n");
        
        head_ob = clone_object(LP_DIR+"obj/torment_head");
        head_ob->set_name( ob->query_name() );
        head_ob->set_short(ob->singular_short());
        head_ob->add_adj( ob->query_adj(1));
        head_ob->set_long(ob->long());
        if(head_ob->move( E(ob) ) )
            head_ob->move( E( E(ob) ) );
        ob->set_heap_size(ob->num_heap() - 1);
        if(ob->num_heap() <= 0)
            ob->remove_object();
        return;
    }
    if(ob->id("hand"))
    {
        tell_object(caster,"You wave your head over the "+ob->short()+
        ", chanting unholy words.\n");
        tell_room(E(caster),QCTNAME(caster)+" waves "+HIS(caster)+" hand over "+
        "the "+ob->short()+", chanting unholy words.\n",caster);
        tell_room(E(caster),"The "+ob->short()+" starts to wiggle!\n");
        head_ob = clone_object(LP_DIR+"obj/mini_druj");
        head_ob->set_race(ob->query_race());
        if(living(E(ob)))
            head_ob->move( E( E(ob) ) );
        else
            head_ob->move(E(ob));
        ob->remove_object();
        return;
    }        
    tell_object(caster,"The spell has no effect on the "+ob->short()+".\n");
}

int
create_spell_ktorment(object caster, object *targets, string arg)
{
    if(!check_ok_cast(caster))
        return 1;
    if(!targets[0]->id("head") &&
       ("/std/leftover" != function_exists("create_food",targets[0])) &&
       MASTER_OB(targets[0]) != KHIRAA+"temple/obj/bloody_hand")
    {
        tell_object(caster,"You cannot cast this on that!\n");
        return 1;
    }
    set_spell_element(SS_ELEMENT_DEATH,10);
    set_spell_form(SS_FORM_TRANSMUTATION,5);
    set_spell_time(3);
    set_spell_mana(15);
    set_spell_effect(do_spell_ktorment);
    set_spell_task(TASK_SIMPLE);
    set_spell_conc_message(ktorment_conc);
    return 0;
}

