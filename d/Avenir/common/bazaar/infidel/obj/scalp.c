// Infidel scalp
// This is worth money to the Punisher in the bazaar
//   -Cirion, Jen 1996

inherit "/std/leftover";
#include "/d/Avenir/common/common.h"
 
create_leftover()
{
   set_name("scalp");
   add_name("avenir_infidel_scalp");
   set_short("bloody scalp");
   set_long("Tufts of hair and blood still cling "
           +"to the rubbery scalp. The seems to be a small "
           +"red tattoo where the forehead once was.\n");
   set_decay_time(10);
   add_prop(OBJ_I_WEIGHT, 5);
   add_prop(OBJ_I_VOLUME, 9);

}
