/**********************************************************************
 * - pants.c                                                        - *
 * - A pair of pants for Dromadus and Junil                         - *
 * - Created by Damaris 4/2002                                      - *
 **********************************************************************/

#pragma strict_types
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include "/d/Khalakhor/sys/basic.h"

inherit "/std/armour";

void
create_armour()
{
	set_short("pair of blue with black trim pants");
	set_pshort("pairs of blue with black trim pants");
	set_name("pants");
	add_adj(({"blue", "black", "pair"}));
	set_long("This is a "+ short() +".\n");
	
	set_ac(0);
	add_prop(OBJ_I_VALUE, 200);
	set_at(A_LEGS);
	set_am( ({-1,3,-2 }) );
	set_af(this_object());
}
