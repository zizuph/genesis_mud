inherit "/std/container";

#include "/sys/stdproperties.h";
#include <money.h>

create_container() {
   object ikey;
   set_name("stove");
   set_short("stove");
   set_pshort("stoves");
   set_long("This is a large iron stove.\n");
   add_prop(CONT_I_WEIGHT,     70000);   /* It weighs 1 Kg            */
   add_prop(CONT_I_MAX_WEIGHT, 90000);   /* It can contain up to 5 Kg  */
   add_prop(CONT_I_VOLUME,     10000);   /* It measures 3 Ltr         */
   add_prop(CONT_I_MAX_VOLUME, 20000);   /* It can contain 10 Ltr       */
   add_prop(CONT_I_RIGID, 1);            /* It is not a rigid object       */
   add_prop(OBJ_I_VALUE,40);    /* Value 40 cc*/
   add_prop(OBJ_I_INVIS, 1);
   add_prop(OBJ_I_NO_GET, 1);
   seteuid(getuid(this_object()));
   ikey=clone_object("/d/Terel/mecien/mountains/ikey");
   ikey->move(this_object());

}
