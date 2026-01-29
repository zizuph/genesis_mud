#include "defs.h"
inherit BASE_WEAPON;

#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>
#include <macros.h>

CONSTRUCT_WEAPON {
   set_name("scimitar");
   add_name("_uruk_scim_");
   set_short("huge nasty scimitar");
   set_pshort("scimitars");
   set_adj(({"huge", "nasty"}));
   set_long(
       "This is a huge and heavy scimitar often used by Uruk trolls.\n");
   set_hit(33);
   set_pen(35);
   set_wt(W_SWORD);
   set_dt(W_SLASH);
   set_hands(W_ANYH);

   add_prop(OBJ_I_VOLUME,  4200);
   add_prop(OBJ_I_WEIGHT, 14600);
   add_prop(OBJ_I_VALUE,  1*F_VALUE_WEAPON(33, 35) + random(1000) - 500);
}

#include "recover"

