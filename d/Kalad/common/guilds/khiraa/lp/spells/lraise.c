/* Sarr */

int
is_real_corpse(object ob)
{
    if(!living(ob) && ob->id("corpse"))
        return 1;
    return 0;
}


object
*target_lraise(object caster, string arg)
{
    object me,*corpses,*temp;
    int amt, i, x_mana;

    me = caster;

    if(!arg)
    {
        tell_object(me,"You must specify the number of corpses you "+
        "wish to raise, which must be from 1-10.\n");
        return ({});   
    }
    sscanf(arg,"%d",amt);
    if(amt > 10 || amt < 1)
    {
        tell_object(me,"You may only specify a number from 1 to 10.\n");
        return ({});   
    }

    x_mana = amt * 10;
    if(me->query_mana() < x_mana)
    {
        tell_object(me,"You don't have the mana to summon "+amt+
        " corpse(s).\n");
        return ({});
    }

    corpses = all_inventory(E(me));
    corpses = filter(corpses,is_real_corpse);

    if(sizeof(corpses) < amt)
    {
        tell_object(me,"There are not "+amt+" corpse(s) in the room "+
        "you are in.\n");
        return ({});
    }

    if(objectp(present("_zombiec_",me)))
    {
        if(amt + present("_zombiec_",me)->query_zombies() > 10)
        {
            tell_object(me,"You cannot raise that many zombies, "+
            "you can only have a max of 10 under your control.\n");
            return ({});
        }
    }

    if(sizeof(corpses) > amt)
    {
        for(i = 0; i < amt; i++)
        {
            temp += ({ corpses[i] });
        } 
        return temp;
    }

    return corpses;
}

void
raise_the_dead(object caster, object corpse)
{
    int i;
    string ar,*adjl;
    object zombie,*items,ct;
    zombie = clone_object(LP_DIR+"obj/animated_corpse");
    items = all_inventory(corpse);
    for(i=0;i<sizeof(items);i++)
        items[i]->move(zombie);
    zombie->set_name(corpse->query_name());
    zombie->set_race_name("zombie");
    zombie->set_gender(corpse->query_gender());

    if(corpse->query_prop(DK_AS_CORPSE))
    {
        zombie->set_long(corpse->query_prop(DK_AS_CORPSE)[0]+
        CAP(HE(zombie))+" looks fresh from the grave.\n");
        adjl = corpse->query_prop(DK_AS_CORPSE)[1];
        for(i=0;i<sizeof(adjl);i++)
            zombie->add_adj(adjl[i]);
    }
    else
        zombie->set_short("zombie "+corpse->query_nonmet_name());
    zombie->set_master(caster);
    tell_room(E(corpse),"The "+corpse->short()+" suddenly glows "+
    "with a fierce red light and springs into motion with inhuman "+
    "rage!\n");
    ct = present("_zombiec_",caster);
    if(!objectp(ct))
    {
        ct = clone_object(LP_DIR+"obj/zombiec");
        ct->move(caster);
    }
    ct->add_zombie(zombie);
    corpse->remove_object();
    zombie->move(E(caster));
    zombie->command("wear all");
}

void
do_lraise_spell(object caster, object *targets, int *r, int res)
{
    int i,x_mana,amt;
    x_mana = sizeof(targets) * 10;

    tell_object(caster,"You extend your arms from your sides, and drawing "+
    "power from the Netherworld, you intone: Rise.\n");

    tell_room(E(caster),QCTNAME(caster)+" extends "+HIS(caster)+" arms "+
    "from "+HIS(caster)+" sides, and while closing "+HIS(caster)+" eyes "+
    "intones in a hollow voice: Rise.\n",({caster}));

    amt = res / 5;

    if(amt < sizeof(targets))
    {
        tell_object(caster,"You attempt to raise "+sizeof(targets)+" "+
        "corpses, but are only able to raise "+amt+".\n");
    }

    if(amt > sizeof(targets))
        amt = sizeof(targets);

    for(i = 0; i < amt; i++)
        raise_the_dead(caster,targets[i]);

    tell_object(caster,"You feel your lifeforce drain from this "+
    "powerful prayer.\n");

    caster->add_mana(-x_mana);
    caster->heal_hp(-100);
    if(caster->query_hp() <= 0)
        caster->do_die(TO);
}

public void
conc_lraise_mess(object caster, object *targets, string arg)
{
    tell_object(caster,"Dark mist gathers around you as you chant the "+
    "most unholy prayer of the Horror.\n");
    tell_room(E(caster),"Dark mist gathers around "+QTNAME(caster)+" as "+
    HE(caster)+" chants gruesome sounding words. His hands glow with "+
    "a black light.\n",caster);
}

public int
create_spell_lraise(object caster, object *targets, string arg)
{
    if(!check_ok_cast(caster))
        return 1;

    set_spell_element(SS_ELEMENT_DEATH,65);
    set_spell_form(SS_FORM_TRANSMUTATION,50);
    set_spell_time(5);
    set_spell_ingredients(({"nightshade","attanar","redeye"}));
    set_spell_mana(140);
    set_spell_effect(do_lraise_spell);
    set_spell_conc_message(conc_lraise_mess);

    set_spell_task(TASK_ROUTINE + 200);
    return 0;
}

