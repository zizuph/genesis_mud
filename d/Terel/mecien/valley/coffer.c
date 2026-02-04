inherit "/std/container";

#include "/sys/stdproperties.h";
#include <money.h>

create_container() {
   object ikey;
   set_name("coffer");
   set_short("jade coffer");
   set_pshort("jade coffers");
   set_long("A beautiful carved jade coffer.\n");
   add_prop(CONT_I_WEIGHT,     700);   /* It weighs 1 Kg            */
   add_prop(CONT_I_MAX_WEIGHT, 900);   /* It can contain up to 5 Kg  */
   add_prop(CONT_I_VOLUME,     1000);   /* It measures 3 Ltr         */
   add_prop(CONT_I_MAX_VOLUME, 2000);   /* It can contain 10 Ltr       */
   add_prop(CONT_I_RIGID, 1);            /* It is not a rigid object       */
   add_prop(CONT_I_CLOSED, 1);
   add_prop(CONT_I_LOCK, 1);
   add_prop(OBJ_I_NO_GET, 1);
   add_prop(OBJ_I_INVIS, 1);
   add_prop(OBJ_I_VALUE,40);    /* Value 40 cc*/
   seteuid(getuid(this_object()));
   ikey=clone_object("/d/Terel/mecien/mountains/ikey");
   ikey->move(this_object());

}
