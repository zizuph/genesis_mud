/* Sarr */

#define DK_DEATH_TIMES  "_dk_death_times"

void
kblade_conc(object caster, object* targets, string arg)
{
    tell_object(caster,"Bowing your head, you chant an unholy "+
    "praise to the Horror as your hands begin to glow purple.\n");
    tell_room(E(caster),"Bowing "+HIS(caster)+" head, "+QTNAME(caster)+
    " chants unholy words as "+HIS(caster)+" hands begin to glow "+
    "purple.\n",caster);
}

void
do_spell_kblade(object caster, object *targets)
{
    object wep, *sh;
    int x_pen,x_hit;
    float time;
    string wshort;

    wep = targets[0];

    if(caster->query_guild_order() >= 5)
    {
        x_pen = 4;
        x_hit = 4;
        time = 240.0;
    }
    else
    {

        x_pen = 3;
        x_hit = 3;
        time = 180.0;  
    }

    wshort = wep->short();

    caster->catch_msg("You wave your hand over the "+wshort+" and "+
    "suddenly it begins to glow with a purple aura!\n");

    tell_room(E(caster),QCTNAME(caster)+" waves "+HIS(caster)+" hand "+
    "over the "+wshort+" and suddenly it begins to glow with a purple "+
    "aura!\n",caster);

    sh = make_spell_effect_object(DK_DIR+"obj/glowing_sh",caster,targets,0,0);
    sh->set_spell_effect_desc("unholy blade");

    sh->set_remove_time(x_pen,x_hit,time);
    
    wep->add_prop(DK_DEATH_TIMES,wep->query_prop(DK_DEATH_TIMES) + 1);

    if(wep->query_wielded())
        wep->query_wielded()->update_weapon(wep);
}


int
create_spell_kblade(object caster, string arg, object *targets)
{
    if(!check_ok_cast(caster))
        return 1;
    if(function_exists("create_object",targets[0]) != WEAPON_OBJECT)
    {
        tell_object(caster,"It is not a weapon!\n");
        return 1;
    }
    if(targets[0]->query_glowing_shadow())
    {
        tell_object(caster,"It is already enchanted!\n");
        return 1;
    }
    if(targets[0]->query_prop(DK_DEATH_TIMES) >= 10)
    {
        tell_object(caster,"It cannot be enchanted anymore, its internal "+
        "power is all used up.\n");
        return 1;
    }
    if(targets[0]->query_prop(OBJ_I_IS_MAGIC_WEAPON))
    {
        tell_object(caster,"This weapon is already enchanted by magical "+
        "powers, and your magic would interfer with it, perhaps even "+
        "destroying it.\n");
        return 1;
    }

    set_spell_element(SS_ELEMENT_DEATH,30);
    set_spell_form(SS_FORM_ENCHANTMENT,30);
    set_spell_time(3+random(5));
    set_spell_mana(60);
    set_spell_ingredients(({"four silver coins","rib","bloodweed"}));
    set_spell_effect(do_spell_kblade);
    set_spell_conc_message(kblade_conc);
    set_spell_task(TASK_ROUTINE);
    return 0;
}

