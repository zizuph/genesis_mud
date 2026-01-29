inherit "/std/object";
#include <macros.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"

void
create_object()
{
   set_name("quill");
   add_name("_gold_sahuagin_priestess_quill");
   set_adj("golden");
   add_adj("gold");
   add_adj("sahuagin");
   set_short("golden sahuagin quill");
   set_long("This long golden quill is incredibly rare, coming " +
       "from an uncommon sahuagin priestess with golden scales, " +
       "one of the matriarchs of a vicious and merciless race of " +
       "sea monster that terrorises sailors and sea " +
       "creatures unfortunate enough to fall into its grasp. " +
       "These golden quills are in high demand by scholars and sages, " +
       "and fetch an excellent price from alchemists.\n");
   add_prop(OBJ_I_VOLUME, 50);
   add_prop(OBJ_I_WEIGHT, 50);
   add_prop(OBJ_I_VALUE, 6000);
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