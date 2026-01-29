/*
 */

#pragma strict_types

inherit "/d/Ansalon/guild/pot/obj/rack";

void
create_rack()
{
    set_name("chest");
    remove_name("rack");
    set_adj("black");
    set_short("black chest");
    set_long("It is a black chest with a hinge on it.\n");
    
    set_no_show_composite(1);
}
