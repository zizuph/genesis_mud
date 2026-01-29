/* Sarr */

void
rot_corpse(object ob)
{
    int i,j;
    object lft,*things;
    mixed leftovers = ob->query_leftover();

    for(i = 0; i <sizeof(leftovers); i++)
    {
        for(j = 0; j < leftovers[i][2]; j++)
        {
            lft = clone_object(leftovers[i][0]);
            lft->leftover_init(leftovers[i][1],
                ob->query_prop(CORPSE_S_RACE));
            lft->move(E(ob),0);
        }
    }

    things = all_inventory(ob);
    for(i = 0; i < sizeof(things);i++)
    {
        if(things[i]->move(E(ob)) )
            things[i]->remove_object();
    }
    tell_room(E(ob),"The "+ob->short()+" suddenly shrinks and dries up "+
    "into a pile of dust that blows away.\n");

    ob->remove_object();
}

void
do_lrot_spell(object caster, object *targets)
{
    int i;
    object *corpses;

    corpses = filter(all_inventory(E(caster)),is_real_corpse);

    tell_object(caster,"Black nauseating waves of death and "+
    "decay eminate from your body.\n");

    tell_room(E(caster),"Black nauseating waves of death and "+
    "decay eminate from "+QTNAME(caster)+"'s body.\n",({caster}));

    for(i = 0; i < sizeof(corpses); i++)
        rot_corpse(corpses[i]);
}

public int
conc_lrot_mess(object caster, object *targets, string arg)
{
    tell_object(caster,"Your hands begin to pulsate with a putrid "+
    "aura as you chant your unholy prayer.\n");
    tell_room(ENV(caster),QCTNAME(caster)+"'s hands begin to pulsate "+
    "with a putrid aura as "+HE(caster)+" chants unholy words.\n",caster);
}

public int
create_spell_lrot(object caster, object *targets, string arg)
{
    if(!check_ok_cast(caster))
        return 1;
    if(!present("_miseryob_",caster))
    {
        tell_object(caster,"You must be under the effects "+
        "of a misery potion!\n");
        return 1;
    }

    set_spell_element(SS_ELEMENT_DEATH,5);
    set_spell_form(SS_FORM_TRANSMUTATION,5);
    set_spell_time(1);
    set_spell_mana(5);
    set_spell_effect(do_lrot_spell);
    set_spell_task(TASK_ROUTINE);
    set_spell_conc_message(conc_lrot_mess);

    return 0;
}

