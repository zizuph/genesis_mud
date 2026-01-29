#pragma strict_types

inherit "/std/object.c";

#include "/d/Gondor/defs.h"
#include "../defs.h"
#include <macros.h>
#include <stdproperties.h>

public void
create_object()
{

  set_name("button");
  set_adj("shiny");
  set_short("shiny silver button");
  add_adj(({"ornate","small","silver"}));
  set_pshort("buttons");
  set_long("This small button looks very ornate.  " +
	   "It appears to be made of silver, and has many " +
	   "intricate patterns engraved in it.  " +
	   "It is quite clean, and looks as if it must have " +
	   "only been recently lost.  " +
	   "\n");

  add_prop(OBJ_I_WEIGHT, 5);
  add_prop(OBJ_I_VOLUME, 10);
  add_prop(OBJ_I_VALUE, 0);

}


