#include "../local.h"
#include <wa_types.h>

inherit SOBJ+"rack";

void
create_rack()
{
    add_adj("sword");
    add_name("rack_sword");
    set_short("sword rack");
    set_long("This is a large rack, made from a blackwood "+
	"pine native to this area. It has been specially designed "+
	"to hold swords.\n");
}

public int
prevent_enter(object ob)
{
    if (!ob->check_weapon() || ob->query_wt() != W_SWORD)
	return 1;
    return ::prevent_enter(ob);
}
