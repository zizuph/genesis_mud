/* Sarr */


public void
do_lbone_spell(object caster, object *targets, int *r, int re)
{
    object *shield;
    int time;

    shield = make_spell_effect_object(LP_DIR+"obj/bone_shield",caster,targets,0,0);
    shield->set_spell_effect_desc("bone shield");
    time = random(101) * 2 + (4 * caster->query_stat(SS_WIS)) + 
       caster->query_stat(SS_INT);
    shield->set_remove_time(time);
}


public int 
create_spell_lbone(object caster, object *targets, string arg)
{
    if(!check_ok_cast(caster))
        return 1;
    set_spell_element(SS_ELEMENT_DEATH,50);
    set_spell_form(SS_FORM_CONJURATION,40);
    set_spell_time(4);
    set_spell_mana(100);
    set_spell_ingredients(({"three ribs","skull","blade"}));
    set_spell_target_verify(spell_verify_present);
    set_spell_effect(do_lbone_spell);
    set_spell_conc_message(conc_lshadow_mess);
    set_spell_task(TASK_ROUTINE);
    return 0;
}

