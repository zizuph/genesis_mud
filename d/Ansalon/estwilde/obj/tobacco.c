
inherit "/std/object";
inherit "/lib/keep";
#include <macros.h>
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"


string
query_auto_load()
{
    return MASTER_OB(TO) + ":";
}


void
create_object()
{
    set_name("tobacco");
    set_adj("fine");
    add_adj("packets");
    add_adj("of");
    add_adj("dwarven");
    set_short("fine dwarven tobacco");
    set_pshort("packets of fine dwarven tobacco");
    set_long("This packet of dried, brown leaves has been grown " +
      "in the eastern regions of Estwilde by hill dwarves. " +
      "It is of good quality, as hill dwarves love their " +
      "smoking almost as much as they love a good battle!\n");

    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_I_VALUE, 30);
    add_prop(OBJ_I_WEIGHT,20);
    add_prop(OBJ_I_VOLUME,20);
    add_prop(OBJ_I_VALUE, 12);
}
