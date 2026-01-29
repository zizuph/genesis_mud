#pragma strict_types

inherit "/std/receptacle.c";

#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/guilds/morgulmage/morgulmage.h"

void    reset_container();

object  dagger;

void
create_receptacle()
{
    set_short("wooden chest");
    set_pshort("wooden chests");
    set_name("chest");
    set_adj("wooden");
    set_long("This ancient chest is made of wood, and covered "
      + "with many dark and foreboding decorations. "
      + "The lid shows the picture of a large Lidless Eye painted in "
      + "the colour of blood.\n");

    set_no_show_composite(1);

    add_prop(OBJ_M_NO_GET, "The chest is fixed to the floor, you cannot take it.\n");
    add_prop(CONT_I_MAX_VOLUME, 50000);
    add_prop(CONT_I_MAX_WEIGHT, 75000);
    add_prop(CONT_I_VOLUME,  4500);
    add_prop(CONT_I_WEIGHT,  5000);
    add_prop(CONT_I_RIGID,      1);
    add_prop(CONT_I_TRANSP,     0);

    enable_reset();
    reset_container();
}

void
reset_container()
{
    if (objectp(dagger))
        return;

    FIX_EUID
    dagger = clone_object(MORGUL_OBJ_DIR + "redeye_dagger");
    if (dagger->move(TO))
        dagger->move(TO, 1);

    add_prop(CONT_I_CLOSED, 1);
}
