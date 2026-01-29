inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>
#include <cmdparse.h>

create_object()
{
     
     set_name("plow");
     set_short("rusty old plow");
     set_long("This plow cannot have been used for a " +
      "very long time. It is all rusty and covered " +
      "with moss.\n");

     add_prop(OBJ_I_VALUE,50);
     add_prop(OBJ_I_WEIGHT,630000);
     add_prop(OBJ_I_VOLUME,600000);
     add_prop(OBJ_M_NO_GET, "The plow is to heavy!\n");

}


