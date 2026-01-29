/**********************************************************************
 * - circlet.c                                                      - *
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
	set_short("golden circlet of flowers");
	set_name("circlet");
	set_adj(({"golden", "flowers"}));
	set_pshort("golden circlets of flowers");
	set_long("This circlet is made of golden flowers that can only "+
	"be found in the Otherworld.\n");
	set_wf(0);
	set_looseness(0);
	set_layers(10);
	set_slots(A_HEAD);

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
