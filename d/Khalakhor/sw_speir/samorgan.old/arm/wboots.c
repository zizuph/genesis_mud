/**********************************************************************
 * - wboots.c                                                       - *
 * - Simple workman boots.                                          - *
 * - Created by Damaris@Genesis 03/2001                             - *
 **********************************************************************/

#pragma strict_types
#include "/d/Khalakhor/sys/basic.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
inherit "/std/armour";
private string query_boots();
string _ADJ = query_boots();

void
create_armour()
{
	set_short("pair of " + _ADJ + " work boots");
	set_pshort("pairs of " + _ADJ + " work boots");
	set_name("boots");
	add_name(""+_ADJ+" boots");
	set_adj( _ADJ  );
	set_long("This is a " + short() +".\n");
	set_ac(10);
	add_prop(OBJ_I_VALUE, 100);
	set_at(A_FEET);
	set_am( ({-1,3,-2 }) );
	set_af(this_object());
}
private string
query_boots()
{
	string *adjectives = ({
		"black", "brown",
		});
		return adjectives[random(sizeof(adjectives))];
}
