/*
 * /d/Kalad/common/guilds/khiraa/lp/spells/lfear.c
 * Purpose    : The spell that will create fear in enemies.
 * Located    : Lich create fear.
 * Created By : Sarr  17.Mar.97
 * Modified By: 
 */

void
kfear_conc(object caster, object* targets, string arg)
{
    tell_object(caster,"You chant dark and unholy words as your "+
    "hands begin glow with a purple aura.\n");
    tell_room(E(caster),QCTNAME(caster)+" chants unholy sounding "+
    "words as "+HIS(caster)+" hands begin to glow with a purple aura.\n",
    caster);
}

void
do_spell_kfear(object caster, object *targets, int *resist, int result)
{
    int my_int,i;
    object *peeps;
    
    my_int = caster->query_stat(SS_WIS);

    tell_room(E(caster),"Waves of black fear radiate from "+
    QTNAME(caster)+"'s hands!\n",caster);
    tell_object(caster,"Waves of black fear radiate from your hands!\n");

    for(i=0;i<sizeof(targets);i++)
    {
        if(IS_DK(targets[i]) || IS_LP(targets[i]))
            return;
        if(resist[i] > 0)
        {
            tell_object(targets[i],"You feel a slight chill along "+
            "your spine.\n");
            return;
        }
        if(!targets[i]->query_prop(NPC_I_NO_RUN_AWAY))
        {
            tell_object(targets[i],"Choking, black fear grips your "+
            "heart, and you run away as fast as you can!!\n");
            targets[i]->add_panic(caster->query_stat(SS_OCCUP) / 2);
            targets[i]->run_away();
        }
    }
}

int
kfear_resist(object caster, object target, int ele, int diff, int succ)
{
    int res;

    res = target->resolve_task(diff, ({TS_DIS,SS_FORM_ABJURATION}),
              caster, ({TS_WIS, SS_SPELLCRAFT}) );

    return res;
}

int
create_spell_kfear(object caster, object *targets, string arg)
{
    if(!check_ok_cast(caster))
        return 1; 
    set_spell_element(SS_ELEMENT_DEATH,10);
    set_spell_form(SS_FORM_TRANSMUTATION,10);
    set_spell_ingredients(({"hemlock","skull","scalp"})); 
    set_spell_time(4);
    set_spell_mana(35);
    set_spell_effect(do_spell_kfear);
    set_spell_task(TASK_ROUTINE);
    set_spell_conc_message(kfear_conc);
    set_spell_resist(kfear_resist);
    set_spell_resist_task(TASK_DIFFICULT);
    return 0;
}
