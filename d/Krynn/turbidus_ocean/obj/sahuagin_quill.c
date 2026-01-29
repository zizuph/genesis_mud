inherit "/std/object";
#include <macros.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"

void
create_object()
{
   set_name("quill");
   set_adj("long");
   add_adj("sahuagin");
   set_short("long sahuagin quill");
   set_long("This long quill comes from a sahuagin, a vicious " +
       "and merciless sea monster that terrorises sailors and sea " +
       "creatures unfortunate enough to fall into its grasp. " +
       "These quills are in high demand by scholars and sages, " +
       "and fetch a good price from merchants.\n");
   add_prop(OBJ_I_VOLUME, 50);
   add_prop(OBJ_I_WEIGHT, 50);
   add_prop(OBJ_I_VALUE, 600);
}

/*
 * Function name: query_recover
 * Description  : We allow this standard object to recover.
 * Returns      : string - the recovery string.
 */
public string
query_recover()
{
    return MASTER;
}