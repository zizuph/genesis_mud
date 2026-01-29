#pragma save_binary
#pragma strict_types

inherit "/std/weapon.c";

#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

public void
create_weapon()
{
    set_name("bottle");
    set_short("broken bottle");
    set_pname("bottles");
    set_adj("broken");
    
    set_long("It is a broken bottle. One might use it as a weapon.\n");
    set_default_weapon(4, 4, W_KNIFE, W_SLASH, W_ANYH);
}

