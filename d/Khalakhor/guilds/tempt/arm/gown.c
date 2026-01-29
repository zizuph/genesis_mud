/**********************************************************************
 * - gown.c                                                         - *
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
	set_short("shimmering white gown");
	set_name("gown");
	set_adj(({"shimmering", "white"}));
	set_pshort("shimmering white gowns");
	set_long("This shimmering white gown is made from the finest "+
	"silk and cotton. It is sleeveless and is joined at each "+
	"shoulder by a golden clasp that resembles a bunch of grapes "+
	"with leaves.\n");
	add_item(({"clasp", "golden clasp", "clasps", "golden clasps"}),
	"These golden clasps join the garment at the shoulders and "+
	"resemble a bunch of grapes with leaves.\n");
	set_wf(0);
	set_looseness(0);
	set_layers(10);
	set_slots(A_BODY);

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
