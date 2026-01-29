/* Sarr */


void
conc_lbanshee_mess(object caster, object *targets, string arg)
{
    tell_object(caster,"You chant horridly as you raise your ethereal-mist "+
    "covered hands above your head, invoking the power of the Horror!\n");
    tell_room(ENV(caster),QCTNAME(caster)+" chants horrible words as "+HE(caster)+
    "raises "+HIS(caster)+" ethereal-mist covered hands above "+HIS(caster)+
    " head!\n",caster);
}

int
lbanshee_resist(object caster, object target, int element, int diff)
{
    int res;
    res = target->resolve_task(diff, ({ SKILL_WEIGHT, 60, TS_DIS, SKILL_AVG,
        SS_FORM_ABJURATION, SS_SPELLCRAFT, SKILL_END, SS_ELEMENT_LIFE }) );
    res = MIN(0,MAX(100,res) );
    res += combine_resistances(target, ({ MAGIC_I_RES_MAGIC, MAGIC_I_RES_COLD,
               resistance_map[element] }) );
}

int
am_undead(object ob)
{
    if(ob->query_prop(LIVE_I_UNDEAD))
        return 0;
    return 1;
}

public object *
target_lbanshee(object caster, string arg)
{
    // Target all living creatures
    object *obs = FILTER_LIVE(all_inventory(ENV(caster)));
    obs = filter(obs,am_undead);
    if(!sizeof(obs))
        tell_object(caster,"There is no one in the area that would be affected "+
        "by this spell.\n");
    return obs;
}

void
do_lbanshee_spell(object caster, object *targets, int *resist, int result)
{
    int i,time;
    object *stn;
    
    tell_room(ENV(caster),"The room is suddenly filled with a swirling horde "+
    "of ghastly, lost souls that shriek out a horrible wail of utter "+
    "missery and desperation!\n");
    tell_object(caster,"Result: "+result+"\n");

    for(i=0;i<sizeof(targets);i++)
    {
        if(targets[i]->query_stun_shadow())
            continue; // Don't stun already stunned

        time = MAX(1,result * 2) - (targets[i]->query_stat(SS_DIS)/2);

        time -= ( resist[i] * time) / 100;

        tell_object(caster,"Target "+i+": "+file_name(targets[i])+"\n"+
                           "    Total Time: "+time+"\n"+
                           "    Resist: "+resist[i]+"\n");

        if(time <= 0 || result < resist[i] )
        {
            tell_object(targets[i],"Despite the terror you feel, your "+
            "iron courage allows you to remain strong.\n");
        }
        else
        {
            tell_object(targets[i],"You colapse in terrible agony and "+
            "despair, unable to do anything!\n");
            
            tell_room(ENV(targets[i]),QCTNAME(targets[i])+" colapses "+
            "to the ground in a pathetic quivering heap.\n",targets[i]);

            stn = make_spell_effect_object(LP_DIR+"obj/stun_sh",
                   caster,targets[i],0,0);
            stn->set_spell_effect_desc("banshee stun");
            stn->set_remove_time(time);
        }
    }
} 

public int
create_spell_lbanshee(object caster, object *members, string arg)
{
    if(!check_ok_cast(caster))
        return 1;

    set_spell_element(SS_ELEMENT_DEATH,70);
    set_spell_form(SS_FORM_CONJURATION,60);
    set_spell_time(4);
    set_spell_mana(180);
    set_spell_stationary(0);
    set_spell_offensive(1);
    set_spell_target_verify(spell_verify_present);    

    set_spell_resist(lbanshee_resist);
    set_spell_resist_task(TASK_DIFFICULT);
    set_spell_conc_message(conc_lbanshee_mess);

    set_spell_ingredients(({"mindleech","nightshade","skull","heart"})); 
    set_spell_effect(do_lbanshee_spell);
    set_spell_task(TASK_ROUTINE);
    return 0;
}

