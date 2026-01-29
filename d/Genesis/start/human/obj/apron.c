#pragma save_binary
#pragma strict_types

inherit "/std/armour";

#include <wa_types.h>

public void
create_armour()
{
    set_name("apron");
    set_short("red and white apron");
    set_adj("smudged");
    add_adj(({"red", "white", }));
    set_long("It is a somewhat smudged red and white apron.\n");
    
    set_default_armour(2, A_BODY);
}
