inherit "/std/armour";
#include "../defs.h"
#include <std.h>
#include <stdproperties.h>
#include <wa_types.h>

create_armour()
{
   set_name("helm");
   set_adj("deathmask");
   set_short("deathmask helm");
   set_long("A grinning face of bone and gore graces the front "
	+"of this helm.  Horribly misshapen features, open mouth "
	+"hanging chunks of flesh adorn the helm.  It looks to be "
	+"actually made of some form of metal, with the skull on "
	+"the front attached by some magical means.\n");
   set_ac(25);
    set_at(A_HEAD);
   set_wf(TO);
}

query_recover()
{
   return 1;
}


