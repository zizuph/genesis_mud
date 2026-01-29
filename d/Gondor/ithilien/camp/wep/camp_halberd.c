inherit "/std/weapon";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include <macros.h>
#include "/sys/formulas.h"
#include "/d/Gondor/defs.h"

void
create_weapon()
{
    set_name("halberd");
    set_pname("halberds");
    set_short("camouflaged halberd");
    set_pshort("camouflaged halberds");
    set_long("This heavy weapon resembles the weaponry of soldiers of "
        + "Gondor. It has been painted in such a way to make it less obvious "
        + "in a forest setting.\n");
    set_adj(({"camouflaged", }));// add adjectives used in the short or the long!
    set_default_weapon(35, 40,W_POLEARM,W_IMPALE|W_SLASH,W_BOTH,0);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(35, 40)+random(400)-200);
    add_prop(OBJ_I_WEIGHT,
     (F_WEIGHT_DEFAULT_WEAPON(35, W_POLEARM) + random(500) + 1000));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);

    add_prop(GONDOR_M_RANGERS_NO_SELL,1);
    add_prop(GONDOR_M_TIRITH_NO_SELL,1);
}
