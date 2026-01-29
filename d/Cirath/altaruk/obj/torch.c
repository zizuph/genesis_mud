#pragma save_binary
#pragma strict_types

inherit "/std/torch";

void
create_torch()
{
    set_name("torch");
    set_adj("wooden");
    set_short("wooden torch");
    set_long("The torch is made of a piece of wood with cloth" +
        " dripping with animal fat rolled around at one end.\n");
    set_pshort("wooden torches");
}
