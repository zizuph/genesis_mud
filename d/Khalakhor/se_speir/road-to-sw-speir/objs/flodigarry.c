/*
 * A piece of junk - a smelly cloth
 * Tapakah, 10/2021
 */

#pragma strict_types;

#include "stdproperties.h"

inherit "/std/object";

void
create_object ()
{
  set_name("flodigarry");
  add_name("oilskin");
  add_adj(({"ankle-length", "broken"}));
  set_short("ankle-length broken oilskin");
  set_long("This is a flodigarry - an ankle-length oilskin worn by "+
           "deep-sea herring fishermen of Cala Fasdagh and by "+
           "some publicans in Port Macdunn. It's not something you "+
           "would consider wearing at all, let alone it's broken.\n");
  add_prop(OBJ_I_WEIGHT, 200);
  add_prop(OBJ_I_VOLUME, 200);
  add_prop(OBJ_I_VALUE, 5);
}
