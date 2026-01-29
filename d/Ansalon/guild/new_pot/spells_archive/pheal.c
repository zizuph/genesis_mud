/*
 * pHeal
 */

#pragma strict_types

inherit "/d/Genesis/specials/std/spells/heal";

#include "../guild.h"
#include "../spells.h"
#include "../admin/admin.h"
#include <wa_types.h>
#include <files.h>
#include "/d/Ansalon/common/defs.h"

inherit GUILDDIRSPELL + "common";

#include <ss_types.h>
#include <macros.h>
#include <tasks.h>

#define TEMP_I_COMPONENT_CHECKED "_temp_i_component_checked"
#define HIS(x)        x->query_possessive()
#define HIM(x)        x->query_objective()
#define HE(x)         x->query_pronoun()

int used_soul_gem = 0;

/* Function name: query_spell_level
 * Description:   Internally used by the standing system
 * Returns:       int - the spell level
 */
public int
query_spell_level(void)
{
    return 7;
}

/*
 * Function:    config_heal_spell
 * Description: Config function for heal spells. Redefine this in your
 *              own heal spells to override the defaults.
 */
public void
config_heal_spell(void)
{
    set_spell_name("pheal");
    set_spell_desc("Healing of yourself or others");

    set_spell_element(SS_ELEMENT_LIFE, 50);
    set_spell_form(SS_FORM_TRANSMUTATION, 40);
    set_spell_fail("Your prayer of healing is unheard.\n");

    set_spell_task(TASK_HARD);
    // 1.5 times the standard cast time for a heal spell 
    set_spell_time_factor(1.5);  

    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(1);
    set_spell_peaceful(0);
    set_spell_offensive(0);
    // max of 150, modified by priest standing in check_valid_action
    set_spell_combat_aid(70.0);
}

/* 
 * Function:    ignore_spell_ingredients
 * Description: Function that allows a person to ignore spell ingredients
 *              By default, npcs and wizards who have a special property
 *              set will be able to ignore spell ingredients.
 */
public int
ignore_spell_ingredients(object caster)
{
    object gem;

    // DEBUG("pheal components: can ignore checked.");

    if (!objectp(caster))
    {
        return 0;
    }

    if(used_soul_gem)
        return 1;

    // DEBUG("pheal components: bypassed used soul gem.");

    if ((gem = P(MEDALLION_ID, caster)->query_soul_gem()) &&
        gem->query_charge() < 100)
    {
        caster->catch_tell("The " + gem->short() + " doesn't " +
            "have enough energy remaining from captured souls, " +
            "so you resort to your prayer components.\n");

        used_soul_gem = 1;

        // DEBUG("ptalon components: not enough charge checked.");
        return 0;
    }

    if ((gem = P(MEDALLION_ID, caster)->query_soul_gem()) &&
        gem->query_charge() >= 100)
    {
        gem->add_charge(-100);
            
        if (calling_function() != "cast_spell")
            caster->catch_tell("The " + gem->short() + " throbs as you " +
               "draw from the energy of your captured souls.\n");

        used_soul_gem = 1;

        // DEBUG("pheal components: charge extracted.");
        return 1;
    }
        
    return 0;
}

object
herb_ingr(object *possible, object *found) 
{
    object *list, comp;
    int i;
    
    list = possible - found;
    for (i = 0; i < sizeof(list); i++)
    {
        if (member_array(list[i]->query_herb_name(),
            ({ "horsetail", "chokecherry" })) > -1 &&
            filter_components(list[i], this_player()))
        {
            if (list[i]->query_prop(HEAP_I_IS))
                prepare_heap_component(list[i]);
            
            comp = list[i];
            break;
        }
    }
    
    if (this_player()->query_real_name() == "carnak")
        dump_array(({comp}));
    
    return comp;
}

/*
 * Function:    query_heal_ingredients
 * Description: This function defines what components are required for
 *              this heal spell.
 */
public string *
query_heal_ingredients(object caster)
{
    return ({ "heart", herb_ingr });
//    return ({ "heart", "horsetail" });
}

public int 
check_valid_action(object caster, mixed * targets, string arg, int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
        return 0;

    // harder to cast on good aligned
    if (targets[0]->query_alignment() > 100)
	set_spell_task(TASK_FORMIDABLE);
    else
	set_spell_task(TASK_ROUTINE);

    int aspect_mod, c_aid;
    int pot_standing = min(1000, caster->query_skill(PS_STANDING));

    // Dark Lady aspect heal combat aid formula:
    //    * base c_aid is priest standing (max 1000) / 10 + 50.
    //    * if the caster is not using pbless defensive spell, this is 
    //    * increased further by 60 (equivalent pbless c_aid). 
    //    * with pbless, combat aid between 30 and 150
    //    * without pbless, combat aid between 30 and 210

    // Dark Warrior and unaspected heal combat aid formula: 
    //    * base c_aid is priest standing (max 1000) / 20, plus 20.
    //    * combat aid between 30 and 70

    if(caster->query_prop(DARK_LADY_ASPECT) && 
      !caster->query_prop("pot_bless_subloc"))
      {
        aspect_mod = 110;
        // DEBUG("pheal cast with Dark Lady aspect and no pblessing active.");
      } 
      else
        aspect_mod = 50;

    if(caster->query_prop(DARK_LADY_ASPECT))
       c_aid = max(30, ((pot_standing) / 10) + aspect_mod);
    else
       c_aid = max(30, ((pot_standing) / 20) + 20);

    if(BETA_CAID_MOD)
        c_aid = (c_aid / 10) * 9;

    set_spell_combat_aid(c_aid);

    // DEBUG("pheal (non-default) combat aid: "+c_aid+".");
    return 1;
}

/*
 * Function name: hook_describe_heal_cast
 * Description:   Describe casting of the spell. This takes place before the
 *                actual healing happens.
 *                This can be redefined for custom messages.
 * Arguments:     object caster   - the caster
 *                object * target - the target(s)
 */
public void
hook_describe_heal_cast(object caster, object *targets)
{
    /* intentionally empty */
}

/*
 * Function name: hook_describe_heal_result
 * Description:   Describe the results of the spell upon its targets. This
 *                happens after the healing has happened.
 *                This can be redefined for custom messages.
 * Arguments:     object caster   - the caster
 *                object * target - the target(s)
 *                int * heal_amts - the amounts healed
 */
public void
hook_describe_heal_result(object caster, object *targets, int * heal_amounts)
{
    object tar = targets[0];
    int heal = heal_amounts[0];

    // Clear soul gem check
    used_soul_gem = 0;

    // casting on good aligned targets results in a standing adjustment.

    if (tar->query_alignment() > 100)
    {
	caster->catch_tell("You find it more difficult healing someone not " +
	    "dark of heart, and feel less in touch with Takhisis.\n");
        caster->adjust_standing(RND_RANGE(-70, 20));
    }

    if (tar == caster)
    {
	caster->catch_tell("You feel new health infusing your body.\n");
	tell_room(environment(caster), QCTNAME(caster) +
	    " straightens up, looking more hale.\n", targets);
    }
    else
    {
	caster->catch_tell("You place your hands on " +
	    tar->query_the_name(caster) + ", and " + HE(tar) +
	    " shivers as " + HIS(tar) + " wounds are healed.\n");
	tar->catch_tell(caster->query_The_name(tar) + " places " +
	    HIS(caster) + " hands on you, and you shiver as your " +
	    "wounds are healed.\n");
	tell_room(environment(caster), QCTNAME(caster) + " places " +
	    HIS(caster) + " hands on " + QTNAME(tar) + ", and " +
	    HE(tar) + " shivers as " + HIS(tar) + " wounds are healed.\n",
	    ({ caster, tar }), caster);
    }

    // DEBUG("Heal amount: " +heal+ ".");
    GUILD_ADMIN->log(caster, "pheal", tar->query_real_name() + ": " + heal);
}


/*
 * Function name: hook_describe_harm_result
 * Description:   Describe the results of the spell upon its targets. This
 *                happens after the healing has happened.
 *                This can be redefined for custom messages.
 * Arguments:     object caster   - the caster
 *                object * target - the target(s)
 *                int * harm_amounts - the amounts healed
 */
public void
hook_describe_harm_result(object caster, object *targets, int * harm_amounts)
{
    object tar = targets[0];

    // Clear soul gem check
    used_soul_gem = 0;

    if (tar == caster)
    {
	caster->catch_tell("You convulse in pain as dark energies shoot "+
	    "through your body.\n");
	tell_room(environment(caster), QCTNAME(caster) + " convulses as if "+
	    "in some kind of pain.\n", targets);
    }
    else
    {
	caster->catch_tell("You place your hands on " +
	    tar->query_the_name(caster) + ", and " + HE(tar) +
	    " convulses in pain.\n");
	tar->catch_tell(caster->query_The_name(tar) + " places " +
	    HIS(caster) + " hands on you, and you feel painful " +
	    "energies shoot through your body.\n");
	tell_room(environment(caster), QCTNAME(caster) + " places " +
	    HIS(caster) + " hands on " + QTNAME(tar) + ", and " +
	    HE(tar) + " convulses in pain.\n",
	    ({ caster, tar }), caster);
    }
}

public int
is_valid_medallion(object caster, object obj)
{
    if (!objectp(obj) || !obj->id(MEDALLION_ID))
    {
        return 0;
    }
    
    return 1;
}

/*
 * Function name: query_casting_success
 * Description:   Determine if a spell is successfully cast
 * Returns:       The result as an integer indicating success or
 *                failure (0 indicating failure, positive integer
 *                indicating % success)
 */
static int
query_casting_success(object caster)
{
    object * med = filter(all_inventory(TP), &is_valid_medallion(caster,));

    int ret = ::query_casting_success(caster);

    /* If we don't wear the medallion, there is only a 10% chance
     * the spell will actually go through
     */
    if(!med[0]->query_worn())
    {
        caster->adjust_standing(RND_RANGE(-200, 50));
        if (random(10))
            return 0;
    }
    if (ret)
        caster->adjust_standing(random(8) ?
            RND_RANGE(TO->query_spell_level() * 3, 10) : RND_RANGE(-10, 10));
    else
        caster->adjust_standing(RND_RANGE(-5, 5));
        
    return ret;
}