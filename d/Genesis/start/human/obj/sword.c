#pragma save_binary
#pragma strict_types

inherit "/std/weapon";

void
create_weapon()
{
    set_name("bat"); set_pname("bats");
    set_short("billy bat"); set_pshort("billy bats");
    set_adj("well used");
    set_long("It is a hard wodden billy bat.\n");
    
    set_default_weapon();
}
