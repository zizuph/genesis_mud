/*
 * pRestore
 */

#pragma strict_types

#include "/d/Ansalon/common/defs.h"
#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <flags.h>
#include <files.h>
#include <poison_types.h>
#include <composite.h>
#include <language.h>
#include <wa_types.h>

#include "../guild.h"
#include "../spells.h"

inherit "/d/Genesis/specials/std/spells/cleanse";
inherit GUILDDIRSPELL + "common";

/* Function name: query_spell_level
 * Description:   Internally used by the standing system
 * Returns:       int - the spell level
 */
int
query_spell_level()
{
    return 8;
}

public void
concentrate_msg(object caster, object *targets, string arg)
{
    object old_tp = TP;

    set_this_player(caster);
    caster->catch_tell("You bow your head in prayer.\n");
    tell_room(environment(caster), QCTNAME(caster) + " bows " + HIS(caster) + 
        " head in prayer.\n", ({ caster }), caster);
    set_this_player(old_tp);
}

/*
 * Function:    resolve_cleanse_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_cleanse_spell(object caster, mixed * targets, int * resist, int result)
{
}

/*
 * Function:    config_cleanse_spell
 * Description: Config function for cleanse spells. Redefine this in your
 *              own cleanse spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */

public void
config_cleanse_spell()
{
    set_spell_name("prestore");
    set_spell_desc("prayer of poison cleansing");

    set_spell_element(SS_ELEMENT_LIFE, 55);
    set_spell_form(SS_FORM_TRANSMUTATION, 40);
    set_spell_fail("Your prayer of healing is unheard.\n");

    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(1);
    set_spell_peaceful(1);

}

/*
 * Function:    query_cleanse_ingredients
 * Description: This function defines what components are required for
 *              this fartell spell.
 */
public string *
query_cleanse_ingredients(object caster)
{
    return ({"rib", "pearl"});
}

public int 
check_valid_action(object caster, mixed * targets, string arg, int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
        return 0;

    if(caster->query_prop(DARK_WARRIOR_ASPECT))
    {
        caster->catch_tell("While under the aspect of the Dark Warrior, you cannot " +
           "request this prayer of cleansing.\n");
        return 0;
    }

    if (targets[0]->query_alignment() > 100)
	set_spell_task(TASK_FORMIDABLE);
    else
	set_spell_task(TASK_ROUTINE);

    // harder to cast on when in poor standings
    if (caster->query_skill(PS_STANDING) < -900)
	set_spell_task(TASK_FORMIDABLE);
    else if ((caster->query_skill(PS_STANDING) < -300) &&
             (targets[0]->query_alignment() < 101)) 
	set_spell_task(TASK_HARD);

      return 1;
}

public void
hook_describe_cleanse_cast(object caster, object * targets)
{
    object tar = targets[0];

    // casting on good aligned targets results in a standing adjustment.

    if (tar->query_alignment() > 100)
    {
	caster->catch_tell("You find it more difficult cleansing poisons from " +
            "someone not dark of heart, and feel less in touch with Takhisis.\n");
        caster->adjust_standing(RND_RANGE(-70, 20));
    }

    if (tar == caster)
    {
	caster->catch_tell("You call upon dark forces to draw poison from your body.\n");
	tell_room(environment(caster), QCTNAME(caster) +
	    " calls upon dark forces to draw poison from " +HIS(caster)+ " body.\n", targets);
    }
    else
    {
	caster->catch_tell("You place your hands on " +
	    tar->query_the_name(caster) + ", and " + HE(tar) +
	    " shivers as you attempt to cleanse " +HIM(tar)+ " of poisons.\n");
	tar->catch_tell(caster->query_The_name(tar) + " places " +
	    HIS(caster) + " hands on you, and you shiver as " + HE(caster)+
	    " attempts to cleanse you of poisons.\n");
	tell_room(environment(caster), QCTNAME(caster) + " places " +
	    HIS(caster) + " hands on " + QTNAME(tar) + ", and " +
	    HE(tar) + " shivers as " + HE(tar) + " is cleansed of poisons.\n",
	    ({ caster, tar }), caster);
    }

}

public void
hook_all_poisons_cleansed(object caster, object target)
{
    if(caster == target)
       caster->catch_tell("You successfully cleanse all poisons from yourself.\n");
    else
    {
      caster->catch_tell("You successfully cleanse all poisons from " +COMPOSITE_LIVE(target)+".\n");
      target->catch_msg(QCTNAME(caster) + " cures all of your poisons.\n");
    }
}
public void
hook_some_poisons_cleansed(object caster, object target)
{
    if(caster == target)
      caster->catch_tell("You successfully cleanse some poisons from yourself, however " +
        "some still remain.\n");
    else
    {
      caster->catch_tell("You manage to cleanse some poisons from " +COMPOSITE_LIVE(target)+
        ", but still some remain.\n");
      target->catch_msg(QCTNAME(caster) + " cures some of your poisons, but "
        + "some still remain.\n");
    }
}

public void
hook_use_ingredients(object *ingrs)
{
    int i;

    if (IS_LEFTOVER_OBJECT(ingrs[0]))
        i = 0;
    else
        i = 1;
            
    write("You use " + LANG_THESHORT(ingrs[i]) + " to tap " +
          LANG_THESHORT(ingrs[!i]) + " which creates a " +
          "resonance that shatters both.\n");
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