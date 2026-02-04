/*  gflow.c */
/*  janus 920831 */

inherit "/std/object";
#include <stdproperties.h>
#include "/d/Terel/common/terel_std_rec.h"

create_object()
{
  set_name("flower");
   add_name("green flower");
  set_adj("green");
  set_long(break_string("This flower has vivid green color. "+
    "It seems to be the embodiment of all living "+
    "green plants. \n",70));
  add_prop(OBJ_I_WEIGHT,20);
  add_prop(OBJ_I_VOLUME,5);
  add_prop(OBJ_I_VALUE, 1);
  add_prop(OBJ_M_NO_DROP, 0);
  add_prop("is_mixable",1);
add_prop("is_bukett",1);
}


