/*  oflow.c */
/*  janus 920831 */

inherit "/std/object";
#include <stdproperties.h>
#include "/d/Terel/common/terel_std_rec.h"

create_object()
{
  set_name("flower");
   add_name("octarine flower");
  set_adj("octarine");
  set_long(break_string("The flower radiates with an inner mystic light. "+
       "Jittering voices can almost be heard from it, but only almost.\n",70));
  add_prop(OBJ_I_WEIGHT,20);
  add_prop(OBJ_I_VOLUME,5);
  add_prop(OBJ_I_VALUE, 1);
  add_prop(OBJ_M_NO_DROP, 0);
  add_prop("is_mixable",1);
   add_prop("is_bukett",1);
}


