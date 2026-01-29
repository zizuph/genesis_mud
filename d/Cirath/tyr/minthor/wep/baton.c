inherit "/std/weapon.c";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "defs.h"
create_weapon()
{
   ::create_weapon();
   set_name("baton");
   add_name("club");
   set_adj("narrow");
   set_short("narrow baton");
   set_long("This is a small thin baton. It is used for beating slaves "
	+"to a pulp, but not killing them. It would probably hurt "
	+"if someone hit you with it.\n");
   set_hit(20);
   set_pen(25);
   set_hands(W_ANYH);
   set_wt(W_CLUB);
   set_dt(W_BLUDGEON);
   add_prop(OBJ_I_WEIGHT,1000);
   add_prop(OBJ_I_VOLUME,1000);
}
