#include "../local.h"
#include <wa_types.h>

inherit SOBJ+"rack";

void
create_rack()
{
    add_adj("polearm");
    add_name("rack_polearm");
    set_short("polearm rack");
    set_long("This is a large rack, made from a blackwood "+
	"pine native to this area. It has been specialy designed "+
	"to hold polearms.\n");
}

public int
prevent_enter(object ob)
{
    if (!ob->check_weapon() || ob->query_wt() != W_POLEARM)
	return 1;
    return ::prevent_enter(ob);
}
