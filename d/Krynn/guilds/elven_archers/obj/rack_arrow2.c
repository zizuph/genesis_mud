#include "../guild.h"
#include <wa_types.h>
#include <files.h>

inherit GUILD_OBJ + "rack";

void
create_rack()
{
    add_adj("arrow");
    add_name("rack_arrow");
    set_short("arrow rack");
    set_long("This is a large rack, made from beech, "+
	"native to this area. It has been specially designed "+
	"to hold arrows.\n");
}

public int
prevent_enter(object ob)
{
    if (!IS_ARROW_OBJECT(ob))
    {
        this_player()->catch_tell("The "+ob->short() + " doesn't go in the " +
                       short()+"; it is only meant for arrows.\n");
	return 1;
    }
    return ::prevent_enter(ob);
}
