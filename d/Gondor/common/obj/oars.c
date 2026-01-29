/* These oars must be present in the rowing boat at Anduin River
 * to maneuver the boat. But the imaginative fellow might try to use
 * them as a weapon - so why not?
 * Stats: Long (+15), heavy (+3), not designed for combat (-4),
 *        Normal hit (+16), not designed for combat (-4).
 * Elessar, Gondor.
 * Revision history:
 * 22/07/96 by Boron, made the oars keepable
 */
inherit "/std/weapon";
inherit "/lib/keep";
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/stdproperties.h"
#include <macros.h>

create_weapon() {
  set_name("oars");
  add_name("oar");
  set_short("pair of wooden oars");
  set_pshort("pairs of wooden oars");
  set_adj("wooden");
  set_adj("long");
  set_long("These long wooden oars are made for use with a rowing boat.\n");
  set_default_weapon(14,12,W_POLEARM,W_BLUDGEON, W_BOTH, 0);
  add_prop(OBJ_I_WEIGHT, 4000);
  add_prop(OBJ_I_VOLUME, 460);
  add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(14,12)+random(30)-15);
  set_keep(1);
}

query_recover()  { return MASTER + ":" + query_wep_recover(); }
init_recover(arg) { init_wep_recover(arg); }
