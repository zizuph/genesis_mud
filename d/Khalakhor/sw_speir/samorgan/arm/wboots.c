/**********************************************************************
 * - wboots.c                                                       - *
 * - Simple workman boots.                                          - *
 * - Created by Damaris@Genesis 03/2001                             - *
 * - Tidied up and optimized a bit, Tapakah 05/2021                 - *
 **********************************************************************/

#pragma strict_types

#include <stdproperties.h>
#include <wa_types.h>

#include "../defs.h"

inherit KSTDARMOUR;

private string query_boots();
string boots_style = query_boots();

void
create_khalakhor_armour ()
{
	set_short("pair of " + boots_style + " work boots");
	set_pshort("pairs of " + boots_style + " work boots");
	set_name("boots");
	add_name(boots_style + " boots");
	set_adj(boots_style);
	set_long("This is a " + short() +".\n");
	set_ac(10);
	add_prop(OBJ_I_VALUE, 100);
	set_at(A_FEET);
	set_am( ({-1,3,-2 }) );
	set_af(this_object());
}

private string
query_boots ()
{
	string *adjectives = ({
		"black", "brown",
  });
  return adjectives[random(sizeof(adjectives))];
}
