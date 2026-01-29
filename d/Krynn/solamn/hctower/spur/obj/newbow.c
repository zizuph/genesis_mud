/*Archer's bow no longer resembles a shield.
Now it resembles a club ;-)
Modification by Macker */
// grace aug 1994

inherit "/std/weapon";
#include "../local.h"
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>

void
create_weapon()
{
   set_name("longbow");
   add_name("bow");
   add_adj("knight's");
   set_long("This is one of the longbows used by Solamnic Knights.\n" +
      "It is made of carefully selected, slightly flexible wood that " +
      "is bent by a waxed string stretched between both ends. Any "+
      "arrow released from this bow would have quite a range.\n");
   AI("string", "It is waxed and is probably made from the intestine " +
      "of some animal.\n");
   AI("wood", "It is unadorned, flexible wood bent into an arc by "+
      "a string tied to both ends.\n");
   
	set_default_weapon(5, 5, W_POLEARM, W_BLUDGEON, W_BOTH);

   add_prop(OBJ_I_VOLUME, 500);
   add_prop(OBJ_I_WEIGHT, 1000);
		add_prop(OBJ_I_VALUE, 100);
}

