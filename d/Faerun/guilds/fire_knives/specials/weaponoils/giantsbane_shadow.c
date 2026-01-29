/*   
 *   
 */

#pragma save_binary
#pragma strict_types

#include <macros.h>
#include <ss_types.h>
#include <formulas.h>
#include <language.h>
#include <stdproperties.h>
#include "../../guild.h";

inherit "/std/shadow";

void
remove_giantsbane_shadow()
{
    object  item_owner = environment(shadow_who);
	
	if (interactive(environment(shadow_who)))
	{   
		string itemdesc = shadow_who->short();
		
		item_owner->catch_tell("The "+GIANTSBANE_FLAME+" substance covering your "
		+itemdesc+" begins to subside until it disappears.\n");
		
		tell_room(environment(item_owner), "The "+GIANTSBANE_FLAME+" substance covering the "
		+itemdesc+" of " +QTNAME(item_owner)+" begins to subside "
		+"until it disappears.\n", item_owner);
	}
    
    shadow_who->remove_prop(GIANTSBANEOIL, 1);

    remove_shadow();
}


int
query_giantsbane_shadow()
{
    return 1;
}


int
query_weaponoil_shadow()
{
    return 1;
}


string 
long(string str, object for_obj)
{
    return (shadow_who->long(str, for_obj) 
    + "This weapon is coated with a thin film "
    + "of "+GIANTSBANE_FLAME+" substance.\n");
}


int
init_giantsbane_shadow()
{
    shadow_who->add_prop(GIANTSBANEOIL, 1);
    
    //30 min duration
    set_alarm(1800.0, 0.0, &remove_giantsbane_shadow());
    
}
