
/*

A saddlebag, for the steeds to use.
Trofast Aug 1999

*/

#include "/d/Terel/include/Terel.h"

inherit "/d/Genesis/std/wearable_pack.c";
inherit "/lib/keep";

void
create_wearable_pack()
{

  set_short("leather saddlebag");
  set_pshort("leather saddlebags");
  set_long("A large, brown leather saddlebag.  You can use it as a "+
	   "pack, or drape it on your steed.\n");

  set_name("saddlebag");
  add_name( ({"bag","leather saddlebag" }) );
  add_pname( ({"saddlebags","bags"}) );

  add_prop(CONT_I_WEIGHT, 2500);      /* grams */
  add_prop(CONT_I_MAX_WEIGHT, 150000); /* grams */
  add_prop(CONT_I_VOLUME, 8000);      /* ml */
  add_prop(CONT_I_MAX_VOLUME, 150000); /* ml */

  add_prop(OBJ_I_VALUE, 450);                 /* Worth 450 cc */ 

  set_keep(1);
  set_mass_storage(1);

}
