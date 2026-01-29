/*
 * Hammer to fix wagon wheel in quest.
 * -- Finwe January 2005
 */

#pragma save_binary
#include "defs.h"
#include <stdproperties.h>
#include <macros.h>

inherit "/std/object";

//int do_hammer(string str);

create_object()
{
    set_name(({"hammer","_faerie_hammer"}));
    set_pname("hammers");
    set_adj(({"heavy", "iron"}));
    set_long("The " + short() + " is small but heavy. It has a square " +
        "head attached to a wooden handle. The head is rusted, and the " +
        "handle looks like it's ready to fall apart.\n");

 /* Some properties of this hammer */
   add_prop(OBJ_I_WEIGHT, 4000);    /* 4.0 Kg            */
   add_prop(OBJ_I_VALUE, 7);        /* 7 Copper coins    */
   add_prop(OBJ_I_VOLUME, 90);      /* 0.09 Ltr          */
}

void
init()
{
    ::init();

    add_action("do_hammer", "hammer");
    add_action("do_hammer", "hit");
    add_action("do_hammer", "pound");
}

int do_hammer(string str)
{

}
