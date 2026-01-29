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
  set_name("glenwhilly");
  add_name("pouch");
  add_adj(({"small", "well-used"}));
  set_short("small well-used pouch");
  set_long("This is a glenwhilly - a small tartan pouch worn beneath "+
           "the kilt during the thistle harvest. You don't want to "+
           "put it on you or use it for any other purpose "+
           "after someone else has worn it though.\n");
  add_prop(OBJ_I_WEIGHT, 200);
  add_prop(OBJ_I_VOLUME, 200);
  add_prop(OBJ_I_VALUE, 5);
}
