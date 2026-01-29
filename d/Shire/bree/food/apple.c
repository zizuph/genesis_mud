/*
 * Fruit from Bree's orchard
 * Coded by Finwe, February 1998
 */
 
inherit "/std/food";
 
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/sys/defs.h"
#include "defs.h"
 
create_food()
{
    setuid();
    seteuid(getuid());

    set_name("apple");
    set_adj("red");
    set_adj("juicy");
    set_short("juicy red apple");
    set_long("It's a large, juicy red apple. It's perfect in " +
        "shape and looks delicious enough to eat right away.\n");
    add_name("fruit");
    set_amount(50); 
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 60);
}
