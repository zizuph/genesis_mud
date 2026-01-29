inherit "/d/Wiz/rastlin/missile/projectile";

#include <macros.h>
#include <stdproperties.h>
#include "missile.h"

create_projectile()
{
   set_long(VBFC_ME("long_desc"));
   set_name("arrow");
   set_pname("arrows");
   set_adj("sheaf");
   add_prop(HEAP_S_UNIQUE_ID,"Fuseboy's Sheaf Arrows");
}

string
long_desc()
{
   if(num_heap() < 2)
      return "A nasty-looking arrow for a bow.\n";
   return "Nasty-looking arrows for a bow.\n";
}
