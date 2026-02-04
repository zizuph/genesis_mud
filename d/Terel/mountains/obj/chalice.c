/*  A small gem */

inherit "/std/object";
#include <stdproperties.h>

create_object()
{
    set_name("chalice");
    set_adj("silver");
  add_name("sacred_chalice");
    set_long("A beautiful silver chalice engraved with stars.\n");
    add_prop(OBJ_I_VALUE, 1000);
}

