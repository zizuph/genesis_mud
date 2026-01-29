/*
 * Divine Wizards Shadow for SOHM
 *
 */
 
#pragma strict_types
#pragma save_binary

#include "/d/Genesis/specials/local.h"
inherit SPELL_OBJ_DIR + "shadow_base_sh";

#include "../defs.h"

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
    spell_object->set_spell_effect_desc("divine wizards");
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


    if(SOHM_MANAGER->query_passed_wohs_test(target) &&
       objectp(target))
    {

      // List of other WoHS members
      mixed wohs_list = SOHM_MANAGER->query_awake_wohs(target);

      wohs_list = sort_array(map(wohs_list, &->query_presentation()));  
      wohs_list = implode(map(wohs_list, &operator(+)("- ",)), "\n");  

      target->more("The following Wizards of High Sorcery are currently " +
                        "active in the realms:\n"+ wohs_list + "\n\n");
    } 

    if (objectp(target))
    {

      // List of other SoHM members
      mixed list = SOHM_MANAGER->query_awake_members(target);

      list = sort_array(map(list, &->query_presentation()));  
      list = implode(map(list, &operator(+)("- ",)), "\n");  

      target->more("The following Students of High Magic are currently " +
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
      target->catch_tell("You snap out of your trance.\n");

      tell_room(environment(target), QCTNAME(target) + " snaps out of " 
      + target->query_possessive() + " trance.\n", ({ target }));
    }    

}
