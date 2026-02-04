

inherit "/std/container";

#include "/sys/stdproperties.h";
#include <money.h>

create_container() {
   object obj,kniv,money, gold;
   set_name("chest");
   set_short("iron chest");
   set_pshort("iron chests");
   set_adj("heavy");
   set_long("A large chest of iron, it is very heavy.\n");
   add_prop(CONT_I_WEIGHT,    270000);   /* It weighs 1 Kg            */
   add_prop(CONT_I_MAX_WEIGHT, 300000);   /* It can contain up to 5 Kg  */
   add_prop(CONT_I_VOLUME,     10000);   /* It measures 3 Ltr         */
   add_prop(CONT_I_MAX_VOLUME, 20000);   /* It can contain 10 Ltr       */
   add_prop(CONT_I_RIGID, 1);            /* It is not a rigid object       */
   add_prop(OBJ_I_VALUE,40);    /* Value 40 cc*/
   seteuid(getuid(this_object()));
   obj=clone_object("/d/Terel/mountains/obj/chalice");
   obj->move(this_object());
   seteuid(getuid(this_object()));
   kniv=clone_object("/d/Terel/mountains/obj/shield");
   kniv->move(this_object());
   money=MONEY_MAKE_CC(400);
   money->move(this_object());
   gold=MONEY_MAKE_GC(15);
   gold->move(this_object());

}
