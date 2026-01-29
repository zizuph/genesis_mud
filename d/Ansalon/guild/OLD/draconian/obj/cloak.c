#pragma strict_types

inherit "/std/object";
inherit "/lib/wearable_item";

#include <stdproperties.h>
#include <wa_types.h>
#include "../guild.h"

void
create_object()
{
    set_name("cloak");
	set_adj("maroon-colored");
	add_adj("hooded");
	add_adj("maroon");
	set_short("maroon-colored hooded cloak");
    add_name(GUILD_CLOAK_ID);
    set_long("This is maroon colored cloak with a large hood. The cloak is very "+
	         "basic, and seems to give no protection at all. The size of the cloak "+
			 "makes it practical for shrouding a persons features and equipment, and "+
			 "the hood itself seems to somewhat cover you facial features.\n"+
			 "A label inside the cloak reads 'dhelp draconians'.\n");

    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_GET,  1);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_M_NO_BUY,  1);
    add_prop(OBJ_I_WEIGHT,  250);
    add_prop(OBJ_I_VOLUME,  500);
	set_slots(A_ROBE);
	set_layers(1);
	set_looseness(20);
}