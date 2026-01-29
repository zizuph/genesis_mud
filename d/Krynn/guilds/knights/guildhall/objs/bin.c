// recyling box
// grace sept 1994

inherit "/std/container";

#include "/sys/stdproperties.h"
#include "/sys/macros.h"

void
create_container()
{
   set_name("_bin_");
   add_name(({"recycling bin", "bin", "box"}));
   set_adj("large");
   
   set_short("large Recycling Bin");   
   set_long("This is a huge wooden bin with iron trimmings. Here you may "
      + "deposit broken and otherwise unusable scraps of metal and wood "
      + "that the blacksmith at Redhammer Smithy might find of use.\n");
   
   add_item("trimmings", "Made of iron.\n"); 
   
   add_prop(CONT_I_MAX_WEIGHT,  2000000); /* 2000 kilos */
   add_prop(CONT_I_MAX_VOLUME,  2000000); /* 2000 liters */
   add_prop(CONT_I_WEIGHT, 20000);
   add_prop(CONT_I_VOLUME, 160000);
   add_prop(CONT_I_RIGID, 1);
   add_prop(OBJ_M_NO_GET, "The box is much too heavy to be lifted.\n");
}                               
