/*
 * phammer enchantment for Priests of Takhisis
 *
 * The shadow should be cloned when the effect is
 * added, and removed when the is gone. 
 *
 * Arman October 2016
 */
 
#pragma strict_types
#pragma save_binary

#include "/d/Genesis/specials/local.h"
inherit SPELL_OBJ_DIR + "spell_enhancer_weapon_sh";

#include "../../guild.h"
#include "../../spells.h"

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>
#include "/d/Ansalon/common/defs.h"

#define MAX_SKILL_GAIN   35
#define ACTIVE_ENCHANTMENT "_pot_enchant_weapon_active"

public object            oldwf;

int     flicker_alarm, parry_bonus, weapon_bonus, weapon_skill, spell_power;
int     weapon_hack = 0;
int     parry_hack = 0;
object  effect_owner;

/*
 * Function:    initialize_shadow
 * Description: Should do all the initialization effects for this 
 *              particular shadow. Shadows derived from this one should
 *              override this.
 */
public void
initialize_shadow(object spell_object, mapping spell_input)
{
    spell_power = spell_object->query_spell_effect_power();

    oldwf = shadow_who->query_wf();
    shadow_who->set_wf(this_object());

    ::initialize_shadow(spell_object, spell_input);

    spell_object->set_spell_effect_desc("Bless a bludgeon weapon");
}

string 
long(string str, object for_obj)
{
    return (shadow_who->long(str, for_obj) 
        + "Shadows seem to writhe around the weapon in torment, the mark of a dark " +
          "blessing of empowerment.\n");
}

void 
display_flicker_message()
{
    object owner = environment(shadow_who);
    string caster_message, watcher_message;

    switch (random(3))
    {
        case 0:
        caster_message = "You feel your grip on the " + shadow_who->query_short() + " be " +
        "corrected by a dark power.\n";
        
        watcher_message = "The " + shadow_who->query_short() + " held by " + QTNAME(owner) + 
        " shifts in " + owner->query_possessive() +" hands.\n";
            break;
        
        case 1:
        caster_message = "Shadows writhe in torment along your " + shadow_who->query_short() +
        ".\n";
        
        watcher_message = "Shadows writhe in torment along the " + shadow_who->query_short() + 
        " held by " + QTNAME(owner)+ ".\n";
            break;
            
        case 2:
        default:
        caster_message = "The fell blessings of the Dark Warrior on your " + 
        shadow_who->query_short() + " fill you with confidence in your martial skills.\n";
        
        watcher_message = QCTNAME(owner)+ " grips " +owner->query_possessive()+ 
        " " + shadow_who->query_short() + " with malignant martial skill.\n";
            break;
    }

    owner->catch_msg(caster_message);
    tell_room(environment(owner), watcher_message, ({ owner }), owner);
   
    set_alarm(135.0, 0.0, &display_flicker_message());
}

/*
 * Function:    hook_spell_effect_started
 * Description: Override this to customize the message when this spell effect
 *              is added to th target.
 */

public void
hook_spell_effect_started(object spell_object)
{
    object target = spell_object->query_effect_target();
    object owner = environment(target);
    int power = spell_power;
    int weapon_mod = (owner->query_priest_level() + 1);

    weapon_skill = target->query_wt();

    if (objectp(target))
    {
        tell_room(owner, "You chant fervently, calling on the martial blessings of " +
            "Takhisis, the Dark Warrior. Shadows "+
            "begin to writhe along the length of the " +shadow_who->query_short() + 
            " in demonstration of her malignant favour.\n", 
            ({ target }));
        tell_room(environment(owner), QCTNAME(owner) + " chants fervently, beseeching " +
            "Takhisis for her dark blessings. Shadows begin to writhe in torment along the " +
            "length of " +HIS(owner)+ " " +shadow_who->query_short() + ".\n", ({ owner }));
    } 

    // Calculate skill bonus - max of 35
    weapon_bonus = min(35, ftoi(itof(power) / 8.0) * weapon_mod);
    parry_bonus = min(35, ftoi(itof(power) / 8.0) * weapon_mod);

    // Int/wis of 100, priest level   0  /  1  /  2  
    //     Enchantment :            40 / 45-64 / 64-70
    //     Air skill:               35 / 40-64 / 64-70
    //     spell power:                  302 / 317
    //     club/parry bonus:             30  / 40

    // DEBUG("phammer power: " +power+ ", club: " +weapon_bonus+
    //      ", parry: " +parry_bonus+ ".");
    // THIS IS WHERE WE ADD THE SKILL BONUSES FOR THE PLAYER
    effect_owner = owner;

    // Because set_skill_extra doesn't work if skill is zero,
    // putting in a hack until fixed to give the caster one point
    // of skill so it works. Removed in hook_spell_effect_ended
    if(!effect_owner->query_skill(SS_PARRY))
    {
      parry_hack = 1;
      effect_owner->set_skill(SS_PARRY, 1);
    }

    if(!effect_owner->query_skill(weapon_skill))
    {
      weapon_hack = 1;
      effect_owner->set_skill(weapon_skill, 1);
    }
  
    effect_owner->set_skill_extra(weapon_skill, 
         effect_owner->query_skill_extra(weapon_skill) + weapon_bonus);
    effect_owner->set_skill_extra(SS_PARRY, 
         effect_owner->query_skill_extra(SS_PARRY) + parry_bonus);

    effect_owner->add_prop(ACTIVE_ENCHANTMENT, 1);

    set_alarm(10.0, 0.0, &display_flicker_message());    
}

/*
 * Function:    hook_spell_effect_ended
 * Description: Override this to customize the message when this spell effect
 *              is dispelled.
 */
public void
hook_spell_effect_ended(object spell_object)
{
    object target = spell_object->query_effect_target();
    object caster = spell_object->query_effect_caster();
    object owner = environment(target);

    if (objectp(target))
    {
      if(living(owner))
      {
        caster->catch_msg("The blessing on the " + shadow_who->query_short() + 
          " has ended.\n");
        tell_room(owner, "The " + shadow_who->query_short() + " is no longer " +
            "blessed.\n", ({ target }));
        tell_room(environment(owner), "The " + shadow_who->query_short() + " held by " 
            + QTNAME(owner)+ " is no longer blessed.\n", ({ owner }));
      }
      else
      { 
        tell_room(environment(owner), "The " + shadow_who->query_short() + " in " 
            +owner->short()+ " is no longer blessed.\n", ({ owner })); 
       }
    }

    effect_owner->set_skill_extra(weapon_skill, 
           effect_owner->query_skill_extra(weapon_skill) - weapon_bonus);
    effect_owner->set_skill_extra(SS_PARRY, 
           effect_owner->query_skill_extra(SS_PARRY) - parry_bonus);
    effect_owner->remove_prop(ACTIVE_ENCHANTMENT);

    if(weapon_hack)
    {
      effect_owner->set_skill(weapon_skill, effect_owner->query_skill(weapon_skill) - 1);
    }

    if(parry_hack)
    {
      effect_owner->set_skill(SS_PARRY, effect_owner->query_skill(SS_PARRY) - 1);
    }

}

/*
 * Function:    hook_spell_effect_warn_fading
 * Description: Override this to customize the message for when
 *              the effect has only a minute left.
 */
public void
hook_spell_effect_warn_fading(object spell_object)
{
    object target = spell_object->query_effect_caster();
    
    if (objectp(target))
    {
        target->catch_tell("You sense the blessing on your " 
             + shadow_who->query_short() + " is beginning to fade.\n");
    }
}

/* 
 * Function:    hook_spell_effect_not_maintained
 * Description: Override this to describe the effect when the caster
 *              cannot maintain the effect.
 */
public void
hook_spell_effect_not_maintained(object spell_object)
{
    object caster = spell_object->query_effect_caster();
    
    if (objectp(caster))
    {
        caster->catch_tell("You are mentally unable to maintain "
            + "the blessing on your weapon.\n");
    }
}

private void
remove_spell_object()
{
    m_spell_object->set_dispel_time(2);
}


public mixed
command_unwield()
{
    mixed results = shadow_who->command_unwield();

    if (intp(results) && results == 1)
    {
        set_alarm(0.0, 0.0, &remove_spell_object());
    }

    return results;
}

public int 
compute_magic_spellpower(int hit, int pen)
{
    int spellpower;
    int strength = (hit + pen);
 
    if(shadow_who->query_wt() == W_CLUB)
        spellpower = strength / 2;

    return spellpower;
}

public void
leave_env(object from, object to)
{
    shadow_who->leave_env(from, to);
    set_alarm(0.0, 0.0, &remove_spell_object());
}

