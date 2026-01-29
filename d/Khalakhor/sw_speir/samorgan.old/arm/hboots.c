/**********************************************************************
 * - hboots.c                                                       - *
 * - A boots for the riddler and in shop                            - *
 * - Created by Damaris 5/2006                                      - *
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
	set_short("pair of black thigh high boots");
	set_pshort("pairs of black thigh boots");
	set_name("boots");
	add_adj(({"pair", "high", "black"}));
	set_long("This is a "+ short() +" made from quality leather.\n");
	
	set_ac(0);
	add_prop(OBJ_I_VALUE, 200);
	set_at(A_FEET);
	set_am( ({-1,3,-2 }) );
	set_af(this_object());
}
