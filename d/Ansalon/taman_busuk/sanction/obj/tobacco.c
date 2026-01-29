
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
    set_adj("blackroot");
    add_adj("packets");
    add_adj("of");
    set_short("blackroot tobacco");
    set_pshort("packets of blackroot tobacco");
    set_long("This is a packet of very dark coloured, strong " +
      "scented tobacco. Ground from the roots of the " +
      "Blackwood tree that grows on the side of the Doom Mountain " +
      "range near Sanction, this tobacco is very hard to ignite, " +
      "but once lit is said to be an enjoyable smoke.\n");

    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_I_VALUE, 30);
    add_prop(OBJ_I_WEIGHT,20);
    add_prop(OBJ_I_VOLUME,20);
    add_prop(OBJ_I_VALUE, 12);
}
