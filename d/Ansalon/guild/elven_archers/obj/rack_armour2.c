#include "../guild.h"
#include <wa_types.h>

inherit GUILD_OBJ + "rack";

void
create_rack()
{
    add_adj("armour");
    add_name("rack_armour");
    set_short("armour rack");
    set_long("This is a large rack, made from oak, native to this area. " +
             "It has been specially designed to hold armours.\n");
}

public int
prevent_enter(object ob)
{
    if (!ob->check_armour())
    {
        this_player()->catch_tell("The " +ob->short() + " doesn't go in the " +
                                  short()+"; it is only meant for armours.\n");
        return 1;
    }
    return ::prevent_enter(ob);
}
