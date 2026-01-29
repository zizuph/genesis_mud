inherit "/std/container";
#include "/d/Kalad/defs.h"
/* by Antharanos */
void
create_container()
{
   set_name("corpse");
   set_short("corpse of a gnome");
   set_long("The dead and decaying remains of a gnome.\n");
   add_prop(CONT_I_WEIGHT,70000);
   add_prop(CONT_I_MAX_WEIGHT,170000);
   add_prop(CONT_I_VOLUME,70000);
   add_prop(CONT_I_MAX_VOLUME,170000);
   add_prop(OBJ_M_NO_SELL,1);
   set_alarm(1.0,0.0,"make_loot");
}
make_loot()
{
   object stuff;
   int n;
   seteuid(getuid(TO));
   for(n=0;n < 1;n++)
   {
      stuff = clone_object(CVAN(obj/oil_lamp));
      stuff -> move(TO);
      stuff = clone_object(CVAN(obj/oilflask));
      stuff -> move(TO);
   }
}
