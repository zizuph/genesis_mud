#include "defs.h"
#pragma save_binary

inherit RACK;

void
create_rack()
{
    set_adj( ({ "misc", "miscellaneous", "equipment" }) );
    set_short("miscellaneous equipment rack");
    set_long(
        "This rack has many attachments for holding all sorts of odd " +
	"equipment.\n");
}

int 
fits(object ob)
{
    return !OBJECT("weapon_rack")->fits(ob) &&
        !OBJECT("armour_rack")->fits(ob);
}
