/**********************************************************************
 * - necklace.c                                                     - *
 * - For NPC Deheune to wear.                                       - *
 * - Created by Damaris@Genesis 03/2006                             - *
 **********************************************************************/
#pragma strict_types
inherit "/std/object";
inherit "/lib/wearable_item";

#include "../guild.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include "/d/Khalakhor/sys/basic.h";

public int
create_object()
{
	set_short("stunning jade necklace");
	set_name("necklace");
	set_adj(({"stunning", "jade"}));
	set_pshort("stunning jade necklace");
	set_long("This stunning jade necklace is a rigid set of jade "+
	"rings woven together to form a single strand necklace. The "+
	"precious jade that can only be found in the Otherworld.\n");
	set_wf(0);
	set_looseness(0);
	set_layers(10);
	set_slots(A_NECK);

}	

void
leave_env(object from, object to)
{
	::leave_env(from, to);
	wearable_item_leave_env(from, to);
}

void
appraise_object(int num)
{
	::appraise_object(num);
	appraise_wearable_item();
}
