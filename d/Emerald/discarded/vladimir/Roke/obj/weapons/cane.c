inherit "/std/weapon";
#include "/sys/wa_types.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/d/Roke/common/defs.h"



void
create_weapon()

{
   set_name("cane");
   set_short("crooked cane");
   set_long("This is a crooked cane. It serves to keep ones balance.\n");
    set_adj(({"crooked", "brown"}));

    add_prop(OBJ_I_WEIGHT, 1500);
    add_prop(OBJ_I_VOLUME, 700);
    add_prop(OBJ_I_VALUE,150);

    set_hit(20);
    set_pen(20);

        set_wt(W_CLUB);
        set_dt(W_BLUDGEON);

        set_hands(W_ANYH);
}
