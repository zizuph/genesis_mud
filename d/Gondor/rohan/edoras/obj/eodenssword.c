#pragma strict_types

inherit "/std/weapon.c";

#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <formulas.h>

#include "/d/Gondor/defs.h"

public void
create_weapon() 
{
    set_name( ({"shortsword","sword","weapon"}));
    set_pname("shortswords");
    add_pname("swords");
    set_short("golden shortsword");
    set_pshort("golden shortswords");
    set_long("This is a small elegant sword made from fine steel. It is "
       + "decorated with gold accents and has been polished to a brilliant "
       + "shine.\n");
    set_adj( ({"elegant", "small"}));
    add_adj("golden");
    set_default_weapon(12, 18, W_SWORD, W_SLASH| W_IMPALE, W_ANYH, 0);
    add_prop(OBJ_I_WEIGHT,4000);
    add_prop(OBJ_I_VOLUME,640);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(12,18)+random(400)+125);
}
