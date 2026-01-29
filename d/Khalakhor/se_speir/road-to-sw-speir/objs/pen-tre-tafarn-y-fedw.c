/*
 * A piece of junk - a useless feather
 * Tapakah, 10/2021
 */

#pragma strict_types;

#include "stdproperties.h"

inherit "/std/object";

void
create_object ()
{
  set_name("pen-tre-tafarn-y-fedw");
  add_name("feather");
  add_adj(({"leaking", "blotchy"}));
  set_short("leaking blotchy feather");
  set_long("This is a pen-tre-tafarn-y-fedw - a term given by the locals "+
           "to the leaking blotchy feathers some uncanny souls steal "+
           "from public offices.\n");
  add_prop(OBJ_I_WEIGHT, 200);
  add_prop(OBJ_I_VOLUME, 200);
  add_prop(OBJ_I_VALUE, 5);
}
