/* Sarr 2.March.98
 */

void
do_burnt_leftover(object room, string race)
{
    object lo;
    lo = clone_object("/std/leftover");
    lo->leftover_init("arm",race);
    lo->set_short("charred "+race+" arm");
    lo->add_adj("charred");
    lo->set_long("This is a charred and burnt arm of a poor "+
    "and unfortunate "+race+".\n");
    lo->move(room);

    lo = clone_object("/std/leftover");
    lo->leftover_init("leg",race);
    lo->set_short("charred "+race+" leg");
    lo->add_adj("charred");
    lo->set_long("This is a charred and burnt leg of a poor "+
    "and unfortunate "+race+".\n");
    lo->move(room);

    lo = clone_object("/std/leftover");
    lo->leftover_init("arm",race);
    lo->set_short("charred "+race+" arm");
    lo->add_adj("charred");
    lo->set_long("This is a charred and burnt arm of a poor "+
    "and unfortunate "+race+".\n");
    lo->move(room);

    lo = clone_object("/std/leftover");
    lo->leftover_init("foot",race);
    lo->set_short("charred "+race+" foot");
    lo->add_adj("charred");
    lo->set_long("This is a charred and burnt foot of a poor "+
    "and unfortunate "+race+".\n");
    lo->move(room);

    lo = clone_object("/std/leftover");
    lo->leftover_init("stomach",race);
    lo->set_short("charred "+race+" stomach");
    lo->add_adj("charred");
    lo->set_long("This is a charred and burnt stomach of a poor "+
    "and unfortunate "+race+".\n");
    lo->move(room);

    lo = clone_object("/std/leftover");
    lo->leftover_init("head",race);
    lo->set_short("charred "+race+" head");
    lo->add_adj("charred");
    lo->set_long("This is a charred and burnt dismembered head of a poor "+
    "and unfortunate "+race+".\n");
    lo->move(room);

}

void
kflame_conc(object caster, object *targets, string arg)
{
    tell_object(caster,"Your hands begin to glow fire-red as you "+
    "chant a prayer to the Horror.\n");
    tell_room(E(caster),QCTNAME(caster)+"'s hands begin to glow fire-red "+
    "as "+HE(caster)+" chants dark words.\n",caster);
}

void
do_spell_kflame(object caster, object *targets, int *resist, int result)
{
    mixed hr;
    string str;
    int pen, i;
    object lo;
    object target = targets[0];
    
    if(resist[0] < 0)
        resist = 0;

    pen = result * 4;

    pen -= (resist[0] * pen / 100);

    str = "slight ";

    hr = target->hit_me(pen,MAGIC_DT,caster,-1);

    if(IS_GUILD_MASTER(caster))
        tell_object(caster,"Stats: \n"+
            "Pen: "+pen+"\n"+
            "Perc: "+hr[0]+"\n"+
            "Dam: "+hr[2]+"\n");

    if(hr[0] == -1)
        str = "no ";
    if(hr[0] > 20)
        str = "some ";
    if(hr[0] > 30)
        str = "";
    if(hr[0] > 40)
        str = "solid ";
    if(hr[0] > 50)
        str = "much ";
    if(hr[0] > 60)
        str = "strong ";
    if(hr[0] > 70)
        str = "great ";
    if(hr[0] > 80)
        str = "massive ";

    tell_object(caster,"You throw the copper coin into the air and "+
    "wave your hand across it, and it turns into a flaming arrow that "+
    "slams into "+target->query_the_name(caster)+"'s "+hr[1]+", doing "+
    str+"damage.\n");

    tell_object(target,caster->query_The_name(target)+" waves "+
    HIS(caster)+" hand through the air, and suddenly a flaming arrow "+
    "appears and slams straight into your "+hr[1]+", doing "+str+"damage.\n");

    tell_room(E(caster),QCTNAME(caster)+" waves "+HIS(caster)+" hand "+
    "through the air, and suddenly a flaming arrow appears and slams "+
    "into "+QTNAME(target)+"'s "+hr[1]+", doing "+str+"damage.\n",
    ({caster,target}));

    if(target->query_hp() <= 0)
    {
        if(!target->query_prop(LIVE_I_NO_CORPSE))
        {
            target->add_prop(LIVE_I_NO_CORPSE,1);
            do_burnt_leftover(E(target),target->query_race_name());
            tell_room(E(caster),QCTNAME(target)+" explodes into many "+
            "chunks of burning flesh!\n",({target}));
            tell_object(target,"You explode into many chunks of burning "+
            "flesh!\n");
        }
        target->do_die(caster);
    }
}

int
create_spell_kflame(object caster, object *targets, string arg)
{
    if(!check_ok_cast(caster))
        return 1;

    set_spell_element(SS_ELEMENT_FIRE,20);
    set_spell_form(SS_FORM_TRANSMUTATION,30);
    set_spell_time(4);
    set_spell_mana(38);
    set_spell_ingredients(({"copper coin","flameroot"}));
    set_spell_effect(do_spell_kflame);
    set_spell_task(TASK_ROUTINE);
    set_spell_stationary(0);
    set_spell_no_reveal(0);
    set_spell_offensive(1);
    set_spell_conc_message(kflame_conc);
    set_spell_resist_task(TASK_DIFFICULT);
    
    return 0;

}
