inherit "/std/object";

#include "../ox_quest.h"

void
create_object()
{
    set_name("horn");
    add_name(THORNLIN_OX_DAMAGED_HORN);
    set_adj("long");
    add_adj("damaged");
    set_long("This is the long horn of an Araw ox. Unfortunately, it " +
      "seems to be damaged.\n");
}
