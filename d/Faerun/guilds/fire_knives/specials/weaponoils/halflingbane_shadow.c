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
remove_halflingbane_shadow()
{
    object  item_owner = environment(shadow_who);
	
	if (interactive(environment(shadow_who)))
	{      
		string itemdesc = shadow_who->short();
		
		item_owner->catch_tell("The "+HALFLINGBANE_FLAME+" substance covering your "
		+itemdesc+" begins to subside until it disappears.\n");
		
		tell_room(environment(item_owner), "The "+HALFLINGBANE_FLAME+" substance covering the "
		+itemdesc+" of " +QTNAME(item_owner)+" begins to subside "
		+"until it disappears.\n", item_owner);
	}
    
    shadow_who->remove_prop(HALFLINGBANEOIL, 1);

    remove_shadow();
}


int
query_halflingbane_shadow()
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
    + "of "+HALFLINGBANE_FLAME+" substance.\n");
}


int
init_halflingbane_shadow()
{
    shadow_who->add_prop(HALFLINGBANEOIL, 1);
    
    //30 min duration
    set_alarm(1800.0, 0.0, &remove_halflingbane_shadow());
    
}
