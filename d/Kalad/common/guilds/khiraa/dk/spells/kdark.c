/*
 * /d/Kalad/common/guilds/khiraa/dk/spells/kdark.c
 * Purpose    : The spell that will create a dark coin from a coin.
 * Located    : Death Knight spell
 * Created By : Sarr  17.Mar.97
 * Modified By: 
 *    Sarr 6.Mar.98
 */

void
kdark_conc(object caster, object *targets, string arg)
{
    tell_object(caster,"A black light shines from your hands "+
    "as you chant unholy words to the Horror.\n");
    tell_room(E(caster),"A black light shines from "+QTNAME(caster)+
    "'s hands as "+HE(caster)+" chants eerie words.\n",caster);
}

void
do_spell_kdark(object caster, object *targets)
{
    object d_coin;
    float time;

    d_coin = clone_object(DK_DIR+"obj/black_coin");

    tell_object(caster,"You create a dark coin from the coin "+
    "you sacrificed to Him.\n");
    tell_room(E(caster),QCTNAME(caster)+" creates a dark coin that "+
    "makes the room darker.\n",caster);

    d_coin->move(caster);
    time = itof(3 * (TP->query_stat(SS_INT) + 100) );
    d_coin->set_coin_remove_time(time);
}


void
create_spell_kdark(object caster, object *targets, string arg)
{
    if(!check_ok_cast(caster))
        return 0;
    set_spell_element(SS_ELEMENT_DEATH,10);
    set_spell_form(SS_FORM_TRANSMUTATION,10);
    set_spell_ingredients(({"coin","dajla"}));
    set_spell_time(5);
    set_spell_mana(20);
    set_spell_effect(do_spell_kdark);
    set_spell_task(TASK_SIMPLE);
    set_spell_conc_message(kdark_conc);
    return 0;
}
