// Chart carried by elven foreman.
// Made by Boriska@Genesis Nov 1994


#include <stdproperties.h>

inherit "/std/object";

create_object()
{
  set_name ("chart");
  set_short ("tunnel chart");
  set_long (
    "The chart drawn on rough paper is totally incomprehensible to you.\n");

  add_prop (OBJ_I_WEIGHT, 10);
  add_prop (OBJ_I_VOLUME, 10);
  add_prop (OBJ_I_VALUE,  80);

}

