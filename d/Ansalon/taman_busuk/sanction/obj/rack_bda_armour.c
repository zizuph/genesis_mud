#include "../local.h"
#include <wa_types.h>

inherit SOBJ+"rack";

void
create_rack()
{
    add_adj("armour");
    add_name("rack_armour");
    set_short("armour rack");
    set_long("This is a large rack, made from a blackwood "+
	"pine native to this area. It has been specially designed "+
	"to hold armours.\n");
}

public int
prevent_enter(object ob)
{
    if (!ob->check_armour())
	return 1;
    return ::prevent_enter(ob);
}
