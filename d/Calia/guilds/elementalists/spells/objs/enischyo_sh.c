/*
 * Spellpower enhancer weapon shadow for enischyo prayer
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

#define ACTIVE_ENCHANTMENT "_ec_enhance_weapon_active"

public object            oldwf;
object                   effect_owner;
string                   adj1, adj2, adj3, power_desc1, power_desc2, power_desc3;

/*
 * Function:    initialize_shadow
 * Description: Should do all the initialization effects for this 
 *              particular shadow. Shadows derived from this one should
 *              override this.
 */
public void
initialize_shadow(object spell_object, mapping spell_input)
{
    oldwf = shadow_who->query_wf();
    shadow_who->set_wf(this_object());

    ::initialize_shadow(spell_object, spell_input);

    spell_object->set_spell_effect_desc("empowering prayer");
}

private void
remove_spell_object()
{
    m_spell_object->set_dispel_time(2);
}

public void
set_ec_adjectives(object caster)
{
    if (GUILD_MANAGER->query_is_child_cleric(caster))
    {
        adj1 = "shadow-infused";
        adj2 = "infused";
        adj3 = "shadow";
        power_desc1 = " and pulses with shadowy energy.";
        power_desc2 = " and is encased by silvery streaks.";
        power_desc3 = " and sparkles with silvery patterns.";
    }
    else
    {
        string primary_element = GUILD_MANAGER->query_primary_element(caster);

        switch(primary_element)
        {
            case "fire":
                adj1 = "fire-engulfed";
                adj2 = "fire";
                adj3 = "engulfed";
                power_desc1 = " and pulses with fiery energy.";
                power_desc2 = " and is surrounded by red flames.";
                power_desc3 = " and is engulfed with roaring flames.";
            break;

            case "earth":
                adj1 = "vine-entangled";
                adj2 = "vine";
                adj3 = "entangled";
                power_desc1 = " and pulses with earthen energy.";
                power_desc2 = " and is entwined in brown vines.";
                power_desc3 = " and is entangled with thorny vines.";
            break;

            case "water":
                adj1 = "ice-studded";
                adj2 = "ice";
                adj3 = "studded";
                power_desc1 = " and pulses with watery energy.";
                power_desc2 = " and is studded with frost.";
                power_desc3 = " and is spiked with glacial ice.";
            break;

            case "air":
                adj1 = "wind-blasted";
                adj2 = "wind";
                adj3 = "blasted";
                power_desc1 = " and pulses with airy energy.";
                power_desc2 = " and is buffeted by a shrieking zephyr.";
                power_desc3 = " and is scoured by violent winds.";
            break;

            default:
                adj1 = "shadow-infused";
                adj2 = "infused";
                adj3 = "shadow";
                power_desc1 = " and pulses with shadowy energy.";
                power_desc2 = " and is encased by silvery streaks.";
                power_desc3 = " and sparkles with silvery patterns.";
            break;
        }
    }
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
   

    if (objectp(target))
    {
        tell_room(owner, "You empower the " +
            shadow_who->query_short() + ", with the blessings of the Elements.\n", 
            ({ target }));
        tell_room(environment(owner), "The " + shadow_who->query_short() + 
            " is imbued with spiritual powers.\n", ({ owner }));
    } 

    effect_owner = owner;
    effect_owner->add_prop(ACTIVE_ENCHANTMENT, 1); 

    set_ec_adjectives(owner); 
  
    shadow_who->add_adj(adj1);
    shadow_who->add_adj(adj2);
    shadow_who->add_adj(adj3);
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
    string wep_desc = shadow_who->query_short();

    if (objectp(target))
    {
      if(!wep_desc)
      {
          caster->catch_msg("The prayer of empowerment expires.\n");
      }
      else if(living(owner))
      {
          caster->catch_msg("The prayer of empowerment on the " + wep_desc + 
              " expires.\n");
          tell_room(owner, "The " + wep_desc + " is no longer " +
              "empowered with the spirit of Psuchae.\n", ({ target }));
          tell_room(environment(owner), "The " + wep_desc + " held by " 
              + QTNAME(owner)+ " is no longer empowered with the " +
              "spirit of Psuchae.\n", ({ owner }));
      }
      else
      { 
          tell_room(environment(owner), "The " + wep_desc + " in " 
              +owner->short()+ " is no longer empowered with the "
              +"spirit of Psuchae.\n", ({ owner })); 
       }
    }

    effect_owner->remove_prop(ACTIVE_ENCHANTMENT);
    shadow_who->remove_adj(adj1);
    shadow_who->remove_adj(adj2);
    shadow_who->remove_adj(adj3);
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
        target->catch_tell("You sense the prayer of empowerment on your " 
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
            + "the prayer of empowerment.\n");
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
    int strength = (hit + pen) / 2;

    return strength;
}

public void
leave_env(object from, object to)
{
    shadow_who->leave_env(from, to);
    set_alarm(0.0, 0.0, &remove_spell_object());
}


public varargs string
short(object for_obj)
{
    return (adj1 + " " + shadow_who->short(for_obj));
}

string 
long(string str, object for_obj)
{
    int enischyo_spellpower = shadow_who->query_magic_spellpower();
    string power_desc = " [should be a message here... report " +
        "to Arman if you are reading this].";

    switch(enischyo_spellpower)
    {
        case 0..35:
            power_desc = ".";
            break;
        case 36..45:
            power_desc = power_desc1;
            break;
        case 46..55:
            power_desc = power_desc2;
            break;
        default:
            power_desc = power_desc3;
            break;
    }

    return (shadow_who->long(str, for_obj) 
        + "It is infused with the spiritual Enischyo "
        + "prayer" +power_desc+ "\n");
}
