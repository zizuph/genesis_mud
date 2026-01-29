// grace
// 09 Feb 1995
// WILLA'S TRAY

inherit "/std/weapon";
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

void
create_weapon()
{
  set_name("tray");
  add_adj("wooden");
  set_short("wooden tray");
  
  add_name(({"willa's tray", "weapon", "club"}));
  set_long("This is Willa's tray. She uses it to carry food from "+
         "the kitchen into the refectory at the Knights' Spur.\n");

  set_default_weapon(10,10,W_CLUB,W_BLUDGEON,W_ANYH,0);
  add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(10,10)+random(40)-20);
}


