/* Roselda's dress. ~mucalytic/hills/armour/dress */

inherit "/std/armour";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

void create_armour()
{
    set_name("dress");
    set_adj("long");
    add_adj("voluminous");
    set_long("A long dress that billows out with many pleats and frills "+
        "all made from many different sections of cloth, sewn haphazardly "+
        "together. It looks quite warm.\n");

    set_ac(3);

    set_at(A_BODY);

    add_prop(OBJ_I_VOLUME, 400);
    add_prop(OBJ_I_WEIGHT, 250);
}
