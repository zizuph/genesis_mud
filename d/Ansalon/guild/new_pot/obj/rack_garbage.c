/*
 */

#pragma strict_types

inherit "/d/Ansalon/guild/pot/obj/rack";

void
create_rack()
{
    set_name("bin");
    remove_name("rack");
    set_adj("rubbish");
    set_short("rubbish bin");
    set_long("It is a bin where the things you do not want can be placed.\n");
    
    set_no_show_composite(1);
}
