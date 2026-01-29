#pragma save_binary
#pragma strict_types

inherit "/std/container";

#include <stdproperties.h>
#include "../defs.h"

void
reset_container()
{
    if(!present("axe",TO)) {
        seteuid(getuid(TO));
        clone_object(D_OBJ+"axe")->move(TO);
        clone_object(D_OBJ+"axe")->move(TO);
    }
}

void
create_container()
{
    set_name("box");
    set_adj("charity");
    set_short("charity box");
    set_long("This is a rather large box, used to exchange gifts between adventurers.\n"+
             "You may take anything you find in this box,\nand feel free to donate things in it.\n");

    add_prop(CONT_I_MAX_WEIGHT,200000); /* lots of stuff */
    add_prop(CONT_I_MAX_VOLUME,200000);
    add_prop(CONT_I_WEIGHT,100000);
    add_prop(CONT_I_VOLUME,50000);

    add_prop(CONT_I_RIGID,1);

    add_prop(CONT_I_TRANSP,1);
    add_prop(OBJ_I_NO_GET,"The charity box is securely fastened to the ground.\n");

    reset_container();
}
