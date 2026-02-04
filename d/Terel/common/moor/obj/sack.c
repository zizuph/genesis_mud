inherit "/std/container";
inherit "/lib/keep";

#include <stdproperties.h>
#include <money.h>

public void
create_container()
{
   
   set_name("sack");
   set_short("large sack");
   set_adj("large");
   set_long("A large sack. It is very dirty, but still useful.\n");
   add_prop(CONT_I_WEIGHT,     1000);   /* It weighs 1 Kg            */
   add_prop(CONT_I_MAX_WEIGHT, 10000);  /* It can contain up to 5 Kg */
   add_prop(CONT_I_VOLUME,     5000);   /* It measures 3 Ltr         */
   add_prop(CONT_I_MAX_VOLUME, 20000);  /* It can contain 10 Ltr     */
   add_prop(CONT_I_RIGID, 0);           /* It is not a rigid object  */
   add_prop(CONT_I_TRANSP, 1);          /* You can see the insides. */
   add_prop(OBJ_I_VALUE, 40);           /* Value 40 cc*/
   
   set_keep();
   
   seteuid(getuid());

   add_object("/d/Terel/common/moor/obj/apple", (2 + random(5))); 
   add_object("/d/Terel/common/moor/obj/cheese", (1 + random(5)));
   MONEY_MAKE_CC(random(40)+100)->move(this_object(), 1);
   MONEY_MAKE_SC(random(15)+5)->move(this_object(), 1);
}
