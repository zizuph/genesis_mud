/*
 * Nornore - Detect other Heralds are in the realms. Cosmetic spell.
 *
 * Arman Kharas, May 2018
 */
 
#pragma strict_types
#pragma save_binary

inherit "/d/Genesis/specials/new/magic/spells/objs/shadow_base_sh";

#include "../../herald.h"

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>

/*
 * Function:    initialize_shadow
 * Description: Should do all the initialization effects for this 
 *              particular shadow. Shadows derived from this one should
 *              override this.
 */
public void
initialize_shadow(object spell_object, mapping spell_input)
{
    spell_object->set_spell_effect_desc("detect Heralds");
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

    if (objectp(target))
    {

      // List of other Herald members
      mixed list = HERALD_MANAGER->query_awake_members(target);

      list = sort_array(map(list, &->query_presentation()));  
      list = implode(map(list, &operator(+)("- ",)), "\n");  

      target->more("The following Heralds of the Valar are currently " +
                        "active in the realms:\n"+ list + "\n\n");
    }    

    spell_object->set_dispel_time(2);

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

    if(target->query_ghost())
        return;

    if (objectp(target))
    {
      target->catch_tell("You finish channelling Astaldo.\n");

      tell_room(environment(target), QCTNAME(target) + " finishes " +
          "channelling.\n", ({ target }));
    }    

}
