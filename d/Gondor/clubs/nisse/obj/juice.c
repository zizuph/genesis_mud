/*
 *  /d/Gondor/clubs/nisse/obj/juice.c
 *
 *  The tumbler of apple juice.
 *
 *  Deagol, March 2003
 */

inherit "/std/drink";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

void
create_drink()
{
    ::create_drink();

    set_name("juice");
    add_name("tumbler");
    set_adj("big");
    add_adj("apple");
    set_pname("juices");
    add_pname("tumblers");
    set_short("big tumbler of apple juice");
    set_pshort("big tumblers of apple juice");
    set_long("This a glass of cool, refreshing apple juice. The taste is " +
        "sweet and spicy and you notice a hint of cinnamon. The juice is " +
        "cloudy, indicating the pulp was left in the juice and has a deep " +
        "amber colour.\n");

    add_prop(OBJ_I_VALUE, 75);
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 200);

    set_soft_amount(180);
    set_alco_amount(0);
    
    setuid();
    seteuid(getuid());
}
