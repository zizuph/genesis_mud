/*
 * Polymorph Self Object for WoHS
 *
 * Created by Arman, 2017
 */

#pragma strict_types
#pragma save_binary

#include <macros.h>

inherit "/d/Genesis/specials/std/spells/obj/shapeshift_obj";

/*
 * Function:    create_spell_object
 * Description: Override this to customize properties for the spell object
 */
public void 
create_spell_object()
{
    set_name("_polymorph_self_object_");
    set_short("polymorph self spell object");    
    set_long("This is the polymorph self spell's object. It "
        + "allows the caster to alter their form into a creature.\n");

    add_prop(OBJ_S_WIZINFO, "This is a spell object " +
                            "created by the polymorph self spell.\n");
    set_spell_effect_desc("polymorph self");    
}

/*
int
intro_live(string str)
{
   object target = query_effect_target();

   target->catch_msg("You cannot introduce yourself or anyone else in this form!\n");
   return 0;
}
*/