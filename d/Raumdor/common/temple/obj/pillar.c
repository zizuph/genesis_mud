/* Sarr */
#include "defs.h"
inherit "/std/object";

void
create_object()
{
    set_name("pillar");
    set_short("stone pillar");
    set_long(
      "The pillar here is made of black stone and soars high up into the " +
      "air, where it holds up the ceiling. You see a carving of a grim skull " +
      "on it.\n");
    add_item(({"skull"}),
      "A rather grim looking skull, it stares at you with an empty " +
      "expression.\n");
    add_prop(OBJ_I_NO_GET, 1);
}
