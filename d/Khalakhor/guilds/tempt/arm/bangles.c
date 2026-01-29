/**********************************************************************
 * - bangles.c                                                      - *
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
	set_short("pair of stunning jade bangles");
	set_name("bangles");
	set_adj(({"stunning", "jade"}));
	set_pshort("pairs of stunning jade bangles");
	set_long("This pair of jade bangles is a rigid set of six "+
	"bracelets each that is made from precious jade that can only "+
	"be found in the Otherworld. Hanging from the first bangle is "+
	"an ornament of a grape leaf.\n");
	add_item(({"ornament"}),
	"This precious ornament is engraved with strange symbols that "+
	"denotes that this pair of jade bangles belongs to a sensuous "+
	"temptress.\n");
	set_wf(0);
	set_looseness(0);
	set_layers(10);
	set_slots(A_WRISTS);

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
