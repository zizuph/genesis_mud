/**********************************************************************
 * - doublet.c                                                      - *
 * - A Doublet for Dromadus and Junil                               - *
 * - Created by Damaris 4/2002                                      - *
 **********************************************************************/

inherit "/std/armour";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include "/d/Khalakhor/sys/basic.h"

void
create_armour()
{
	set_short("blue with black trim brass studded doublet");
	set_name("doublet");
	add_adj(({"blue", "black", "brass"}));
	set_long("This is a "+ short() +".\n");
	
	set_ac(0);
	add_prop(OBJ_I_VALUE, 200);
	set_at(A_CHEST);
	set_am( ({-1,3,-2 }) );
	set_af(this_object());
}
