#include "../local.h"
#include <wa_types.h>

inherit GUILD_OBJ + "rack";

void
create_rack()
{
    add_adj("weapon");
    set_short("weapon rack");
    set_long("This is a large rack, made from a blackwood "+
	"pine native to this area. It has been specialy designed "+
	"to hold various weapons.\n");
}

public int
prevent_enter(object ob)
{
    if (!ob->check_weapon())
	return 1;
    return ::prevent_enter(ob);
}
