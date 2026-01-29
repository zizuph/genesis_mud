/*
 * Spell effect for the morgul mage narusse spell. 
 *
 * Created by Eowul, Oktober 2009
 */
 
#include "../../morgulmage.h"

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>

inherit "/d/Genesis/specials/new/magic/spells/objs/spell_enhancer_weapon_sh.c";

#define _NO_PREP_TIME_ADJUSTMENT
#include "../generic_functions.c"
#define MAX_WEAPON_SKILL_GAIN   35
#define MAX_PARRY_SKILL_GAIN   35


public varargs string flaming_short();
private void display_flicker_message();

object  weapon_owner;
mixed   original_short;
int     flicker_alarm;
object  description;
int ability_active;

int weapon_skill_gain, weapon_skill, parry_skill_gain, parry_hack;
object original_wf, enhanced_player;
void execute_enhancement(object wielder, object weapon);
void remove_enhancement();
object description;
mixed original_is_magic_weapon, original_am_magic, original_magic_info;


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

/*
 * Function:    initialize_shadow
 * Description: Should do all the initialization effects for this 
 *              particular shadow. Shadows derived from this one should
 *              override this.
 */
public void
initialize_shadow(object spell_object, mapping spell_input)
{
    ::initialize_shadow(spell_object, spell_input);
    
    object target = spell_object->query_spell_effect_target();

    original_wf = target->query_wf();
    target->set_wf(this_object());
    
    description = find_description_file(target);
    
    original_is_magic_weapon = target->query_prop(OBJ_I_IS_MAGIC_WEAPON);
    original_am_magic = target->query_prop(MAGIC_AM_MAGIC);
    original_magic_info = target->query_prop(MAGIC_AM_ID_INFO);
    
    target->add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    target->add_prop(MAGIC_AM_MAGIC, 
        ({ spell_object->query_effect_caster()->query_skill(SS_FORM_ENCHANTMENT), "enchantment" }));
    target->add_prop(MAGIC_AM_ID_INFO, ({
        1, "The Fires of Orodruin have been summoned upon this weapon.\n",
        10, "When wielded by a servant of the Dark Lord, the blade will "
            + "be set aflame.\n",
        20, "While the enchantment lasts, the mage will be more skilled "
            + "using this weapon in combat.\n" }));
            
    weapon_skill = SS_WEP_FIRST + spell_object->query_spell_effect_target()->query_wt();
    
    if(spell_object->query_spell_effect_caster()->query_mage_option(OPTION_NARUSSE_IGNITE)) {
        description->display_wield_message(spell_object->query_spell_effect_caster(), spell_object->query_spell_effect_target());
        description->display_wield_flame_message(spell_object->query_spell_effect_caster(), spell_object->query_spell_effect_target());
        execute_enhancement(spell_object->query_spell_effect_caster(), spell_object->query_spell_effect_target());
    }

    flicker_alarm = set_alarm(20.0 + (rnd() * 20.0), 0.0, display_flicker_message);
}

string long(string str, object for_obj)
{
    return (shadow_who->long(str, for_obj) 
        + "It is engulfed in searing-hot flames.\n");
}

public varargs string flaming_short()
{
    string text;
    if (functionp(original_short)) 
    {
        text = shadow_who->check_call(original_short);
    }
    else 
    {
        text = original_short;
    }
    
    return "flaming " + text;
}


int is_narusse_enhanced()
{
    return ability_active;
}

void display_flicker_message()
{
    mixed messages = description->get_flicker_messages();

    int selected_message = random(sizeof(messages));
    object wielder = environment(shadow_who);
    wielder->catch_msg(messages[selected_message][0] + "your "
        + shadow_who->short() + messages[selected_message][1]);
    can_see_caster(wielder)->catch_msg(messages[selected_message][0]
        + QTPNAME(wielder) + " " + shadow_who->short()
        + messages[selected_message][1]);
    
    flicker_alarm = set_alarm(30.0 + (rnd() * 60.0), 0.0, display_flicker_message);
}

int did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit, int dam)
{
    object wielder = shadow_who->query_wielded();

    int original_didhit = shadow_who->did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
    if (original_didhit == 1) return original_didhit;
    
    if (enemy->query_hp() <= 0) {
        if(!enemy->query_npc() || (random(10) == 0)) {
            return description->display_death_message(wielder, enemy, 
                shadow_who);
        }
    }
    
    if ((random(enemy->query_npc() ? 20 : 10) != 0)) return 0;
        
    if (phurt == -2) {
        // Parry
        return 0;
    } else if (phurt == -1) {
        // Evade
        return description->display_miss_message(wielder, enemy, shadow_who);
    } else if (phurt == 0) {
        // Miss
        return description->display_miss_message(wielder, enemy, shadow_who);
    }

    return description->display_hit_message(wielder, enemy, shadow_who, hdesc,
        phurt, dt);
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
    object caster = m_spell_object->query_spell_effect_caster();
    object target = m_spell_object->query_spell_effect_target();
    object env = find_living_environment(target);
    
    if ((env == caster) || (!objectp(env))) {
        return "the " + target->short();
    } else {
        return "the " + target->short() + " held by " 
            + env->query_the_name(caster);
    }
}

public void
hook_spell_effect_started(object spell_object)
{
}

public void
hook_spell_effect_ended(object spell_object)
{
    object caster = spell_object->query_spell_effect_caster();
    object target = spell_object->query_spell_effect_target();    

    if (objectp(target) && objectp(caster))
    {
        caster->catch_tell("The effects of narusse on "
            + describe_target() + " have dispersed.\n");
    }

    if(shadow_who->is_narusse_enhanced()) {
        object wielder = shadow_who->query_wielded();
        description->display_unwield_message(wielder, shadow_who);        
    }
    
    remove_enhancement();
    shadow_who->set_wf(original_wf);
    
    shadow_who->add_prop(OBJ_I_IS_MAGIC_WEAPON, original_is_magic_weapon);
    shadow_who->add_prop(MAGIC_AM_MAGIC, original_am_magic);
    shadow_who->add_prop(MAGIC_AM_ID_INFO, original_magic_info);
}

public void
hook_spell_effect_warn_fading(object spell_object)
{
    object target = spell_object->query_effect_target();
    object caster = spell_object->query_spell_effect_caster();
    
    if (objectp(target) && objectp(caster))
    {
        target->catch_tell("You feel the effects of narusse "
            + "on " + describe_target() + " weaken.\n");
    }
}

public void
hook_spell_effect_not_maintained(object spell_object)
{
    object caster = spell_object->query_effect_caster();
    object target = spell_object->query_effect_target();
    
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

    wielder->add_prop(MORGUL_I_NARUSSE_ENHANCED, this_object());   
    wielder->catch_msg("You feel more like a fighter.\n");
    
    if(!wielder->query_base_skill(SS_PARRY))
    {
      parry_hack = 1;
      wielder->set_skill(SS_PARRY, 1);
    }
    
    if (!ability_active)
    {
        weapon_skill_gain = (query_spell_guild_strength() * MAX_WEAPON_SKILL_GAIN) / 100;
        parry_skill_gain = (query_spell_guild_strength() * MAX_PARRY_SKILL_GAIN) / 100;

        wielder->set_skill_extra(weapon_skill, 
            wielder->query_skill_extra(weapon_skill) + weapon_skill_gain);
        wielder->set_skill_extra(SS_PARRY, 
            wielder->query_skill_extra(SS_PARRY) + parry_skill_gain);
    }
    
    enhanced_player = wielder;
    ability_active = 1;

    original_short = m_spell_object->query_spell_effect_target()->query_short();
    m_spell_object->query_spell_effect_target()->set_short(flaming_short);
}

public void remove_enhancement()
{
    remove_alarm(flicker_alarm);
    
    shadow_who->set_short(original_short);    

    if (!objectp(enhanced_player)) return;
    if (enhanced_player->query_prop(MORGUL_I_NARUSSE_ENHANCED) != this_object()) return;
    
    enhanced_player->remove_prop(MORGUL_I_NARUSSE_ENHANCED);   
    enhanced_player->catch_msg("You feel less like a fighter.\n");
    
    if(parry_hack)
    {
      parry_hack = 0;
      enhanced_player->set_skill(SS_PARRY,
          enhanced_player->query_base_skill(SS_PARRY) - 1);
    }
    
    enhanced_player->set_skill_extra(weapon_skill, 
        enhanced_player->query_skill_extra(weapon_skill) - weapon_skill_gain);
    weapon_skill_gain = 0;
    enhanced_player->set_skill_extra(SS_PARRY, 
        enhanced_player->query_skill_extra(SS_PARRY) - parry_skill_gain);
    parry_skill_gain = 0;
    ability_active = 0;
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
            remove_enhancement();
            description->display_unwield_message(enhanced_player, obj);
        }
        return result;
    }
    
    if (obj->is_narusse_enhanced()) {
        remove_enhancement();
        description->display_unwield_message(enhanced_player, obj);
    }
    return 0;
}


