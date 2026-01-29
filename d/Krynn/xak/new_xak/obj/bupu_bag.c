/*
 * Bupu's bag.
 * By Rastlin
 */
inherit "/std/receptacle";

#include "../local.h"
#include <stdproperties.h>

public void
create_receptacle()
{
    set_name("bag");
    add_name("_bupu_bag_");
    set_adj("small");
    add_adj("filthy");

    set_long("It is a small flithy bag and it doesn't seem to " +
	     "be able to hold much, but it is filled to the limit.\n");

    add_prop(CONT_I_WEIGHT, 250);
    add_prop(CONT_I_MAX_WEIGHT, 2250);
    add_prop(CONT_I_VOLUME, 30);
    add_prop(CONT_I_MAX_VOLUME, 2030);
    add_prop(CONT_I_CLOSED, 1);

    add_prop(OBJ_M_NO_SELL, 1);
    seteuid(getuid());
    clone_object(OBJ + "bag_junk")->move(TO);
}
