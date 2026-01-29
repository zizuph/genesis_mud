/*
 */

#pragma strict_types

inherit "/d/Ansalon/guild/pot/obj/rack";

#include <stdproperties.h>

void
create_rack()
{
    set_name(({"shelves", "shelf"}));
    remove_name("rack");
    set_adj("wooden");
    set_short("wooden shelves");
    set_long("Wooden shelves cover the north and west walls which " +
        "seems to have been made to display armours.\n");

    add_prop(CONT_I_ATTACH, 1);
    
    set_no_show_composite(1);
}

int
prevent_enter(object ob)
{
    if (!ob->check_armour())
        return 1;
    
    return ::prevent_enter(ob);
}
