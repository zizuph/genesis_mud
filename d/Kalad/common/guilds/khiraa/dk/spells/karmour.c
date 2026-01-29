/*
 * Sarr
 * 2.Mar.98
 */

#define DK_UNHOLY_ARM_TIMES "_dk_unholy_arm_times"

void
do_spell_karmour(object caster, object *targets, int result, int *resist)
{
    object arm, *sh;
    int x_ac;
    float time;
    string ashort;
    arm = targets[0];

    if(caster->query_guild_order() >= 5)
    {
        x_ac = 8;
        time = 240.0;
    }
    else
    {
        x_ac = 6;
        time = 180.0;  
    }
    ashort = arm->short();

    caster->catch_msg("You wave your hand over the "+ashort+" and "+
    "suddenly it begins to glow with a purple aura!\n");

    tell_room(E(caster),QCTNAME(caster)+" waves "+HIS(caster)+" hand "+
    "over the "+ashort+" and suddenly it begins to glow with a purple "+
    "aura!\n",caster);

    sh = make_spell_effect_object(DK_DIR+"obj/glowing_sh",caster,targets,resist,result);
    sh->set_remove_time(-1,x_ac,time);
    sh->set_spell_effect_desc("unholy armour");

    arm->add_prop(DK_UNHOLY_ARM_TIMES, arm->query_prop(DK_UNHOLY_ARM_TIMES)+1);

    if(arm->query_worn())
        arm->query_worn()->update_armour(arm);

}

int
create_spell_karmour(object caster, object *targets, string args)
{
    if(!check_ok_cast(caster))
        return 1;
    if(function_exists("create_object",targets[0]) != ARMOUR_OBJECT)    
    {
        tell_object(caster,"It is not an armour!\n");
        return 1;
    }
    if(targets[0]->query_prop(DK_UNHOLY_ARM_TIMES) >= 10)
    {
        tell_object(caster,"You cannot enchant that armour anymore, its "+
        "internal power is gone.\n");
        return 1;
    }
    if(targets[0]->query_prop(OBJ_I_IS_MAGIC_ARMOUR))
    {
        tell_object(caster,"This armour is already enchanted by magical "+
        "powers, your magic would only interfer and possibly destroy "+
        "it.\n");
        return 1;
    }
    if(targets[0]->query_glowing_shadow())
    {
        tell_object(caster,"It is already enchanted!\n");
        return 1;
    }
    set_spell_element(SS_ELEMENT_DEATH,30);
    set_spell_form(SS_FORM_ENCHANTMENT,30);
    set_spell_time(3+random(4));
    set_spell_ingredients(({"four silver coins","scalp","bloodweed"})); 
    set_spell_mana(60);
    set_spell_effect(do_spell_karmour);
    set_spell_task(TASK_ROUTINE);
    set_spell_conc_message(kblade_conc);
    return 0;
}

