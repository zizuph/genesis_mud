/* Sarr */

void
do_lshadow_spell(object caster, object *targets, int *r, int re)
{
    object *shad;
    int time;
    shad = make_spell_effect_object(LP_DIR+"obj/shadow_sh",caster,targets,0,0);
    time = (3 * caster->query_stat(SS_WIS)) + caster->query_stat(SS_INT) +
           (2 * caster->query_stat(SS_OCCUP));
    shad->set_spell_effect_desc("shadow defense");
    shad->set_remove_time(time);
}

void
conc_lshadow_mess(object caster, object *targets, string arg)
{
    tell_object(caster,"You utter the unholy incantation to the Horror as "+
    "a black light begins to shine from your broken form.\n");
    tell_room(ENV(caster),QCTNAME(caster)+" utters some unholy incantation "+
    "as a black light begins to shine from "+HIS(caster)+" broken form.\n",caster);

}

public int 
create_spell_lshadow(object caster, object *targets, string arg)
{
    if(!check_ok_cast(caster))
        return 1;
    if(caster->query_shadow_shadow())
    {
        tell_object(caster,"You are already under the effects of Shadow Defense.\n");
        return 1;
    }
    set_spell_element(SS_ELEMENT_DEATH,40);
    set_spell_form(SS_FORM_CONJURATION,30);
    set_spell_time(3);
    set_spell_mana(80);
    set_spell_ingredients(({"pepper","rib","lore"})); 
    set_spell_stationary(0);
    set_spell_effect(do_lshadow_spell);
    set_spell_conc_message(conc_lshadow_mess);
    set_spell_target_verify(spell_verify_present);
    set_spell_task(TASK_ROUTINE);
    return 0;
}

