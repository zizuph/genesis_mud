/*
 * Filename:      bow.c
 * Description:   Archers bow, originally coded by Grace aka. Lilith,
 *                converted into using the new arrow an bow module
 *                by Boron.
 *
 * Coded by Grace 1994
 * Updated by Boron April 2002
 *
 */

inherit "/std/bow";

#include "../local.h"
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>

void
create_bow()
{
   set_name("longbow");
   add_name("bow");
   set_adj(({"wooden", "knight's", "knights", "solamnian"}));
   set_short("wooden longbow");
   set_long("This is one of the longbows used by Solamnic Knights.\n" +
      "It is made of carefully selected, slightly flexible wood that " +
      "is bent by a waxed string stretched between both ends. Any "+
      "arrow released from this bow would have quite a range.\n");
   AI("string", "It is waxed and is probably made from the intestine " +
      "of some animal.\n");
   AI("wood", "It is unadorned, flexible wood bent into an arc by "+
      "a string tied to both ends.\n");

   set_hit(39);
   set_pen(32);

   add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(39, 32));
   add_prop(OBJ_I_VOLUME, 1434);
   add_prop(OBJ_I_WEIGHT, 1000);
}

