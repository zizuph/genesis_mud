/**********************************************************************
 * - dmantle.c                                                      - *
 * - A mantle for Dromodus                                          - *
 * - Created by Damaris 4/2002                                      - *
 **********************************************************************/

#pragma strict_types
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include "/d/Khalakhor/sys/basic.h"

inherit "/std/armour";
inherit "/lib/wearable_item";

void
create_armour()
{
	set_short("crimson and gold mantle");
	set_pshort("crimson and gold mantles");
	set_name("mantle");
	add_adj(({"crimson", "gold"}));
	set_long("This is a "+ short() +".\n");
	
	set_ac(0);
	add_prop(OBJ_I_VALUE, 200);
	set_am( ({-1,3,-2 }) );
	set_af(this_object());
	
	set_layers(1);
	set_looseness(10);
	set_wf(this_object());
	set_slots(A_BODY | A_ARMS);

}
