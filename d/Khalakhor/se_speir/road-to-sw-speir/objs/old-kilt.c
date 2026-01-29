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
  set_name("kilt");
  add_adj(({"smelly", "torn"}));
  set_short("smelly torn kilt");
  set_long("This old kilt of unrecognizable colors has been torn and looks "+
           "and smells more like a rag than a wearable item.\n");
  add_prop(OBJ_I_WEIGHT, 200);
  add_prop(OBJ_I_VOLUME, 200);
  add_prop(OBJ_I_VALUE, 5);
}
