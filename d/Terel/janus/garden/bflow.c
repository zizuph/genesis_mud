/*  bflow.c */
/*  janus 920831 */

inherit "/std/object";
#include <stdproperties.h>
#include "/d/Terel/common/terel_std_rec.h"

create_object()
{
  set_name("flower");
   add_name("black flower");
  set_adj("black");
  set_long(break_string("This flower is the pure essence of black. It is so "+
		"dark that the light in the area gets sucked into it.\n",70));
  add_prop(OBJ_I_WEIGHT,20);
  add_prop(OBJ_I_VOLUME,5);
  add_prop(OBJ_I_VALUE, 1);
  add_prop(OBJ_M_NO_DROP, 0);
  add_prop("is_mixable",1);
   add_prop("is_bukett",1);
}


