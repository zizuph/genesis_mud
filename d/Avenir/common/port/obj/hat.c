//hat for the stormy haven waitress

inherit "/std/armour";

#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"

create_armour()
{
   int i, max, type;

   set_name("hat");
   set_pname("hats");
   set_short("lovely blue hat");
   set_pshort("lovely blue hats");
   set_adj(({"lovely","blue"}));
   set_long("This cute little hat is all the rage in such cosmopolitan "+
            "cities like Minas Tiranth. You wonder how it could have "+
            "made it to this remote corner of the world.\n");

   set_default_armour(2, A_HEAD, 0, 0);

   add_prop(OBJ_I_WEIGHT,370);
   add_prop(OBJ_I_VOLUME,240);
   add_prop(OBJ_I_VALUE,37);
}

