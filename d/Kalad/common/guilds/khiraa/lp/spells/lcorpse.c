/* Sarr */

void
do_lcorpse_spell(object caster, object *targets)
{
    object corpse,*obs;
    string str2,kname;
    int i;
    corpse = targets[0];

    if(caster->query_armour(A_R_HAND))
        str2 = "armoured";
    else
        str2 = "skeletal";

    if(!sizeof(corpse->query_prop(CORPSE_AS_KILLER)))
    {
        tell_object(caster,"You feel powers blocking you from revealing its killer.\n");
        return;
    }
    kname = corpse->query_prop(CORPSE_AS_KILLER)[0];

    tell_object(caster,"You kneel down and place your "+str2+" hand on the "+
    corpse->short()+".\n");
    tell_room(E(caster),QCTNAME(caster)+" kneels down and places "+HIS(caster)+
    " "+str2+" hand on the "+corpse->short()+".\n",caster);
    tell_room(E(caster),"The "+corpse->short()+" suddenly sits up and "+
    "shrieks: "+CAP(kname)+"!\n");

    obs = FILTER_OTHER_LIVE(all_inventory(E(caster)));
    for(i=0;i<sizeof(obs);i++)
    {
        if(!obs[i]->query_prop(LIVE_I_UNDEAD))
        {
            tell_object(obs[i],"You shudder and put your hands to your "+
            "ears to stop from hearing to that horrible scream.\n");
            tell_room(E(obs[i]),QCTNAME(obs[i])+" shudders and puts "+
            HIS(obs[i])+" hands to "+HIS(obs[i])+" ears to stop from "+
            "hearing that horrible scream.\n",obs[i]);
        }
    }
} 

public void
conc_lcorpse_mess(object caster, object *targets, string arg)
{
    tell_object(caster,"You kneel to the ground as you utter the unholy "+
    "prayers to the Horror; your hands beging to glow an eerie blue.\n");
    tell_room(ENV(caster),QCTNAME(caster)+" slowly kneels to the ground as "+
    HIS(caster)+" hands begin to glow an eerie blue and utters unholy "+
    "words.\n", caster);
}

public int
create_spell_lcorpse(object caster, object *targets, string arg)
{
    if(!check_ok_cast(caster))
        return 1;
    if(!targets[0]->id("corpse") || living(targets[0]) )
    {
        tell_object(caster,"That is not a corpse.\n");
        return 1;
    }
    set_spell_element(SS_ELEMENT_DEATH,10);
    set_spell_form(SS_FORM_DIVINATION,15);
    set_spell_time(5);
    set_spell_mana(40);
    set_spell_ingredients(({"vinerot","mindleech"})); 
    set_spell_target_verify(spell_verify_present);
    set_spell_effect(do_lcorpse_spell);
    set_spell_task(TASK_ROUTINE);
    set_spell_conc_message(conc_lcorpse_mess);
    return 0;
}

