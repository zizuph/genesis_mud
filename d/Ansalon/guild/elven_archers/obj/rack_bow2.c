#include "../guild.h"
#include <wa_types.h>

inherit GUILD_OBJ + "rack";

void
create_rack()
{
    add_adj("bow");
    add_name("rack_weapon");
    set_short("bow rack");
    set_long("This is a large rack, made from oak, "+
	"native to this area. It has been specially designed "+
	"to hold bows.\n");
}

public int
prevent_enter(object ob)
{
    if (!ob->check_weapon() || ob->query_wt() != W_MISSILE)
    {
        this_player()->catch_tell("The "+ob->short() + " doesn't go in the " +
                       short()+"; it is only meant for bows.\n");
	return 1;
    }
    return ::prevent_enter(ob);
}
