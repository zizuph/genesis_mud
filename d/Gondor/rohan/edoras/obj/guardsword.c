/*
 * High quality longsword of Rohirrims
 * - Last Mod: changed WC to 33,29 (+3,+3 for longsword)
 * Olorin, July 1994
 */
inherit "/std/weapon";
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include "/d/Gondor/defs.h"

void
create_weapon()
{
  set_name(({"broadsword","sword","broad sword"}));
  set_pname("broadswords");
  add_pname("swords");
  set_short("broadsword");
  set_pshort("broadswords");
  set_adj(({"green-hilted", "valuable", "powerful", "rohirrim", "steel"}));
  set_long(BSN("This is an extremely valuable and powerful " +
      "Rohirrim broadsword. It has been forged of high quality steel " +
      "by a master of his trade, and green gems are flashing on the " +
      "hilt."));
  set_default_weapon(32,28,W_SWORD,W_SLASH|W_IMPALE,W_RIGHT,0);
  /* blade made of steel, rho = 6.9 g/cm^3, hilt of wood and     *
   * leather, so overall rho slightly lower.                     */
  add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 6);
  add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(32,28)+random(750)+250);
  /* It is not possible to sell this weapon to a Rohirrim        *
   * (or allied) shop keeper                                     */
  add_prop(GONDOR_M_ROHIRRIM_NO_SELL, 1);
}

query_recover()  { return MASTER + ":" + query_wep_recover(); }
init_recover(arg) { init_wep_recover(arg); }
