/*
 * Enchant weapon shadow for SOHM
 *
 * The shadow should be cloned when the effect is
 * added, and removed when the is gone. 
 *
 */
 
#pragma strict_types
#pragma save_binary

#include "/d/Genesis/specials/local.h"
inherit SPELL_OBJ_DIR + "spell_enhancer_weapon_sh";

#include "../defs.h"

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>

#define MAX_SKILL_GAIN   40
#define ACTIVE_ENCHANTMENT "_sohm_enchant_weapon_active"

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

    spell_object->set_spell_effect_desc("enchant weapon");
}


public varargs string
short(object for_obj)
{
    return ("enchanted " + shadow_who->short(for_obj));
}

string 
long(string str, object for_obj)
{
    return (shadow_who->long(str, for_obj) 
        + "You can just make out faint azure runes of an enchantment " +
          "upon it.\n");
}

private void
remove_spell_object()
{
    m_spell_object->set_dispel_time(2);
}

void 
display_flicker_message(object target)
{
    if(!objectp(shadow_who))
    {
        set_alarm(0.0, 0.0, &remove_spell_object());
        return;
    }

    object owner = environment(shadow_who);
    string caster_message, watcher_message;

    if(target->query_prop(OBJ_I_BROKEN))
    {
        set_alarm(0.0, 0.0, &remove_spell_object());
        return;
    }

    if(!owner->query_humanoid())
    {
        set_alarm(0.0, 0.0, &remove_spell_object());
        return;
    }

    switch (random(3))
    {
        case 0:
        caster_message = "Your " + shadow_who->query_short() + " moves " +
            "in your hands, correcting your grip.\n";
        
        watcher_message = "The " + shadow_who->query_short() + " held by " +
            QTNAME(owner) + " shifts in " + owner->query_possessive() +
            " hands.\n";
            break;
        
        case 1:
        caster_message = "Azure runes glow briefly on your " + 
            shadow_who->query_short() +  ".\n";
        
        watcher_message = "Azure runes glow briefly on the " + 
            shadow_who->query_short() + " held by " + QTNAME(owner)+ ".\n";
            break;
            
        case 2:
        default:
        caster_message = "You feel the enchantment radiating from the " + 
            shadow_who->query_short() + " fill you with confidence in " +
            "your martial skills.\n";
        
        watcher_message = QCTNAME(owner)+ " grips " +
            owner->query_possessive()+ " " + shadow_who->query_short() + 
            " with surprising martial skill.\n";
            break;
    }

    owner->catch_msg(caster_message);
    tell_room(environment(owner), watcher_message, ({ owner }), owner);
   
    set_alarm(120.0, 0.0, &display_flicker_message(target));
}

// Staves and daggers require a lower spell power to reach maximum benefit

int
weapon_type_modifier(object spell_object)
{
    int modifier;

    switch(spell_object->query_wt()) 
    {
        case W_SWORD:
        case W_AXE:
        case W_CLUB:
        {
            modifier = 3;
            break;
        }
        case W_POLEARM:
        {
            if(spell_object->id("staff"))
            {
                modifier = 1;
                break;
            }
            else 
            {
                modifier = 3;
                break;
            }
        }
        case W_KNIFE:
        {
            modifier = 1;
            break;
        }
        default:
        {
            modifier = 3;
            break;
        }
    }
    return modifier;
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
    int weapon_mod = weapon_type_modifier(target);

    weapon_skill = target->query_wt();

    if (objectp(target))
    {
        tell_room(owner, "You trace runes of martial enchantments on the " +
            shadow_who->query_short() + ", which glow briefly with " +
            "bright azure flames before fading.\n", ({ target }));
        tell_room(environment(owner), "The " + shadow_who->query_short() + 
            " glows briefly with azure runes of magic.\n", ({ owner }));
    } 

    //  target->set_short(enchantment_short);

    // Duration determined as a factor of spell power
    //int duration = ftoi(itof(power) * 10.0);

    // spell_object->set_dispel_time(get_default_spell_time());


    // Calculate skill bonus - max of 40, max of 25 if one handed
    // and non-knife
    if(shadow_who->query_hands() != W_BOTH && weapon_skill != W_KNIFE)
      weapon_bonus = min(25, ftoi(itof(power) / itof(weapon_mod)));
    else
      weapon_bonus = min(40, ftoi(itof(power) / itof(weapon_mod)));

    // If cast on a one-handed item the parry bonus is max of 20
    if(shadow_who->query_hands() != W_BOTH)
      parry_bonus = min(20, ftoi(itof(power) / 5.0));
    else
      parry_bonus = min(40, ftoi(itof(power) / 5.0));

    // Int/wis of 100, spell skills  50 / 75 / 100
    //     spell power:              284 / 302 / 317
    //     staff/knife/parry bonus:  40 / 40 / 40
    //     other weapon bonus:       28 / 30 / 31

    // Int/wis of 200, spell skills  50 / 75 / 100
    //     spell power:              348 / 364 / 384
    //     staff/knife/parry bonus:  40 / 40 / 40
    //     other weapon bonus:       34 / 36 / 38 

    // THIS IS WHERE WE ADD THE SKILL BONUSES FOR THE PLAYER
    effect_owner = owner;

    // Because set_skill_extra doesn't work if skill is zero,
    // putting in a hack until fixed to give the caster one point
    // of skill so it works. Removed in hook_spell_effect_ended
    if(!effect_owner->query_base_skill(SS_PARRY))
    {
      parry_hack = 1;
      effect_owner->set_skill(SS_PARRY, 1);
    }

    if(!effect_owner->query_base_skill(weapon_skill))
    {
      weapon_hack = 1;
      effect_owner->set_skill(weapon_skill, 1);
    }
  
    effect_owner->set_skill_extra(weapon_skill, 
         effect_owner->query_skill_extra(weapon_skill) + weapon_bonus);
    effect_owner->set_skill_extra(SS_PARRY, 
         effect_owner->query_skill_extra(SS_PARRY) + parry_bonus);

    effect_owner->add_prop(ACTIVE_ENCHANTMENT, 1);

    set_alarm(10.0, 0.0, &display_flicker_message(target));    
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
    string wep_desc = shadow_who->query_short();

    if (objectp(target))
    {
      object owner = environment(target);
      if(!wep_desc)
      {
          caster->catch_msg("The enchant weapon spell expires.\n");
      }
      else if(living(owner))
      {
          caster->catch_msg("The enchantment on the " + wep_desc + 
              " expires.\n");
          tell_room(owner, "The " + wep_desc + " is no longer " +
              "enchanted.\n", ({ target }));
          tell_room(environment(owner), "The " + wep_desc + " held by " 
              + QTNAME(owner)+ " is no longer enchanted.\n", ({ owner }));
      }
      else
      { 
          tell_room(environment(owner), "The " + wep_desc + " in " 
              +owner->short()+ " is no longer enchanted.\n", ({ owner })); 
       }
    }

    effect_owner->set_skill_extra(weapon_skill, 
           effect_owner->query_skill_extra(weapon_skill) - weapon_bonus);
    weapon_bonus = 0;
    effect_owner->set_skill_extra(SS_PARRY, 
           effect_owner->query_skill_extra(SS_PARRY) - parry_bonus);
    parry_bonus = 0;
    effect_owner->remove_prop(ACTIVE_ENCHANTMENT);

    if(weapon_hack)
    {
        effect_owner->set_skill(weapon_skill, 
            effect_owner->query_base_skill(weapon_skill) - 1);
        weapon_hack = 0;
    }

    if(parry_hack)
    {
        effect_owner->set_skill(SS_PARRY, 
            effect_owner->query_base_skill(SS_PARRY) - 1);
        parry_hack = 0;
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
    string wep_desc = shadow_who->query_short();
    
    if (objectp(target) && wep_desc)
    {
        target->catch_tell("You sense the enchant weapon spell on your " 
             + wep_desc + " is beginning to fade.\n");
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
            + "the enchant weapon spell.\n");
    }
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
    int strength = (hit + pen);

 
    if(shadow_who->query_wt() == W_KNIFE)
        strength = strength / 2;
    else
        strength = strength * 7 / 16;

    return strength;
}

public void
leave_env(object from, object to)
{
    shadow_who->leave_env(from, to);
    set_alarm(0.0, 0.0, &remove_spell_object());
}

