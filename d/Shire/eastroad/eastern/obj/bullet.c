inherit "/std/object";

#include <stdproperties.h>

void
create_object()
{
    set_name("bullet");
    add_name("sling");
    add_name("_Shire_bullet");
    set_adj(({"round","dense","lead","ammunition"}));
    set_short("sling bullet");
    set_pshort("sling bullets");
    set_long("This round, dense ball of lead is used by sling "+
       "wielding folk as effective ammunition.\n");
    add_prop(HEAP_I_UNIT_WEIGHT, 200);
    add_prop(HEAP_I_UNIT_VOLUME, 30);

    add_prop(HEAP_S_UNIQUE_ID,"_sling_bullet");
}
