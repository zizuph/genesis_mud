/* The Crystal from Icewall. One of the spell components
	for the sabre quest. */
/* Created by Macker April 12th, 1995 */

inherit "/std/object.c";
#include "/d/Krynn/common/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include "/d/Krynn/icewall/local.h"
inherit MELT_BASE

void
create_object()
{
	set_name("crystal");
	add_name("sabre_quest_ob1");
	add_name("sabre_quest_item");
	add_adj("long");
	add_adj("icy");
	set_long("This is a long piece of ice which appears " +
		"to be crystalized. It eminates a strange blue " +
		"light, which makes you wonder if it is magical.\n");
	add_prop(OBJ_I_VOLUME, 1500);
	add_prop(OBJ_I_WEIGHT, 1000);
	add_prop(OBJ_I_VALUE, 50);
}


