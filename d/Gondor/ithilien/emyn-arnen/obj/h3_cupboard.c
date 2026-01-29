inherit "/std/receptacle";

#include <stdproperties.h>
#include "/d/Gondor/defs.h"

void    reset_container();

void
create_receptacle()
{
    set_short("small cupboard");
    set_name("cupboard");
    set_adj("small");
    set_long(BSN("Surprisingly, the cupboard seems to have survived "
      + "the sacking of the house and the village unscathed. It is "
      + "a small wooden box with a door."));

    set_no_show_composite(1);

    add_prop(OBJ_M_NO_GET, "The cupboard is fixed to the wall, you cannot take it.\n");
    add_prop(OBJ_I_VOLUME,   100);
    add_prop(OBJ_I_WEIGHT,   500);
    add_prop(CONT_I_VOLUME, 1000);
    add_prop(CONT_I_WEIGHT, 5000);
    add_prop(CONT_I_RIGID,     1);
    add_prop(CONT_I_TRANSP,    0);

    reset_container();
}

void
reset_container()
{
    add_prop(CONT_I_CLOSED, 1);
    if (present("key", TO))
        return;

    FIX_EUID
    clone_object(ITH_DIR + "emyn-arnen/obj/kitchen_key")->move(TO, 1);
}
