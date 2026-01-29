/*
 * /d/Kalad/common/guilds/khiraa/dk/spells/kinfra.c
 * Purpose    : The spell that will allow caster to see in the dark.
 * Located    : Death Knight spell
 * Created By : Sarr  17.Mar.97
 * Modified By: 
 *      Sarr 28.Feb.98
 *      Sarr 26.May.98 (updates to new spellcasting.c)
 */


void
infra_conc(object caster, object* targets, string arg)
{

    tell_object(caster,"You stroke your "+TO->short()+" as you "+
    "utter a prayer to the Horror.\n");

    tell_room(E(caster),QCTNAME(caster)+" strokes "+HIS(caster)+
    " "+TO->short()+" as "+HE(caster)+" utters a prayer.\n",caster);

}

void
do_spell_kinfra(object caster, object *targets)
{
    object target, *sh;
    int time, power;
    target = targets[0];

    time = 600.0 + itof(caster->query_stat(SS_WIS));

    power = 1;

    if(caster->query_guild_order() > 4)
        power = 2;
    sh = make_spell_effect_object(DK_DIR+"obj/infra_sh",caster,targets,0,0);
    sh->set_spell_effect_desc("infravison");

    sh->set_remove_time(time,power);
}

int
create_spell_kinfra(object caster, object *targets, string arg)
{

    if(!check_ok_cast(caster))
        return 1;
    if(caster->query_infra_shadow())
    {
        tell_object(caster,"You are already under the effects of this "+
        "spell.\n");
        return 1;
    }

    set_spell_effect(do_spell_kinfra);
    set_spell_element(SS_ELEMENT_DEATH,10);
    set_spell_form(SS_FORM_ENCHANTMENT,10);
    set_spell_time(3);
    set_spell_ingredients(({"redeye"}));
    set_spell_mana(20);
    set_spell_task(TASK_SIMPLE);
    set_spell_conc_message(infra_conc);

    return 0;
}

