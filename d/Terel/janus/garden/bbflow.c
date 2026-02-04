/*  bbflow.c */
/*  janus 920831 */

inherit "/std/object";
#include <stdproperties.h>
#include "/d/Terel/common/terel_std_rec.h"

create_object()
{
  set_name("flower");
  set_adj("aquamarine");
   add_name("blue flower");
  set_long(break_string("Besides from having the color of the "+
   "summer sky it also sports a very strong smell. The smell is hard "+
   "to identify but it is close to the smell af"+
    "ter a light summer rain.\n",70));
  add_prop(OBJ_I_WEIGHT,20);
  add_prop(OBJ_I_VOLUME,5);
  add_prop(OBJ_I_VALUE, 1);
  add_prop(OBJ_M_NO_DROP, 0);
  add_prop("is_mixable",1);
   add_prop("is_bukett",1);
}


