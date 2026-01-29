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

inherit "/std/shadow";

public string            llong_desc = "";


void
remove_nondull_shadow()
{
    shadow_who->set_long(llong_desc);
    
	remove_shadow();
}


int
query_nondull_shadow()
{
	return 1;
}


int
set_dull(int du)
{
    return 0;
}


int
query_dull()
{
    return 0;
}


int
init_nondull_shadow()
{
	llong_desc = shadow_who->long();

	shadow_who->set_long(llong_desc + "This blade seems to radiate a dim purple glow.\n");
    
    // 24 hours duration
    set_alarm(86400.0, 0.0, &remove_nondull_shadow());
}


public void remove_object()
{
	shadow_who->set_long(llong_desc);
}

