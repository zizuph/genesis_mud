/**********************************************************************
 * - hboots.c                                                       - *
 * - A boots for the riddler and in shop                            - *
 * - Created by Damaris 5/2006                                      - *
 **********************************************************************/


#include <stdproperties.h>
#include <wa_types.h>

#include "../defs.h"

inherit KSTDARMOUR;

void
create_khalakhor_armour()
{
  ::create_khalakhor_armour();
  set_short("pair of black thigh high boots");
  set_pshort("pairs of black thigh boots");
  set_name("boots");
  add_adj(({"pair", "high", "black"}));
  set_long("This is a "+ short() +" made from quality leather.\n");
  
  set_ac(0);
  add_prop(OBJ_I_VALUE, 200);
  set_at(A_FEET);
  set_am( ({-1,3,-2 }) );
  set_af(this_object());
}

void
tug_boots ()
{
}
