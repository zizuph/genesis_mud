/*
 * A piece of junk - a smelly old kilt
 * Tapakah, 10/2021
 */

#pragma strict_types;

#include "stdproperties.h"

inherit "/std/object";

void
create_object ()
{
  set_name("rarebit");
  add_name("food");
  add_adj(({"disgusting", "greasy"}));
  set_short("disgusting piece of rarebit");
  set_long("This is a disgusting old piece of a rarebit. The rarebits "+
           "are strange local types of melted cheese and toasted bread "+
           "dishes. You do not dare even to think about eating it though"+
           ".\n");
  add_prop(OBJ_I_WEIGHT, 200);
  add_prop(OBJ_I_VOLUME, 200);
  add_prop(OBJ_I_VALUE, 5);
}
