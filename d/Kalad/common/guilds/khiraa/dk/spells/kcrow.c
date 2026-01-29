/*
 * /d/Kalad/common/guilds/khiraa/dk/spells/kcrow.c
 * Purpose    : The spell that will summon a crow from Raumdor.
 * Located    : Death Knight spell
 * Created By : Sarr  17.Mar.97
 * Modified By: 
 *   Sarr 2.Mar.98 (fix)
 */

void
kcrow_conc(object caster, object *targets, string arg)
{
    tell_object(caster, "You bow your head and utter a prayer to the "+
    "Horror.\n");
    tell_room(E(caster),QCTNAME(caster)+" bows "+HIS(caster)+" head "+
    "and utters a prayer.\n",caster);
}

void
do_spell_kcrow(object caster, object *targets)
{
    object crow;

    crow = clone_object(DK_DIR+"obj/crow");

    tell_object(caster,"An "+crow->short()+" suddenly forms from the "+
    "black feathery leaf and it hops on your shoulder.\n");

    tell_room(E(caster),"A black feathery leaf held by "+QTNAME(caster)+
    " suddenly turns into an "+crow->short()+" that hops on "+HIS(caster)+
    " shoulder!\n",caster);

    crow->move(caster);
}

int
create_spell_kcrow(object caster, object *targets, string arg)
{
    if(!check_ok_cast(caster))
        return 1;

    set_spell_effect(do_spell_kcrow);
    set_spell_element(SS_ELEMENT_DEATH,10);
    set_spell_form(SS_FORM_TRANSMUTATION,10);
    set_spell_ingredients(({"darfern"}));
    set_spell_time(3);
    set_spell_mana(10);
    set_spell_task(TASK_SIMPLE);
    set_spell_conc_message(kcrow_conc);
    return 0;
}
