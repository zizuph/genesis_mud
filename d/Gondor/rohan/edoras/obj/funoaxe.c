inherit "/std/weapon";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

void
create_weapon() 
{
  set_name(({"war axe","waraxe","axe","weapon"}));
  set_pname("axes");
  add_pname("waraxes");
  set_short("eoth`odian war axe");
  set_pshort("eoth'odian war axes");
  set_long(BSN("This is a war axe with a handle " +
    "made out of hard redwood. On the steel " +
    "blade you can see the rune 'F'. " +
    "If you carefully study the design of the axe, " +
    "you see that its made far up north, probably at the sources  " +
    " of Anduin, long long ago."));
  set_adj(({"eoth`odian", "war", "steel"}));
  set_default_weapon(30,35,W_AXE,W_SLASH|W_BLUDGEON,W_ANYH,0);
  add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(30,35)+random(300)-150);
  add_prop(OBJ_I_WEIGHT,
	(F_WEIGHT_DEFAULT_WEAPON(20, W_AXE) + random(500) - 250));
  add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
}

query_recover()  { return MASTER + ":" + query_wep_recover(); }
init_recover(arg) { init_wep_recover(arg); }
