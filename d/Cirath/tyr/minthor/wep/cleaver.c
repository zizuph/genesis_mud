inherit "/std/weapon.c";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "defs.h"
create_weapon()
{
   ::create_weapon();
   set_name("cleaver");
   add_name("knife");
   set_adj("meat");
   set_short("meat cleaver");
   set_long("This is a big meat cleaver, it could really hurt "
	+"someone.\n");
   set_hit(20);
   set_pen(15);
   set_hands(W_ANYH);
   set_wt(W_KNIFE);
   set_dt(W_SLASH);
   add_prop(OBJ_I_WEIGHT,100);
   add_prop(OBJ_I_VOLUME,100);
}

