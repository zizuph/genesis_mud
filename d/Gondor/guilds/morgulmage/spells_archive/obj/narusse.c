#include "../../morgulmage.h"
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>

inherit "/d/Genesis/specials/std/spells/obj/spell_obj_base";

#define _NO_PREP_TIME_ADJUSTMENT
#include "../generic_functions.c"
#define MAX_WEAPON_SKILL_GAIN   35

int weapon_skill_gain, weapon_skill;
object original_wf, enhanced_player;
void execute_enhancement(object wielder, object weapon);
void remove_enhancement(object weapon);
object description;
mixed original_is_magic_weapon, original_am_magic, original_magic_info;

void create_spell_object() {
    set_spell_effect_desc("narusse");
    
    set_name("_narusse_spell_obj");
    add_name( ({"narusse_spell_obj" }) );
    set_short("hidden narusse spell object");    
    set_long("Spell effect for narusse. Monitors the weapons wield "
        + "and unwield, and adds the flaming shadow.\n");
}

private object find_description_file(object weapon)
{
    string filename = "description_base";
    switch(weapon->query_wt()) {
        case W_SWORD: filename = "sword"; break;
        case W_POLEARM: filename = "polearm"; break;
        case W_AXE: filename = "axe"; break;
        case W_KNIFE: filename = "knife"; break;
        case W_CLUB: filename = "club"; break;
    }
    
    setuid();
    seteuid(getuid());

    string file = MORGUL_SPELL_OBJ_DIR + "narusse_descriptions/" + filename;
    if (LOAD_ERR(file))
        return 0;
    return find_object(file);
}

public object get_description() 
{
    return description;
}

public int setup_spell_effect()
{
    int result = ::setup_spell_effect();
    if (!result)
    {
        return result;
    }

    int power = query_spell_effect_power();
    int duration = ftoi(log(itof(power)) * 600.0);
    set_dispel_time(duration);
    
    original_wf = query_effect_target()->query_wf();
    query_effect_target()->set_wf(this_object());
    
    description = find_description_file(query_effect_target());
    
    original_is_magic_weapon = query_effect_target()->query_prop(OBJ_I_IS_MAGIC_WEAPON);
    original_am_magic = query_effect_target()->query_prop(MAGIC_AM_MAGIC);
    original_magic_info = query_effect_target()->query_prop(MAGIC_AM_ID_INFO);
    
    query_effect_target()->add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    query_effect_target()->add_prop(MAGIC_AM_MAGIC, 
        ({ query_effect_caster()->query_skill(SS_FORM_ENCHANTMENT), "enchantment" }));
    query_effect_target()->add_prop(MAGIC_AM_ID_INFO, ({
        1, "The Fires of Orodruin have been summoned upon this weapon.\n",
        10, "When wielded by a servant of the Dark Lord, the blade will "
            + "be set aflame.\n",
        20, "While the enchantment lasts, the mage will be more skilled "
            + "using this weapon in combat.\n" }));
            
    weapon_skill_gain = (query_spell_guild_strength() * MAX_WEAPON_SKILL_GAIN) / 100;
    weapon_skill = SS_WEP_FIRST + query_effect_target()->query_wt();
    
    if(query_spell_effect_caster()->query_mage_option(OPTION_NARUSSE_IGNITE)) {
        description->display_wield_message(query_spell_effect_caster(), query_effect_target());
        description->display_wield_flame_message(query_spell_effect_caster(), query_effect_target());
        execute_enhancement(query_spell_effect_caster(), query_effect_target());
    }
    return result;
}

public varargs int
dispel_spell_effect(object dispeller)
{
    int result = ::dispel_spell_effect(dispeller);
    if (!result)
    {
        return result;
    }

    if(query_effect_target()->is_narusse_enhanced()) {
        object wielder = query_effect_target()->query_wielded();
        description->display_unwield_message(wielder, query_effect_target());        
    }
    
    remove_enhancement(query_effect_target());
    query_effect_target()->set_wf(original_wf);
    
    query_effect_target()->add_prop(OBJ_I_IS_MAGIC_WEAPON, original_is_magic_weapon);
    query_effect_target()->add_prop(MAGIC_AM_MAGIC, original_am_magic);
    query_effect_target()->add_prop(MAGIC_AM_ID_INFO, original_magic_info);
    return 1;
}

private object find_living_environment(object target)
{
    object env = target;
    while(objectp(env = environment(env))) {
        if (living(env)) return env;
    }
    return 0;
}

private string describe_target()
{
    object caster = query_spell_effect_caster();
    object target = query_spell_effect_target();
    object env = find_living_environment(target);
    
    if ((env == caster) || (!objectp(env))) {
        return "the " + target->short();
    } else {
        return "the " + target->short() + " held by " 
            + env->query_the_name(caster);
    }
}

public void
hook_spell_effect_ended()
{
    object caster = query_spell_effect_caster();
    object target = query_spell_effect_target();    

    if (objectp(target) && objectp(caster))
    {
        caster->catch_tell("The effects of narusse on "
            + describe_target() + " have dispersed.\n");
    }
}

public void
hook_spell_effect_warn_fading()
{
    object target = query_effect_target();
    object caster = query_spell_effect_caster();
    
    if (objectp(target) && objectp(caster))
    {
        target->catch_tell("You feel the effects of narusse "
            + "on " + describe_target() + " weaken.\n");
    }
}

public void
hook_spell_effect_not_maintained()
{
    object caster = query_effect_caster();
    object target = query_effect_target();
    
    if (objectp(caster))
    {
        caster->catch_tell("You are mentally unable to maintain "
            + "the effects of narusse on " + describe_target() + ".\n");
    }    
}

void execute_enhancement(object wielder, object weapon)
{
    if (wielder->query_prop(MORGUL_I_NARUSSE_ENHANCED)) return;
    
    setuid();
    seteuid(getuid());
    clone_object(MORGUL_SPELL_OBJ_DIR + "narusse_sh")->setup_shadow(weapon, description);

    wielder->add_prop(MORGUL_I_NARUSSE_ENHANCED, this_object());   
    wielder->catch_msg("You feel more like a fighter.\n");
    wielder->set_skill_extra(weapon_skill, 
        wielder->query_skill_extra(weapon_skill) + weapon_skill_gain);
    
    enhanced_player = wielder;
}

void remove_enhancement(object weapon)
{
    if (!objectp(weapon)) return;
    weapon->remove_narusse_enhancement();
    
    if (!objectp(enhanced_player)) return;
    if (enhanced_player->query_prop(MORGUL_I_NARUSSE_ENHANCED) != this_object()) return;
    
    enhanced_player->remove_prop(MORGUL_I_NARUSSE_ENHANCED);   
    enhanced_player->catch_msg("You feel less like a fighter.\n");
    enhanced_player->set_skill_extra(weapon_skill, 
        enhanced_player->query_skill_extra(weapon_skill) - weapon_skill_gain);
}

public mixed wield(object weapon)
{
    object wielder = environment(weapon);

    if (objectp(original_wf)) {
        if (!IS_MEMBER(wielder) 
            || wielder->query_prop(MORGUL_I_NARUSSE_ENHANCED)) 
        {
            return original_wf->wield(weapon);
        }
        
        mixed result = original_wf->wield(weapon);
        if (stringp(result) || (result == -1)) return result;
        if (result == 1) 
        {
            if(!wielder->query_prop(MORGUL_I_SUPPRESS_AUTOIGNITE) 
                && (wielder->query_mage_option(OPTION_NARUSSE_IGNITE)))
            {
                description->display_wield_flame_message(wielder, weapon);
                execute_enhancement(wielder, weapon);
            }
            return 1;
        }    
    } 
    else 
    {
        if (!IS_MEMBER(wielder)) return 0;
        if (wielder->query_prop(MORGUL_I_NARUSSE_ENHANCED)) return 0;
    }
    
    if (wielder->query_prop(MORGUL_I_SUPPRESS_AUTOIGNITE))
    {
        return 1;
    } 
    else if (wielder->query_mage_option(OPTION_NARUSSE_IGNITE)) 
    {
        description->display_wield_message(wielder, weapon);
        description->display_wield_flame_message(wielder, weapon);
        execute_enhancement(wielder, weapon);
        return 1;
    } 
    else 
    {
        return 0;
    }
}

/*
 * Returns      : int  0 - the weapon can be unwielded normally.
 *                     1 - unwield the weapon, but print no messages.
 *                    -1 - do not unwield the weapon, print default messages.
 *                string - do not unwield the weapon, use this fail message.
 */
public mixed unwield(object obj)
{
    if (objectp(original_wf)) {
        mixed result = original_wf->unwield(obj);
        // Return when failure to unwield
        if (stringp(result) || (result == -1)) return result;
        
        // Unwield continues, so remove enhancement     
        if(obj->is_narusse_enhanced()) {
            remove_enhancement(obj);
            description->display_unwield_message(enhanced_player, obj);
        }
        return result;
    }
    
    if (obj->is_narusse_enhanced()) {
        remove_enhancement(obj);
        description->display_unwield_message(enhanced_player, obj);
    }
    return 0;
}
