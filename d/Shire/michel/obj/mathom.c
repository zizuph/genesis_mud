inherit "/std/object";
#include "/sys/stdproperties.h"
#include "/d/Shire/common/defs.h"
#include "/d/Shire/michel/obj/mathomdefs.h"

#define IS_MATHOM_OBJ  "_is_mathom_obj"

void
create_object()
{
   int ran;

   ran = random(MATHOMNUMBER);

   set_long(MATHOMLONG[ran]);
   set_adj(MATHOMADJ[ran]);
   set_name(MATHOMNAME[ran]);
   add_name("mathom");
   add_prop(OBJ_I_WEIGHT, 100 + ran);
   add_prop(OBJ_I_VOLUME, 200 + ran);
   add_prop(OBJ_I_VALUE, 0);
   add_prop(IS_MATHOM_OBJ, 1);

}
