inherit "/std/object";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <filter_funs.h>
#include <options.h>
#include "/d/Gondor/defs.h"


create_object() 
{
  set_short("dainty pink handkerchief");
  add_adj( ({"dainty", "pink"}));
  set_long("This handkerchief is pink. It's made out of cotton so "
    + "it is very soft. It seems to be well-used, but still unstained. "
    + "It has a pleasant smell to it.\n");
  set_name(({"handkerchief", "tissue", "hankie", "hanky"}));


  add_prop(OBJ_I_WEIGHT,100);
  add_prop(OBJ_I_VOLUME,100);
  add_prop(OBJ_I_VALUE,10);
  
}

