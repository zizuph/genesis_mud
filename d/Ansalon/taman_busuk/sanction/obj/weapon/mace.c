inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

create_weapon()
{
    set_name("mace");
    set_adj("old");
    add_adj("heavy");
    add_adj("metal");
    set_short("old heavy mace");
    set_long("The mace is a favoured weapon of people who just enjoy using " +
             "their brute strength to bludgeon their enemies down. With the marks on this old weapon "+
             "you can't help but wonder how many battles it has seen before it was left here to wither away.\n");
    set_default_weapon(30,34,W_CLUB,W_BLUDGEON,W_ANYH);
    add_prop(OBJ_I_VOLUME, 6000);
    add_prop(OBJ_I_WEIGHT, 6000);
}
