inherit "/std/container";
#include <stdproperties.h>
#include "/d/Terel/common/terel_defs.h"

void
create_container() {
    object  candle, plate, knife;

    seteuid(getuid());
   set_short("enormous oak dining table");
    set_name("table");
    set_adj("dining");
   set_long("A long and beautiful table, solid oak, it is carved\n"
     + "with intricate scroll-work and designs. It is large\n"
     + "enough for twelve people to use it.\n");
    add_prop(CONT_I_WEIGHT,75000);
    add_prop(CONT_I_MAX_WEIGHT,80000);
    add_prop(CONT_I_VOLUME,100000);
    add_prop(CONT_I_MAX_VOLUME,130000);
    add_prop(CONT_I_TRANSP,1);
    add_prop(CONT_I_RIGID,1);
    add_prop(OBJ_I_NO_GET,1);
    add_prop(OBJ_I_NO_DROP,1);
    candle = clone_object(TOWNDIR + "mansion/obj/candle");
    candle->move(this_object());
}
