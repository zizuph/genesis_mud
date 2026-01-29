/*
 */

#pragma strict_types

inherit "/d/Ansalon/guild/pot/obj/rack";

void
create_rack()
{
    set_name("rack");
    set_adj("weapon");
    set_short("weapon rack");
    set_long("It is a weapon rack standing against the wall.\n");
    
    set_no_show_composite(1);
}

int
prevent_enter(object ob)
{
    if (!ob->check_weapon())
        return 1;
    
    return ::prevent_enter(ob);
}
