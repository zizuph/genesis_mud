/* Creative rights reserved to Mecien (Jeff Babcock) and team. */
inherit "/std/food";

#include <stdproperties.h>

#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

public void
create_food()
{
    set_name("grapes");
    add_name(MYSTIC_GRAPES);
    set_short("bunch of grapes");
    set_pshort("bunches of grapes");
    set_long("A ripe bunch of delicious looking ruby red grapes.\n");

    set_heap_size(1);
    set_amount(250);
  add_prop(OBJ_I_VALUE, 20);

    add_prop(HEAP_S_UNIQUE_ID, "mystic_grapes");
}

